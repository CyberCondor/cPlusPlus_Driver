#include "string.h"

String::String()                                         // Default Constructor
{
    head         = nullptr;
    curr         = nullptr;
    totalMemUsed = sizeof(*this);
}

String::String(Element *value) : String()                          // Param Constructor
{
    this->insert(value);
    //curr          = value;
    //head          = value;
    //totalMemUsed += value->getMemUsed();
}
String::String(Element element) : String()
{
    this->insert(element);
    //head = new Element(element);
    //curr = head;
    //totalMemUsed += element.getMemUsed();
}
//String::String(const Element & element) : String()
//{
//    head = new Element(element);
//    curr = head;
//    totalMemUsed += element.getMemUsed();
//}

String::~String()                                        // Destructor!
{
    if (head != nullptr)
    {
        curr = head;
        Element * next = nullptr;
        do
        {
            if (totalMemUsed > 0) {totalMemUsed -= curr->getMemUsed();}
            next = curr->getNext();
            delete curr;
            curr = next;
        } while (curr != head);
        head = nullptr;
    }
}

String::String(const String &other)  : String()                      // Copy Constructor 
{                               
    // Initialize head and curr pointers for the new string
    head = nullptr;
    curr = nullptr;

    // Copy each element from the other string to the new string
    if (other.head != nullptr) {
        Element *otherCurr = other.head;

        do
        {   // Create a new Element instance with the data from 'otherCurr'
            Element * newNode = new Element(*otherCurr);                       
            if (head == nullptr) {            // Insert the new node into the new string
                head = newNode;
                newNode->setNext(head);
            } else {
                curr->setNext(newNode);
                newNode->setNext(head);
            }

            curr = newNode;                   // Update curr pointer

            otherCurr = otherCurr->getNext(); // Move to the next node in 'other'
        } while (otherCurr != other.head);
        totalMemUsed = other.getMemUsed();
    }
}

void String::clear()                                   // Completely clear a String
{
    if (head != nullptr) {
        Element *curr = head;
        Element *next = nullptr;
        do 
        {   // Traverse the circular linked string and delete nodes
            totalMemUsed -= curr->getMemUsed();
            next = curr->getNext();
            delete curr;
            curr = next;
        }while (curr != head);
        head = nullptr; // Reset the head pointer
    }
}

/* This function inserts an Element at a specfied position.
 * Insert target @ position
 *
 * Function: insert
 * Param:  Element *, int, value and position to insert into String
 * return: void
 */
void String::insert(Element *target, int pos)
{
    if(head == nullptr) {      // If no String 
        head = target;		   // Create String
        target->setNext(head); // Point head to itself
        totalMemUsed += target->getMemUsed();
    }                         
    else
    {   
        curr = head;
        Element * prev = nullptr;
        int counter = 0;
        if (pos <= 0) {                   // Insert at head
            while(curr->getNext() != head)
                curr = curr->getNext();    
            curr->setNext(target);
            target->setNext(head);        // Set next pointer
            head = target;                // Reset head
            totalMemUsed += target->getMemUsed();
        } 
        else if (pos >= this->size()) {   // Insert at tail
            while(curr->getNext() != head) 
                curr = curr->getNext();   // Find end
            curr->setNext(target);        // Add to end of String
            target->setNext(head);        // Point end of String back to head
            totalMemUsed += target->getMemUsed();
        }
        else                              // Insert at position
        {
            while(curr->getNext() != head && counter < pos)
            {
                prev = curr;            // Save trailing ptr
                curr = curr->getNext(); // Point to next ptr
                counter++;              // Increment counter
            }
            target->setNext(curr);  // Target goes at position occupied by curr
            prev->setNext(target);  // prev points to target
            totalMemUsed += target->getMemUsed(); 
        }
    }
}
/* This function is a sorted insertion mutator.
 * Used to insert an Element to the string.
 * No duplicate Elements are allowed in this insertion.
 * 
 * Function: insert
 * Param:  Element *, value to insert into string
 * return: bool
 */
bool String::insert(Element *value) // Insertion Mutator
{
    int  position = 0;
    
    if (head == nullptr)            // If no String
    {
        head = value;               // Create the String
        value->setNext(head);       // Point head to itself  
        totalMemUsed += value->getMemUsed();
    }
    else
    {	curr = head;
        do
        {
            curr = curr->getNext();
            position++;
        }while(curr != head);
        insert(value,position);
    }
    return true;	
}
/* This function delegates insert @ position to the main insertion function
 * Insert target @ position
 *
 * Function: insert
 * Param:  Element &, int, value and position to insert into String
 * return: void
 */
void String::insert(const Element &targetRef, int pos) 
{
    Element *target = new Element(targetRef);  // Create a copy of the target Element
    insert(target, pos);                      // Delegate to the existing insert function
}
/* Delegate to existing insert function ^
 * 
 * Function: insert
 * Param:  Element &, value to insert into string
 * return: bool
 */
bool String::insert(const Element &targetRef)         
{
    Element *target = new Element(targetRef);
    return insert(target);
}

/* This function deletes an Element at a specified position in the String
 * Position Deletion Mutator
 * 
 * Function: remove
 * Param:  int, position of Element to remove from String
 * return: void
 */
void String::remove(int pos) 
{
    if (head == nullptr || size() == 0) {
        std::cout << "Nothing to remove." << std::endl;
        return; // Exit the method without doing anything
    }
    if (size() == 1) {  // If head.next points to self, nothing to traverse
        delete head;
        head = nullptr; 
        std::cout << "Delete Head." << std::endl;
        return;
    }
    if(head != nullptr) // If no String, nothing to remove. Redundant from above check.
    {
        curr = head;
        Element * prev = nullptr;
        int counter = 0;
        if(pos <= 0)                // Remove head
        {    
            totalMemUsed -= head->getMemUsed();
            head = head->getNext();
            prev = head;
            while (prev->getNext() != curr)
            {
                prev = prev->getNext();
            }
            prev->setNext(head);
            delete curr;
           // head = head->getNext(); // New head is next element
            std::cout << "Removed Position: 0" << std::endl;
        }
        else if(pos >= this->size()) // Remove tail
        {  
            while(curr->getNext() != head)
            {
                prev = curr;
                curr = curr->getNext();
            }
            prev->setNext(head);    // New end of the String
            totalMemUsed -= curr->getMemUsed();
            delete curr;            // Delete last element
            //std::cout << "Removed Position: " << this->size() + 1 << std::endl;
        }
        else
        { 
            while(curr->getNext() != head && counter < pos)
            {
                prev    = curr;
                curr    = curr->getNext();
                counter++;
            }
            //std::cout << "Removed Position: " << counter << std::endl;
            prev->setNext(curr->getNext()); 
            totalMemUsed -= curr->getMemUsed();
            delete curr;
        }
    }
}
/* This function deletes an Element from the string by value
 * Specific Deletion Mutator -> Delegates to Position Deletion Mutator.^
 *
 * Function: remove
 * Param:  Element *, value of Element to remove from String 
 * return: bool
 */
bool String::remove(Element *target)
{
    int position = 0;
    if(head != nullptr) { // If no String, nothing to remove.
        curr = head;
        while(curr->getNext() != head)
        {
            if(strcmp(curr->getData(), target->getData()) == 0)
            {
                //std::cout << "Removed " << target->getData() << " from the string.\n";
                remove(position);
                delete target;
                return true;
            }
            curr = curr->getNext();
            position++;
        }
    }
    std::cout << "Target '" << target->getData() << "' NOT FOUND.\n";
    delete target;
    return false;
}
/* Delegates to existing remove function ^
 *
 * Function: remove
 * Param:  Element , value of Element to remove from String 
 * return: bool
 */
bool String::remove(const Element &targetRef)
{
    Element * target = new Element(targetRef);
    return remove(target);
}

/* This function is a size accessor. It returns the size of the string.
 * If string is empty, returns 0, else returns size of the string.
 * Suggest re-writing this into a part of the class that is always tracked.*
 *
 *
 * Function: size
 * Param:  null
 * return: int
 */
int String::size() const
{
    int result = 1;
    if (head != nullptr) {
        Element * curr = head;
        while(curr->getNext() != head)
        {
            result++;
            curr = curr->getNext();
        }
    }
    else {return 0;}
    return result;
}  

/* This function prints detailed information about the memory of the String to standard out
 * 
 * Function: getDeets
 * Param:  null
 * return: void
 */
void String::getDeets() 
{ 
    if (head == nullptr) {
        std::cout << "String is empty." << std::endl;
        return;
    } 
    
    curr = head;
    size_t index     = 0;
    int colWidth     = static_cast<int>(log10(abs(sizeOfLargestElement()))) + 2; // Dynamically adjusts the column width based on largest element and size of string
    int indexSize    = 1;
    int maxIndexSize = static_cast<int>(log10(abs(size()))) + 2;
    size_t positionOfLargestElement  = 0;
    size_t sizeOfLargestElementBytes = 0;
    std::cout << "-------------------------*STRING DETAILS*-------------------------"                 << std::endl;
    std::cout << "\t                      String       Size :("<< this->size()                << ")"<< std::endl;
    std::cout << "\tTotal Memory of this  String    in BYTES:("<< this->getMemUsed()          << ")"<< std::endl;
    std::cout << "\tChar Count of Largest Element In String :("<< this->sizeOfLargestElement()<< ")"<< std::endl;
    std::cout << "\tStringMEM:      "                          << static_cast<const void*>(this)    << std::endl;
    std::cout << "\tHeadPTR:        "                          << &head                             << std::endl;
    std::cout << "\tHeadMEM:        "                          << static_cast<const void*>(head)    << std::endl;
    std::cout << std::endl;
    do 
    {
        if (curr->size() == this->sizeOfLargestElement()) {
            sizeOfLargestElementBytes = curr->getMemUsed();
            positionOfLargestElement  = index;
        }

        int nodeSize = static_cast<int>(log10(abs(curr->size()))) + 1; 
        if (index != 0) indexSize = static_cast<int>(log10(abs(index))) + 1;
        std::cout << std::left;
        std::cout << "idx:(" << index << ")";
        std::cout << std::setw((maxIndexSize - indexSize)) << " ";
        std::cout << "-NextMEM: "   << static_cast<const void*>(curr->getNext()) << " ";
        std::cout << "-CurrMEM: "   << static_cast<const void*>(curr) << " ";
        std::cout << "-DataMEM: "   << static_cast<const void*>(curr->getData()) << " ";
        std::cout << "-CharCountOfDataInElement:(" + std::to_string(curr->size()) + ")";
        std::cout << std::setw((colWidth - nodeSize))  << " ";
        std::cout << "-SizeOfElement_BYTES:(" << curr->getMemUsed() << ")";
        std::cout << std::endl;
		curr = curr->getNext();
        index++;
    } while(curr != head);
    std::cout << std::endl;
    std::cout << "\tHeadMEM:        "                            << static_cast<const void*>(head)    << std::endl;
    std::cout << "\tHeadPTR:        "                            << &head                             << std::endl;
    std::cout << "\tStringMEM:      "                            << static_cast<const void*>(this)    << std::endl;
    std::cout << "\tPosition     of Largest Element:("           << positionOfLargestElement    << ")"<< std::endl;
    std::cout << "\tChar Count   of Largest Element:("           << this->sizeOfLargestElement()<< ")"<< std::endl;
    std::cout << "\tSize         of Largest Element in BYTES:("  << sizeOfLargestElementBytes   << ")"<< std::endl;
    std::cout << "\tTotal Memory of this    String    in BYTES:("<< this->getMemUsed()          << ")"<< std::endl;
    std::cout << "\t                        String       Size :("<< this->size()                << ")"<< std::endl;
    std::cout << "-------------------------*END STRING DETAILS*-------------------------"               << std::endl;
}

/* This function prints the String to standard out
 * 
 * Function: print
 * Param:  null
 * return: void
 */
void String::print()
{ 
    if (head == nullptr) {
        std::cout << "String is empty." << std::endl;
        return;
    } 
    
    curr = head;
    int count        = 0;
    int indexSize    = 1;
    int maxIndexSize = static_cast<int>(log10(abs(size()))) + 2;
    std::cout << "-------------------------*FORWARD STRING*-------------------------" << std::endl;
    do 
    {
        if (count != 0) indexSize = static_cast<int>(log10(abs(count))) + 1;
        std::cout << std::left;
        std::cout << "idx:(" << count << ")";
        std::cout << std::setw((maxIndexSize - indexSize)) << " ";
        std::cout << "-Data: "<< curr->getData()          << std::endl;
		curr = curr->getNext();
        count++;
    } while(curr != head);
    std::cout << "-------------------------*END FORWARD STRING*-------------------------" << std::endl;
}

/* This function uses recursion to print the String to standard out in reverse
 * 
 * Function: printReverseHelper
 * Param:  the next node, the end of the string, if reached begining, where are we at in string, index size for column formatting
 * return: void
 */
void String::printReverseHelper(Element *node, Element *tail, bool isFirstNode, int &index, int &maxIndexSize)
{
    int indexSize = static_cast<int>(log10(abs(index))) + 1;
    
    if (node == tail && !isFirstNode) {
        std::cout << "-------------------------*REVERSE STRING*-------------------------" << std::endl;
        std::cout << std::left;
        std::cout << "idx:(" << index << ")";
        std::cout << std::setw((maxIndexSize - indexSize)) << " ";
        std::cout << " -Data: " << node->getData()     << std::endl;
        return;
    }

    printReverseHelper(node->getNext(), tail, false, index, maxIndexSize);
 
    index--;   
    if (index != 0){indexSize = static_cast<int>(log10(abs(index))) + 1;}
    if (index == 0){indexSize = 1;}
    
    std::cout << std::left;              // Print the data of the current node
    std::cout << "idx:(" << index << ")";
    std::cout << std::setw((maxIndexSize - indexSize)) << " ";
    std::cout << " -Data: " << node->getData() << std::endl;
}
/* This function prints detailed information about the memory of the string to standard out in reverse
 * Delegates to printReverseHelper 
 *
 * Function: printReverse
 * Param:  null
 * return: void
 */
void String::printReverse()
{
    if (head == nullptr) {
        std::cout << "String is empty." << std::endl;
        return;
    }

    curr = head;
    Element *tail    = nullptr;
    int index        = size() - 1; 
    int maxIndexSize = static_cast<int>(log10(abs(size()))) + 2;

    while (curr->getNext() != head) {
        curr = curr->getNext();
    }
    tail = curr;

    curr = head;                                               // Reset curr to head before starting recursion
    printReverseHelper(curr, tail, true, index, maxIndexSize); // Start recursion from the head node and pass the tail node
    std::cout << std::fixed;
    std::cout << "-------------------------*END REVERSE STRING*-------------------------" << std::endl;
}

/* This function returns the size of the largest element in the String
 * 
 * Function: sizeOfLargestElement
 * Param:  null
 * return: int
 */
int String::sizeOfLargestElement() const
{
    if (head == nullptr) {
        return 0;                 // Return 0 for an empty string
    }
    Element *curr = head;
    int      size = curr->size(); // Initialize with the size of the first element
    do                            // Traverse the string
    {
        if (curr->size() > size) {
            size = curr->size();
        }
        curr = curr->getNext();
    } while (curr != head);
    return size;
}

/* This function finds matching target value in the String. Exact match logic.
 * Delegates to strcmp, depends on Element class, <string.h>, <string>, etc.
 * 
 * Function: findMatch
 * Param:  Element *, the target value to find a match for in the string
 * return: bool
 */
bool String::findMatch(Element *target)
{
    bool found    = false;
    int  position = 0;
    if (head != nullptr) {
        curr = head;
        do
        {
            if(strcmp(curr->getData(), target->getData()) == 0)
            {	
                if(found == false) {
                    found = true;
                    std::cout << "\n-------------------------BEGIN String FIND MATCH: '" << target->getData() << "'------------------------" << std::endl;
                }
                std::cout << "idx:(" << position << ") \tData:" << curr->getData() << std::endl;
            }
            curr = curr->getNext();
            position++;
        } while(curr != head);
        if (found == true) {
            std::cout << "-------------------------END String FIND MATCH: '" << target->getData() << "'------------------------" << std::endl;
        }
    }
    delete target;
    return found;   
}
// CASE INSENSITIVE VERSION
bool String::findMatch_i(Element *target)
{
    bool found    = false;
    int  position = 0;
    if (head != nullptr) {
        curr = head;
        do
        {
            if(strcmp_i(curr->getData(), target->getData()) == 0)
            {	
                if(found == false) {
                    found = true;
                    std::cout << "\n-------------------------BEGIN String FIND CASE INSENSITIVE MATCH: '" << target->getData() << "'------------------------" << std::endl;
                }
                std::cout << "idx:(" << position << ") \tData:" << curr->getData() << std::endl;
            }
            curr = curr->getNext();
            position++;
        } while(curr != head);
        if (found == true) {
            std::cout << "-------------------------END String FIND CASE INSENSITIVE MATCH: '" << target->getData() << "'------------------------" << std::endl;
        }
    }
    delete target;
    return found;   
}
/* This function finds matching target value in the String. Exact match logic.
 * Delegates to existing findMatch function ^
 * 
 * Function: findMatch
 * Param:  Element &, the target value to find a match for in the string
 * return: bool
 */
bool String::findMatch(const Element &targetRef)
{
    Element * target = new Element(targetRef);
    return findMatch(target);
}
bool String::findMatch_i(const Element &targetRef)
{
    Element * target = new Element(targetRef);
    return findMatch_i(target);
}

/* Contains Chars in Sequence | e.g. car, aM, haM, caM, (etc.) contained in charM
 * An implicit wildcard in front of, behind, and between all chars in target search value.
 * Basically a super wildcard match.
 *
 * Function: containsSequence
 * Param:  Element &, the target value to search for in the string.
 * return: bool
 */
bool String::containsSequence(Element *target)
{
    bool found    = false;
    bool foundOne = false;
    int  position = 0;
    if (head != nullptr) {
        curr = head;
        do
        {
            const char* data       = curr->getData();
            const char* searchData = target->getData();

            int i = 0;
            int j = 0;

            while (data[i] != '\0') {
       
                if (data[i] == searchData[j]) {
                    j++;
                    if (searchData[j] == '\0') {
                        found = true;
                        break;
                    }
                }
                i++;
            }

            if (found) {
                if (foundOne == false) {
                    foundOne = true;
                    std::cout << "\n-------------------------BEGIN String CONTAINS Sequence: '" << target->getData() << "'------------------------" << std::endl;
                }
                std::cout << "idx:(" << position << ") \tData:" << curr->getData() << std::endl;
                found = false; // reset fount for next.
            }
             
            curr = curr->getNext();
            position++;
        } while(curr != head);
    } 
    if (foundOne) {
        std::cout << "-------------------------END String CONTAINS Sequence: '" << target->getData() << "'------------------------" << std::endl;
    }
    delete target;
    return foundOne;   
}
/* This function delegates to the existing containsSequence function ^
 * Contains Chars in Sequence | e.g. car, aM, haM, caM, (etc.) contained in charM
 * An implicit wildcard in front of, behind, and between all chars in target search value.
 * Basically a super wildcard match.
 *
 * Function: containsSequence
 * Param:  Element &, the target value to search for in the string.
 * return: bool
 */
bool String::containsSequence(const Element &targetRef)
{
    Element * target = new Element(targetRef);
    return containsSequence(target);
}

/* Case insensitive super wildcard search.
 * Contains Chars in Sequence | e.g. car, aM, ham, CAm, (etc.) contained in CHarM
 * An implicit wildcard in front of, behind, and between all chars in target search value.
 *
 * Function: containsSequence
 * Param:  Element &, the target value to search for in the string.
 * return: bool
 */
bool String::containsSequence_i(Element *target)
{
    bool found    = false;
    bool foundOne = false;
    int  position = 0;
    if (head != nullptr) {
        Element *curr = head;
        do
        {
            const char* data       = curr->getData();
            const char* searchData = target->getData();
            int i = 0;
            int j = 0;
            while (data[i] != '\0') {
           
                if (toLower(data[i]) == toLower(searchData[j])) {
                    j++;
                    if (searchData[j] == '\0') {
                        found = true;
                        break;
                    }
                }
                i++;
            }
            if (found) {
                if (foundOne == false) {
                    foundOne = true;
                    std::cout << "\n-------------------------BEGIN String Case Insensitive CONTAINS Sequence: '" << target->getData() << "'------------------------" << std::endl;
                }
                std::cout << "idx:(" << position << ") \tData:" << data << std::endl;
                found = false; // reset fount for next.
            }
            
            curr = curr->getNext();
            position++;
        } while(curr != head);
    } 
    if (foundOne) {
        std::cout << "-------------------------END String Case Insensitive CONTAINS Sequence: '" << target->getData() << "'------------------------" << std::endl;
    }
    delete target;
    return foundOne;   
}
// Case insensitive super wildcard search - delegates to existing ^
bool String::containsSequence_i(const Element &targetRef)
{
    Element * target = new Element(targetRef);
    return containsSequence_i(target);
}

/* This function is an explicit wildcard search. Requires explicit '*' wildcard search in Element target value.
 * 
 * Function: wildcardSearch
 * Param:  Element, explicit wildcard value to find in the string
 * return: bool
 */
bool String::wildcardSearch(Element *target)
{
    bool found    = false;
    bool foundOne = false;
    int  position = 0;
    if (head != nullptr) {
        curr = head;
        do
        {
            if (wildcardSearch(curr->getData(), target->getData())) {
                if (foundOne == false) {
                    std::cout << "\n-------------------------BEGIN String WILDCARD Search: '" << target->getData() << "'------------------------" << std::endl;
                    foundOne = true;
                }
                found = true;
                std::cout << "idx:(" << position << ") \tData:" << curr->getData() << std::endl;
            }
            curr = curr->getNext();
            position++;
        } while(curr != head);
        if (found == true) {
            std::cout << "-------------------------END String WILDCARD Search: '" << target->getData() << "'------------------------" << std::endl;
        }
    }
    delete target;
    return found;   
}
bool String::wildcardSearch_i(Element *target)
{
    bool found    = false;
    bool foundOne = false;
    int  position = 0;
    if (head != nullptr) {
        curr = head;
        do
        {
            if (wildcardSearch_i(curr->getData(), target->getData())) {
                if (foundOne == false) {
                    std::cout << "\n-------------------------BEGIN String Case Insensitive WILDCARD Search: '" << target->getData() << "'------------------------" << std::endl;
                    foundOne = true;
                }
                found = true;
                std::cout << "idx:(" << position << ") \tData:" << curr->getData() << std::endl;
            }
            curr = curr->getNext();
            position++;
        } while(curr != head);
        if (found == true) {
            std::cout << "-------------------------END String Case Insensitive WILDCARD Search: '" << target->getData() << "'------------------------" << std::endl;
        }
    }
    delete target;
    return found;   
}
/* This function is a wildcard search. Requires explicit '*' wildcard search in Element target value.
 * Delegates to the existing wildcardSearch function ^ 
 *
 * Function: wildcardSearch
 * Param:  Element, explicit wildcard value to find in the string
 * return: bool
 */
bool String::wildcardSearch(const Element &targetRef)
{
    Element * target = new Element(targetRef);
    return wildcardSearch(target);
}
bool String::wildcardSearch_i(const Element &targetRef)
{
    Element * target = new Element(targetRef);
    return wildcardSearch_i(target);
}
/* This function is a wildcard search helper.
 * 
 * Function: wildcardSearch
 * Param:  char *, char *, char and pattern to compare in search
 * return: bool
 */
bool String::wildcardSearch(const char *str, const char *pattern)
{
    // Initialize indices for str and pattern
    int strIndex = 0;
    int patternIndex = 0;
    int strStarIndex = -1; // Index of the last '*' character in str
    int patternStarIndex = -1; // Index of the last '*' character in pattern

    while (str[strIndex] != '\0') {
        if (pattern[patternIndex] == str[strIndex] || pattern[patternIndex] == '?') {
            strIndex++;                             // Characters match or pattern has a '?'; continue matching
            patternIndex++;
        }
        else if (pattern[patternIndex] == '*') {
            strStarIndex = strIndex;                // '*' character in pattern; update indices
            patternStarIndex = patternIndex;
            patternIndex++;
        }
        else if (patternStarIndex != -1) {
            patternIndex = patternStarIndex + 1;    // Mismatch, but we have a previous '*'; backtrack
            strStarIndex++;
            strIndex = strStarIndex;
        }
        else {return false;}                        // Mismatch and no previous '*'; not matching
    }

    while (pattern[patternIndex] == '*') {          // Check for remaining characters in the pattern
        patternIndex++;
    }

    return (pattern[patternIndex] == '\0');         // If we've consumed the entire pattern, it's a match
}
bool String::wildcardSearch_i(const char *str, const char *pattern)
{
    // Initialize indices for str and pattern
    int strIndex = 0;
    int patternIndex = 0;
    int strStarIndex = -1; // Index of the last '*' character in str
    int patternStarIndex = -1; // Index of the last '*' character in pattern

    while (str[strIndex] != '\0') {
        if (toLower(pattern[patternIndex]) == toLower(str[strIndex]) || pattern[patternIndex] == '?') {
            strIndex++;                             // Characters match or pattern has a '?'; continue matching
            patternIndex++;
        }
        else if (pattern[patternIndex] == '*') {
            strStarIndex = strIndex;                // '*' character in pattern; update indices
            patternStarIndex = patternIndex;
            patternIndex++;
        }
        else if (patternStarIndex != -1) {
            patternIndex = patternStarIndex + 1;    // Mismatch, but we have a previous '*'; backtrack
            strStarIndex++;
            strIndex = strStarIndex;
        }
        else {return false;}                        // Mismatch and no previous '*'; not matching
    }

    while (pattern[patternIndex] == '*') {          // Check for remaining characters in the pattern
        patternIndex++;
    }

    return (pattern[patternIndex] == '\0');         // If we've consumed the entire pattern, it's a match
}

// vvvvvvvvvvvvvvvvvvvvvvvvvvv--------------------------------------------------------------------------- 
//
// Operator Overload Functions
//
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^---------------------------------------------------------------------------

/* This function copies the contents of one String to another String. COPY assignment operator
 * 
 * Operator: =
 * Param:  const String & other, The string to be copied FROM
 * return: String &,             The string to be copied to
 * e.g. 
 *  string1 = string2
 */
String & String::operator=(const String &other)  
{
    //std::cout << "copy assignment called" << std::endl;
    if (this != &other) {
        this->clear();                                 // Clear the current string
        Element *otherCurr = other.head;               // Copy elements from the other string
        if(otherCurr != nullptr) {
            do 
            {
                this->insert(new Element(*otherCurr)); // Copy the Element element
                otherCurr = otherCurr->getNext();
            } while (otherCurr != other.head);
        } 
    }
    return *this;
}

/* This operator moves the contents of one String to another String. MOVE assignment operator
 * This operation moves the ownership of memory of the data to this String from other String.
 * Results in the other string being cleared 
 *
 * Operator: =
 * Param:  const String && other, The string to be moved FROM
 * return: String &,              The string to be moved to
 * e.g. 
 *  string1 = std::move(string2)
 */
String & String::operator=(String &&other)  
{
    std::cout << "move assignment called" << std::endl;
    if (this != &other) {
        this->clear();                     // Clear the current string
        this->head = other.head;           // Move elements from the other string
        this->totalMemUsed = other.getMemUsed();
        other.head = nullptr;              // Dereference other's head
        other.clear();                     // Clear other to an empty string to prevent unexpected behavior
        std::cout << this << " " << &other << std::endl;
    }
    return *this;
}

/* This operator adds one string to another string and returns a new string
 * Addition Operator
 *
 * Operator: +
 * Param:  const String && other, The string to be added from
 * return: String &,              The string to be added to
 * e.g. 
 *  string1 = string2 + string3 + string4 + string5
 */
String String::operator+(const String &other) const 
{
    String newString(*this);                   // Create a new string by copying the current string 
    Element *otherCurr = other.head;       // Initialize otherCurr to the head of the other string 
    if (otherCurr != nullptr) {            // Traverse the circular linked string
        do 
        {   // Create a new Element object with the same data as otherCurr
            Element *newElement = new Element(otherCurr->getData());
            newString.insert(newElement);     // Insert the new Element into the new string
            otherCurr = otherCurr->getNext();
        } while (otherCurr != other.head); // Loop until we reach the head again
    }
    return newString;                        // Return the new string with concatenated elements
}    

/* This operator compares equality of Strings
 * Equality operator
 *
 * Operator: ==
 * Param:  const String & other, rvalue
 * return: bool
 * e.g. 
 *  string1 == string2
 */
bool String::operator==(const String &other) const  
{
    if (this == &other)                    // Check if it's the same object
        return true;

    Element *thisCurr = head;
    Element *otherCurr = other.head;

    if (thisCurr == nullptr && otherCurr == nullptr) {
        return true;                       // Both strings are empty, consider them equal
    }
    if (thisCurr != nullptr && otherCurr == nullptr) {
        return false;
    }
    if (thisCurr == nullptr && otherCurr != nullptr) {
        return false;
    }
    if (thisCurr != nullptr && otherCurr != nullptr) {
         do                                // Traverse the circular linked strings
         {    
             if (!(strcmp(thisCurr->getData(), otherCurr->getData()) == 0)) {
                 return false;             // If any node doesn't match or reaches the end, strings are not equal
             }
             thisCurr = thisCurr->getNext();
             otherCurr = otherCurr->getNext();
             if (thisCurr == head && otherCurr == other.head)
                 break;                    // If we reach the head again, we've completed a full loop, exit the loop

         } while (thisCurr != head && otherCurr != other.head);
    }

    return true;                           // Strings are equal if both strings complete a full loop
}

/* This operator compares inequality of Strings
 * inequality operator -> delegates to equality operator
 *
 * Operator: !=
 * Param:  const String & other, rvalue
 * return: bool
 * e.g. 
 *  string1 != string2
 */
bool String::operator!=(const String &other) const 
{
    return !(*this == other);
}

/* This operator prints to std::ostream
 * Delegates to Element's stream output operator
 * CSV style format
 *
 * Operator: <<
 * Param:  String &
 * return: std::ostream
 */
std::ostream & operator<<(std::ostream &out, String &string) // Stream output operator Comma Sepperated Values (CSV format)
{
    Element *curr = string.getHead();
    if (curr != nullptr) {
        do 
        {
            if(curr->getNext() != string.getHead()){
                out << *curr << " "; // Call the Element's stream output operator
            }
            else{out << *curr;}
            curr = curr->getNext();
        }while(curr != string.getHead());
    }
    return out;
}
std::ostream & operator<<(std::ostream &out, String string) // Stream output operator Comma Sepperated Values (CSV format)
{
    Element *curr = string.getHead();
    if (curr != nullptr) {
        do 
        {
            if(curr->getNext() != string.getHead()){
                out << *curr << " "; // Call the Element's stream output operator
            }
            else{out << *curr;}
            curr = curr->getNext();
        }while(curr != string.getHead());
    }
    return out;
}

std::istream & operator >> (std::istream & in, String & string)        //Stream Extraction
{
    while(in.good() == true && in.peek() != '\0' && in.peek() != '\n' && in.peek() != EOF) {
        Element * newE = new Element;
        in >> newE;
        string.insert(newE);
    }
    in.clear();
    in.ignore();
    return in;	
}
