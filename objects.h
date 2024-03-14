#pragma once
#include <iostream>
#include <iomanip>
#include <cmath>
#include "object.h"
#include "space.h"
#include "list.h"
#include "element.h"
#include "positions.h"

class Objects
{
private:
    Object * head;                                                   // Head pointer: points to the first Object
    Object * curr;                                                   // Points to current Object
public:
   ~Objects();                                                       // Destructor
    Objects();                                                       // Default constructor
    Objects(Object*);                                                // Parameterized constructor
    Objects(Object object);                                          // Parameterized constructor 
    Objects(const Objects &other);                                   // Copy constructor
    
    void insert(      Object *, int);                                // Insert @ position
    void insert(const Object &, int);                                // Insert @ position        <- Delegates to Existing ^
    bool insert(      Object *     );                                // Sorted Insertion Mutator
    bool insert(const Object &     );                                // Sorted Insertion Mutator <- Delegates to Existing ^
    
    void clear();                                                    // Deallocate memory of the linked string - completely empty the string.
    void remove(      int      );                                    // Remove at position
    bool remove(      Object *);                                     // Remove by value
    bool remove(const Object &);                                     // Remove by value <- Delegates to Existing ^ 

    void importObjects(const Matrix &);
    void importObjects(const Matrix &, const Element &);
    void importObjects(const Space &);
    void importObjects(const Space &,  const List &);
    void importCSVs(const List &);
    void importCSVs(const List &, const List &);

    void print();                                                    // Display information about the Objects  
    
    int  size() const;                                               // Size Accessor - Returns size of Objects
    int  sizeOfLargestObject() const;                                // Get size of largest object in the Objects
    inline bool isEmpty() const {return head == nullptr;};

    inline const Object * getHead()    const {return head;};         // Get Head
    inline       Object * getHead()          {return head;};         // Get Head
    inline       Object * setHead()    const {return head;};         // Set Head  
    
                                                                      //*Operator Overload Functions
    Objects & operator= (const Objects  &other);                      // Copy assignment operator
    Objects & operator= (      Objects &&other);                      // Move assignment operator
    Objects   operator+ (const Objects  &other) const;                // Addition operator
    bool     operator==(const Objects  &other) const;                 // Equality operator
    bool     operator!=(const Objects  &other) const;                 // Inequality operator
};
