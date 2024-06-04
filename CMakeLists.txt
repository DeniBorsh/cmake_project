cmake_minimum_required(VERSION 3.22.1)

project(MyProject)

add_executable(${PROJECT_NAME} main.cpp)
add_subdirectory(external/glfw)
add_subdirectory(adder)

find_package(Git QUIET)

if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/external/glfw/CMakeLists.txt")
    message(FATAL_ERROR "The glfw submoduels was not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules")
endif()


target_include_directories(${PROJECT_NAME} PUBLIC adder/
                                           PUBLIC external/glfw/include)

target_link_directories(${PROJECT_NAME} PRIVATE adder/build/
                                        PRIVATE build/external/glfw/src)

target_link_libraries(${PROJECT_NAME} mearlymath glfw)