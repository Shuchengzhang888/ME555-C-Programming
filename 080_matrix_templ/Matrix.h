#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>
#include <iostream>
#include <vector>
#include <cstdlib>


//YOUR CODE GOES HERE!
template<typename T> 
class Matrix{
  private:
    int numRows;
    int numColumns;
    //new ??
    std::vector<std::vector<T> > rows;
 public:
    Matrix();
    Matrix(int r, int c);
    Matrix(const Matrix & rhs);
    ~Matrix();
    Matrix & operator=(const Matrix & rhs);
    int getRows() const;
    int getColumns() const;
    const std::vector<T> & operator[](int index) const;
    std::vector<T> & operator[](int index);
    bool operator==(const Matrix & rhs) const;
    Matrix operator+(const Matrix & rhs) const;
    // friend std::ostream & operator<<(std::ostream & s, const std::vector<T> & rhs);
    // friend std::ostream & operator<<(std::ostream & s, const Matrix & rhs);

};

template<typename T> 
std::ostream & operator<<(std::ostream & s, const std::vector<T> & row);
template<typename T> 
std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs);



template<typename T> 
Matrix<T>::Matrix(): numRows(0), numColumns(0) {}

template<typename T>
Matrix<T>::Matrix(int r, int c): numRows(r), numColumns(c){
    for (int i = 0; i < numRows; i++){
        //Build a vector "row" with c column, put "row" in "rows" r times
        std::vector<T> row(c);
        rows.push_back(row);
    }
}

template<typename T>
Matrix<T>::Matrix(const Matrix & rhs){
    numRows = rhs.numRows;
    numColumns = rhs.numColumns;
    rows = rhs.rows;
}

template<typename T>
Matrix<T>::~Matrix(){}

template<typename T>
Matrix<T> & Matrix<T>::operator=(const Matrix & rhs){
    if(this != & rhs){
        rows.clear();
        numRows = rhs.numRows;
        numColumns = rhs.numColumns;
        rows = rhs.rows;
    }
    return *this;
}

template<typename T>
int Matrix<T>::getRows() const{
    return numRows;
}

template<typename T>
int Matrix<T>::getColumns() const{
    return numColumns;
}

template<typename T>
const std::vector<T> & Matrix<T>::operator[](int index) const{
    assert((index >= 0) && (index < numRows));
    return rows[index];
}

template<typename T>
std::vector<T> & Matrix<T>::operator[](int index){
    assert((index >= 0) && (index < numRows));
    return rows[index];
}

template<typename T>
bool Matrix<T>::operator==(const Matrix<T> & rhs) const{
    if (numRows != rhs.numRows || numColumns != rhs.numColumns || rows != rhs.rows){
        return false;
    }
    return true;
}
template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> & rhs) const{
    assert((numRows == rhs.numRows) && (numColumns == rhs.numColumns));
    Matrix<T> res(numRows, numColumns);
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numColumns; j++) {
            res[i][j] = rows[i][j] + rhs[i][j];
        }
    }
    return res;
  }

template<typename T> 
std::ostream & operator<<(std::ostream & s, const std::vector<T> & row){
    s << "{";
    for(size_t i = 0; i < row.size(); i++){
        s << row[i];
        if (i != row.size() - 1){
            s << ",";
        }
    }
    s << "}";
    return s;
}

template<typename T> 
std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs){
    s << "[";
    for(int i = 0; i < rhs.getRows(); i++){
        //Next fuction is used here
        s << rhs[i];
        if(i != rhs.getRows() - 1){
            s << ", \n";
        }
    }
    s << "]";
    return s;
}

#endif
