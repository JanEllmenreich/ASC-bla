#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "vector.hpp"

TEST_CASE("Fill vector", "[Vector tests]") {

    ASC_bla::Vector<double> v(10);
    v = 3.14;

    for (size_t i = 0; i < v.Size(); i++)
      REQUIRE_THAT(v(i) , Catch::Matchers::WithinAbs(3.14, 1e-12));
}

TEST_CASE("Add vector", "[Vector tests]") {

  ASC_bla::Vector<double> x(10);
  ASC_bla::Vector<double> y(10);
  x = 3.14;
  y = 1;

  auto z = x + y;

  for (size_t i = 0; i < z.Size(); i++)
    REQUIRE_THAT(z(i) , Catch::Matchers::WithinAbs(4.14, 1e-12));
}

