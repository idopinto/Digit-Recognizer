
#include "Matrix.h"
#include <cmath>

using std::cout;
using std::endl;
using std::cerr;

#define DIM_ERR "Invalid dimensions exiting with code 1"
#define THRESHOLD 0.1

Matrix::Matrix (int rows, int cols) : _rows (rows), _cols (cols)
{
  _mat = new float[_rows * _cols]{0};
}

Matrix::Matrix () : Matrix (1, 1)
{}

Matrix::Matrix (const Matrix &other)
{
  this->_rows = other._rows;
  this->_cols = other._cols;
  this->_mat = new float[_rows * _cols];
  for (int i = 0; i < _rows * _cols; ++i)
    {
      this->_mat[i] = other._mat[i];
    }
}

int Matrix:: get_rows() const
{
  return this->_rows;
}

int  Matrix:: get_cols() const
{
  return this->_cols;
}

Matrix::~Matrix ()
{
  delete[] _mat;
}

void swap(int &a,int &b)
{
  int temp = a;
  a = b;
  b = temp;
}

Matrix& Matrix:: transpose ()
{
  auto *t = new float[_rows*_cols];
  for (int i = 0; i < _rows; ++i)
    {
      for (int j = 0; j < _cols; ++j)
        {
          t[j*_rows+i] = _mat[i*_cols + j];
        }
    }
    delete[] _mat;
  this->_mat = t;
  swap(_rows,_cols);
  return *this;
}

Matrix& Matrix:: vectorize ()
{
  _rows = _rows * _cols;
  _cols = 1;
  return *this;
}

void Matrix:: plain_print () const
{
  for (int i = 0; i < _rows; ++i)
    {
      for (int j = 0; j < _cols; ++j)
        {
          cout << _mat[i * _cols + j] << " ";
        }
      cout << endl;
    }
}

Matrix Matrix:: dot (Matrix &m)
{

  if (m._rows == _rows && m._cols == _cols)
    {
      Matrix dot_product (_rows, _cols);
      for (int i = 0; i < _rows*_cols; ++i)
        {
          dot_product[i] = _mat[i] * m._mat[i];
        }
      return dot_product;
    }
  cerr<<DIM_ERR<<endl;
  exit (EXIT_FAILURE);
}

float Matrix:: norm () const
{
  float sum = 0;
  for (int i = 0; i < _rows*_cols; ++i)
    {
      sum += _mat[i]*_mat[i];
    }
  return (float)std::sqrt (sum);
}

std::ifstream& read_binary_file(std::ifstream& is, Matrix &m)
{
  is.seekg(0,is.beg);
  unsigned long size = m._cols * m._rows*sizeof(float);
  is.read ((char*)m._mat,(long)size);
  if(size == is.tellg())
    {
      return is;
    }
  cout<<"Error: couldn't read file"<<endl;
  return is;
}


Matrix Matrix:: operator+ (const Matrix &b) const
{
  if(_rows == b._rows && _cols == b._cols)
    {
      Matrix add (_rows, _cols);
      for (int i = 0; i < _rows*_cols; ++i)
        {
          add[i] =this->_mat[i] + b[i];
        }
      return add;
    }
  std::cerr<<DIM_ERR<<endl;
  exit (EXIT_FAILURE);
}
Matrix& Matrix:: operator= (const Matrix &other)
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
Matrix Matrix:: operator* (const Matrix &b) const
{
  if (_cols != b._rows)
    {
      std::cerr<<DIM_ERR<<endl;
      exit (EXIT_FAILURE);
    }
  Matrix mult(_rows, b._cols);
  for (int i = 0; i < _rows; ++i)
    {
      for (int j = 0; j < b._cols; ++j)
        {
          for (int k = 0; k < _cols; ++k)
            {
              mult[i * mult._cols + j] +=\
              _mat[i *_cols + k] * b[k * b._cols + j];
            }
        }
    }
  return mult;
}
Matrix Matrix:: operator*(float c)
{
  Matrix m(*this);
  for (int i = 0; i <_rows*_cols; ++i)
    {
      m[i] *=c;
    }
  return m;
}
Matrix operator*(float c, Matrix &rhs)
{
  Matrix m(rhs);
  for (int i = 0; i < rhs._rows*rhs._cols; ++i)
    {
        m[i] *=c;
    }
  return m;
}
Matrix& Matrix:: operator+=(const Matrix& rhs)
{
  if(_rows == rhs._rows && _cols == rhs._cols)
    {
      for (int i = 0; i < _rows; ++i)
        {
          for (int j = 0; j < _cols; ++j)
            {
              _mat[i * _cols + j] += rhs[i * _cols + j];
            }
        }
      return *this;
    }
  std::cerr<<DIM_ERR<<endl;
  exit (EXIT_FAILURE);
}

float Matrix::operator() (int i, int j) const
{
  return _mat[i*_cols+j];
}
float& Matrix::operator() (int i, int j)
{
  return _mat[i*_cols+j];
}

float Matrix::operator[] (int i) const
{
  return _mat[i];
}
float& Matrix::operator[] (int i)
{
  return _mat[i];
}

std::ostream &operator<< (std::ostream &os, const Matrix &m)
{
  for(int i=0;i<m._rows;++i)
    {
      for(int j = 0;j< m._cols;++j)
        {
          if(m(i,j) >= THRESHOLD)
            {
              cout<<"  ";
            }
          else
            {
              cout<<"**";
            }
        }
        cout<<std::endl;
    }
  return os;
}
