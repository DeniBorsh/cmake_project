cmake_minimum_required(VERSION 3.22.1)

project(MyProject VERSION 1.0)

configure_file(MyProjectConfig.h.in MyProjectConfig.h)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR})

option(USE_ADDER "A simple library for adding 2 floats." ON)

if(USE_ADDER)
    add_subdirectory(adder)

    list(APPEND EXTRA_LIB_DIRS mearlymath)
    list(APPEND EXTRA_INCLUDE_DIRS adder)
    list(APPEND EXTRA_LINKS mearlymath)
endif()

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

add_subdirectory(external/glfw)

target_include_directories(${PROJECT_NAME} PUBLIC external/glfw/include
                                           ${EXTRA_INCLUDE_DIRS})

target_link_directories(${PROJECT_NAME} PRIVATE build/external/glfw/src
                                        ${EXTRA_LIB_DIRS})

target_link_libraries(${PROJECT_NAME} glfw
                                      ${EXTRA_LINKS})

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/MyProjectConfig.h" DESTINATION include)

include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/license.txt")
set(CPACK_PACKAGE_VERSION_MAJOR "${Tutorial_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${Tutorial_VERSION_MINOR}")
include(CPack)