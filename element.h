#pragma once
#include <iostream>

class Element
{
private:
    char    * data;                                          // Points to first char in array
    Element * next;                                          // Forward link to next char in array
    size_t    totalMemUsed;                                  // Make program self-aware of how much memory it's using
public:	 
    ~Element();                                              // Destructor
    Element();                                               // Default constructor
    Element(const char*);                                    // Parameterized constructor
    Element(Element*);                                       // Parameterized constructor
    Element(const Element&);                                 // Copy Constructor

    int strlen(const char *) const;                          // Get size of data for dynamic runtime
    const char & operator [](int) const;                     // Value Accessor Subscript Operator
    char & operator [](int);                                 // Reference Mutator Subscript Operator
    void strcpy(char*,const char*);                          // Used for Dynamic Copy Construction

    Element *  setNext(Element *);                           // Set pointer to next

    void setData(const char*);  
    void appendData(const char &);  

    inline const char    * getData() const {return data;};         // Data Accessor
    inline       char    * getData()       {return data;};         // Data Accessor
    inline const Element * getNext() const {return next;};         // Get Next
    inline       Element * getNext()       {return next;};         // Get Next

    inline char** getDataMem()            {return &data;};         // Get memory location of data
    
    inline int    size() {if(strlen(this->data) == 0){return 0;}   // Size Accessor   - includes nullbyte in size
                          else{return strlen(this->data) + 1;}}; 
  
    inline int    length()           {return strlen(this->data);}; // Length Accessor - excludes nullbyte in length
    inline size_t getMemUsed() const {return totalMemUsed;};       // Mem Size Accessor  
    
    Element & operator+ (const Element&);                          // Append and Element to Element 
    Element   operator+ (const char*);                             // Append a char to Element
    Element   operator+ (      char );                             // Append a char to Element
    Element   operator+ (      int  );                             // Append an Int to Element
    Element & operator+=(const int  );                             // Append an Int to Element
    Element & operator+=(const char*);                             // Append a char to Element
    Element & operator+=(const char&);                             // Append a char to Element
    Element & operator+=(const Element&);                          // Append a char to Element
    
    Element & operator= (const Element  &other);                   // Copy assignment operator
    Element & operator= (      Element &&other);                   // Move assignment operator
    
    char * intToString(int);                                       // Custom Int to String function - used to append an int to a Element 'string'
};
                                                              // Operator Overload Functions
bool operator == (const Element &, const Element &);          // Equality                  Operator
bool operator != (const Element &, const Element &);          // Inequality                Operator
bool operator >  (const Element &, const Element &);          // Greater Than              Operator
bool operator >= (const Element &, const Element &);          // Greater Than or Equal to  Operator
bool operator <= (const Element &, const Element &);          // Less Than or Equal to     Operator
bool operator <  (const Element &, const Element &);          // Less Than                 Operator

std::ostream & operator << (std::ostream &, const Element &); // Stream Insertion
std::istream & operator >> (std::istream &, Element &);       // Stream Extraction
std::istream & operator >> (std::istream &, Element *);       // Stream Extraction

int strcmp  (const char *, const char *);                     // Standard Element Compare
int strcmp_i(const char *, const char *);                     // Standard Element Compare - Case Insensitive.

char    toUpper(const char    &);
char    toLower(const char    &);
Element intToString(int);                                     // Custom Int to String function - used to append an int to a Element 'string'
