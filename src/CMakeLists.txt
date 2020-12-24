add_library(eighties app.cpp window.cpp window_impl.hpp eighties_app.cpp eighties_app.hpp)
set_project_warnings(eighties PRIVATE)
target_include_directories(eighties
        INTERFACE
            $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:include>
        PRIVATE
            ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(eighties PUBLIC Qt5::Widgets Qt5::Gui)
target_link_libraries(eighties PUBLIC ${CMAKE_THREAD_LIBS_INIT})
install(TARGETS eighties EXPORT eighties DESTINATION lib)
install(EXPORT eighties DESTINATION lib/cmake/eighties)