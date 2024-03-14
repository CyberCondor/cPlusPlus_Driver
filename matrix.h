#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include "list.h"
#include "element.h"
#include "positions.h"
#include "position.h"

// A matrix is also known as a 2D plane - it's just a plot of points or like an Excel spreadsheet.
class Matrix {
private:
    Positions * X;
    Positions * Y;
    List      * rows;    // List of rows
    List      * columns; // List of columns
    int         numRows; // Number of rows
    int         numCols; // Number of columns
    Position    position;// Position in 3D space
    Matrix    * next;    // Next element to traverse 3D space
public:
    ~Matrix();                              // Destructor!
    Matrix();                               // Default Constructor    
    Matrix(const Matrix   &);               // Copy    Constructor    
    Matrix(      Matrix   *);               // Param   Constructor    
    Matrix(const Position &);               // Constructor to create a 1x1 matrix with z specified
    Matrix(int);                            // Constructor to create a 1x1 matrix with z specified
    Matrix(int, int);                       // Constructor to create a matrix with the specified number of rows and columns
    Matrix(int, int, int);                  // Constructor to create a matrix with the specified number of rows and columns and z
    Matrix(int, int,      const Element  &);// Constructor to create a matrix with the specified number of rows and columns & a default Element
    Matrix(int, int, int, const Element  &);// Constructor to create a matrix with the specified number of rows and columns & a default Element
    Matrix(const char * filePath);

    bool importCsv(const char * filePath);

    void transpose();

    void resize(int, int);

    Positions getPositions(const Element &) const;

    Matrix getMatrixWhereElementIs        (const Element &) const;
    Matrix getMatrixWhereElementIs_i      (const Element &) const;
    Matrix getMatrixWhereElementLike      (const Element &) const;
    Matrix getMatrixWhereElementLike_i    (const Element &) const;
    Matrix getMatrixWhereElementContains  (const Element &) const;
    Matrix getMatrixWhereElementContains_i(const Element &) const;
    Matrix getMatrixWhereElementInPositions(Positions) const;

    Matrix getPropertyFrequencies() const;
    Matrix getPropertyFrequencies(const Element & propertyKey) const;

    void consolidateEmptyPositions();
    int removeEmptyRows();
    bool removeRow(int);
    bool removeColumn(int);

    Element getValue  (int, int) const;
    Element getValue_i(int, int) const;
    void    setValue  (int, int, const Element &);
    void    setValues (          const Element &);

    void print()                   const;
    void printPositions()          const;
    void printEachPosition()       const;

    void printRowPositions()       const;
    void printColPositions()       const;

    void printRowPositionsRaw()    const;
    void printColPositionsRaw()    const;

    void printPositionsCrawlLeft() const;
    void printPositionsCrawlRight()const;

    void printPositionsSlopeLeft() const;
    void printPositionsSlopeRight()const;

    void printRow    (int) const;       // Print a specific row    no new line
    void printColumn (int) const;       // Print a specific column no new line
    void prettyRow   (int) const;       // Print a specific row       new line
    void prettyColumn(int) const;       // Print a specific column    new line

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

    inline int        getNumRows()    const {return numRows;};
    inline int        getNumCols()    const {return numCols;};
    inline Position   getPosition()   const {return position;};
    inline void     setPosition(  const Position & pos) {
                            this->position.setX(pos.getX());
                            this->position.setY(pos.getY());
                            this->position.setZ(pos.getZ());};

    inline List *getRows()    const {return rows;};
    inline List *getColumns() const {return columns;};

    inline const Matrix * getNext() const{return next;};
    inline       Matrix * getNext()      {return next;};
    inline       Matrix * setNext(Matrix * direction)         // Setter for the next Position in the linked list
                    {this->next = direction;return this;};
    
    inline int size() const {return this->numRows * this->numCols;};

    Matrix & operator= (const Matrix &other);         // Copy assignment operator
    bool     operator==(const Matrix  &other) const;  // Equality operator
    bool     operator!=(const Matrix  &other) const;  // Equality operator
};
