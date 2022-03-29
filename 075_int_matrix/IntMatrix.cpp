#include "IntMatrix.h"


//A default constructor: it should initialize the matrix to have 0 rows and 0 columns.
IntMatrix::IntMatrix(): numRows(0), numColumns(0), rows(NULL){}

//A constructor that takes the number of rows and columns. 
//It should initialize the matrix to have the specified number of rows and columns.
IntMatrix::IntMatrix(int r, int c): numRows(r), numColumns(c), rows(new IntArray *[numRows]){
    for(int i = 0; i < numRows; i++){
        rows[i] = new IntArray(numColumns);
    }
}

//A copy constructor, which makes a deep copy.
IntMatrix::IntMatrix(const IntMatrix & rhs): numRows(rhs.numRows), numColumns(rhs.numColumns), rows(new IntArray *[rhs.numRows]){
    for(int i = 0; i < numRows; i++){
        rows[i] = new IntArray(rhs[i]);
    }
}

//A destructor, which frees any memory the Matrix has allocated.
IntMatrix::~IntMatrix(){
    for(int i = 0; i < numRows; i++){
        delete rows[i];
    }
    delete[] rows;
}

//An assignment operator, which makes a deep copy
IntMatrix & IntMatrix::operator=(const IntMatrix & rhs){
    if(this != &rhs){
        for(int i = 0; i < numRows; i++){
            delete rows[i];
        }
        delete[] rows;
        numRows = rhs.numRows;
        numColumns = rhs.numColumns;
        rows = new IntArray *[numRows];
        for(int i = 0; i < numRows; i++){
            rows[i] = new IntArray(rhs[i]);
        }
    }
    return *this;
}

//Returns the number of rows
int IntMatrix::getRows() const{
    return numRows;
}

//Returns the number of columns
int IntMatrix::getColumns() const{
    return numColumns;
}

// Uses assert() to check that index is valid, Returns a reference to the requested row.
IntArray & IntMatrix::operator[](int index){
    assert((index >= 0) && (index < numRows));
    return *rows[index];
}
const IntArray & IntMatrix::operator[](int index) const{
    assert((index >= 0) && (index < numRows));
    return *rows[index];
}

//Compares two matricies for equality. The matricies are equal if they have the same number of rows, the same number of columns, and each element is the same as the corresponding element in the other matrix. 
bool IntMatrix::operator==(const IntMatrix & rhs) const{
    if((numRows == rhs.numRows) && (numColumns == rhs.numColumns)){
        for(int i = 0; i < numRows; i++){
	  if((*this)[i] != rhs[i]){
                return false;
            }
        }
        return true;
    }
    return false;
}

//assert()s that this and rhs have the same dimensions.
//Returns matrix (also the same dimensions as this and rhs) whose elements are the sum of the corresponding elements of this matrix and rhs (does matrix addition).
IntMatrix IntMatrix::operator+(const IntMatrix & rhs) const{
    assert((numRows == rhs.numRows) && (numColumns == rhs.numColumns));
    IntMatrix a_matrix(numRows,numColumns);
    for(int i = 0; i < numRows; i++){
        for(int j = 0; j < numColumns; j++){
            a_matrix[i][j] = (*this)[i][j] + rhs[i][j];
        }
    }
    return a_matrix;
}

std::ostream & operator<<(std::ostream & s, const IntMatrix & rhs){
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
