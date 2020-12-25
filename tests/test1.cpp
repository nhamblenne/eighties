#include "eighties/window.hpp"

#include <iostream>

int emain(int argc, char* argv[])
{
    for (int i = 0; i < argc; ++i) {
        std::cout << "arg " << i << ": " << argv[i] << '\n';
    }
    eighties::window winT(800, 600);
    winT.resize(200, 150);
    winT.resize(640, 480);
    winT.wait_for_close();
    return 0;
}
