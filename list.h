#pragma once
#include <iostream>
#include <iomanip>
#include <cmath>
#include "string.h"

class List
{
private:
    String * head;                                                   // Head pointer: points to the first String
    String * curr;                                                   // Points to current String
    size_t   totalMemUsed;                                           // Make program self-aware of how much memory it's using 
public:
    ~List();                                                         // Destructor
    void clear();                                                    // Deallocate memory occupied by the linked list 
    List();                                                          // Default constructor
    List(String*);                                                   // Parameterized constructor
    List(const List &other);                                         // Copy constructor
    int  size() const;                                               // Size Accessor
    void insert(String *, int);                                      // Insert at position
    bool insert(String *);                                           // Sorted Insertion Mutator
    void insert(const String &, int);                                // Insert at position
    bool insert(const String &);                                     // Sorted Insertion Mutator
//    bool find(String &);                                             // Find Accessor
    bool find(String *);                                             // Find Accessor
    void remove(int);                                                // Remove at position
    void remove(String *);                                           // Remove by value
    
    void getDeets();                                                 // Display information about the MEMORY of the List  
    void print();                                                    // Display information about the List  
    void printReverse();                                             // Display information about the List in REVERSE
    int  sizeOfLargestElement() const;                               // Get size of largest element in the List
  
    inline size_t      getMemUsed()    const {return totalMemUsed;}; // Mem Size Accessor  
    inline const String * getHead()    const {return head;};         // Getter
    inline       String * getHead()          {return head;};         // Getter
    inline       String * setHead()    const {return head;};         // Setter    
                                                                     //*Operator Overload Functions
    List & operator=(const List &other);                             // Copy assignment operator
    List & operator=(List &&other);                                  // Move assignment operator - NEEDS WORK?
    List operator+(const List &other)  const;                        // Addition operator
    bool operator==(const List &other) const;                        // Equality operator
    bool operator!=(const List &other) const;                        // Inequality operator
    friend std::ostream & operator<<(std::ostream &out, List &list); // Stream output operator
};
