#ifndef BINARY_TREE_HPP
#define BINARY_TREE_HPP

#include <algorithm>
#include <cstddef>
#include <functional>
#include <iostream>
#include <memory>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

#include "BinaryNode.hpp"

template <typename T> class BinaryTree {
   public:
    std::shared_ptr<BinaryNode<T>> root;
    size_t rotation_count;
    enum class PrintType {
        LINEAR,
        TREE,
    };

    BinaryTree() : root(nullptr), rotation_count(0) {}
    explicit BinaryTree(const T& value)
        : root(std::make_shared<BinaryNode<T>>(value)) {}

    void insert(const T& value) {
        if (root == nullptr) {
            root = std::make_shared<BinaryNode<T>>(value);
            return;
        }

        insertHelper(root, value);
    }

    bool search(const T& value) { return searchHelper(root, value); }

    void print(PrintType prettyPrint) {
        if (prettyPrint == PrintType::LINEAR) {
            printLinear(root);
        } else if (prettyPrint == PrintType::TREE) {
            printTree("", root, false);
        }
    }
    void print_order() {
        if (root == nullptr) {
            return;
        }

        root->print_order();
    }
    void print_preorder() {
        if (root == nullptr) {
            return;
        }
        root->print_preorder();
    }
    void print_postorder() {
        if (root == nullptr) {
            return;
        }
        root->print_postorder();
    }

    void for_each(
        const std::function<void(const std::shared_ptr<BinaryNode<T>>)>& func) {
        for_each_helper(root, func);
    }

   private:
    void printLinear(std::shared_ptr<BinaryNode<T>> current) {
        if (current != nullptr) {
            printLinear(current->left);
            std::cout << current->data << " ";
            printLinear(current->right);
        }
    }
    void printTree(const std::string& prefix,
                   const std::shared_ptr<BinaryNode<T>> node, bool is_left) {
        // NOTE: http://stackoverflow.com/questions/36802354/ddg#51730733
        if (node != nullptr) {
            std::cout << prefix;

            std::cout << (is_left ? "├──" : "└──");

            node->print_data();
            std::cout << std::endl;

            printTree(prefix + (is_left ? "│   " : "    "), node->left, true);
            printTree(prefix + (is_left ? "│   " : "    "), node->right, false);
        }
    }

    void for_each_helper(
        std::shared_ptr<BinaryNode<T>> node,
        const std::function<void(const std::shared_ptr<BinaryNode<T>>)>& func) {
        if (node == nullptr) {
            return;
        }

        for_each_helper(node->left, func);
        func(node);
        for_each_helper(node->right, func);
    }

    struct cell_display {
        std::string valstr;
        bool present;
        typename BinaryNode<T>::Color color;
        cell_display() : present(false) {}
        cell_display(std::string valstr, typename BinaryNode<T>::Color color)
            : valstr(valstr), present(true), color(color) {}
    };

    using display_rows = std::vector<std::vector<cell_display>>;

    // The text tree generation code below is all iterative, to avoid stack
    // faults.

    // get_row_display builds a vector of vectors of cell_display structs
    // each vector of cell_display structs represents one row, starting at the
    // root
    display_rows get_row_display() const {
        std::vector<std::shared_ptr<BinaryNode<T>>> traversal_stack;
        std::vector<std::vector<std::shared_ptr<BinaryNode<T>>>> rows;
        if (!root) return display_rows();

        std::shared_ptr<BinaryNode<T>> p = root;
        const size_t max_depth           = root->height();
        rows.resize(max_depth);
        size_t depth = 0;
        for (;;) {
            // Max-depth Nodes are always a leaf or null
            // This special case blocks deeper traversal
            if (depth + 1 == max_depth) {
                rows[depth].push_back(p);
                if (depth == 0) break;
                --depth;
                continue;
            }

            // First visit to node?  Go to left child.
            if (traversal_stack.size() == depth) {
                rows[depth].push_back(p);
                traversal_stack.push_back(p);
                if (p) p = p->left;
                ++depth;
                continue;
            }

            // Odd child count? Go to right child.
            if (rows[depth + 1].size() % 2) {
                p = traversal_stack.back();
                if (p) p = p->right;
                ++depth;
                continue;
            }

            // Time to leave if we get here

            // Exit loop if this is the root
            if (depth == 0) break;

            traversal_stack.pop_back();
            p = traversal_stack.back();
            --depth;
        }

        // Use rows of Node pointers to populate rows of cell_display structs.
        // All possible slots in the tree get a cell_display struct,
        // so if there is no actual Node at a struct's location,
        // its boolean "present" field is set to false.
        // The struct also contains a string representation of
        // its Node's value, created using a std::stringstream object.
        display_rows rows_disp;
        std::stringstream ss;
        for (const auto& row : rows) {
            rows_disp.emplace_back();
            for (std::shared_ptr<BinaryNode<T>> pn : row) {
                if (pn) {
                    ss << pn->data;
                    rows_disp.back().push_back(
                        cell_display(ss.str(), pn->color));
                    ss = std::stringstream();
                } else {
                    rows_disp.back().push_back(cell_display());
                }
            }
        }
        return rows_disp;
    }

    // row_formatter takes the vector of rows of cell_display structs
    // generated by get_row_display and formats it into a test representation
    // as a vector of strings
    std::vector<std::string> row_formatter(
        const display_rows& rows_disp) const {
        using s_t = std::string::size_type;

        // First find the maximum value string length and put it in cell_width
        s_t cell_width = 0;
        for (const auto& row_disp : rows_disp) {
            for (const struct cell_display& cd : row_disp) {
                if (cd.present && cd.valstr.length() > cell_width) {
                    cell_width = cd.valstr.length();
                }
            }
        }

        // make sure the cell_width is an odd number
        if (cell_width % 2 == 0) ++cell_width;

        // allows leaf nodes to be connected when they are
        // all with size of a single character
        if (cell_width < 3) cell_width = 3;

        // formatted_rows will hold the results
        std::vector<std::string> formatted_rows;

        // some of these counting variables are related,
        // so its should be possible to eliminate some of them.
        s_t row_count = rows_disp.size();

        // this row's element count, a power of two
        s_t row_elem_count = 1 << (row_count - 1);

        // left_pad holds the number of space charactes at the beginning of the
        // bottom row
        s_t left_pad = 0;

        // Work from the level of maximum depth, up to the root
        // ("formatted_rows" will need to be reversed when done)
        for (s_t r = 0; r < row_count; ++r) {
            const auto& cd_row =
                rows_disp[row_count - r - 1];  // r reverse-indexes the row
            // "space" will be the number of rows of slashes needed to get
            // from this row to the next.  It is also used to determine other
            // text offsets.
            s_t space = (s_t(1) << r) * (cell_width + 1) / 2 - 1;
            // "row" holds the line of text currently being assembled
            std::string row;
            // iterate over each element in this row
            for (s_t c = 0; c < row_elem_count; ++c) {
                // add padding, more when this is not the leftmost element
                row += std::string(c ? left_pad * 2 + 1 : left_pad, ' ');
                if (cd_row[c].present) {
                    const struct cell_display cd = cd_row[c];
                    // This position corresponds to an existing Node
                    const std::string& valstr    = cd.valstr;
                    // Try to pad the left and right sides of the value string
                    // with the same number of spaces.  If padding requires an
                    // odd number of spaces, right-sided children get the longer
                    // padding on the right side, while left-sided children
                    // get it on the left side.
                    s_t long_padding             = cell_width - valstr.length();
                    s_t short_padding            = long_padding / 2;
                    long_padding -= short_padding;
                    row +=
                        std::string(c % 2 ? short_padding : long_padding, ' ');
                    if (cd.color == BinaryNode<T>::Color::RED) {
                        row += "\e[41m\e[30m";
                    } else if (cd.color == BinaryNode<T>::Color::BLACK) {
                        row += "\e[40;100;32m";
                    }
                    row += valstr;
                    if (cd.color != BinaryNode<T>::Color::NONE) {
                        row += "\e[0m";
                    }
                    row +=
                        std::string(c % 2 ? long_padding : short_padding, ' ');
                } else {
                    // This position is empty, Nodeless...
                    row += std::string(cell_width, ' ');
                }
            }
            // A row of spaced-apart value strings is ready, add it to the
            // result vector
            formatted_rows.push_back(row);

            // The root has been added, so this loop is finsished
            if (row_elem_count == 1) break;

            // Add rows of forward- and back- slash characters, spaced apart
            // to "connect" two rows' Node value strings.
            // The "space" variable counts the number of rows needed here.
            s_t left_space  = space + 1;
            s_t right_space = space - 1;
            for (s_t sr = 0; sr < space; ++sr) {
                std::string row;
                for (s_t c = 0; c < row_elem_count; ++c) {
                    if (c % 2 == 0) {
                        row += std::string(c ? left_space * 2 + 1 : left_space,
                                           ' ');
                        row += cd_row[c].present ? '/' : ' ';
                        row += std::string(right_space + 1, ' ');
                    } else {
                        row += std::string(right_space, ' ');
                        row += cd_row[c].present ? '\\' : ' ';
                    }
                }
                formatted_rows.push_back(row);
                ++left_space;
                --right_space;
            }
            left_pad       += space + 1;
            row_elem_count /= 2;
        }

        // Reverse the result, placing the root node at the beginning (top)
        std::reverse(formatted_rows.begin(), formatted_rows.end());

        return formatted_rows;
    }

    // Trims an equal number of space characters from
    // the beginning of each string in the vector.
    // At least one string in the vector will end up beginning
    // with no space characters.
    static void trim_rows_left(std::vector<std::string>& rows) {
        if (!rows.size()) return;
        auto min_space = rows.front().length();
        for (const auto& row : rows) {
            auto i = row.find_first_not_of(' ');
            if (i == std::string::npos) i = row.length();
            if (i == 0) return;
            if (i < min_space) min_space = i;
        }
        for (auto& row : rows) {
            row.erase(0, min_space);
        }
    }

   public:
    // Dumps a representation of the tree to cout
    void Dump() const {
        const int d = root->height();

        // If this tree is empty, tell someone
        if (d == 0) {
            std::cout << " <empty tree>\n";
            return;
        }

        // This tree is not empty, so get a list of node values...
        const auto rows_disp = get_row_display();
        // then format these into a text representation...
        auto formatted_rows  = row_formatter(rows_disp);
        // then trim excess space characters from the left sides of the text...
        trim_rows_left(formatted_rows);
        // then dump the text to cout.
        for (const auto& row : formatted_rows) {
            std::cout << ' ' << row << '\n';
        }
    }
};

#endif  // !BINARY_TREE_HPP
