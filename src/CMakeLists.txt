add_library(eighties app.cpp)
set_project_warnings(eighties PRIVATE)
target_include_directories(eighties
        INTERFACE
            $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:include>
        PRIVATE
            ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(eighties PUBLIC ${CMAKE_THREAD_LIBS_INIT})
install(TARGETS eighties EXPORT eighties DESTINATION lib)
install(EXPORT eighties DESTINATION lib/cmake/eighties)