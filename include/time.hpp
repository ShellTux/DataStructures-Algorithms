#ifndef TIME_HPP
#define TIME_HPP

#define MEASURE_TIME(code)                                            \
    {                                                                 \
        const auto start = std::chrono::high_resolution_clock::now(); \
        code;                                                         \
        const auto end = std::chrono::high_resolution_clock::now();   \
        duration       = end - start;                                 \
    }

#endif  // !TIME_HPP
