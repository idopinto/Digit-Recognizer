//
// Created by Ido_2 on 6/5/2021.
//
#include "Dense.h"
Dense:: Dense(Matrix& w, Matrix& bias, ActivationType activation_type): _act(activation_type)
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
ActivationType Dense:: get_activation() const
{
  return _act.get_activation_type();
}
Matrix& Dense:: operator()(Matrix& x) const
{

  x = _act(_w*x +_bias);
  return x;
}

