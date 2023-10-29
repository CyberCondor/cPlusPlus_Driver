#pragma once
#include "string.h"
#include "element.h"

class Property {
private:
    Element    key;
    String     value;
    Property * next;
public:
    inline Property() : key(), value(){};                         // Default Constructor  
    
    inline Property(const Element & key) : key(key), value(){};   // Param Constructor
    
    inline Property(const Element & key, const Element & value)   // Param Constructor 
            : key(key),value() { this->value.insert(Element(value)); };
    
    inline Property(const Element & key, String value)            // Param Constructor 
            : key(key),value(value) { this->value = value; };

    inline Property(const Property & other)                       // Copy Constructor
            : key(other.getKey()), value(other.getValue()), next(nullptr){};

    inline Element getKey()   const { return key;   };
    inline String  getValue() const { return value; };

    inline void setKey     (const Element & value) {this->key.setData(value.getData());};
    inline void setValue   (const Element & value) {this->value.insert(Element(value));};
    inline void setValue   (const String  & value) {this->value = value;};
    inline void appendValue(const Element & value) {this->value.insert(Element(value));};

    inline void print()const { if(key.getData() != nullptr || value != String()) {
                                std::cout << key <<": ";
                                std::cout << value << std::endl;}};

    inline const Property * getNext() const {return next;}; // Get Next
    inline       Property * getNext()       {return next;}; // Get Next

    inline       Property * setNext(Property * direction)
                    {this->next = direction;return this;};  // Set pointer to next
};
