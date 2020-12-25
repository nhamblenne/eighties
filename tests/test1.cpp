#include "eighties/window.hpp"

#include <iostream>

int emain(int argc, char* argv[])
{
    for (int i = 0; i < argc; ++i) {
        std::cout << "arg " << i << ": " << argv[i] << '\n';
    }
    eighties::window winT(800, 600);
    winT.wait_for_close();
    return 0;
}
