// Matrix.h

#ifndef MATRIX_H
#define MATRIX_H

#include <cstring>
#include <iostream>
#include <cmath>
#include <fstream>
/**
 * @struct matrix_dims
 * @brief Matrix dimensions container. Used in MlpNetwork.h and main.cpp
 */
typedef struct matrix_dims{
    int rows, cols;
} matrix_dims;

/**
 * @class Matrix
 * @brief Matrix class. Holds Dimension and 1-D array of floats.
 * supports  Transpose, Vectorize,Dot product,Finding Norm, Plain Print
 * and reading from binary file.
 * supports overloaded operators s.t +,=,+=,A*B,c*A,A*c,
 * {[],()} indexing(const & non-const), <<.
 */
class Matrix {
 public:
  /* Constructor*/
  Matrix (int rows, int cols);
  /* Default Constructor*/
  Matrix ();
  /* Copy Constructor */
  Matrix (const Matrix &other);
  /* Destructor */
  ~Matrix ();

  // Getters
  int get_rows() const;
  int get_cols() const;

  // Methods & Functions
  /*Transpose*/
  Matrix& transpose();
  /*Vectorize*/
  Matrix& vectorize();
  /*Matrix plain print function*/
  void plain_print() const;
  /*Matrix dot multiplication*/
  Matrix dot(Matrix &m);
  /*Returns the norm of Matrix*/
  float norm() const;
  /*Input stream function */
  friend std::ifstream& read_binary_file(std::ifstream& is, Matrix &m);

  // Operators
  /*Matrix addition*/
  Matrix operator+(const Matrix &b) const;
  /* Assignment */
  Matrix& operator= (const Matrix &other);
  /* Matrix multiplication */
  Matrix operator*(const Matrix &b) const;
  /* Scalar multiplication on the right */
  Matrix operator*(float c);
  /* Scalar multiplication on the left */
   friend Matrix operator*(float c, Matrix &rhs);
  /*Matrix addition accumulation*/
  Matrix& operator+=(const Matrix& rhs);
  /* const Brackets indexing */
  float operator[] (int i) const;
  /* Brackets indexing */
  float& operator[] (int i);
  /* Parenthesis indexing */
  float& operator() (int i,int j);
  /* const Parenthesis indexing */
  float operator() (int i,int j) const;
  /*Output stream*/
  friend std::ostream& operator<<(std::ostream& os,const Matrix& m);

 private:
  int _rows;   /*integer for Row Dimension*/
  int _cols;  /*integer for Column Dimension*/
  float *_mat;  /*1-D Array of floats that represents Matrix (2D-Array)*/
};


#endif //MATRIX_H
