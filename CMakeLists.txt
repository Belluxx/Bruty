cmake_minimum_required(VERSION 3.20)
project (Bruty)

set(CMAKE_CXX_STANDARD 14)

add_executable(Bruty src/main.cpp src/utils/brutetools.h src/utils/brutetools.cpp)
