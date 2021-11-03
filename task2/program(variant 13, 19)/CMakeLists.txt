cmake_minimum_required(VERSION 3.20)
project(plants)

set(CMAKE_CXX_STANDARD 17)

add_executable(plants main.cpp container.cpp plant.cpp flower.cpp bush.cpp tree.cpp)
