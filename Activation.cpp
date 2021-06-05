//
// Created by Ido_2 on 6/5/2021.
//
#include "Activation.h"


Activation:: Activation(ActivationType act_type):_act_type(act_type){}

ActivationType Activation:: get_activation_type() const
{
  return _act_type;
}

void relu_function(const Matrix& x,Matrix &output)
{

}
void soft_max_function(const Matrix& x,Matrix& output)
{
  float sum = 0;
  for(int i=0;i < output.get_rows();i++)
    {
      output[i] = exp (x[i]);
      sum += exp(x[i]);
    }
    if(sum != 0)
      {
        output = 1/sum * output;
      }


}
Matrix Activation:: operator()(const Matrix& x) const
{
  Matrix output(x.get_rows(),1);
  switch(_act_type) {
      case RELU  :
        {
          for(int i=0;i< x.get_rows();i++)
            {
              output[i] = (x[i] < 0) ? 0 : x[i];
            }
        }
        return output;
      case SOFTMAX  :
        {
          soft_max_function (x,output);
          return output;
        }
    }
    return output;
}

