#pragma once
#include <iostream>

#define MEM_LIMIT 200000000                                 // 200MB

class Element
{
private:
    char    * data;                                          // Single character
    Element * next;                                          // Forward link
    size_t    totalMemUsed;                                  // Make program self-aware of how much memory it's using
public:	 
    ~Element();                                              // Destructor
    Element();                                               // Default constructor
    Element(const char*);                                    // Parameterized constructor
    Element(Element*);                                       // Parameterized constructor
    Element(const Element&);                                 // Copy Constructor
    int strlen(const char *) const;                          // Get size of Element for dynamic runtime
    const char & operator [](int) const;                     // Value Accessor Subscript Operator
    char & operator [](int);                                 // Reference Mutator Subscript Operator
    void strcpy(char*,const char*);                          // Used for Dynamic Copy Construction

    Element *  setNext(Element *);                                 // Setter
    
    inline const char    * getData() const {return data;};         // Data Accessor 
    inline       char    * getData()       {return data;};         // Data Accessor
    inline const Element * getNext() const {return next;};         // Get Next
    inline       Element * getNext()       {return next;};         // Get Next

    inline char** getDataMem()            {return &data;};         // Get memory location of data
    
    inline int    size() {if(strlen(this->data) == 0){return 0;}   // Size Accessor   - includes nullbyte in size
                          else{return strlen(this->data) + 1;}}; 
  
    inline int    length()           {return strlen(this->data);}; // Length Accessor - excludes nullbyte in length
    inline size_t getMemUsed() const {return totalMemUsed;};       // Mem Size Accessor  

    char * intToString(int); 

    Element   operator+ (const Element&) const; 
    Element   operator+ (const char*); 
    Element   operator+ (      char ); 
    Element   operator+ (      int  ); 
    Element & operator+=(      int  ); 
    Element & operator+=(const char*); 
};

bool operator == (const Element &, const Element &);          // Relational Operator
bool operator >  (const Element &, const Element &);          // Relational Operator
bool operator != (const Element &, const Element &);          // Relational Operator
bool operator <= (const Element &, const Element &);          // Relational Operator
bool operator >= (const Element &, const Element &);          // Relational Operator
bool operator <  (const Element &, const Element &);          // Relational Operator

std::ostream & operator << (std::ostream &, const Element &); // Stream Insertion
std::istream & operator >> (std::istream &, Element &);       // Stream Extraction

int strcmp(const char *, const char *);                       // Standard Element Compare
