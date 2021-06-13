#ifndef C___PROJECT_DENSE_H
#define C___PROJECT_DENSE_H

#include "Activation.h"

class Dense{
 public:
  Dense(Matrix& w, Matrix& bias, ActivationType act);

  Matrix get_weights()const;
  Matrix get_bias()const;
  Activation get_activation()const;

  Matrix operator()(Matrix& x) const;

 private:
  Matrix _w;
  Matrix _bias;
  Activation _act;
};

#endif //C___PROJECT_DENSE_H
