cmake_minimum_required(VERSION 3.7)
project(PuissanceC C CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_STANDARD 99)

add_executable(PuissanceC main.c Game.c Game.h minmax.c minmax.h ihm.c network.c network.h)

#SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(PuissanceC ${SDL2_LIBRARIES})

#GTEST
include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
        testSolver
        testSolver.cc
)
target_link_libraries(
        testSolver
        GTest::gtest_main
)

add_library(solver minmax.c Game.c)
target_link_libraries(testSolver solver)

include(GoogleTest)
gtest_discover_tests(testSolver)
