#pragma once
#include <iostream>
#include <iomanip>
#include <cmath>
#include "element.h"
#include "position.h"
#include "matrix.h"

class Space
{
private:
    Matrix * head;                                                  // Head pointer: points to the first Matrix
    Matrix * curr;                                                  // Points to current Matrix
    size_t   totalMemUsed;                                          // Make program self-aware of how much memory it's using - Adds 8 bytes and calculation upon Space insert/remove to overhead 
public:
   ~Space();                                                        // Destructor
    Space();                                                        // Default constructor
    Space(Matrix*);                                                 // Parameterized constructor
    Space(Matrix);                                                  // Parameterized constructor
    Space(                     const Element &);                    // Parameterized constructor
    Space(int z,               const Element &);                    // Parameterized constructor
    Space(int z);                                                   // Parameterized constructor
    Space(int x, int y,        const Element &);                    // Parameterized constructor
    Space(int x, int y);                                            // Parameterized constructor
    Space(int x, int y, int z, const Element &);                    // Parameterized constructor
    Space(int x, int y, int z);                                     // Parameterized constructor
    Space(const Space &other);                                      // Copy constructor
    
    void insert(      Matrix *, int);                               // Insert @ position
    void insert(const Matrix &, int);                               // Insert @ position        <- Delegates to Existing ^
    bool insert(      Matrix *     );                               // Sorted Insertion Mutator
    bool insert(const Matrix &     );                               // Sorted Insertion Mutator <- Delegates to Existing ^
    
    void clear();                                                   // Deallocate memory of the linked space - completely empty the space.
    void remove(       int    );                                    // Remove at position
    bool remove(      Matrix *);                                    // Remove by value
    bool remove(const Matrix &);                                    // Remove by value <- Delegates to Existing ^ 
    
    void   print()  const;                                         // Display information about the Space  
    void   print(   const Matrix &);                               // Display a Matrix if found.
    bool   findPos( const Matrix &);                               // Display a Matrix if found. return true if found, false if not found
    Matrix getPos(  const Matrix &);                               // Display a Matrix if found. return Matrix if found, empty Matrix if not found
    
    int  size() const;                                             // Size Accessor - Returns size of Space
  
    inline size_t      getMemUsed() const {return totalMemUsed;};  // Get Memory Size of this Space  
    inline const Matrix * getHead() const {return head;};          // Get Head
    inline       Matrix * getHead()       {return head;};          // Get Head
    inline       Matrix * setHead() const {return head;};          // Set Head  
    
                                                                  //*Operator Overload Functions
    Space & operator= (const Space  &other);                      // Copy assignment operator
    Space & operator= (      Space &&other);                      // Move assignment operator
    Space   operator+ (const Space  &other) const;                // Addition operator
    bool    operator==(const Space  &other) const;                // Equality operator
    bool    operator!=(const Space  &other) const;                // Inequality operator
    
    friend std::ostream & operator<<(std::ostream &out, Space &space);  // Stream output operator - Comma-separated values (CSV) format
};
