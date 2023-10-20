#pragma once
#include <iostream>
#include "element.h"
#include "matrix.h"

class Object {
private:
    Matrix matrix; // Matrix to represent the object
    Element name;  // Name of the object

public:
    Object();
    Object(Element, int, int);           // Param Constructor

    void rename(const Element &);

    void print() const ;

    void setMatrixValue(int row, int col, const Element &);
    void setMatrixValues(const Element &);

    void setAllMatrixValues_UpperLeftToBottomRight(const Element &);
    void setAllMatrixValues_UpperRightToBottomLeft(const Element &);
    void setAllMatrixValues_BottomLeftToUpperRight(const Element &);
    void setAllMatrixValues_BottomRightToUpperLeft(const Element &);
    
    void setMatrixValuesDiagonal_UpperLeftToBottomRight(const Element &);
    void setMatrixValuesDiagonal_UpperRightToBottomLeft(const Element &);
    void setMatrixValuesDiagonal_BottomLeftToUpperRight(const Element &);
    void setMatrixValuesDiagonal_BottomRightToUpperLeft(const Element &);

    inline int  getNumRows() const {return matrix.getNumRows();};
    inline int  getNumCols() const {return matrix.getNumCols();};
    
    inline Matrix &getMatrix()     {return matrix;};
    inline Element &getName()      {return name;};
};
