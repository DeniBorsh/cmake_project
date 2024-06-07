cmake_minimum_required(VERSION 3.11)
project(mearlymath)
add_library(mearlymath adder.cpp)

install(TARGETS mearlymath DESTINATION lib)
install(FILES adder.h DESTINATION include)