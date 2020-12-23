#include "eighties/app.hpp"

#include <iostream>

int e_main(int argc, char* argv[])
{
    for (int i = 0; i < argc; ++i) {
        std::cout << "arg " << i << ": " << argv[i] << '\n';
    }
    return 0;
}

int main(int argc, char* argv[])
{
    int status = EXIT_SUCCESS;
    try {
        status = eighties::main(argc, argv, e_main);
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
