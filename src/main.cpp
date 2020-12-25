/* =======================================================================
 * main.cpp.c
 * Copyright (c) 2020 Nicolas Ivan Hamblenne
 * =======================================================================
 */

#include "eighties/app.hpp"

#include <stdlib.h>
#include <exception>
#include <iostream>

int emain(int argc, char* argv[]);

int main(int argc, char* argv[])
{
    int status = EXIT_SUCCESS;
    try {
        status = eighties::main(argc, argv, emain);
    } catch (std::exception& e) {
        std::cerr << "Unexpected exception: " << e.what() << ".\n";
        status = EXIT_FAILURE;
    } catch (int s) {
        status = s;
    } catch (char const* msg) {
        std::cerr << msg << '\n';
        status = EXIT_FAILURE;
    } catch (...) {
        std::cerr << "Unexpected unknown exception.\n";
        status = EXIT_FAILURE;
    }
    return status;
}
