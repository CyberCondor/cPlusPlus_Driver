#include "string.h"

String::String()                                          // Default Constructor
{
    data         = nullptr;
    next         = nullptr;
    totalMemUsed = sizeof(*this);
}

String::~String()                                         // Destructor!
{
    totalMemUsed -=  ((strlen(data) + 1) * sizeof(char)); //(sizeof(String) + ((strlen(data) + 1) * sizeof(char)));
    delete [] data;
}

String::String(const char * value) : String::String()     // Parameterized Constructor
{
    size_t strlenData   = strlen(value);

   // if(((strlenData + 1) * sizeof(char))) < MEM_LIMIT) {
    
        this->data = new char [strlenData + 1]; // +1 for nullbyte
        strcpy(this->data,value);	
        this->next = nullptr;

        totalMemUsed += ((strlenData + 1) * sizeof(char));
  //  }
}

String::String(String * ptr) : String::String()           // Parameterized Constructor
{
    size_t strlenData   = strlen(ptr->getData());

  //  if((((strlenData + 1) * sizeof(char))) < MEM_LIMIT) {
        this->data = new char [strlenData + 1]; // +1 for nullbyte
        strcpy(this->data,ptr->getData());
        this->setNext(ptr->getNext());

        totalMemUsed += ((strlenData + 1) * sizeof(char));
   // }
}

//String::String(const String* other) : String::String()           // Copy Constructor
//{
//    int length = strlen(other->data);
//                                 // Allocate memory for the new data
//    data = new char[length + 1]; // +1 for null-terminator
//    strcpy(data, other->data);   // Copy the characters and add a null-terminator
//    data[length] = '\0';
//
//    next = nullptr;              // Initialize next
//}

String::String(const String& other) : String::String()           // Copy Constructor
{

    size_t strlenData   = strlen(other.data);

  //  if((((strlenData + 1) * sizeof(char))) < MEM_LIMIT) {
                                        
        data = new char[strlenData + 1];    // Allocate memory and copy the data from the other object
        strcpy(data, other.data);
        data[strlenData] = '\0';

        next = nullptr;              // Initialize next
        totalMemUsed += ((strlenData + 1) * sizeof(char));
   // }
}

int String::strlen(const char * value)                    // Calculate length of source data
{
    int count = 0;
    if(value != nullptr){
        for(auto ptr = 0; value[ptr] != '\0'; ptr++)
            count++;
    }
    return count;
}

const char & String::operator [] (int position) const     // Value Subscript Operator
{
    if (position <= 0) return data[0];
    return data[position];
}

char & String::operator [] (int position)                 // Reference Subscript Operator
{	
    if (position <= 0) return data[0];
    return data[position];
}

void String::strcpy(char * left, const char * right)      // Used for Dynamic Copy Construction
{
    int ptr;
    for(ptr = 0; ptr < strlen(right); ptr++)
        left[ptr] = right[ptr];
    left[ptr++] = '\0';
}

String * String::setNext(String * direction)              // Set Data Pointer to Next 
{
    this->next = direction;
    return this;
}
//String * String::setNext(String   direction)              // Set Data Pointer to Next 
//{
//    this->next = &direction;
//    return this;
//}

//Relational Operators
//bool operator >  (const String & left, const String & right) { return left.getData() >  right.getData(); }
//bool operator == (const String & left, const String & right) { return left.getData() == right.getData(); }
bool operator == (const String & left, const String & right)
{
    return strcmp(left.getData(), right.getData()) == 0;
}

bool operator > (const String & left, const String & right)
{
    return strcmp(left.getData(), right.getData()) > 0;
}

bool operator != (const String & left, const String & right){ return !(left.getData() == right.getData()); } 
bool operator >= (const String & left, const String & right){ return !(left.getData() < right.getData()) ; }
bool operator <= (const String & left, const String & right){ return !(left.getData() > right.getData()) ; }
bool operator <  (const String & left, const String & right){ return   left.getData() < right.getData()  ; }

std::ostream & operator << (std::ostream & out, const String & right) //Stream Insertion
{
    out << right.getData();
    return out;
}

std::istream & operator >> (std::istream & in, String & right)        //Stream Extraction
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


//int strcmp(const char * left, const char * right)
//{
//	int 	lPtr = 0;
//	int 	rPtr = 0;
//	unsigned char lByte = '\0';
//	unsigned char rByte = '\0';
//	
//	do
//	{
//		lByte = left[lPtr++];
//		rByte = right[rPtr++];
//		if(lByte == '\0') 
//			return lByte - rByte;
//	} while(lByte == rByte);
//	return lByte - rByte;
//}



int strcmp(const char * left, const char * right)
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
