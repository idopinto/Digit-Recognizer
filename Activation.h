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

/**
 * @class Activation
 * @brief Activation class. Holds act type (enum) and relu, softmax functions
 * supports overloaded operators s.t ()
 */
class Activation{
 public:
  /**
   * constructor
 */
  explicit Activation(ActivationType act_type);

/*Returns activation type*/
  ActivationType get_activation_type() const;

/*parenthesis operator*/
  Matrix operator()(const Matrix& x) const;

 private:
  ActivationType  _act_type; /* act type (RELO OR SOFTMAX)*/
  static void _soft_max(const Matrix& x,Matrix &m); /*implemented soft_max*/
  static void _relu(const Matrix& x,Matrix &m);/*implemented relu function*/
};

#endif //ACTIVATION_H
