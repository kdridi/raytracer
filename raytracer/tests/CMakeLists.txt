set(TESTS
    main.cpp
    camera_tests.cpp
    canvas_tests.cpp
    color_tests.cpp
    cone_tests.cpp
    cube_tests.cpp
    cylinder_tests.cpp
    intersections_tests.cpp
    lights_tests.cpp
    material_tests.cpp
    matrix_tests.cpp
    pattern_tests.cpp
    plane_tests.cpp
    ray_tests.cpp
    shape_tests.cpp
    sphere_tests.cpp
    tuple_tests.cpp
    world_tests.cpp
)

add_executable(tests ${TESTS})
target_link_libraries(tests raytracer gtest gmock)