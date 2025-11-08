#include <catch2/catch_test_macros.hpp>

#include "matrix.hpp"
#include "vector.hpp"

TEST_CASE("Vector tests", "[Vector std::ranges concepts]") {

    STATIC_CHECK(std::ranges::contiguous_range<asc::dynamic_vector<double>>);
    STATIC_CHECK(std::ranges::contiguous_range<asc::contiguous_vector_view<double>>);

    STATIC_CHECK(std::ranges::random_access_range<asc::slice_vector_view<double, 1>>);
    STATIC_CHECK(std::ranges::random_access_range<asc::slice_vector_view<double>>);
}

