#include <iostream>

#include <matrix.hpp>

namespace bla = ASC_bla;


int main()
{
  bla::Matrix<double> M(3, 2);
  bla::Matrix<double, bla::Ordering::ColMajor> N(2, 3);
  bla::Vector<double> x(2);

  for (size_t i = 0; i < M.Rows(); i++)
    for (size_t j = 0; j < M.Cols(); j++)
      M(i, j) = i + j;

  x = 2;
  N = 3;

  auto a = M * x;

//   for (size_t i = 0; i < x.Size(); i++)
//     {
//       x(i) = i;
//       y(i) = 10;
//     }

//   bla::Matrix<double> z = x+y;
  std::cout << "x = " << a << std::endl;
  std::cout << M << std::endl;
  std::cout << M.transpose() << std::endl;
  std::cout << M * N << std::endl;
}
