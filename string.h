#pragma once
#include <iostream>
#include <iomanip>
#include <cmath>
#include "element.h"
#include "positions.h"

class String
{
private:
    Element * head;                                                   // Head pointer: points to the first Element
    Element * curr;                                                   // Points to current Element
    size_t    totalMemUsed;                                           // Make program self-aware of how much memory it's using - Adds 8 bytes and calculation upon String insert/remove to overhead 
public:
   ~String();                                                         // Destructor
    String();                                                         // Default constructor
    String(Element*);                                                 // Parameterized constructor
    String(Element element);                                          // Parameterized constructor 
    String(const String &other);                                      // Copy constructor
    
    void insert(      Element *, int);                                // Insert @ position
    void insert(const Element &, int);                                // Insert @ position        <- Delegates to Existing ^
    bool insert(      Element *     );                                // Sorted Insertion Mutator
    bool insert(const Element &     );                                // Sorted Insertion Mutator <- Delegates to Existing ^
    
    void clear();                                                     // Deallocate memory of the linked string - completely empty the string.
    void remove(      int      );                                     // Remove at position
    bool remove(      Element *);                                     // Remove by value
    bool remove(const Element &);                                     // Remove by value <- Delegates to Existing ^ 
    void sort  ();
    
    bool      findMatch    (      Element *);                                // Find Exact Match
    bool      findMatch    (const Element &);                                // Find Exact Match <- Delegates to Existing ^
    Positions findMatch_p  (      Element *);                                // Find Exact Match
    Positions findMatch_p  (const Element &);                                // Find Exact Match <- Delegates to Existing ^
    String    findMatch_z  (      Element *);                                // Find Exact Match
    String    findMatch_z  (const Element &);                                // Find Exact Match <- Delegates to Existing ^
    bool      findMatch_i  (      Element *);                                // Find Match                               - CASE INSENSITIVE
    bool      findMatch_i  (const Element &);                                // Find Match <- Delegates to Existing ^    - CASE INSENSITIVE
    Positions findMatch_i_p(      Element *);                                // Find Match                               - CASE INSENSITIVE
    Positions findMatch_i_p(const Element &);                                // Find Match <- Delegates to Existing ^    - CASE INSENSITIVE
    String    findMatch_i_z(      Element *);                                // Find Match                               - CASE INSENSITIVE
    String    findMatch_i_z(const Element &);                                // Find Match <- Delegates to Existing ^    - CASE INSENSITIVE
    
    bool      containsSequence    (      Element *);                         // Contains Chars in Sequence | e.g. car, aM, haM, caM, (etc.) contained in charM
    bool      containsSequence    (const Element &);                         // Contains Chars in Sequence <- Delegates to Existing ^
    Positions containsSequence_p  (      Element *);                         // Contains Chars in Sequence | e.g. car, aM, haM, caM, (etc.) contained in charM
    Positions containsSequence_p  (const Element &);                         // Contains Chars in Sequence <- Delegates to Existing ^
    String    containsSequence_z  (      Element *);                         // Contains Chars in Sequence | e.g. car, aM, haM, caM, (etc.) contained in charM
    String    containsSequence_z  (const Element &);                         // Contains Chars in Sequence <- Delegates to Existing ^
    bool      containsSequence_i  (      Element *);                         // Contains  | e.g. car, HAM (etc.) contained in CHarM - CASE INSENSITIVE
    bool      containsSequence_i  (const Element &);                         // Contains <- Delegates to Existing ^                 - CASE INSENSITIVE
    Positions containsSequence_i_p(      Element *);                         // Contains  | e.g. car, HAM (etc.) contained in CHarM - CASE INSENSITIVE
    Positions containsSequence_i_p(const Element &);                         // Contains <- Delegates to Existing ^                 - CASE INSENSITIVE
    String    containsSequence_i_z(      Element *);                         // Contains  | e.g. car, HAM (etc.) contained in CHarM - CASE INSENSITIVE
    String    containsSequence_i_z(const Element &);                         // Contains <- Delegates to Existing ^                 - CASE INSENSITIVE
    
    
    bool      wildcardSearch    (      Element *);                           // Search String Starts with*, ends *with, or *contains*
    bool      wildcardSearch    (const Element &);                           // Search String Starts with*, ends *with, or *contains*
    Positions wildcardSearch_p  (      Element *);                           // Search String Starts with*, ends *with, or *contains*
    Positions wildcardSearch_p  (const Element &);                           // Search String Starts with*, ends *with, or *contains*
    String    wildcardSearch_z  (      Element *);                           // Search String Starts with*, ends *with, or *contains*
    String    wildcardSearch_z  (const Element &);                           // Search String Starts with*, ends *with, or *contains*
    bool      wildcardSearch_i  (      Element *);                           // Search String Starts with*, ends *with, or *contains* - CASE INSENSITIVE
    bool      wildcardSearch_i  (const Element &);                           // Search String Starts with*, ends *with, or *contains* - CASE INSENSITIVE
    Positions wildcardSearch_i_p(      Element *);                           // Search String Starts with*, ends *with, or *contains* - CASE INSENSITIVE
    Positions wildcardSearch_i_p(const Element &);                           // Search String Starts with*, ends *with, or *contains* - CASE INSENSITIVE
    String    wildcardSearch_i_z(      Element *);                           // Search String Starts with*, ends *with, or *contains* - CASE INSENSITIVE
    String    wildcardSearch_i_z(const Element &);                           // Search String Starts with*, ends *with, or *contains* - CASE INSENSITIVE
    bool      wildcardSearch_i  (const char *, const char*);                 // Wildcard Search string helper.
    bool      wildcardSearch    (const char *, const char*);                 // Wildcard Search string helper.
    
    Element getDataAtPosition(int) const;                             // Returns data at position in the List  
    void getDeets();                                                  // Display information about the MEMORY of the String  
    void print();                                                     // Display information about the String  
    void printReverseHelper(Element *, Element *, bool, int &, int &);
    void printReverse();                                              // Display information about the String in REVERSE
    
    int  size() const;                                                // Size Accessor - Returns size of String
    int  sizeOfLargestElement() const;                                // Get size of largest element in the String
    inline bool isEmpty() const {return head == nullptr;};

    inline size_t       getMemUsed()    const {return totalMemUsed;}; // Get Memory Size of this String  
    inline const Element * getHead()    const {return head;};         // Get Head
    inline       Element * getHead()          {return head;};         // Get Head
    inline       Element * setHead()    const {return head;};         // Set Head  
    
                                                                      //*Operator Overload Functions
    String & operator= (const String  &other);                          // Copy assignment operator
    String & operator= (      String &&other);                          // Move assignment operator
    String   operator+ (const String  &other) const;                    // Addition operator
    bool     operator==(const String  &other) const;                      // Equality operator
    bool     operator!=(const String  &other) const;                      // Inequality operator
   
    friend std::ostream & operator<<(std::ostream &out, String string);   // Stream Insertion operator - Comma-separated values (CSV) format
    friend std::ostream & operator<<(std::ostream &out, String &string);  // Stream Insertion operator - Comma-separated values (CSV) format
    friend std::istream & operator>>(std::istream &, String &);           // Stream Extraction
};
