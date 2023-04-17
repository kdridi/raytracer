set(TESTS
    main.cpp
    canvas_tests.cpp
    color_tests.cpp
    matrix_tests.cpp
    tuple_tests.cpp
)

add_executable(tests ${TESTS})
target_link_libraries(tests raytracer gtest gmock)