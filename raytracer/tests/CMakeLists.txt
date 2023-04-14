set(TESTS
    main.cpp
    tuple_tests.cpp
)

add_executable(tests ${TESTS})
target_link_libraries(tests raytracer gtest gmock)