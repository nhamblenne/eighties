/* =======================================================================
 * app.cpp.c
 * Copyright (c) 2020 Nicolas Ivan Hamblenne
 * =======================================================================
 */

#include "eighties/app.hpp"

#include <future>

namespace eighties {

int main(int argc, char* argv[], int (*wrapped)(int, char**))
{
    auto future = std::async(std::launch::async, wrapped, argc, argv);
    return future.get();
}

}