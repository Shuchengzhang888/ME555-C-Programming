#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>
#include <iostream>
#include <vector>
#include <cstdlib>


//YOUR CODE GOES HERE!
template<typename T>
class Matrix {
 private:
  int numRows;
  int numColumns;
  std::vector<std::vector<T> > rows;

 public:
  Matrix() : numRows(0), numColumns(0) {}
  Matrix(int r, int c) : numRows(r), numColumns(c) {
    for (int i = 0; i < numRows; i++) {
      std::vector<T> row(c);
      rows.push_back(row);
    }
  }
  Matrix(const Matrix & rhs) : numRows(rhs.numRows), numColumns(rhs.numColumns) {
    rows = rhs.rows;
  }
  ~Matrix() {}
  Matrix & operator=(const Matrix & rhs) {
    if (this != &rhs) {
      rows.clear();
      numRows = rhs.numRows;
      numColumns = rhs.numColumns;
      rows = rhs.rows;
    }
    return *this;
  }
  int getRows() const { return numRows; }
  int getColumns() const { return numColumns; }
  const std::vector<T> & operator[](int index) const {
    assert((index >= 0) && (index < numRows));
    return rows[index];
  }
  std::vector<T> & operator[](int index) {
    assert((index >= 0) && (index < numRows));
    return rows[index];
  }

  bool operator==(const Matrix & rhs) const {
    if (numRows != rhs.numRows || numColumns != rhs.numColumns) {
      return false;
    }

    if (rows != rhs.rows) {
      return false;
    }
    return true;
  }

  Matrix operator+(const Matrix & rhs) const {
    assert((numRows == rhs.numRows) && (numColumns == rhs.numColumns));
    Matrix res(numRows, numColumns);
    for (int i = 0; i < numRows; i++) {
      for (int j = 0; j < numColumns; j++) {
        res[i][j] = rows[i][j] + rhs[i][j];
      }
    }
    return res;
  }
};

template<typename T>
std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs) {
  if (rhs.getRows() == 0) {
    s << "[ ]";
    return s;
  }
  s << "[ ";
  for (int i = 0; i < rhs.getRows(); i++) {
    s << rhs[i];

    if (i != rhs.getRows() - 1) {
      s << ", \n";
    }
  }
  s << " ]";
  return s;
}
template<typename T>
std::ostream & operator<<(std::ostream & s, const std::vector<T> & rhs) {
  s << "{";
  for (size_t i = 0; i < rhs.size(); i++) {
    s << rhs[i];

    if (i != rhs.size() - 1) {
      s << ",";
    }
  }
  s << "}";
  return s;
}
#endif
