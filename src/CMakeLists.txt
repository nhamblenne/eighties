#######################################################################
# CMakeLists.txt
# Copyright (c) 2020 Nicolas Ivan Hamblenne
#######################################################################

add_library(eighties_s STATIC main.cpp)
set_project_warnings(eighties_s PRIVATE)
target_include_directories(eighties_s
        PRIVATE
            ${PROJECT_SOURCE_DIR}/include)

add_library(eighties_core app.cpp window.cpp window_impl.hpp eighties_app.cpp
        eighties_app.hpp canvas.cpp canvas.hpp scroll_area.cpp scroll_area.hpp
        image.cpp image_impl.hpp event.cpp)
set_project_warnings(eighties_core PRIVATE)
set_target_properties(eighties_core PROPERTIES
        AUTOMOC ON)
target_include_directories(eighties_core
        INTERFACE
            $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:include>
        PRIVATE
            ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(eighties_core PUBLIC Qt5::Widgets Qt5::Gui)
target_link_libraries(eighties_core PUBLIC ${CMAKE_THREAD_LIBS_INIT})

add_library(eighties INTERFACE)
target_link_libraries(eighties INTERFACE eighties_s eighties_core)

install(TARGETS eighties eighties_core eighties_s EXPORT eightiesConfig DESTINATION lib)
install(FILES
           ${PROJECT_SOURCE_DIR}/include/eighties/app.hpp
           ${PROJECT_SOURCE_DIR}/include/eighties/color.hpp
           ${PROJECT_SOURCE_DIR}/include/eighties/event.hpp
           ${PROJECT_SOURCE_DIR}/include/eighties/image.hpp
           ${PROJECT_SOURCE_DIR}/include/eighties/point.hpp
           ${PROJECT_SOURCE_DIR}/include/eighties/window.hpp
        DESTINATION include/eighties)
install(EXPORT eightiesConfig DESTINATION lib/cmake/eighties)
