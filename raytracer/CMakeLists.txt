set(SOURCES
    include/raytracer.hpp

    include/canvas.hpp
    src/canvas.cpp

    include/color.hpp
    src/color.cpp

    include/matrix.hpp
    src/matrix.cpp

    include/point.hpp
    src/point.cpp

    include/tuple.hpp
    src/tuple.cpp

    include/vector.hpp
    src/vector.cpp
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
add_subdirectory(snippets)