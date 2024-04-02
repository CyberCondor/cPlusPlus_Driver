#pragma once
#include <iostream>
#include "element.h"
#include "string.h"
#include "property.h"

class Properties {
private:
    Property* head;

public:
    ~Properties();
    Properties() : head(nullptr) {};
    Properties(Property*);
    Properties(Property);
    Properties(const Properties &);

    void insert(Property *, int);
    bool insert(Property *);
    bool insert(const Property & property);
    bool insert(const Element  &);
    bool insert(const Element  &, const Element &);
    bool insert(const Element  &, const String  &);

    bool       findMatch         (const Element &, const Element &);// Find Match Key to Value
    bool       findMatch_i       (const Element &, const Element &);// Find Match Key to Value
    Properties findMatch         (const Element &);                 // Find Exact Match
    Properties findMatch_i       (const Element &);                 // Find Match                  - CASE INSENSITIVE
    bool       containsSequence  (const Element &, const Element &);// Key Contains Value
    bool       containsSequence_i(const Element &, const Element &);// Key Contains Value
    Properties containsSequence  (const Element &);                 // Contains Chars in Sequence
    Properties containsSequence_i(const Element &);                 // Contains                    - CASE INSENSITIVE
    bool       wildcardSearch    (const Element &, const Element &);// Key like *value*
    bool       wildcardSearch_i  (const Element &, const Element &);// Key like *value*
    Properties wildcardSearch    (const Element &);             // Search String Starts with*, ends *with, or *contains*
    Properties wildcardSearch_i  (const Element &);             // Search String Starts with*, ends *with, or *contains* - CASE INSENSITIVE


    bool       findKey(const Element &) const;
    Properties getKeys() const;
    Properties getProperties() const;
    Property   getProperty(const Element & key) const;
    Property   getProperty(int pos) const;

    void print() const;

    int size() const; 

    void setDefault();
   
    void clear();
    

    inline const Property * getHead()    const {return head;};         // Get Head
    inline       Property * getHead()          {return head;};         // Get Head
    inline       Property * setHead()    const {return head;};         // Set Head  

    Properties   operator+ (const Properties  &other) const;           // Addition operator
    Properties & operator= (const Properties  &other);                 // Copy assignment operator
};
