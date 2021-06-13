#include "MlpNetwork.h"

/*constructor*/
MlpNetwork:: MlpNetwork(Matrix *weights,Matrix *biases): _weights(weights),
                                                          _biases(biases){}

/*returns the index of the maximum value in probability vector*/
void MlpNetwork:: make_prob_vec( Matrix &input)
{
  ActivationType arr[MLP_SIZE] = {RELU,RELU,RELU,SOFTMAX};
  for(int i=0;i<MLP_SIZE;i++)
    {
      Dense layer(_weights[i],_biases[i],arr[i]);
      input = layer(input);
    }

}
/*transforms matrix to probability vector*/
digit MlpNetwork:: find_max_prob(Matrix m)
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

/*parenthesis operator*/
digit MlpNetwork:: operator()(const Matrix& input)
{
  Matrix cpy_input(input);
  make_prob_vec (cpy_input);
  return find_max_prob (cpy_input);
}