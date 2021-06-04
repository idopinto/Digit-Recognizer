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
  Matrix (int rows, int cols);

  // Default c'tor
  Matrix ();

  // Copy c'tor
  Matrix (const Matrix &other);
  // Destructor
  ~Matrix ();

  // Getters
  int get_rows() const;
  int get_cols() const;

  // methods & functions
  Matrix& transpose(); // FIXME
  Matrix& vectorize();
  void plain_print() const;
  Matrix dot(Matrix &m);
  float norm() const;
  std::istream& read_binary_File(std::istream, Matrix m);

  // operators
  Matrix operator+(const Matrix &b) const; /*Matrix addition*/
  Matrix &operator= (const Matrix &other); /* Assignment */
  Matrix operator*(const Matrix &b) const;/* Matrix multiplication */
  Matrix& operator*(float c);/* Scalar multiplication on the right */
  friend Matrix& operator*(float c, Matrix &rhs); /* Scalar multiplication on the left */
  float& operator() (int i,int j);/* Parenthesis indexing */
  const float& operator[] (int i) const;/* const Parenthesis indexing */
  float& operator[] (int i); /* Brackets indexing */
  const float& operator() (int i,int j) const; /*Output stream*/


  Matrix& operator+=(const Matrix& rhs);/*Matrix addition accumulation*/
  friend std::ostream& operator<<(std::ostream& os,const Matrix& m);

 private:
  int _rows;
  int _cols;
  float *_mat;

};


#endif //MATRIX_H
