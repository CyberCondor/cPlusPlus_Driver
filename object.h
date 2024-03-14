#pragma once
#include <iostream>
#include "element.h"
#include "string.h"
#include "matrix.h"
#include "space.h"
#include "position.h"
#include "property.h"
#include "properties.h"

class Object {
private:
    Element    name;        // Name of the Object
    Space      space;       // 3D Space to represent the Object.
    Matrix     matrix;      // 2D Matrix to represent the Object.
    Properties properties;  // Properties to define properties of the Object
    Position   position;    // Position to locate the Object in Space.
    Object * next;
public:
    inline Object() : name("NULL"), space(), matrix(), properties(), position(){};

    inline Object(const Element & name)                           : name(name),   // Param Constructor
                                                                    space(name),
                                                                    matrix(), 
                                                                    //matrix(3,3,name), 
                                                                    properties(), 
                                                                    position()
                                                                   {this->properties.insert(Element("Name"),Element(name));};
    
    inline Object(const Element & name, int numRows, int numCols) : name(name),   // Param Constructor
                                                                    space(numRows, numCols, name), 
                                                                    matrix(numRows, numCols, name), 
                                                                    properties(),
                                                                    position()
                                                                   {this->properties.insert(Element("Name"),Element(name));};
    
    inline Object(const Element & name, Space &space)             : name(name),   // Param Constructor
                                                                    space(space), 
                                                                    matrix(), 
                                                                    properties(),
                                                                    position()
                                                                   {this->properties.insert(Element("Name"),Element(name));};
    
    inline Object(const Element & name, Matrix &matrix)           : name(name),   // Param Constructor
                                                                    space(), 
                                                                    matrix(matrix), 
                                                                    properties(),
                                                                    position()
                                                                   {};
    
    inline Object(const Element & name, const Matrix &matrix)           : name(name),   // Param Constructor
                                                                    space(), 
                                                                    matrix(matrix), 
                                                                    properties(),
                                                                    position()
                                                                   {};
    inline       Object * setNext(Object * direction)
                    {this->next = direction;return this;};        // Set pointer to next
    
    inline const Object * getNext() const {return next;};         // Get Next
    inline       Object * getNext()       {return next;};         // Get Next
   
    inline int size(){return space.size();};
    inline int trueSize(){return space.trueSize() * space.size();};

    void rename(const Element &);

    void print() const ;

    inline void setPosition(const Position & pos) {
                            Element buffer = Element("(");
                            buffer += pos.getX();
                            buffer += Element(",");
                            buffer += pos.getY();
                            buffer += Element(")->");
                            buffer += pos.getZ();
                            this->properties.insert(Element("Position"),buffer);
                            this->position.setX(pos.getX());
                            this->position.setY(pos.getY());
                            this->position.setZ(pos.getZ());};

    void setDefaultProperties();
    bool addProperty(const Property &);
    bool addProperty(const Element  &);
    bool addProperty(const Element  &, const Element &);
    bool addProperty(const Element  &, const String  &);
    bool setProperty(const Property &);
    bool setProperty(const Element  &, const Element &);
    bool setProperty(const Element  &, const String  &);
    inline void setProperties(const Properties & properties) {
                                this->properties = properties;}

    inline void setMatrix(const Matrix & matrix) {this->matrix = matrix;}

    inline void setName(const Element & name) {this->name = name;}

    inline void setSpace(const Space & space) {this->space = space;}

    void setMatrixValue (int row, int col, const Element &);
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
    
    inline Element    const getName()       const {return name;      };
    inline Matrix     const getMatrix()     const {return matrix;    };
    inline Space      const getSpace()      const {return space;     };
    inline Position   const getPosition()   const {return position;  };
    inline Properties const getProperties() const {return properties;};
    inline Element         &getName()             {return name;      };
    inline Matrix          &getMatrix()           {return matrix;    };
    inline Space           &getSpace()            {return space;     };
    inline Position        &getPosition()         {return position;  };
    inline Properties      &getProperties()       {return properties;};

    inline bool operator==(const Object  &other) const {return this->name == other.getName();};                      // Equality operator
};
