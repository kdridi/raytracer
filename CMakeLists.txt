cmake_minimum_required(VERSION 3.22 FATAL_ERROR)
project(raytracer VERSION 0.1 LANGUAGES CXX)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_subdirectory(vendor/github.com/google/googletest.git)

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

add_subdirectory(raytracer)
