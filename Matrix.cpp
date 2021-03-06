
#include "Matrix.h"

using std::cout;
using std::endl;
using std::cerr;

#define DIM_ERR "Invalid dimensions exiting with code 1"
#define FILE_ERR "Error: Couldn't read full file existing with code 1"
#define MEM_ERR "Error: Memory allocation failure"
#define THRESHOLD 0.1

/**
 * Constructor
 * */
Matrix::Matrix (int rows, int cols) : _rows (rows), _cols (cols)
{
  _mat = new (std::nothrow)float[_rows * _cols];
  if(_mat == nullptr)
    {
      cerr<< MEM_ERR <<endl;
      exit(EXIT_FAILURE);
    }
  for(int i=0;i<_rows*_cols;++i)
    {
      _mat[i] = 0;
    }
}
/**
 * Default Constructor
 * */
Matrix::Matrix () : Matrix (1, 1)
{}

/**
 * Copy Constructor
 * */
Matrix::Matrix (const Matrix &other)
{
  this->_rows = other._rows;
  this->_cols = other._cols;
  this->_mat = new(std::nothrow)float[_rows * _cols];
  if(_mat == nullptr)
    {
      cerr<< MEM_ERR<<endl;
      exit(EXIT_FAILURE);
    }
  for (int i = 0; i < _rows * _cols; ++i)
    {
      this->_mat[i] = other._mat[i];
    }
}

/**
 * Destructor
 * */
Matrix::~Matrix ()
{
  delete[] _mat;
}
/**
 * returns # of rows
 **/
int Matrix:: get_rows() const
{
  return this->_rows;
}
/**
 * returns # of cols
 **/
int  Matrix:: get_cols() const
{
  return this->_cols;
}

/**
 * this function swaps two integers by reference
 **/
void swap(int &a,int &b)
{
  int temp = a;
  a = b;
  b = temp;
}

/**
 * Returns the transposed matrix
 * */
Matrix& Matrix:: transpose ()
{
  auto *t = new(std::nothrow)float[_rows*_cols];
  if(t == nullptr)
    {
      cerr<< MEM_ERR<<endl;
      exit(EXIT_FAILURE);
    }
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

/**
 * this function transform matrix mxn to vector (mxn) x 1
 * */
Matrix& Matrix:: vectorize ()
{
  _rows = _rows * _cols;
  _cols = 1;
  return *this;
}

/**
 * Matrix plain print function
 * */
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

/**
 * this function return new matrix which is dot product
 *
 **/
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
/**
 * Returns the norm of Matrix
 * */
float Matrix:: norm () const
{
  float sum = 0;
  for (int i = 0; i < _rows*_cols; ++i)
    {
      sum += _mat[i]*_mat[i];
    }
  return (float)std::sqrt (sum);
}

/**
 * Input stream function
 * */
void read_binary_file(std::istream& is, Matrix &m)
{
  is.seekg(0,std::istream::end);
  int n_bytes = is.tellg();
  is.seekg (0,std::istream::beg);
  unsigned int n = n_bytes / sizeof(float);
  if((unsigned int)(m.get_rows()*m.get_cols()) != n)
    {
      cerr<<FILE_ERR<<endl;
      exit (EXIT_FAILURE);
    }
  is.read ((char*)m._mat,n_bytes);
  if(is.gcount() != n_bytes)
    {
      cerr<<FILE_ERR<<endl;
      exit (EXIT_FAILURE);
    }
}

/**
 * Matrix addition
 * */
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
/**
 * Assignment
 * */
Matrix& Matrix:: operator= (const Matrix &other)
{
  if (this != &other)
    {
      // de-allocates old allocations
      delete[] _mat;
      //copy rows&cols
      this->_rows = other._rows;
      this->_cols = other._cols;
      this->_mat = new(std::nothrow) float[_rows * _cols];
      if(_mat == nullptr)
        {
          cerr<< MEM_ERR<<endl;
          exit(EXIT_FAILURE);
        }
      for (int i = 0; i < _rows * _cols; ++i)
        {
          this->_mat[i] = other._mat[i];
        }
    }
  return *this;
}

/**
 * Matrix multiplication
 * */
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
/**
 * Scalar multiplication on the right
 * */
Matrix Matrix:: operator*(float c)
{
  Matrix m(*this);
  for (int i = 0; i <_rows*_cols; ++i)
    {
      m[i] *=c;
    }
  return m;
}
/**
 * Scalar multiplication on the left
 * */
Matrix operator*(float c, Matrix &rhs)
{
  Matrix m(rhs);
  for (int i = 0; i < rhs._rows*rhs._cols; ++i)
    {
        m[i] *=c;
    }
  return m;
}

/**
 * Matrix addition accumulation
 * */
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
/**
 * Parenthesis indexing
 * */
float Matrix::operator() (int i, int j) const
{
  return _mat[i*_cols+j];
}
/**
 * const Parenthesis indexing
 * */
float& Matrix::operator() (int i, int j)
{
  return _mat[i*_cols+j];
}

/**
 * Brackets indexing
 * */
float Matrix::operator[] (int i) const
{
  return _mat[i];
}
/**
 * const Brackets indexing
 * */
float& Matrix::operator[] (int i)
{
  return _mat[i];
}
/**
 * Output stream
 * */
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
