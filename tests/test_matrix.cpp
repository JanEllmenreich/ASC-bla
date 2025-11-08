#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "matrix.hpp"

TEST_CASE("Fill matrix", "[Matrix tests]") {

  ASC_bla::Matrix<double> mat(2, 5);
  mat = 3.14;

  for (size_t i = 0; i < mat.Rows(); i++)
    for (size_t j = 0; j < mat.Cols(); j++)
      REQUIRE_THAT(mat(i, j) , Catch::Matchers::WithinAbs(3.14, 1e-12));
}

TEST_CASE("Add matrix", "[Matrix tests]") {

  ASC_bla::Matrix<double> x(2, 5);
  ASC_bla::Matrix<double> y(2, 5);
  x = 3.14;
  y = 1;

  auto z = x + y;

  for (size_t i = 0; i < z.Rows(); i++)
    for (size_t j = 0; j < z.Cols(); j++)
      REQUIRE_THAT(z(i, j) , Catch::Matchers::WithinAbs(4.14, 1e-12));
}