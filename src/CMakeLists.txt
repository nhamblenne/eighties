#######################################################################
# CMakeLists.txt
# Copyright (c) 2020 Nicolas Ivan Hamblenne
#######################################################################

add_library(eighties_s STATIC main.cpp)
set_project_warnings(eighties_s PRIVATE)
target_include_directories(eighties_s
        PRIVATE
            ${PROJECT_SOURCE_DIR}/include)

add_library(eighties app.cpp window.cpp window_impl.hpp eighties_app.cpp eighties_app.hpp canvas.cpp canvas.hpp scroll_area.cpp scroll_area.hpp ../include/eighties/color.hpp)
set_project_warnings(eighties PRIVATE)
set_target_properties(eighties PROPERTIES
        AUTOMOC ON)
target_include_directories(eighties
        INTERFACE
            $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:include>
        PRIVATE
            ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(eighties PUBLIC Qt5::Widgets Qt5::Gui)
target_link_libraries(eighties PUBLIC ${CMAKE_THREAD_LIBS_INIT})

install(TARGETS eighties eighties_s EXPORT eighties DESTINATION lib)
install(EXPORT eighties DESTINATION lib/cmake/eighties)
