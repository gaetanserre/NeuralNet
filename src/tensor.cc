#include "tensor.hh"

Tensor::Tensor(const Matrix &m, const bool &require_grad) {
  this->data = std::move(m);
  this->require_grad = require_grad;
}

void Tensor::backward(const Matrix* g) {}