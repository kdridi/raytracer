# add -fsanitize=address to CMAKE_CXX_FLAGS to enable address sanitizer if debug build
if(CMAKE_BUILD_TYPE MATCHES Debug)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
endif()

add_executable(01 01.cpp)
target_link_libraries(01 raytracer)

add_executable(02 02.cpp)
target_link_libraries(02 raytracer)

add_executable(03 03.cpp)
target_link_libraries(03 raytracer)

add_executable(04 04.cpp)
target_link_libraries(04 raytracer)

add_executable(05 05.cpp)
target_link_libraries(05 raytracer)

add_executable(06 06.cpp)
target_link_libraries(06 raytracer)

add_executable(07 07.cpp)
target_link_libraries(07 raytracer)

add_executable(08 08.cpp)
target_link_libraries(08 raytracer)

add_executable(09 09.cpp)
target_link_libraries(09 raytracer)

add_executable(10 10.cpp)
target_link_libraries(10 raytracer)

add_executable(11 11.cpp)
target_link_libraries(11 raytracer)

add_executable(12 12.cpp)
target_link_libraries(12 raytracer)
