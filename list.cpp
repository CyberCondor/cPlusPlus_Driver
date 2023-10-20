#include "list.h"

List::List()                                         // Default Constructor
{
    head         = nullptr;
    curr         = nullptr;
    totalMemUsed = sizeof(*this);
}
List::List(Element *value)                           // Param Constructor
{
    curr          = value;
    head          = value;
    totalMemUsed += value->getMemUsed();
}
List::~List()                                        // Destructor!
{
    if (head != nullptr)
    {
        curr = head;
        Element * next = nullptr;
        do
        {
            totalMemUsed -= curr->getMemUsed();
            next = curr->getNext();
            delete curr;
            curr = next;
        } while (curr != head);
        head = nullptr;
    }
}
List::List(const List &other)                        // Copy Constructor 
{                               
    // Initialize head and curr pointers for the new list
    head = nullptr;
    curr = nullptr;

    // Copy each element from the other list to the new list
    if (other.head != nullptr) {
        Element *otherCurr = other.head;

        do
        {   // Create a new Element instance with the data from 'otherCurr'
            Element *newNode = new Element(*otherCurr);                       
            if (head == nullptr) {            // Insert the new node into the new list
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

void List::clear()                                   // Completely clear a List
{
    if (head != nullptr) {
        Element *curr = head;
        Element *next = nullptr;
        do 
        {   // Traverse the circular linked list and delete nodes
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
 * Param:  Element *, int, value and position to insert into List
 * return: void
 */
void List::insert(Element *target, int pos)   
{
    if(head == nullptr) {      // If no List 
        head = target;		   // Create List
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
            curr->setNext(target);        // Add to end of List
            target->setNext(head);        // Point end of List back to head
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
 * Used to insert an Element to the list.
 * No duplicate Elements are allowed in this insertion.
 * 
 * Function: insert
 * Param:  Element *, value to insert into list
 * return: bool
 */
bool List::insert(Element *value)   // Sorted Insertion Mutator
{
    int  position = 0;
    bool found    = false;

    if (head == nullptr)            // If no List
    {
        head = value;               // Create the List
        value->setNext(head);       // Point head to itself  
        totalMemUsed += value->getMemUsed();
    }
    else
    {	curr = head;
        do
        {
            if(strcmp(curr->getData(), value->getData()) == 0) {
                found = true;      // Don't add to the list. Duplicate was found.
                delete value;
                break;
            }
            if(strcmp(curr->getData(), value->getData()) > 0) {
                found = false;    // Sort list by title. Break and insert at position.
                break;
            }
            curr = curr->getNext();
            position++;
        }while(curr != head);
        if(found == false) {
            insert(value,position);
            return true;	
        }
        else { return false; }
    }
    return true;	
}
/* This function delegates insert @ position to the main insertion function
 * Insert target @ position
 *
 * Function: insert
 * Param:  Element &, int, value and position to insert into List
 * return: void
 */
void List::insert(const Element &targetRef, int pos) 
{
    Element *target = new Element(targetRef);  // Create a copy of the target Element
    insert(target, pos);                      // Delegate to the existing insert function
}
/* Delegate to existing insert function ^
 * 
 * Function: insert
 * Param:  Element &, value to insert into list
 * return: bool
 */
bool List::insert(const Element &targetRef)         
{
    Element *target = new Element(targetRef);
    return insert(target);
}

/* This function deletes an Element at a specified position in the List
 * Position Deletion Mutator
 * 
 * Function: getDeets
 * Param:  int, position of Element to remove from List
 * return: void
 */
void List::remove(int pos) 
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
    if(head != nullptr) // If no List, nothing to remove. Redundant from above check.
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
            //std::cout << "Removed Position: 0" << std::endl;
        }
        else if(pos >= this->size()) // Remove tail
        {  
            while(curr->getNext() != head)
            {
                prev = curr;
                curr = curr->getNext();
            }
            prev->setNext(head);    // New end of the List
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
/* This function deletes an Element from the list by value
 * Specific Deletion Mutator -> Delegates to Position Deletion Mutator.^
 *
 * Function: remove
 * Param:  Element *, value of Element to remove from List 
 * return: bool
 */
bool List::remove(Element *target)
{
    int position = 0;
    if(head != nullptr) { // If no List, nothing to remove.
        curr = head;
        while(curr->getNext() != head)
        {
            if(strcmp(curr->getData(), target->getData()) == 0)
            {
                //std::cout << "Removed " << target->getData() << " from the list.\n";
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
 * Param:  Element , value of Element to remove from List 
 * return: bool
 */
bool List::remove(const Element &targetRef)
{
    Element * target = new Element(targetRef);
    return remove(target);
}

/* This function is a size accessor. It returns the size of the list.
 * If list is empty, returns 0, else returns size of the list.
 * Suggest re-writing this into a part of the class that is always tracked.*
 *
 *
 * Function: size
 * Param:  null
 * return: int
 */
int List::size() const
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

Element List::getDataAtPosition(int pos)   
{
    if(head == nullptr) {      // If no List 
        return Element();
    }                         
    else
    {   
        Element * curr = head;
        int counter = 0;
        if (pos <= 0) {                   // Get head
            return Element(curr->getData());
        } 
        else if (pos >= this->size()) {   // Get tail
            while(curr->getNext() != head) 
                curr = curr->getNext();   // Find end
            return Element(curr->getData());
        }
        else                              // Insert at position
        {
            while(curr->getNext() != head && counter < pos)
            {
                curr = curr->getNext(); // Point to next ptr
                counter++;              // Increment counter
            }
            return Element(curr->getData());
        }
    }
    return Element();    // Return Empty Element by Default
}

/* This function prints detailed information about the memory of the List to standard out
 * 
 * Function: getDeets
 * Param:  null
 * return: void
 */
void List::getDeets() 
{ 
    if (head == nullptr) {
        std::cout << "List is empty." << std::endl;
        return;
    } 
    
    curr = head;
    size_t index     = 0;
    int colWidth     = static_cast<int>(log10(abs(sizeOfLargestElement()))) + 2; // Dynamically adjusts the column width based on largest element and size of list
    int indexSize    = 1;
    int maxIndexSize = static_cast<int>(log10(abs(size()))) + 2;
    size_t positionOfLargestElement  = 0;
    size_t sizeOfLargestElementBytes = 0;
    std::cout << "-------------------------*LIST DETAILS*-------------------------"               << std::endl;
    std::cout << "\t                      List       Size :("<< this->size()                << ")"<< std::endl;
    std::cout << "\tTotal Memory of this  List    in BYTES:("<< this->getMemUsed()          << ")"<< std::endl;
    std::cout << "\tChar Count of Largest Element In List :("<< this->sizeOfLargestElement()<< ")"<< std::endl;
    std::cout << "\tListMEM:        "                        << static_cast<const void*>(this)    << std::endl;
    std::cout << "\tHeadPTR:        "                        << &head                             << std::endl;
    std::cout << "\tHeadMEM:        "                        << static_cast<const void*>(head)    << std::endl;
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
    std::cout << "\tHeadMEM:        "                          << static_cast<const void*>(head)    << std::endl;
    std::cout << "\tHeadPTR:        "                          << &head                             << std::endl;
    std::cout << "\tListMEM:        "                          << static_cast<const void*>(this)    << std::endl;
    std::cout << "\tPosition     of Largest Element:("         << positionOfLargestElement    << ")"<< std::endl;
    std::cout << "\tChar Count   of Largest Element:("         << this->sizeOfLargestElement()<< ")"<< std::endl;
    std::cout << "\tSize         of Largest Element in BYTES:("<< sizeOfLargestElementBytes   << ")"<< std::endl;
    std::cout << "\tTotal Memory of this    List    in BYTES:("<< this->getMemUsed()          << ")"<< std::endl;
    std::cout << "\t                        List       Size :("<< this->size()                << ")"<< std::endl;
    std::cout << "-------------------------*END LIST DETAILS*-------------------------"             << std::endl;
}

/* This function prints the List to standard out
 * 
 * Function: print
 * Param:  null
 * return: void
 */
void List::print()
{ 
    if (head == nullptr) {
        std::cout << "List is empty." << std::endl;
        return;
    } 
    
    curr = head;
    int count        = 0;
    int indexSize    = 1;
    int maxIndexSize = static_cast<int>(log10(abs(size()))) + 2;
    std::cout << "-------------------------*FORWARD LIST*-------------------------" << std::endl;
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
    std::cout << "-------------------------*END FORWARD LIST*-------------------------" << std::endl;
}

/* This function uses recursion to print the List to standard out in reverse
 * 
 * Function: printReverseHelper
 * Param:  the next node, the end of the list, if reached begining, where are we at in list, index size for column formatting
 * return: void
 */
void printReverseHelper(Element *node, Element *tail, bool isFirstNode, int &index, int &maxIndexSize)
{
    int indexSize = static_cast<int>(log10(abs(index))) + 1;
    
    if (node == tail && !isFirstNode) {
        std::cout << "-------------------------*REVERSE LIST*-------------------------" << std::endl;
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
/* This function prints detailed information about the memory of the list to standard out in reverse
 * Delegates to printReverseHelper 
 *
 * Function: printReverse
 * Param:  null
 * return: void
 */
void List::printReverse()
{
    if (head == nullptr) {
        std::cout << "List is empty." << std::endl;
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
    std::cout << "-------------------------*END REVERSE LIST*-------------------------" << std::endl;
}

/* This function returns the size of the largest element in the List
 * 
 * Function: sizeOfLargestElement
 * Param:  null
 * return: int
 */
int List::sizeOfLargestElement() const
{
    if (head == nullptr) {
        return 0;                 // Return 0 for an empty list
    }
    Element *curr = head;
    int      size = curr->size(); // Initialize with the size of the first element
    do                            // Traverse the list
    {
        if (curr->size() > size) {
            size = curr->size();
        }
        curr = curr->getNext();
    } while (curr != head);
    return size;
}

/* This function finds matching target value in the List. Exact match logic.
 * Delegates to strcmp, depends on Element class, <string.h>, <string>, etc.
 * 
 * Function: findMatch
 * Param:  Element *, the target value to find a match for in the list
 * return: bool
 */
bool List::findMatch(Element *target)
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
                    std::cout << "\n-------------------------BEGIN List FIND MATCH: '" << target->getData() << "'------------------------" << std::endl;
                }
                std::cout << "idx:(" << position << ") \tData:" << curr->getData() << std::endl;
            }
            curr = curr->getNext();
            position++;
        } while(curr != head);
        if (found == true) {
            std::cout << "-------------------------END List FIND MATCH: '" << target->getData() << "'------------------------" << std::endl;
        }
    }
    delete target;
    return found;   
}
// CASE INSENSITIVE VERSION
bool List::findMatch_i(Element *target)
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
                    std::cout << "\n-------------------------BEGIN List FIND CASE INSENSITIVE MATCH: '" << target->getData() << "'------------------------" << std::endl;
                }
                std::cout << "idx:(" << position << ") \tData:" << curr->getData() << std::endl;
            }
            curr = curr->getNext();
            position++;
        } while (curr != head);
        if (found == true) {
            std::cout << "-------------------------END List FIND CASE INSENSITIVE MATCH: '" << target->getData() << "'------------------------" << std::endl;
        }
    }
    delete target;
    return found;   
}
/* This function finds matching target value in the List. Exact match logic.
 * Delegates to existing findMatch function ^
 * 
 * Function: findMatch
 * Param:  Element &, the target value to find a match for in the list
 * return: bool
 */
bool List::findMatch(const Element &targetRef)
{
    Element * target = new Element(targetRef);
    return findMatch(target);
}
bool List::findMatch_i(const Element &targetRef)
{
    Element * target = new Element(targetRef);
    return findMatch_i(target);
}

/* Contains Chars in Sequence | e.g. car, aM, haM, caM, (etc.) contained in charM
 * An implicit wildcard in front of, behind, and between all chars in target search value.
 * Basically a super wildcard match.
 *
 * Function: containsSequence
 * Param:  Element &, the target value to search for in the list.
 * return: bool
 */
bool List::containsSequence(Element *target)
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
                    std::cout << "\n-------------------------BEGIN List CONTAINS Sequence: '" << target->getData() << "'------------------------" << std::endl;
                }
                std::cout << "idx:(" << position << ") \tData:" << curr->getData() << std::endl;
                found = false; // reset fount for next.
            }
            
            curr = curr->getNext();
            position++;
        } while (curr != head);
    } 
    if (foundOne) {
        std::cout << "-------------------------END List CONTAINS Sequence: '" << target->getData() << "'------------------------" << std::endl;
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
 * Param:  Element &, the target value to search for in the list.
 * return: bool
 */
bool List::containsSequence(const Element &targetRef)
{
    Element * target = new Element(targetRef);
    return containsSequence(target);
}

/* Case insensitive super wildcard search.
 * Contains Chars in Sequence | e.g. car, aM, ham, CAm, (etc.) contained in CHarM
 * An implicit wildcard in front of, behind, and between all chars in target search value.
 *
 * Function: containsSequence
 * Param:  Element &, the target value to search for in the list.
 * return: bool
 */
bool List::containsSequence_i(Element *target)
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
                    std::cout << "\n-------------------------BEGIN List Case Insensitive CONTAINS Sequence: '" << target->getData() << "'------------------------" << std::endl;
                }
                std::cout << "idx:(" << position << ") \tData:" << data << std::endl;
                found = false; // reset fount for next.
            }
            
            curr = curr->getNext();
            position++;
        } while (curr != head);
    } 
    if (foundOne) {
        std::cout << "-------------------------END List Case Insensitive CONTAINS Sequence: '" << target->getData() << "'------------------------" << std::endl;
    }
    delete target;
    return foundOne;   
}
// Case insensitive super wildcard search - delegates to existing ^
bool List::containsSequence_i(const Element &targetRef)
{
    Element * target = new Element(targetRef);
    return containsSequence_i(target);
}

/* This function is an explicit wildcard search. Requires explicit '*' wildcard search in Element target value.
 * 
 * Function: wildcardSearch
 * Param:  Element, explicit wildcard value to find in the list
 * return: bool
 */
bool List::wildcardSearch(Element *target)
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
                    std::cout << "\n-------------------------BEGIN List WILDCARD Search: '" << target->getData() << "'------------------------" << std::endl;
                    foundOne = true;
                }
                found = true;
                std::cout << "idx:(" << position << ") \tData:" << curr->getData() << std::endl;
            }
            curr = curr->getNext();
            position++;
        } while (curr != head);
        if (found == true) {
            std::cout << "-------------------------END List WILDCARD Search: '" << target->getData() << "'------------------------" << std::endl;
        }
    }
    delete target;
    return found;   
}
bool List::wildcardSearch_i(Element *target)
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
                    std::cout << "\n-------------------------BEGIN List Case Insensitive WILDCARD Search: '" << target->getData() << "'------------------------" << std::endl;
                    foundOne = true;
                }
                found = true;
                std::cout << "idx:(" << position << ") \tData:" << curr->getData() << std::endl;
            }
            curr = curr->getNext();
            position++;
        } while (curr != head);
        if (found == true) {
            std::cout << "-------------------------END List Case Insensitive WILDCARD Search: '" << target->getData() << "'------------------------" << std::endl;
        }
    }
    delete target;
    return found;   
}
/* This function is a wildcard search. Requires explicit '*' wildcard search in Element target value.
 * Delegates to the existing wildcardSearch function ^ 
 *
 * Function: wildcardSearch
 * Param:  Element, explicit wildcard value to find in the list
 * return: bool
 */
bool List::wildcardSearch(const Element &targetRef)
{
    Element * target = new Element(targetRef);
    return wildcardSearch(target);
}
bool List::wildcardSearch_i(const Element &targetRef)
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
bool List::wildcardSearch(const char *str, const char *pattern)
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
bool List::wildcardSearch_i(const char *str, const char *pattern)
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

/* This function copies the contents of one List to another List. COPY assignment operator
 * 
 * Operator: =
 * Param:  const List & other, The list to be copied FROM
 * return: List &,             The list to be copied to
 * e.g. 
 *  list1 = list2
 */
List & List::operator=(const List &other)  
{
    std::cout << "copy assignment called" << std::endl;
    if (this != &other) {
        this->clear();                                 // Clear the current list
        Element *otherCurr = other.head;               // Copy elements from the other list
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

/* This operator moves the contents of one List to another List. MOVE assignment operator
 * This operation moves the ownership of memory of the data to this List from other List.
 * Results in the other list being cleared 
 *
 * Operator: =
 * Param:  const List && other, The list to be moved FROM
 * return: List &,              The list to be moved to
 * e.g. 
 *  list1 = std::move(list2)
 */
List & List::operator=(List &&other)  
{
    std::cout << "move assignment called" << std::endl;
    if (this != &other) {
        this->clear();                     // Clear the current list
        this->head = other.head;           // Move elements from the other list
        this->totalMemUsed = other.getMemUsed();
        other.head = nullptr;              // Dereference other's head
        other.clear();                     // Clear other to an empty list to prevent unexpected behavior
        std::cout << this << " " << &other << std::endl;
    }
    return *this;
}

/* This operator adds one list to another list and returns a new list
 * Addition Operator
 *
 * Operator: +
 * Param:  const List && other, The list to be added from
 * return: List &,              The list to be added to
 * e.g. 
 *  list1 = list2 + list3 + list4 + list5
 */
List List::operator+(const List &other) const 
{
    List newList(*this);                   // Create a new list by copying the current list 
    Element *otherCurr = other.head;       // Initialize otherCurr to the head of the other list 
    if (otherCurr != nullptr) {            // Traverse the circular linked list
        do 
        {   // Create a new Element object with the same data as otherCurr
            Element *newElement = new Element(otherCurr->getData());
            newList.insert(newElement);     // Insert the new Element into the new list
            otherCurr = otherCurr->getNext();
        } while (otherCurr != other.head); // Loop until we reach the head again
    }
    return newList;                        // Return the new list with concatenated elements
}    

/* This operator compares equality of Lists
 * Equality operator
 *
 * Operator: ==
 * Param:  const List & other, rvalue
 * return: bool
 * e.g. 
 *  list1 == list2
 */
bool List::operator==(const List &other) const  
{
    if (this == &other)                    // Check if it's the same object
        return true;

    Element *thisCurr = head;
    Element *otherCurr = other.head;

    if (thisCurr == nullptr && otherCurr == nullptr) {
        return true;                       // Both lists are empty, consider them equal
    }
    if (thisCurr != nullptr && otherCurr == nullptr) {
        return false;
    }
    if (thisCurr == nullptr && otherCurr != nullptr) {
        return false;
    }
    if (thisCurr != nullptr && otherCurr != nullptr) {
         do                                // Traverse the circular linked lists
         {    
             if (!(strcmp(thisCurr->getData(), otherCurr->getData()) == 0)) {
                 return false;             // If any node doesn't match or reaches the end, lists are not equal
             }
             thisCurr = thisCurr->getNext();
             otherCurr = otherCurr->getNext();
             if (thisCurr == head && otherCurr == other.head)
                 break;                    // If we reach the head again, we've completed a full loop, exit the loop

         } while (thisCurr != head && otherCurr != other.head);
    }
    return true;                           // Lists are equal if both lists complete a full loop
}

/* This operator compares inequality of Lists
 * inequality operator -> delegates to equality operator
 *
 * Operator: !=
 * Param:  const List & other, rvalue
 * return: bool
 * e.g. 
 *  list1 != list2
 */
bool List::operator!=(const List &other) const 
{
    return !(*this == other);
}

/* This operator prints to std::ostream
 * Delegates to Element's stream output operator
 * CSV style format
 *
 * Operator: <<
 * Param:  List &
 * return: std::ostream
 */
std::ostream & operator<<(std::ostream &out, List &list) // Stream output operator Comma Sepperated Values (CSV format)
{
    Element *curr = list.getHead();
    if (curr != nullptr) {
        do 
        {
            if (curr->getNext() != list.getHead())
                 out <<"\""<< *curr << "\","; // Call the Element's stream output operator
            else out <<"\""<< *curr << "\"";  
            curr = curr->getNext();
        } while (curr != list.getHead());
    }
    return out;
}
