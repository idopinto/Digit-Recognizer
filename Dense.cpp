
#include "Dense.h"

/*constructor*/
Dense:: Dense(Matrix& w, Matrix& bias, ActivationType activation_type)
:_act(activation_type)
{
  _w = w;
  _bias = bias;
}


/*returns weights matrix*/
Matrix Dense:: get_weights() const
{
  return _w;
}
/*returns bias matrix*/
Matrix Dense:: get_bias() const{
  return _bias;
}
/*returns activation instance*/
Activation Dense:: get_activation() const
{
  return _act;
}
/*parenthesis operator*/
Matrix Dense:: operator()(Matrix& x) const
{
  Matrix m = _act(_w*x +_bias);
  return m;
}

