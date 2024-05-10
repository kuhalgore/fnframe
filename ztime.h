#ifndef ZTIME_H
#define ZTIME_H

//#include <fmt/color.h>
//#include <fmt/core.h>

#include <chrono>
#include <iostream>

template <typename TFunc, typename... Args>
void run_and_measure(TFunc func, char const *title, Args... args)
{
    //fmt::print(fmt::emphasis::bold, title, std::forward<Args>(args)...);

    auto const start = std::chrono::high_resolution_clock::now();

    func();

    auto const end = std::chrono::high_resolution_clock::now();

    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    //fmt::print(fg(fmt::color::green), "Elapsed {:.3f} msec\n", elapsed.count() / 1000.0);
    std::cout << "Elapsed {:" << elapsed.count() / 1000.0 << "} msec\n"<<std::endl;
}

#endif
