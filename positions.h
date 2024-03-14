#pragma once
#include <iostream>
#include <iomanip>
#include <cmath>
#include "position.h"

class Positions
{
private:
    Position * head;                                                  // Head pointer: points to the first Position
    Position * curr;                                                  // Points to current Position
    size_t     totalMemUsed;                                          // Make program self-aware of how much memory it's using - Adds 8 bytes and calculation upon Positions insert/remove to overhead 
public:
   ~Positions();                                                      // Destructor
    Positions();                                                      // Default constructor
    Positions(Position*);                                             // Parameterized constructor
    Positions(const Position &);                                      // Parameterized constructor
    Positions(const Positions &other);                                // Copy constructor
    
    void insert(      Position *, int);                               // Insert @ position
    void insert(const Position &, int);                               // Insert @ position        <- Delegates to Existing ^
    bool insert(      Position *     );                               // Sorted Insertion Mutator
    bool insert(const Position &     );                               // Sorted Insertion Mutator <- Delegates to Existing ^
    
    void clear();                                                     // Deallocate memory of the linked positions - completely empty the positions.
    void remove(       int      );                                    // Remove at position
    bool remove(      Position *);                                    // Remove by value
    bool remove(const Position &);                                    // Remove by value <- Delegates to Existing ^ 
    
    void     print();                                                 // Display information about the Positions  
    void     print(  const Position &);                               // Display a Position if found.
    bool     findPos(const Position &);                               // Display a Position if found. return true if found, false if not found
    Position getPos( const Position &);                               // Display a Position if found. return Position if found, empty Position if not found
    Position getPos(       int       );                               // Display a Position if found. return Position if found, empty Position if not found
    
    int  size() const;                                                // Size Accessor - Returns size of Positions
  
    inline size_t        getMemUsed()    const {return totalMemUsed;};// Get Memory Size of this Positions  
    inline const Position * getHead()    const {return head;};        // Get Head
    inline       Position * getHead()          {return head;};        // Get Head
    inline       Position * setHead()    const {return head;};        // Set Head  
    
                                                                      //*Operator Overload Functions
    Positions & operator= (const Positions  &other);                      // Copy assignment operator
    Positions & operator= (      Positions &&other);                      // Move assignment operator
    Positions   operator+ (const Positions  &other) const;                // Addition operator
    bool   operator==(const Positions  &other) const;                     // Equality operator
    bool   operator!=(const Positions  &other) const;                     // Inequality operator
    
    friend std::ostream & operator<<(std::ostream &out, Positions &positions);  // Stream output operator - Comma-separated values (CSV) format
};
