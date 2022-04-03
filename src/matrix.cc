#include "matrix.hh"

std::ostream& operator<<(std::ostream& os, const Matrix& m) {
  os << m.matrix;
  return os;
}

void Matrix::init_values(double (*f) (void)) {
  for (int i = 0; i < this->rows(); i++) {
    for (int j = 0; j < this->cols(); j++) {
      this->matrix(i, j) = f();
    }
  }
}