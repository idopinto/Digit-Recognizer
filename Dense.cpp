
#include "Dense.h"
Dense:: Dense(Matrix& w, Matrix& bias, ActivationType activation_type)
:_act(activation_type)
{
  _w = w;
  _bias = bias;
}

Matrix Dense:: get_weights() const
{
  return _w;
}
Matrix Dense:: get_bias() const{
  return _bias;
}
Activation Dense:: get_activation() const
{
  return _act;
}
Matrix Dense:: operator()(Matrix& x) const
{
  Matrix m = _act(_w*x +_bias);
  return m;
}

