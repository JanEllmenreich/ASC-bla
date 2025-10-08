#ifndef FILE_MATRIX
#define FILE_MATRIX

#include <iostream>

namespace ASC_bla {

enum class Ordering { RowMajor, ColMajor };

template <typename T, Ordering O = Ordering::RowMajor>
class Matrix {
  T* data;
  size_t rows;
  size_t cols;

 public:
  explicit Matrix(size_t n) : Matrix(n, n) {}

  Matrix(size_t rows_, size_t cols_)
      : data(new T[rows_ * cols_]), rows(rows_), cols(cols_) {
    ;
  }

  Matrix(const Matrix& mat) : Matrix(mat.Rows(), mat.Cols()) { *this = mat; }

  Matrix(Matrix&& v) : data(nullptr), rows(0), cols(0) {
    std::swap(data, v.data);
    std::swap(cols, v.cols);
    std::swap(rows, v.rows);
  }

  ~Matrix() { delete[] data; }

  Matrix& operator=(const Matrix& mat) {
    for (size_t i = 0; i < Size(); i++) data[i] = mat(i);
    return *this;
  }

  Matrix& operator=(T value) {
    std::fill(data, data + Size(), value);
    return *this;
  }

  Matrix& operator=(Matrix&& mat) {
    std::swap(data, mat.data);
    std::swap(rows, mat.rows);
    std::swap(cols, mat.cols);
    return *this;
  }

  size_t Size() const { return rows * cols; }
  size_t Rows() const { return rows; }
  size_t Cols() const { return cols; }

  T& operator()(size_t i) { return data[i]; }
  const T& operator()(size_t i) const { return data[i]; }

  T& operator()(size_t i, size_t j) {
    if constexpr (O == Ordering::RowMajor)
      return data[j + i * rows];
    else
      return data[i + j * cols];
  }

  const T& operator()(size_t i, size_t j) const {
    if constexpr (O == Ordering::RowMajor)
    {
      std::cout << "i, k = " << i << " " << j << "\n";
      std::cout << Rows() << " " << Cols() << "\n";
      return data[j + i * rows];
    }
    else
    {
      std::cout << "k, j = " << i << " " << j << "\n";
      std::cout << Rows() << " " << Cols() << "\n";
      return data[i + j * cols];
    }
  }
};

template <typename T, Ordering O>
Matrix<T, O> operator+(const Matrix<T, O>& a, const Matrix<T, O>& b) {
  Matrix<T> sum(a.Rows(), a.Cols());
  for (size_t i = 0; i < a.Size(); i++) sum(i) = a(i) + b(i);
  return sum;
}

template <typename T>
Matrix<T> operator*(const Matrix<T, Ordering::RowMajor>& a,
                    const Matrix<T, Ordering::ColMajor>& b) {
  Matrix<T> sum(a.Rows(), b.Cols());

  sum = 0.0;

  for (size_t i = 0; i < 1; i++)
    for (size_t j = 0; j < 1; j++)
      for (size_t k = 0; k < 3; k++) 
      {
        std::cout << i << " " << j << " " << k << "\n";
        sum(i, j) += a(i, k) * b(k, j);
      }

  return sum;
}

template <typename T, Ordering O>
std::ostream& operator<<(std::ostream& ost, const Matrix<T, O>& v) {
  if (v.Size() > 0) ost << v(0);
  for (size_t i = 1; i < v.Size(); i++) ost << ", " << v(i);
  return ost;
}

}  // namespace ASC_bla

#endif
