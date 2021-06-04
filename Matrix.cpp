
#include "Matrix.h"
#define DIM_ERR "Invalid dimensions exiting with code 1"

Matrix::Matrix (int rows, int cols) : _rows (rows), _cols (cols)
{
  _mat = new float[_rows * _cols];
  for (int i = 0; i < _rows * _cols; ++i)
    {
      _mat[i] = 0;
    }
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

Matrix& Matrix:: transpose ()
{
  float *mat = this->_mat;
  int temp = _rows;
  _rows = _cols;
  _cols = temp;
  for (int i = 0; i < _rows; ++i)
    {
      for (int j = 0; j < _cols; ++j)
        {
          this->_mat[i * _cols + j] = mat[j * _rows + i];
        }
    }

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

// check if need by ref
Matrix Matrix:: dot (Matrix &m)
{

  if (m._rows == _rows && m._cols == _cols)
    {
      Matrix dot_product (_rows, _cols);
      for (int i = 0; i < _rows; ++i)
        {
          for (int j = 0; j < _cols; ++j)
            {
              dot_product[i * _cols + j] =
                  _mat[i * _cols + j] * m._mat[i * _cols + j];
            }
        }
      return dot_product;
    }
  std::cerr<<" Invalid dimensions exiting with code 1"<<endl;
  exit (EXIT_FAILURE);
}
// Norm
float Matrix:: norm () const
{
  float sum = 0;
  for (int i = 0; i < _rows; ++i)
    {
      for (int j = 0; j < _cols; ++j)
        {
          sum += (float) pow (_mat[i * _cols + j], 2.0);
        }
    }
  return sqrt (sum);
}

std::istream &Matrix::read_binary_File (std::istream, Matrix m)
{
  return <#initializer#>;
}


Matrix Matrix:: operator+ (const Matrix &b) const
{
  if(_rows == b._rows && _cols == b._cols)
    {
      Matrix add (_rows, _cols);
      for (int i = 0; i < _rows; ++i)
        {
          for (int j = 0; j < _cols; ++j)
            {
              add[i * _cols + j] = this->_mat[i * _cols + j] + b[i * _cols + j];
            }
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
              mult[i * mult._cols + j] +=
                  _mat[i *_cols + k] * b[k * b._cols + j];
            }
        }
    }
  return mult;
}
Matrix& Matrix:: operator*(float c)
{
  for (int i = 0; i < _rows; ++i)
    {
      for (int j = 0; j <_cols; ++j)
        {
          _mat[i * _cols + j] *= c;
        }
    }
  return *this;
}
Matrix& operator*(float c, Matrix &rhs)
{
  for (int i = 0; i < rhs._rows; ++i)
    {
      for (int j = 0; j < rhs._cols; ++j)
        {
          rhs._mat[i * rhs._cols + j] *= c;
        }
    }
  return rhs;
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

const float &Matrix::operator() (int i, int j) const
{
  return _mat[i*_cols+j];
}
float &Matrix::operator() (int i, int j)
{
  return _mat[i*_cols+j];
}

const float& Matrix::operator[] (int i) const
{
  return _mat[i];
}
float& Matrix::operator[] (int i)
{
  return _mat[i];
}

std::ostream &operator<< (ostream &os, const Matrix &m)
{
  for(int i=0;i<m._rows;++i)
    {
      for(int j = 0;j< m._cols;++j)
        {
          if(m(i,j) >= 0.1)
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
