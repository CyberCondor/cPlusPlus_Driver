#pragma once
#include <iostream>
#include <iomanip>
#include "list.h"
#include "element.h"

class Matrix {
private:
    List * rows;    // List of rows
    List * columns; // List of columns
    int    numRows; // Number of rows
    int    numCols; // Number of columns

public:
    ~Matrix();                         // Destructor!
    Matrix();                          // Default Constructor    
    Matrix(int, int);                  // Constructor to create a matrix with the specified number of rows and columns
    Matrix(int, int, const Element &); // Constructor to create a matrix with the specified number of rows and columns & a default Element

    void transpose();

    void resize(int, int);

    Element getValue (int, int) const;
    void    setValue (int, int, const Element &);
    void    setValues(const Element &);

    void print() const;

    void printRow   (int) const;       // Print a specific row
    void printColumn(int) const;       // Print a specific column

    void printIntersection(int, int) const;
    void printIntersections()        const;

    void setValues_BottomRightToUpperLeft(const Element &);
    void setValues_BottomLeftToUpperRight(const Element &);
    void setValues_UpperLeftToBottomRight(const Element &);
    void setValues_UpperRightToBottomLeft(const Element &);
    
    void setValuesDiagonal_BottomRightToUpperLeft(const Element &);
    void setValuesDiagonal_BottomLeftToUpperRight(const Element &);
    void setValuesDiagonal_UpperLeftToBottomRight(const Element &);
    void setValuesDiagonal_UpperRightToBottomLeft(const Element &);

    inline int getNumRows() const {return numRows;};
    inline int getNumCols() const {return numCols;};

};
