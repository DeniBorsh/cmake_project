cmake_minimum_required(VERSION 3.22.1)

project(MyProject)

add_executable(${PROJECT_NAME} main.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/../mylib/)
target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/../mylib/build/)
target_link_libraries(${PROJECT_NAME} mearlymath)