#pragma once
#include <iostream>

#define MEM_LIMIT 200000000                                 // 200MB

class String
{
private:
    char   * data;                                          // Single character
    String * next;                                          // Forward link
    size_t   totalMemUsed;                                  // Make program self-aware of how much memory it's using
public:	 
    ~String();                                              // Destructor
    String();                                               // Default constructor
    String(const char*);                                    // Parameterized constructor
    String(String*);                                        // Parameterized constructor
//    String(const String*);                                  // Copy Constructor
    String(const String&);                                  // Copy Constructor
    int strlen(const char *);                               // Get size of String for dynamic runtime
    int strlen(const String*);                              // Get size of String
    const char & operator [](int) const;                    // Value Accessor Subscript Operator
    char & operator [](int);                                // Reference Mutator Subscript Operator
    void strcpy(char*,const char*);                         // Used for Dynamic Copy Construction
    inline const char * getData() const {return data;};     // Data Accessor 
    inline char * getData() {return data;};                 // Data Accessor
    inline const String * getNext() const {return next;};   // Get Next
    inline String * getNext() {return next;};               // Get Next
    String *  setNext(String *);                            // Setter
//    String *  setNext(String  );                            // Setter

    inline char** getDataMem()       {return &data;};       // Get memory location of data
    inline int size() {if(strlen(this->data) == 0){return 0;}// Size Accessor   - includes nullbyte in size
                       else{return strlen(this->data) + 1;}}; 
    inline int length()              {return strlen(this->data);}; // Length Accessor - excludes nullbyte in length
    inline size_t getMemUsed() const {return totalMemUsed;};       // Mem Size Accessor  
};

bool operator == (const String &, const String &);          // Relational Operator
bool operator >  (const String &, const String &);          // Relational Operator
bool operator != (const String &, const String &);          // Relational Operator
bool operator <= (const String &, const String &);          // Relational Operator
bool operator >= (const String &, const String &);          // Relational Operator
bool operator <  (const String &, const String &);          // Relational Operator

std::ostream & operator << (std::ostream &, const String &);// Stream Insertion
std::istream & operator >> (std::istream &, String &);      // Stream Extraction

int strcmp(const char *, const char *);                     // Standard String Compare
