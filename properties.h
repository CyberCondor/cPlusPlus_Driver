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

    void insert(Property *, int);
    bool insert(Property *);
    bool insert(const Property & property);
    bool insert(const Element  &);
    bool insert(const Element  &, const Element &);
    bool insert(const Element  &, const String  &);

    void print() const;

    int size() const; 

    void setDefault();
};
