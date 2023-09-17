#pragma once
#include <iostream>
#include <iomanip>
#include <cmath>
#include "element.h"

class List
{
private:
    Element * head;                                                   // Head pointer: points to the first Element
    Element * curr;                                                   // Points to current Element
    size_t    totalMemUsed;                                           // Make program self-aware of how much memory it's using - Adds 8 bytes and calculation upon List insert/remove to overhead 
public:
   ~List();                                                           // Destructor
    List();                                                           // Default constructor
    List(Element*);                                                   // Parameterized constructor
    List(const List &other);                                          // Copy constructor
    
    void insert(      Element *, int);                                // Insert at position
    void insert(const Element &, int);                                // Insert at position       <- Delegates to Existing ^
    bool insert(      Element *     );                                // Sorted Insertion Mutator
    bool insert(const Element &     );                                // Sorted Insertion Mutator <- Delegates to Existing ^
    
    void clear();                                                     // Deallocate memory of the linked list - completely empty the list.
    void remove(      int      );                                     // Remove at position
    bool remove(      Element *);                                     // Remove by value
    bool remove(const Element &);                                     // Remove by value <- Delegates to Existing ^ 
    
    bool findMatch(      Element *);                                  // Find Exact Match
    bool findMatch(const Element &);                                  // Find Exact Match <- Delegates to Existing ^

    bool containsSequence  (      Element *);                         // Contains Chars in Sequence | e.g. car, aM, haM, caM, (etc.) contained in charM
    bool containsSequence  (const Element &);                         // Contains Chars in Sequence <- Delegates to Existing ^
    bool containsSequence_i(      Element *);                         // Case insensitive contains  | e.g. car, am, ham, cam, HAM (etc.) contained in CHarM
    bool containsSequence_i(const Element &);                         // Case insensitive contains  <- Delegates to Existing ^
    
    bool wildcardSearch(      Element *);                             // Search String Starts with*, ends *with, or *contains*
    bool wildcardSearch(const Element &);                             // Search String Starts with*, ends *with, or *contains*
    bool wildcardSearch(const char *, const char*);                   // Wildcard Search string helper.
    
    void getDeets();                                                  // Display information about the MEMORY of the List  
    void print();                                                     // Display information about the List  
    void printReverse();                                              // Display information about the List in REVERSE
    
    int  size() const;                                                // Size Accessor - Returns size of List
    int  sizeOfLargestElement() const;                                // Get size of largest element in the List
  
    inline size_t       getMemUsed()    const {return totalMemUsed;}; // Get Memory Size of this List  
    inline const Element * getHead()    const {return head;};         // Get Head
    inline       Element * getHead()          {return head;};         // Get Head
    inline       Element * setHead()    const {return head;};         // Set Head  
    
                                                                      //*Operator Overload Functions
    List & operator= (const List  &other);                            // Copy assignment operator
    List & operator= (      List &&other);                            // Move assignment operator
    List   operator+ (const List  &other) const;                      // Addition operator
    bool   operator==(const List  &other) const;                      // Equality operator
    bool   operator!=(const List  &other) const;                      // Inequality operator
    
    friend std::ostream & operator<<(std::ostream &out, List &list);  // Stream output operator - Comma-separated values (CSV) format
};
