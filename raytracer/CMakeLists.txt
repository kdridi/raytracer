set(SOURCES
    include/raytracer.hpp

    include/camera.hpp
    src/camera.cpp

    include/canvas.hpp
    src/canvas.cpp

    include/color.hpp
    src/color.cpp

    include/cone.hpp
    src/cone.cpp

    include/cube.hpp
    src/cube.cpp

    include/cylinder.hpp
    src/cylinder.cpp

    include/group.hpp
    src/group.cpp

    include/intersections.hpp
    src/intersections.cpp

    include/lights.hpp
    src/lights.cpp

    include/material.hpp
    src/material.cpp

    include/matrix.hpp
    src/matrix.cpp

    include/pattern.hpp
    src/pattern.cpp

    include/plane.hpp
    src/plane.cpp

    include/point.hpp
    src/point.cpp

    include/ray.hpp
    src/ray.cpp

    include/shape.hpp
    src/shape.cpp

    include/sphere.hpp
    src/sphere.cpp

    include/tuple.hpp
    src/tuple.cpp

    include/vector.hpp
    src/vector.cpp

    include/world.hpp
    src/world.cpp
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