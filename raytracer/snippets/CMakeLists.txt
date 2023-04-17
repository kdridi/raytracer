find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

add_executable(01 01.cpp)
target_link_libraries(01 raytracer)

add_executable(02 02.cpp)
target_link_libraries(02 raytracer)

add_executable(03 03.cpp)
target_link_libraries(03 raytracer)

add_executable(04 04.cpp)
target_link_libraries(04 raytracer)
