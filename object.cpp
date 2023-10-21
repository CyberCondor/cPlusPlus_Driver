#include "object.h"

Object::Object() : matrix(), name("NULL")
{
    // Default Constructor - Delegate to existing default constructors. Object is null.
}
Object::Object(Element name, int numRows, int numCols) : matrix(numRows, numCols, Element(" ")), name(name)
{
    // Initialize the matrix with the specified number of rows and columns
}

void Object::rename(const Element & name)
{
    Element e(name); //// ~!!!!!!!!! need Element copy and move constructors for this->name = name;
    this->name.setData(e.getData());
}

void Object::print() const {
    std::cout << "Object: ";
    std::cout << name << std::endl; // Print the name using the Element class
    this->matrix.print();           // Delegate printing to the matrix
}

void Object::setMatrixValue(int row, int col, const Element & value)
{
    if(row < matrix.getNumRows() && col < matrix.getNumCols()) {
        Element e = value; 
        matrix.setValue(row, col, e);
    }
}
void Object::setMatrixValues(const Element & value)
{
    matrix.setValues(value);
}

void Object::setAllMatrixValues_BottomRightToUpperLeft(const Element & value)
{
    matrix.setValues_BottomRightToUpperLeft(value);
}
void Object::setAllMatrixValues_BottomLeftToUpperRight(const Element & value)
{
    matrix.setValues_BottomLeftToUpperRight(value);
}
void Object::setAllMatrixValues_UpperLeftToBottomRight(const Element & value)
{
    matrix.setValues_UpperLeftToBottomRight(value);
}
void Object::setAllMatrixValues_UpperRightToBottomLeft(const Element & value)
{
    matrix.setValues_UpperRightToBottomLeft(value);
}

void Object::setMatrixValuesDiagonal_BottomRightToUpperLeft(const Element & value)
{
    matrix.setValuesDiagonal_BottomRightToUpperLeft(value);
}
void Object::setMatrixValuesDiagonal_BottomLeftToUpperRight(const Element & value)
{
    matrix.setValuesDiagonal_BottomLeftToUpperRight(value);
}
void Object::setMatrixValuesDiagonal_UpperLeftToBottomRight(const Element & value)
{
    matrix.setValuesDiagonal_UpperLeftToBottomRight(value);
}
void Object::setMatrixValuesDiagonal_UpperRightToBottomLeft(const Element & value)
{
    matrix.setValuesDiagonal_UpperRightToBottomLeft(value);
}
