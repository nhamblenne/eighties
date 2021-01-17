#######################################################################
# CMakeLists.txt
# Copyright (c) 2020 Nicolas Ivan Hamblenne
#######################################################################

add_executable(test1 WIN32 test1.cpp)
target_link_libraries(test1 eighties)

add_executable(mandelbrot WIN32 mandelbrot.cpp)
target_link_libraries(mandelbrot eighties)

add_executable(mandelbrot-par WIN32 mandelbrot-par.cpp)
target_link_libraries(mandelbrot-par eighties)

add_executable(mandelbrot-zoom WIN32 mandelbrot-zoom.cpp)
target_link_libraries(mandelbrot-zoom eighties)

add_executable(test-image WIN32 test-image.cpp)
target_link_libraries(test-image eighties)

add_executable(test-position WIN32 test-position.cpp)
target_link_libraries(test-position eighties)
