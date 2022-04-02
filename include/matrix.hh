#include <iostream>
#include <memory>
#include <Eigen/Dense>


class Matrix {
  public:
    Matrix(const unsigned int &m, const unsigned int &n);
    Matrix(const Eigen::MatrixXd &matrix);
    ~Matrix() = default;

    void init_values(double (*f) (void));

    Matrix transpose();

    Matrix operator + (const Matrix& m);
    Matrix operator * (const Matrix& m);
    Matrix operator % (const Matrix& m);

    friend std::ostream& operator<<(std::ostream& os, const Matrix& m);
  
  protected:
    Eigen::MatrixXd matrix;
};


inline Matrix::Matrix(const unsigned int &m, const unsigned int &n) {
  this->matrix = Eigen::MatrixXd(m, n);
}

inline Matrix::Matrix(const Eigen::MatrixXd &m) {
  this->matrix = std::move(m);
}

void Matrix::init_values(double (*f) (void)) {
  for (int i = 0; i < this->matrix.rows(); i++) {
    for (int j = 0; j < this->matrix.cols(); j++) {
      this->matrix(i, j) = f();
    }
  }
}

inline Matrix Matrix::transpose() {
  return Matrix(this->matrix.transpose());
}

inline Matrix Matrix::operator + (const Matrix& m) {
  return Matrix(this->matrix + m.matrix);
}

inline Matrix Matrix::operator * (const Matrix& m) {
  return Matrix(this->matrix.cwiseProduct(m.matrix));
}

inline Matrix Matrix::operator % (const Matrix& m) {
  return Matrix(this->matrix * m.matrix);
}

std::ostream& operator<<(std::ostream& os, const Matrix& m) {
  os << m.matrix;
  return os;
}
