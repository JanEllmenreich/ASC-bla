find_package(Catch2 3 REQUIRED)

add_executable(catch_tests_run
        test_vector.cpp
        test_matrix.cpp
)
target_link_libraries(catch_tests_run PRIVATE Catch2::Catch2WithMain)

include(Catch)
catch_discover_tests(catch_tests_run)
