//MlpNetwork.h

#ifndef MLPNETWORK_H
#define MLPNETWORK_H

#include "Matrix.h"

#define MLP_SIZE 4

//
const matrix_dims img_dims = {28, 28};
const matrix_dims weights_dims[] = {{128, 784},
                                    {64, 128},
                                    {20, 64},
                                    {10, 20}};
const matrix_dims bias_dims[]    = {{128, 1},
                                    {64, 1},
                                    {20, 1},
                                    {10, 1}};

class MlpNetwork{
 public:
  MlpNetwork(Matrix[] weights,Matrix[] biases);

  digit operator()(Matrix x) const;

 private:
  Matrix[MLP_SIZE] _weights;
  Matrix[MLP_SIZE] _biases;



};

#endif // MLPNETWORK_H
