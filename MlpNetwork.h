//MlpNetwork.h

#ifndef MLPNETWORK_H
#define MLPNETWORK_H

#include "Matrix.h"
#include "Digit.h"
#include "Dense.h"
#define MLP_SIZE 4

const matrix_dims img_dims = {28, 28};
const matrix_dims weights_dims[] = {{128, 784},
                                    {64, 128},
                                    {20, 64},
                                    {10, 20}};
const matrix_dims bias_dims[]    = {{128, 1},
                                    {64, 1},
                                    {20, 1},
                                    {10, 1}};
/**
 * @class MlpNetwork
 * @brief MlpNetworkMlpNetwork class. Holds weights matrices array
 * biases matrices array.
 * supports overloaded operators s.t ()
 */
class MlpNetwork{
 public:
  /*constructor*/
  MlpNetwork(Matrix *weights,Matrix *biases);
  /*parenthesis operator*/
  digit operator()(const Matrix& input);

 private:
  Matrix *_weights;  /*weights matrices array*/
  Matrix *_biases;  /*biases matrices array*/
  void make_prob_vec(Matrix &input);  /*transforms matrix to probability
                                                                *vector*/
  static digit find_max_prob(Matrix m);  /*returns the index of the maximum
                                          * value in probability vector*/
};

#endif // MLPNETWORK_H
