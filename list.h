#pragma once
#include <iostream>
#include <iomanip>
#include <cmath>
#include "positions.h"
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
    List(Element);                                                    // Parameterized constructor
    List(const List &other);                                          // Copy constructor
    
    void insert(      Element *, int);                                // Insert @ position
    void insert(const Element &, int);                                // Insert @ position        <- Delegates to Existing ^
    bool insert(      Element *     );                                // Sorted Insertion Mutator
    bool insert(const Element &     );                                // Sorted Insertion Mutator <- Delegates to Existing ^
    
    void clear();                                                     // Deallocate memory of the linked list - completely empty the list.
    void remove(      int      );                                     // Remove at position
    bool remove(      Element *);                                     // Remove by value
    bool remove(const Element &);                                     // Remove by value <- Delegates to Existing ^ 
   
    bool      findMatch    (      Element *);                           // Find Exact Match
    bool      findMatch    (const Element &);                           // Find Exact Match <- Delegates to Existing ^
    Positions findMatch_p  (      Element *);                           // Find Exact Match
    Positions findMatch_p  (const Element &);                           // Find Exact Match <- Delegates to Existing ^
    List      findMatch_z  (      Element *);                           // Find Exact Match
    List      findMatch_z  (const Element &);                           // Find Exact Match <- Delegates to Existing ^
    bool      findMatch_i  (      Element *);                           // Find Match                               - CASE INSENSITIVE
    bool      findMatch_i  (const Element &);                           // Find Match <- Delegates to Existing ^    - CASE INSENSITIVE
    Positions findMatch_i_p(      Element *);                           // Find Match                               - CASE INSENSITIVE
    Positions findMatch_i_p(const Element &);                           // Find Match <- Delegates to Existing ^    - CASE INSENSITIVE
    List      findMatch_i_z(      Element *);                           // Find Match                               - CASE INSENSITIVE
    List      findMatch_i_z(const Element &);                           // Find Match <- Delegates to Existing ^    - CASE INSENSITIVE
    
    bool      containsSequence    (      Element *);                    // Contains Chars in Sequence | e.g. car, aM, haM, caM, (etc.) contained in charM
    bool      containsSequence    (const Element &);                    // Contains Chars in Sequence <- Delegates to Existing ^
    Positions containsSequence_p  (      Element *);                    // Contains Chars in Sequence | e.g. car, aM, haM, caM, (etc.) contained in charM
    Positions containsSequence_p  (const Element &);                    // Contains Chars in Sequence <- Delegates to Existing ^
    List      containsSequence_z  (      Element *);                    // Contains Chars in Sequence | e.g. car, aM, haM, caM, (etc.) contained in charM
    List      containsSequence_z  (const Element &);                    // Contains Chars in Sequence <- Delegates to Existing ^
    bool      containsSequence_i  (      Element *);                    // Contains  | e.g. car, HAM (etc.) contained in CHarM - CASE INSENSITIVE
    bool      containsSequence_i  (const Element &);                    // Contains <- Delegates to Existing ^                 - CASE INSENSITIVE
    Positions containsSequence_i_p(      Element *);                    // Contains  | e.g. car, HAM (etc.) contained in CHarM - CASE INSENSITIVE
    Positions containsSequence_i_p(const Element &);                    // Contains <- Delegates to Existing ^                 - CASE INSENSITIVE
    List      containsSequence_i_z(      Element *);                    // Contains  | e.g. car, HAM (etc.) contained in CHarM - CASE INSENSITIVE
    List      containsSequence_i_z(const Element &);                    // Contains <- Delegates to Existing ^                 - CASE INSENSITIVE
    
    bool      wildcardSearch    (      Element *);                      // Search List Starts with*, ends *with, or *contains*
    bool      wildcardSearch    (const Element &);                      // Search List Starts with*, ends *with, or *contains*
    Positions wildcardSearch_p  (      Element *);                      // Search List Starts with*, ends *with, or *contains*
    Positions wildcardSearch_p  (const Element &);                      // Search List Starts with*, ends *with, or *contains*
    List      wildcardSearch_z  (      Element *);                      // Search List Starts with*, ends *with, or *contains*
    List      wildcardSearch_z  (const Element &);                      // Search List Starts with*, ends *with, or *contains*
    bool      wildcardSearch_i  (      Element *);                      // Search List Starts with*, ends *with, or *contains* - CASE INSENSITIVE
    bool      wildcardSearch_i  (const Element &);                      // Search List Starts with*, ends *with, or *contains* - CASE INSENSITIVE
    Positions wildcardSearch_i_p(      Element *);                      // Search List Starts with*, ends *with, or *contains* - CASE INSENSITIVE
    Positions wildcardSearch_i_p(const Element &);                      // Search List Starts with*, ends *with, or *contains* - CASE INSENSITIVE
    List      wildcardSearch_i_z(      Element *);                      // Search List Starts with*, ends *with, or *contains* - CASE INSENSITIVE
    List      wildcardSearch_i_z(const Element &);                      // Search List Starts with*, ends *with, or *contains* - CASE INSENSITIVE
    bool      wildcardSearch_i  (const char *, const char*);            // Wildcard Search string helper.
    bool      wildcardSearch    (const char *, const char*);            // Wildcard Search string helper.

    Element getDataAtPosition(int) const;                             // Returns data at position in the List  
    void getDeets();                                                  // Display information about the MEMORY of the List  
    void print();                                                     // Display information about the List  
    void printReverse();                                              // Display information about the List in REVERSE
    
    int  size() const;                                                // Size Accessor - Returns size of List
    int  sizeOfLargestElement() const;                                // Get size of largest element in the List
    inline bool isEmpty() const {return head == nullptr;};
    
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
