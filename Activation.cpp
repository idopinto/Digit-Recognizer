//
// Created by Ido_2 on 6/5/2021.
//
#include "Activation.h"


Activation:: Activation(ActivationType act_type):_act_type(act_type){}

ActivationType Activation:: get_activation_type() const
{
  return _act_type;
}

Matrix Activation:: operator()(const Matrix& x) const
{
  Matrix output(x.get_rows(),1);
  switch(_act_type) {
      case RELU  :
        {
          for(int i=0;i< x.get_rows();i++)
            {
              output(i,0) = (x(i,0) < 0) ? 0 : x(i,0);
            }
        }
        return output;
      case SOFTMAX  :
        {
          float sum = 0;
          for(int i=0;i< x.get_rows();i++)
            {
              output(i,0) = std::exp (x(i,0));
              sum += std::exp (x(i,0));
            }
            output = (1/sum) * output;
          return output;
        }
    }

}

