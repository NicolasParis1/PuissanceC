cmake_minimum_required(VERSION 3.23)
project(PuissanceC C)

set(CMAKE_CXX_STANDARD 14)

add_executable(PuissanceC main.c Game.c Game.h solver.c solver.h network.c network.h ihm.cpp ihm.h)

add_subdirectory(Google_tests)