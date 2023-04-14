cmake_minimum_required(VERSION 3.22 FATAL_ERROR)
project(raytracer VERSION 0.1 LANGUAGES CXX)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_subdirectory(vendor/github.com/google/googletest.git)

add_subdirectory(raytracer)
