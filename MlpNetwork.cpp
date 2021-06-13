#include "MlpNetwork.h"

MlpNetwork:: MlpNetwork(Matrix *weights,Matrix *biases): _weights(weights),
                                                          _biases(biases){}

void make_prob_vec(Matrix &input,Matrix *weights,Matrix *biases)
{
  ActivationType arr[MLP_SIZE] = {RELU,RELU,RELU,SOFTMAX};
  for(int i=0;i<MLP_SIZE;i++)
    {
      Dense layer(weights[i],biases[i],arr[i]);
      input = layer(input);
    }

}
digit find_max_prob(Matrix m)
{
  digit result{0, m[0]};
  for(int i=1; i<m.get_rows();i++)
    {
      if(result.probability < m[i])
        {
          result.value = i;
          result.probability = m[i];
        }
    }
    return result;
}

digit MlpNetwork:: operator()(Matrix input)
{
  make_prob_vec (input,_weights,_biases);
  return find_max_prob (input);
}