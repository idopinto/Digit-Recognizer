//Activation.h
#ifndef ACTIVATION_H
#define ACTIVATION_H

#include "Matrix.h"
#include <cmath>
/**
 * @enum ActivationType
 * @brief Indicator of activation function.
 */
enum ActivationType
{
    RELU,
    SOFTMAX
};

class Activation{
 public:
  explicit Activation(ActivationType act_type);

  ActivationType get_activation_type() const;

  Matrix operator()(const Matrix& x) const;

 private:
  ActivationType  _act_type;

};

#endif //ACTIVATION_H
