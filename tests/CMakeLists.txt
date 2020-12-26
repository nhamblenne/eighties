#######################################################################
# CMakeLists.txt
# Copyright (c) 2020 Nicolas Ivan Hamblenne
#######################################################################

add_executable(test1 test1.cpp)
target_link_libraries(test1 eighties_s eighties)

add_executable(mandelbrot mandelbrot.cpp)
target_link_libraries(mandelbrot eighties_s eighties)

add_executable(mandelbrot-par mandelbrot-par.cpp)
target_link_libraries(mandelbrot-par eighties_s eighties)
