//
// Created by Ido_2 on 6/5/2021.
//
#include "Activation.h"

#include <cmath>

/**
 * constructor
*/
Activation:: Activation(ActivationType act_type):_act_type(act_type){}

/*Returns activation type*/
ActivationType Activation:: get_activation_type() const {return _act_type;}

/*parenthesis operator*/
Matrix Activation:: operator()(const Matrix& x) const
{
  Matrix output(x.get_rows(),x.get_cols());
  switch(_act_type) {
      case RELU :
        {

          _relu(x,output);
        }
        break;
      case SOFTMAX  :
        {
          _soft_max (x,output);
        }
        break;
    }
    return output;
}


/*implemented relu function*/
void Activation:: _relu(const Matrix& x,Matrix &m)
{
  for(int i=0;i< m.get_rows()*m.get_cols();i++)
    {
      m[i] = (x[i] < 0) ? 0 : x[i];
    }
}
/*implemented soft_max*/
void Activation:: _soft_max(const Matrix& x,Matrix &m)
{
  float sum = 0;
  for(int i=0;i < m.get_rows()*m.get_cols();i++)
    {
      m[i] = std::exp (x[i]);
      sum += m[i];
    }
  m = m * (1/sum) ;
}

