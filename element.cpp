#include "element.h"

Element::Element()                                          // Default Constructor
{
    data         = nullptr;
    next         = nullptr;
    totalMemUsed = sizeof(*this);
}

Element::~Element()                                         // Destructor!
{
    totalMemUsed -=  ((strlen(data) + 1) * sizeof(char)); 
    delete [] data;
}

Element::Element(const char * value) : Element::Element()     // Parameterized Constructor
{
    size_t strlenData   = strlen(value);

    this->data = new char [strlenData + 1]; // +1 for nullbyte
    strcpy(this->data,value);	
    this->next = nullptr;

    totalMemUsed += ((strlenData + 1) * sizeof(char));
}

Element::Element(Element * ptr) : Element::Element()           // Parameterized Constructor
{
    size_t strlenData   = strlen(ptr->getData());
        
    this->data = new char [strlenData + 1]; // +1 for nullbyte
    strcpy(this->data,ptr->getData());
    this->setNext(ptr->getNext());

    totalMemUsed += ((strlenData + 1) * sizeof(char));
}

Element::Element(const Element& other) : Element::Element()           // Copy Constructor
{

    size_t strlenData   = strlen(other.data);
                                        
    data = new char[strlenData + 1];    // Allocate memory and copy the data from the other object
    strcpy(data, other.data);
    data[strlenData] = '\0';

    next = nullptr;              // Initialize next
    totalMemUsed += ((strlenData + 1) * sizeof(char));
}

int Element::strlen(const char * value) const               // Calculate length of source data
{
    int count = 0;
    if(value != nullptr){
        for(auto ptr = 0; value[ptr] != '\0'; ptr++)
            count++;
    }
    return count;
}

const char & Element::operator [] (int position) const     // Value Subscript Operator
{
    if (position <= 0) return data[0];
    return data[position];
}

char & Element::operator [] (int position)                 // Reference Subscript Operator
{	
    if (position <= 0) return data[0];
    return data[position];
}

void Element::strcpy(char * left, const char * right)      // Used for Dynamic Copy Construction
{
    int ptr;
    for(ptr = 0; ptr < strlen(right); ptr++)
        left[ptr] = right[ptr];
    left[ptr++] = '\0';
}

Element * Element::setNext(Element * direction)            // Set Data Pointer to Next 
{
    this->next = direction;
    return this;
}

Element Element::operator+(const Element& other) const {
    int newLength = strlen(data) + strlen(other.data);      // Calculate the new length
    char* newData = new char[newLength + 1];                // Allocate memory for the new data
    int i = 0;
    for (; data[i] != '\0'; ++i) {                          // Copy the existing data to the new data
        newData[i] = data[i];
    }
    int j = 0;
    for (; other.data[j] != '\0'; ++j) {                    // Append the other.data to the new data
        newData[i + j] = other.data[j];
    }
    newData[i + j] = '\0';                                  // Null-terminate the new data
    Element result(newData);                                // Create a new Element object with the concatenated data
    delete[] newData;                                       // Free the memory allocated for newData
    return result;
}

Element Element::operator+(const char* rvalue) {
    Element result(*this);                                  // Create a new Element to store the result
    int currentLength = strlen(data);                       // Calculate the length of the current data and the length of the right-hand value
    int rhsLength = strlen(rvalue);
    char* combinedData = new char[currentLength + rhsLength + 1];   // Allocate memory for the combined data
    strcpy(combinedData, data);                             // Copy the current data and the right-hand value into the combinedData
    strcpy(combinedData + currentLength, rvalue);
    delete[] result.data;                                   // Update the result's data
    result.data = combinedData;
    result.totalMemUsed = sizeof(result) + (currentLength + rhsLength + 1) * sizeof(char);  // Update the memory usage
    return result;
}

Element Element::operator+(char rvalue) {
    Element result(*this);                                  // Create a new Element to store the result
    int currentLength = strlen(data);                       // Calculate the length of the current data (excluding the null terminator)
                                                            // Allocate memory for the combined data
    char* combinedData = new char[currentLength + 2];       // +2 for the current data and the new character
    strcpy(combinedData, data);                             // Copy the current data and append the right-hand character
    combinedData[currentLength] = rvalue;
    combinedData[currentLength + 1] = '\0';
    delete[] result.data;                                   // Update the result's data
    result.data = combinedData;
    result.totalMemUsed = sizeof(result) + (currentLength + 2) * sizeof(char);  // Update the memory usage
    return result;
}

char* Element::intToString(int value) {
    char* buffer = new char[12];    // Allocate memory for the string
    int len = 0;
    if (value == 0) {               // Handle the case of 0 separately
        buffer[len++] = '0';
    } else {
        bool isNegative = false;

        if (value < 0) {            // Handle negative numbers
            isNegative = true;
            value = -value;
        }

        while (value > 0) {         // Generate the string in reverse order
            buffer[len++] = '0' + (value % 10);
            value /= 10;
        }

        if (isNegative) {           // Add a negative sign if necessary
            buffer[len++] = '-';
        }

        for (int i = 0; i < len / 2; i++) { // Reverse the string to get the correct order
            char temp = buffer[i];
            buffer[i] = buffer[len - i - 1];
            buffer[len - i - 1] = temp;
        }
    }
    buffer[len] = '\0';                     // Null-terminate the string
    return buffer;
}

Element Element::operator+(int rvalue) {
    char* intValue = intToString(rvalue);       // Convert the integer to a string
    Element result(*this);                      // Create a new Element to store the result
    result += intValue;                         // Call the existing += operator for C-style strings to append the right-hand value
    delete[] intValue;                          // Free the memory allocated for the converted string
    return result;
}

Element& Element::operator+=(int rvalue) {
    char* intValue = intToString(rvalue);      // Convert the integer to a string
    *this += intValue;                         // Call the existing += operator for C-style strings to append the right-hand value
    delete[] intValue;                         // Free the memory allocated for the converted string
    return *this;
}

Element& Element::operator+=(const char* rvalue)
{
    if (rvalue) {
        int newLength = strlen(data) + strlen(rvalue);     // Calculate the new length
        char* newData = new char[newLength + 1];           // Allocate memory for the new data
        int i = 0;
        for (; data[i] != '\0'; ++i) {                     // Copy the existing data to the new data
            newData[i] = data[i];
        }
        int j = 0;
        for (; rvalue[j] != '\0'; ++j) {                   // Append the new data
            newData[i + j] = rvalue[j];
        }
        newData[i + j] = '\0';                             // Null-terminate the new data
        delete[] data;                                     // Free the old data and set the new data
        data = newData;
    }
    return *this;
}



//Relational Operators
bool operator == (const Element & left, const Element & right)
{
    return strcmp(left.getData(), right.getData()) == 0;
}
bool operator > (const Element & left, const Element & right)
{
    return strcmp(left.getData(), right.getData()) > 0;
}
bool operator != (const Element & left, const Element & right){ return !(left.getData() == right.getData()); } 
bool operator >= (const Element & left, const Element & right){ return !(left.getData() <  right.getData()); }
bool operator <= (const Element & left, const Element & right){ return !(left.getData() >  right.getData()); }
bool operator <  (const Element & left, const Element & right){ return   left.getData() <  right.getData() ; }

std::ostream & operator << (std::ostream & out, const Element & right) //Stream Insertion
{
    out << right.getData();
    return out;
}
std::istream & operator >> (std::istream & in, Element & right)        //Stream Extraction
{
    int     insert = 0;
    char    byte   = '\0';
    bool    word   = false; 
	
    while(in.good() == true && in.peek() != EOF)
    {
        byte = in.get();
        if(byte <= ' ' || byte >= '~')
        {
            if(word == true)
            {
                right[insert++] = '\0';
                in.putback(byte);
                break;
            }
        }
        else
        {	
            right[insert++] = byte;
            word = true;
        }
    } 
    return in;
}

int strcmp(const char * left, const char * right)                    // String Compare
{
    int lPtr = 0;
    int rPtr = 0;

    while (left[lPtr] != '\0' && right[rPtr] != '\0')
    {
        if (left[lPtr] < right[rPtr])
            return -1;
        else if (left[lPtr] > right[rPtr])
            return 1;

        lPtr++;
        rPtr++;
    }

    if (left[lPtr] == '\0' && right[rPtr] == '\0')
        return 0;
    else if (left[lPtr] == '\0')
        return -1;
    else
        return 1;
}

// Custom case-insensitive toUpper for Element class
char toUpper(char ch)
{
    if (ch >= 'a' && ch <= 'z') {
        return ch - 'a' + 'A';
    }
    return ch;
}

// Custom case-insensitive tolower for Element class
char toLower(char ch)
{
    if (ch >= 'A' && ch <= 'Z') {
        return ch - 'A' + 'a';
    }
    return ch;
}
