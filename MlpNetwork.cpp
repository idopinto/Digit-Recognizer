//
// Created by Ido_2 on 6/5/2021.
//

#include "MlpNetwork.h"
MlpNetwork:: MlpNetwork(Matrix *weights,Matrix *biases)
{
  _weights = weights;
  _biases = biases;
  for(int i=0;i<MLP_SIZE;i++)
    {
      _weights[i] = weights[i];
    }
  for(int i=0;i<MLP_SIZE;i++)
    {
      _biases[i] = biases[i];
    }
}

digit MlpNetwork:: operator()(Matrix input) const
{
  for(int i=0;i<MLP_SIZE-1;i++)
    {
      Dense layer(_weights[i],_biases[i],RELU);
      input = layer(input);
    }
  Dense layer(_weights[3],_biases[3],SOFTMAX);
  input = layer(input);
  input.plain_print();
  digit result{0, input[0]};
  for(int i=1; i<input.get_rows();i++)
    {
      if(result.probability < input[i])
        {
          result.value = i;
          result.probability = input[i];
        }
    }
  return result;
}