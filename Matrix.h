// Matrix.h

#ifndef MATRIX_H
#define MATRIX_H

#include <cstring>
#include <iostream>
#include <cmath>
/**
 * @struct matrix_dims
 * @brief Matrix dimensions container. Used in MlpNetwork.h and main.cpp
 */
typedef struct matrix_dims {
    int rows, cols;
} matrix_dims;

// Insert Matrix class here...
using namespace std;

class Matrix {
 public:
  // Constructor
  Matrix (int rows, int cols) : _rows (rows), _cols (cols)
  {
    _mat = new float[_rows * _cols];
    for (int i = 0; i < _rows * _cols; ++i)
      {
        _mat[i] = 0;
      }
  }
  // Default c'tor
  Matrix () : Matrix (1, 1)
  {}

  // Copy c'tor
  Matrix (const Matrix &other)
  {
    this->_rows = other._rows;
    this->_cols = other._cols;
    this->_mat = new float[_rows * _cols];
    for (int i = 0; i < _rows * _cols; ++i)
      {
        this->_mat[i] = other._mat[i];
      }
  }

  // Destructor
  ~Matrix ()
  {
    delete[] _mat;
  }

  // Getters
  int get_rows() const
  {
    return this->_rows;
  }

  int get_cols() const
  {
    return this->_cols;
  }

  // Transpose()
  Matrix& transpose()
  {
    for(int j=0;j<_cols;++j)
      {
        for(int i=0;i<_rows;++i)
          {
            _mat[j*_rows+i] = _mat[i*_cols+j];
          }
      }
    return *this;
  }

  //Vectorize()
  Matrix& vectorize()
  {
    _rows = _rows *_cols;
    _cols  = 1;
    return *this;
  }

  // plain_print()
  void plain_print() const
  {
    for(int i=0;i<_rows;++i)
      {
        for(int j=0;j<_cols;++j)
          {
            cout<<_mat[i*_cols+j]<<" ";
          }
          cout<<endl;
      }
  }

  // Dot(Matrix)
  Matrix dot(Matrix &m)
  {

    if (m._rows == _rows && m._cols == _cols)
      {
        Matrix dot_product(_rows,_cols);
        for(int i=0;i<_rows;++i)
          {
            for(int j=0;j<_cols;++j)
              {
                dot_product[i*_cols+j] = _mat[i*_cols+j]*m._mat[i*_cols+j];
              }
          }
        return dot_product;
      }
    return nullptr;
  }
  // Norm
  float norm() const
  {
    float sum = 0;
    for(int i=0;i<_rows;++i)
      {
        for(int j=0;j<_cols;++j)
          {
            sum +=(float)pow(_mat[i*_rows+j],2.0);
          }
      }
    return sqrt (sum);
  }
//read_binary_File(istream, Matrix) friend i think

  // operator= copy assignment
  Matrix &operator= (const Matrix &other)
  {
    if (this != &other)
      {
        // de-allocates old allocations
        delete[] _mat;
        //copy rows&cols
        this->_rows = other._rows;
        this->_cols = other._cols;
        this->_mat = new float[_rows * _cols];
        for (int i = 0; i < _rows * _cols; ++i)
          {
            this->_mat[i] = other._mat[i];
          }
      }
    return *this;
  }

  Matrix operator+(const Matrix &a, const Matrix &b);

 private:
  int _rows;
  int _cols;
  float *_mat;

};

#endif //MATRIX_H
