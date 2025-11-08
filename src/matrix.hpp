#ifndef FILE_MATRIX
#define FILE_MATRIX

#include <iostream>
#include <vector.hpp>

namespace ASC_bla {

enum class Ordering { RowMajor, ColMajor };

template <typename T, Ordering ORD = Ordering::RowMajor>
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

  auto transpose() const {
    Matrix<T, (ORD == Ordering::RowMajor) ? Ordering::ColMajor
                                         : Ordering::RowMajor>

        result(cols, rows);
    for (size_t i = 0; i < rows; i++)
      for (size_t j = 0; j < cols; j++) result(j, i) = (*this)(i, j);
    return result;
  }

  size_t Size() const { return rows * cols; }
  size_t Rows() const { return rows; }
  size_t Cols() const { return cols; }

  T& operator()(size_t i, size_t j) {
    if constexpr (ORD == Ordering::RowMajor)
      return data[j + i * cols];
    else
      return data[i + j * rows];
  }

  const T& operator()(size_t i, size_t j) const {
    if constexpr (ORD == Ordering::RowMajor)
    {
      return data[j + i * cols];
    }
    else
    {
      return data[i + j * rows];
    }
  }
};

template <typename T, Ordering ORD>
Matrix<T, ORD> operator+(const Matrix<T, ORD>& a, const Matrix<T, ORD>& b) {
  Matrix<T> sum(a.Rows(), a.Cols());
  for (size_t i = 0; i < a.Rows(); i++)
    for (size_t j = 0; j < a.Cols(); j++) sum(i, j) = a(i, j) + b(i, j);
  return sum;
}

template<typename T, Ordering ORD>
Vector<T> operator*(const Matrix<T, ORD>& mat, const Vector<T>& vec) {
  Vector<T> result(mat.Rows());
  for (size_t i = 0; i < mat.Rows(); i++) {
    result(i) = 0;
    for (size_t j = 0; j < mat.Cols(); j++) {
      result(i) += mat(i, j) * vec(j);
    }
  }
  return result;
}

template <typename T>
Matrix<T> operator*(const Matrix<T, Ordering::RowMajor>& a,
                    const Matrix<T, Ordering::ColMajor>& b) {
  Matrix<T> sum(a.Rows(), b.Cols());

  sum = 0.0;

  for (size_t i = 0; i < a.Rows(); i++)
    for (size_t j = 0; j < b.Cols(); j++)
      for (size_t k = 0; k < a.Cols(); k++)
      {
        sum(i, j) += a(i, k) * b(k, j);
      }

  return sum;
}

template <typename T, Ordering ORD>
std::ostream& operator<<(std::ostream& ost, const Matrix<T, ORD>& mat) {

  if (mat.Size() == 0) return ost << "[[]]";

  ost << "[[" << mat(0, 0);
  for (size_t j = 1; j < mat.Cols(); j++) {
    ost << ", " << mat(0, j);
  }
  ost << "]";
  for (size_t i = 1; i < mat.Rows(); i++) {
    ost << "\n ["<< mat(i, 0);;
    for (size_t j = 1; j < mat.Cols(); j++) {
      ost << ", " << mat(i, j);
    }
    ost << "]";
  }
  ost << "]";
  return ost;
}

}  // namespace ASC_bla

#endif
