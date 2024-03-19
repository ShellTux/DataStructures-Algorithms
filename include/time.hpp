#ifndef TIME_HPP
#define TIME_HPP

#define MEASURE_TIME(code, iterations)                                     \
    duration = std::chrono::duration<double>::zero();                      \
    for (size_t measure_time_index = 0; measure_time_index < (iterations); \
         measure_time_index++) {                                           \
        const auto start = std::chrono::high_resolution_clock::now();      \
        code;                                                              \
        const auto end  = std::chrono::high_resolution_clock::now();       \
        duration       += end - start;                                     \
    }                                                                      \
    duration = duration / (iterations)

#endif  // !TIME_HPP
