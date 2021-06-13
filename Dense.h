#ifndef C___PROJECT_DENSE_H
#define C___PROJECT_DENSE_H

#include "Activation.h"
/**
 * @class Dense
 * @brief Dense class. holds weight matrix, bias matrix and activation
 * supports overloaded operators s.t ()
 */
class Dense{
 public:
  /*constructor*/
  Dense(Matrix& w, Matrix& bias, ActivationType act);

  /*returns weights matrix*/
  Matrix get_weights()const;

  /*returns biases array*/
  Matrix get_bias()const;

  /*returns activation*/
  Activation get_activation()const;

  /*parenthesis operator*/
  Matrix operator()(Matrix& x) const;

 private:
  Matrix _w;/*weights matrix*/
  Matrix _bias;/*bias matrix*/
  Activation _act;/*Activation instance*/
};

#endif //C___PROJECT_DENSE_H
