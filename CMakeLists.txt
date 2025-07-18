cmake_minimum_required(VERSION 3.16)
project(Linx VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

add_library(Linx INTERFACE)
target_include_directories(Linx INTERFACE include)

add_executable(LinxTest src/LinxTest.cpp)
target_link_libraries(LinxTest Linx)
