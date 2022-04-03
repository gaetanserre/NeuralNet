#include "matrix.hh"

class Tensor {
  public:
    Tensor(const Matrix &m, const bool &require_grad=false);

    void backward(const Matrix* g=nullptr);

    Matrix data;
    bool require_grad;

    Matrix gradient;    
};