set(SOURCES
    include/tuple.hpp
    src/tuple.cpp
)

add_library(raytracer ${SOURCES})
target_include_directories(raytracer PUBLIC include)
target_compile_features(raytracer PUBLIC cxx_std_23)

install(
    TARGETS raytracer
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

add_subdirectory(tests)