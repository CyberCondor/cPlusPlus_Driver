#include "object.h"

void Object::rename(const Element & name)
{
    Element e(name); //// ~!!!!!!!!! need Element copy and move constructors for this->name = name;
    this->name.setData(e.getData());
    this->properties.insert(Element("Name"),e);
    //this->setMatrixValues(e);
}

void Object::print() const
{
    std::cout << "Object: ";
    std::cout << name << "\n" << std::endl; // Print the name using the Element class
    this->properties.print();
    if(this->matrix.getNumRows() > 1) {
        this->matrix.print();           // Delegate printing to the matrix
    }
    if(this->space.size() > 0) {
        this->space.print();            // Delegate printing to object space
    }
}


void Object::setDefaultProperties()
{
    this->properties.setDefault();
}

bool Object::addProperty(const Property & property)
{
    return this->properties.insert(property);
}
bool Object::addProperty(const Element & key)
{
    return this->properties.insert(key);
}
bool Object::addProperty(const Element & key, const Element & value)
{
    return this->properties.insert(key, value);
}
bool Object::addProperty(const Element & key, const String & value)
{
    return this->properties.insert(key, value);
}
bool Object::setProperty(const Property & property)
{
    return this->properties.insert(property);
}
bool Object::setProperty(const Element & key, const Element & value)
{
    return this->properties.insert(key, value);
}
bool Object::setProperty(const Element & key, const String & value)
{
    return this->properties.insert(key, value);
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
