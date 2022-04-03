#include <iostream>
#include <memory>
#include <Eigen/Dense>


class Matrix {
  public:
    Matrix(const unsigned int &m, const unsigned int &n);
    Matrix(const Eigen::MatrixXd &matrix);
    Matrix() = default;
    ~Matrix() = default;

    void init_values(double (*f) (void));

    Matrix transpose() const;
    int rows() const;
    int cols() const;
    void set(const unsigned int &i, const unsigned int &j, const double &v);

    Matrix operator +  (const Matrix &m);
    Matrix operator *  (const Matrix &m);
    Matrix operator %  (const Matrix &m);
    double operator () (const unsigned int &i, const unsigned int &j) const;

    friend std::ostream& operator<<(std::ostream& os, const Matrix& m);
  
  protected:
    Eigen::MatrixXd matrix;
};

// Constructors
inline Matrix::Matrix(const unsigned int &m, const unsigned int &n) {
  this->matrix = Eigen::MatrixXd(m, n);
}

inline Matrix::Matrix(const Eigen::MatrixXd &m) {
  this->matrix = std::move(m);
}

// Methods
inline Matrix Matrix::transpose() const {
  return Matrix(this->matrix.transpose());
}

inline int Matrix::rows() const {
  return this->matrix.rows();
}

inline int Matrix::cols() const {
  return this->matrix.cols();
}

inline void Matrix::set(const unsigned int &i, const unsigned int &j, const double &v)
{
  this->matrix(i, j) = v;
}

// Operators
inline Matrix Matrix::operator + (const Matrix &m) {
  return Matrix(this->matrix + m.matrix);
}

inline Matrix Matrix::operator * (const Matrix &m) {
  return Matrix(this->matrix.cwiseProduct(m.matrix));
}

inline Matrix Matrix::operator % (const Matrix &m) {
  return Matrix(this->matrix * m.matrix);
}

inline double Matrix::operator () (const unsigned int &i, const unsigned int &j) const
{
  return this->matrix(i, j);
}
