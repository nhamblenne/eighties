#######################################################################
# CMakeLists.txt
# Copyright (c) 2020 Nicolas Ivan Hamblenne
#######################################################################

add_executable(test1 test1.cpp)
target_link_libraries(test1 eighties)

add_executable(mandelbrot mandelbrot.cpp)
target_link_libraries(mandelbrot eighties)

add_executable(mandelbrot-par mandelbrot-par.cpp)
target_link_libraries(mandelbrot-par eighties)

add_executable(mandelbrot-zoom mandelbrot-zoom.cpp)
target_link_libraries(mandelbrot-zoom eighties)

add_executable(test-image test-image.cpp)
target_link_libraries(test-image eighties)

add_executable(test-position test-position.cpp)
target_link_libraries(test-position eighties)

