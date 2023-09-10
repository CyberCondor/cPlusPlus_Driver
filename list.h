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
    size_t    totalMemUsed;                                           // Make program self-aware of how much memory it's using 
public:
    ~List();                                                          // Destructor
    void clear();                                                     // Deallocate memory occupied by the linked list 
    List();                                                           // Default constructor
    List(Element*);                                                   // Parameterized constructor
    List(const List &other);                                          // Copy constructor
    
    int  size() const;                                                // Size Accessor
    void insert(      Element *, int);                                // Insert at position
    bool insert(      Element *     );                                // Sorted Insertion Mutator
    void insert(const Element &, int);                                // Insert at position
    bool insert(const Element &     );                                // Sorted Insertion Mutator
    bool find  (Element  );                                           // Find Accessor
    bool find  (Element *);                                           // Find Accessor

    bool contains(const Element &);
    bool contains(Element *);

    bool wildcardMatch(Element  );
    bool wildcardMatch(Element *);
    bool wildcardMatch(const char *, const char*);
    
    void remove(int      );                                           // Remove at position
    void remove(Element *);                                           // Remove by value
    void remove(Element  );                                           // Remove by value
    
    void getDeets();                                                  // Display information about the MEMORY of the List  
    void print();                                                     // Display information about the List  
    void printReverse();                                              // Display information about the List in REVERSE
    int  sizeOfLargestElement() const;                                // Get size of largest element in the List
  
    inline size_t       getMemUsed()    const {return totalMemUsed;}; // Mem Size Accessor  
    inline const Element * getHead()    const {return head;};         // Getter
    inline       Element * getHead()          {return head;};         // Getter
    inline       Element * setHead()    const {return head;};         // Setter    
                                                                      //*Operator Overload Functions
    List & operator= (const List  &other);                            // Copy assignment operator
    List & operator= (      List &&other);                            // Move assignment operator - NEEDS WORK?
    List   operator+ (const List  &other) const;                      // Addition operator
    bool   operator==(const List  &other) const;                      // Equality operator
    bool   operator!=(const List  &other) const;                      // Inequality operator
    friend std::ostream & operator<<(std::ostream &out, List &list);  // Stream output operator
};
