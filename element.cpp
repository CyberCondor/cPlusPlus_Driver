#include "element.h"

Element::Element()                                          // Default Constructor
{
    data         = nullptr;
    next         = nullptr;
    totalMemUsed = sizeof(*this);
}

Element::~Element()                                         // Destructor!
{
    totalMemUsed -= ((strlen(data) + 1) * sizeof(char)); 
    delete [] data;
}

Element::Element(const char * value) : Element::Element()     // Parameterized Constructor
{
    size_t strlenData = strlen(value);

    this->data = new char [strlenData + 1]; // +1 for nullbyte
    strcpy(this->data,value);	
    this->next = nullptr;

    totalMemUsed += ((strlenData + 1) * sizeof(char));
}

Element::Element(Element * ptr) : Element::Element()           // Parameterized Constructor
{
    size_t strlenData = strlen(ptr->getData());
        
    this->data = new char [strlenData + 1]; // +1 for nullbyte
    strcpy(this->data,ptr->getData());
    this->setNext(ptr->getNext());

    totalMemUsed += ((strlenData + 1) * sizeof(char));
}

Element::Element(const Element& other) : Element::Element()           // Copy Constructor
{
    size_t strlenData = strlen(other.data);
                                        
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

void Element::strcpy(char * left, const char * right)      // Used for Dynamic Copy Construction - unsafe if used without allocating enough space for left string.
{
    int ptr;
    for(ptr = 0; ptr < strlen(right); ptr++)
        left[ptr] = right[ptr];
    left[ptr++] = '\0';
}

void Element::setData(const char* newData)
{
    if (data != nullptr) {                            // Make sure to free existing memory if it's not nullptr
        delete[] data;
        totalMemUsed = sizeof(*this);
    }
    size_t newLength = strlen(newData);               // Calculate the length of the new data
                                                      // Allocate memory for the new data and copy it
    data = new char[newLength + 1];                   // +1 for the null terminator
    strcpy(data, newData);
    totalMemUsed += ((newLength + 1) * sizeof(char)); // Update the total memory usage
}

void Element::appendData(const char &newChar)
{
    if(newChar && newChar != '\0' && newChar != '\n') {
        
        int thisLength = strlen(this->getData());        
    
        char * combinedData = new char[thisLength + 2];
        strcpy(combinedData, this->getData());

        combinedData[thisLength] = newChar;
        combinedData[thisLength + 1] = '\0';

        if (data != nullptr) {
            delete[] data;
        }
        data = combinedData;
        totalMemUsed +=  sizeof(char);
    }
    else{return;}
}


Element * Element::setNext(Element *direction)              // Set Data Pointer to Next 
{
    this->next = direction;
    return this;
}

Element & Element::operator+(const Element &rvalue)
{
    if(this == &rvalue) {
        Element newE = rvalue; 
        for(int i = 0; newE.data[i] != '\0'; i++){
            this->appendData(newE.data[i]);
        }
    }
    else if(rvalue.data != nullptr) {
        for(int i = 0; rvalue.data[i] != '\0'; i++){
            this->appendData(rvalue.data[i]);
        }
    }
    return *this;
}

Element Element::operator+(const char *rvalue)
{
    Element result(*this);                                  // Create a new Element to store the result
    int currentLength = strlen(data);                       // Calculate the length of the current data and the length of the right-hand value
    int rhsLength = strlen(rvalue);
    char* combinedData = new char[currentLength + rhsLength + 1];  // Allocate memory for the combined data
    strcpy(combinedData, data);                             // Copy the current data and the right-hand value into the combinedData
    strcpy(combinedData + currentLength, rvalue);
    delete[] result.data;                                   // Update the result's data
    result.data = combinedData;
    result.totalMemUsed = sizeof(result) + (currentLength + rhsLength + 1) * sizeof(char);  // Update the memory usage
    return result;
}

Element Element::operator+(char rvalue)
{
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



Element Element::operator+(int rvalue)
{
    char * intValue = intToString(rvalue);     // Convert the integer to a string
    Element result(*this);                     // Create a new Element to store the result
    result += intValue;                        // Call the existing += operator for C-style strings to append the right-hand value
    delete[] intValue;                         // Free the memory allocated for the converted string
    return result;
}

Element & Element::operator+=(const int rvalue)
{
    char * intValue = intToString(rvalue);      // Convert the integer to a string
    *this += intValue;                          // Call the existing += operator for C-style strings to append the right-hand value
    delete[] intValue;                          // Free the memory allocated for the converted string
    return *this;
}

Element & Element::operator+=(const char &rvalue)
{
    if (rvalue != '\0') {
        this->appendData(rvalue);
    }
    return *this;
}
Element & Element::operator+=(const char * rvalue)
{
    if (rvalue != nullptr) {
        for(int i = 0; i < strlen(rvalue); i++){
            this->appendData(rvalue[i]);
        }
    }
    return *this;
}
Element & Element::operator+=(const Element &rvalue)
{
   if(this == &rvalue) {
        Element newE = rvalue; 
        for(int i = 0; newE.data[i] != '\0'; i++){
            this->appendData(newE.data[i]);
        }
    }
    else if(rvalue.data != nullptr) {
        for(int i = 0; i < strlen(rvalue.getData()); i++){
            this->appendData(rvalue.data[i]);
        }
    }
    return *this;
}


char * Element::intToString(int value)
{
    char * buffer = new char[12];    // Allocate memory for the string
    int len = 0;
    if (value == 0) {                // Handle the case of 0 separately
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
Element intToString(int value)
{
    char * buffer = new char[12];    // Allocate memory for the string
    int len = 0;
    if (value == 0) {                // Handle the case of 0 separately
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
    Element string = Element(buffer);
    delete [] buffer;
    return string;
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
    if(right.getData() != nullptr) {
        out << right.getData();
    }
    return out;
}

std::istream & operator >> (std::istream & in, Element & right)        //Stream Extraction
{
    size_t bufferSize = 4095;
    size_t bufferIdx  = 0;
    char * buffer  = new char[bufferSize + 1];
    while(bufferIdx < bufferSize && in.peek() != '\n' && in.good() == true && in.peek() != EOF)
    {
        in >> buffer[bufferIdx++];
       // byte = in.get();
       // right.appendData(byte); // linear time copy operator- slow af - should implement Element as a double linked list to just grow the end here
       // size++;
    }
    in.clear();
    in.ignore();
    buffer[bufferIdx] = '\0';
    right.setData(buffer);
    delete [] buffer;
    return in;
}
std::istream & operator >> (std::istream & in, Element * right)        //Stream Extraction
{
   // size_t size = 0;
   // size_t MAX  = sizeof(size_t);
   // for(size_t i = 0; i <= sizeof(size_t) * 2; i++) {
   //     MAX = sizeof(size_t) * MAX; 
   // }
    size_t bufferSize = 4095;
    size_t bufferIdx  = 0;
    char * string     = new char[bufferSize + 1];
    while(bufferIdx < bufferSize && in.peek() != '\n' && in.good() == true && in.peek() != EOF)
    {
        in >> string[bufferIdx++];
        if(in.peek() == ' ') {
            break;
        }
       // byte = in.get();
       // right.appendData(byte); // linear time copy operator- slow af - should implement Element as a double linked list to just grow the end here
       // size++;
    }
    string[bufferIdx] = '\0';
    right->setData(string);
    delete [] string;
    return in;
}

int strcmp(const char * left, const char * right)                    // String Compare
{
    if (left == nullptr)
        return -1;
    if (right == nullptr)
        return 1;
    if (left == nullptr && right == nullptr)
        return 0;
    
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

int strcmp_i(const char * left, const char * right)                 // String Compare Case Insensitive
{
    if (left == nullptr)
        return -1;
    if (right == nullptr)
        return 1;
    if (left == nullptr && right == nullptr)
        return 0;

    int lPtr = 0;
    int rPtr = 0;
    while (left[lPtr] != '\0' && right[rPtr] != '\0')
    {
        if ( toLower(left[lPtr]) < toLower(right[rPtr]) )
            return -1;
        else if ( toLower(left[lPtr]) > toLower(right[rPtr]) )
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

char toUpper(const char &ch)
{
    if (ch >= 'a' && ch <= 'z') {
        return ch - 'a' + 'A';
    }
    return ch;
}
char toLower(const char &ch)
{
    if (ch >= 'A' && ch <= 'Z') {
        return ch - 'A' + 'a';
    }
    return ch;
}
