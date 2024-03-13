CXX = g++
CXXFLAGS = -Wall -Wextra -g -std=c++11 -I./include/Tree

all: binTree

binTree: src/binTree.cpp
	$(CXX) $(CXXFLAGS) -o binTree src/binTree.cpp

clean:
	rm -f binTree
