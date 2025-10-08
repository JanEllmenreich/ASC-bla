#include <iostream>

#include <matrix.hpp>

namespace bla = ASC_bla;


int main()
{
  size_t n = 5;
  bla::Matrix<double> x(3, 2);
  bla::Matrix<double, bla::Ordering::ColMajor> y(2, 3);

  x = 1;
  y = 2;

//   for (size_t i = 0; i < x.Size(); i++)
//     {
//       x(i) = i;
//       y(i) = 10;
//     }

//   bla::Matrix<double> z = x+y;
  std::cout << "x = " << x << std::endl;
  std::cout << "y = " << y << std::endl;
  std::cout << "z = " << x * y << std::endl;
}
