#ifndef TIME_HPP
#define TIME_HPP

/***************************************************************************
 * Project                                      ___       _______  _______
 *                                             /   \     |   ____||       \
 *                                            /  ^  \    |  |__   |  .--.  |
 *                                           /  /_\  \   |   __|  |  |  |  |
 *                                          /  _____  \  |  |____ |  '--'  |
 *                                         /__/     \__\ |_______||_______/
 *
 * Author: Luís Góis
 *
 * This software is licensed as described in the file LICENSE, which
 * you should have received as part of this distribution.
 *
 * You may opt to use, copy, modify, merge, publish, distribute and/or sell
 * copies of the Software, and permit persons to whom the Software is
 * furnished to do so, under the terms of the LICENSE file.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 ***************************************************************************/

#define MEASURE_TIME(CODE, INDEX_VARIABLE, ITERATIONS, REPORT_PER_ITERATIONS, \
                     TOTAL_ITERATIONS, TIME_THRESHOLD_SECONDS)                \
    duration = std::chrono::duration<double>::zero();                         \
                                                                              \
    for (size_t measure_time_index = 0;                                       \
         measure_time_index < (TOTAL_ITERATIONS); measure_time_index++) {     \
        using clock = std::chrono::high_resolution_clock;                     \
                                                                              \
        const std::chrono::duration<double> time_threshold_seconds(           \
            TIME_THRESHOLD_SECONDS);                                          \
                                                                              \
        const auto start = clock::now();                                      \
                                                                              \
        size_t INDEX_VARIABLE;                                                \
        for (INDEX_VARIABLE = 0; INDEX_VARIABLE < (ITERATIONS);               \
             ++INDEX_VARIABLE) {                                              \
            if (INDEX_VARIABLE % (REPORT_PER_ITERATIONS) == 0) {              \
                std::cerr << (INDEX_VARIABLE) << " Iterations completed!"     \
                          << " (" << (INDEX_VARIABLE * 100 / (ITERATIONS))    \
                          << "\%)"                                            \
                          << " - "                                            \
                          << "(" << (measure_time_index + 1) << "/"           \
                          << (TOTAL_ITERATIONS) << ")" << std::endl;          \
                                                                              \
                if (clock::now() - start > time_threshold_seconds) {          \
                    break;                                                    \
                }                                                             \
            }                                                                 \
                                                                              \
            CODE;                                                             \
        }                                                                     \
                                                                              \
        const auto end  = clock::now();                                       \
        duration       += (end - start) * INDEX_VARIABLE / (ITERATIONS);      \
    }                                                                         \
    duration = duration / (TOTAL_ITERATIONS)

#endif  // !TIME_HPP
