#include "list.h"

List::List()
{
    head         = nullptr;
    curr         = nullptr;
    totalMemUsed = sizeof(*this);
}

List::List(String * value)
{
    curr          = value;
    head          = value;
    totalMemUsed += value->getMemUsed();
}

List::~List()
{
    if (head != nullptr)
    {
        curr = head;
        String * next = nullptr;
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
void List::clear()
{
    if (head != nullptr) {
        String *curr = head;
        String *next = nullptr;
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

List::List(const List &other)                                 // Copy Constructor 
{                               
    // Initialize head and curr pointers for the new list
    head = nullptr;
    curr = nullptr;

    // Copy each element from the other list to the new list
    if (other.head != nullptr) {
        String *otherCurr = other.head;

        do
        {                                            // Create a new String instance with the data from 'otherCurr'
            String *newNode = new String(*otherCurr);                        //(otherCurr->getData());
            if (head == nullptr) {                   // Insert the new node into the new list
                head = newNode;
                newNode->setNext(head);
            } else {
                curr->setNext(newNode);
                newNode->setNext(head);
            }

            curr = newNode; // Update curr pointer

            otherCurr = otherCurr->getNext(); // Move to the next node in 'other'
        } while (otherCurr != other.head);
        totalMemUsed = other.getMemUsed();
    }
}

void List::insert(String * target, int pos)   // Insert target @ position
{
    if(head == nullptr) {      // If no List 
        head = target;		   // Create List
        target->setNext(head); // Point head to itself
        totalMemUsed += target->getMemUsed();
    }                         
    else
    {   
        curr = head;
        String * prev = nullptr;
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

bool List::insert(String * value)   // Sorted Insertion Mutator
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
//    insert(value, size());
    return true;	
}

void List::insert(const String &target, int pos)   // Insert target @ position
{
    String *value = new String(target);  // Create a copy of the target String
    insert(value, pos);                  // Delegate to the existing insert function
}

bool List::insert(const String &valueRef)     // Sorted Insertion Mutator
{
    int  position = 0;
    bool found    = false;

    String *value = new String(valueRef);

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
//    insert(value, size());
    return true;	
}

void List::remove(int pos)         // Position Deletion Mutator
{
    if(head != nullptr) // If no List, nothing to remove.
    {
        curr = head;
        String * prev = nullptr;
        int counter = 0;
        if(pos <= 0)                // Remove head
        {                    
            totalMemUsed -= head->getMemUsed();
            head = head->getNext(); // New head is next element
            std::cout << "Removed Position: " << pos << std::endl;
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
            std::cout << "Removed Position: " << this->size() + 1 << std::endl;
        }
        else
        { 
            while(curr->getNext() != head && counter < pos)
            {
                prev    = curr;
                curr    = curr->getNext();
                counter = counter + 1;
            }
            std::cout << "Removed Position: " << counter << std::endl;
            prev->setNext(curr->getNext()); 
            totalMemUsed -= curr->getMemUsed();
            delete curr;
        }
    }
}

void List::remove(String * target)  // Specific Deletion mutator
{
    int position = 0;
    curr = head;
    while(curr->getNext() != head)
    {
        if(strcmp(curr->getData(), target->getData()) == 0)
        {
            std::cout << "Removed " << target->getData() << " from the list.\n";
            remove(position);	
        }
        curr = curr->getNext();
        position++;
    }
}

int List::size() const            // Size Accessor
{
    int result = 0;
    String * curr = head;
    if (curr != nullptr) {
        while(curr->getNext() != head)
        {
            result++;
            curr = curr->getNext();
        }
    }
    return result;
}  

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
    std::cout << "-------------------------*LIST DETAILS*-------------------------"              << std::endl;
    std::cout << "\tTotal Memory of this List in bytes:("   << this->getMemUsed()          << ")"<< std::endl;
    std::cout << "\tChar Count of Largest Element In List:("<< this->sizeOfLargestElement()<< ")"<< std::endl;
    std::cout << "\tListMEM:        "                       << static_cast<const void*>(this)    << std::endl;
    std::cout << "\tHeadPTR:        "                       << &head                             << std::endl;
    std::cout << "\tHeadMEM:        "                       << static_cast<const void*>(head)    << std::endl;
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
    std::cout << "\tSize         of Largest Element in Bytes:("<< sizeOfLargestElementBytes   << ")"<< std::endl;
    std::cout << "\tTotal Memory of this* List      in bytes:("<< this->getMemUsed()          << ")"<< std::endl;
    std::cout << "-------------------------*END LIST DETAILS*-------------------------"             << std::endl;
}

void List::print()
{ 
    if (head == nullptr) {
        std::cout << "List is empty." << std::endl;
        return;
    } 
    
    curr = head;
    int count        = 0;
  //  int colWidth     = static_cast<int>(log10(abs(sizeOfLargestElement()))) + 2; // Dynamically adjusts the column width based on largest element and size of list
    int indexSize    = 1;
    int maxIndexSize = static_cast<int>(log10(abs(size()))) + 2;
    std::cout << "-------------------------*FORWARD LIST*-------------------------" << std::endl;
    do 
    {
        //int nodeSize = static_cast<int>(log10(abs(curr->size()))) + 1; 
        if (count != 0) indexSize = static_cast<int>(log10(abs(count))) + 1;
        std::cout << std::left;
        std::cout << "idx:(" << count << ")";
        std::cout << std::setw((maxIndexSize - indexSize)) << " ";
//        std::cout << "-dataSize:(" + std::to_string(curr->size()) + ")";
//        std::cout << std::setw((colWidth - nodeSize))     << " ";
        std::cout << "-Data: "<< curr->getData()          << std::endl;
		curr = curr->getNext();
        count++;
    } while(curr != head);
    std::cout << "-------------------------*END FORWARD LIST*-------------------------" << std::endl;
}

void printReverseHelper(String *node, String *tail, bool isFirstNode, int &index, int &colWidth)
{
    int nodeSize = static_cast<int>(log10(abs(node->size()))) + 1; 
    int indexSize = static_cast<int>(log10(abs(index))) + 1;
    
    if (node == tail && !isFirstNode) {
        std::cout << "-------------------------*REVERSE LIST*-------------------------" << std::endl;
        std::cout << std::left;
        std::cout << "idx:(" << index << ")";
        std::cout << std::setw((colWidth - indexSize)) << " ";
        std::cout << " -dataSize:(" + std::to_string(node->size()) + ")";
        std::cout << std::setw((colWidth - nodeSize))  << " ";
        std::cout << " -Data: " << node->getData()     << std::endl;
        return;
    }

    printReverseHelper(node->getNext(), tail, false, index, colWidth);
 
    index--;   
    if (index != 0){indexSize = static_cast<int>(log10(abs(index))) + 1;}
    if (index == 0){indexSize = 1;}
    // Print the data of the current node
    std::cout << std::left;
    std::cout << "idx:(" << index << ")";
    std::cout << std::setw((colWidth - indexSize)) << " ";
    std::cout << " - sizeOfData:(" + std::to_string(node->size()) + ")";
    std::cout << std::setw((colWidth - nodeSize)) << " ";
    std::cout << " - Data: " << node->getData() << std::endl;
}

void List::printReverse()
{
    if (head == nullptr) {
        std::cout << "List is empty." << std::endl;
        return;
    }

    curr = head;
    String *tail = nullptr;
    int index = size(); 
    int colWidth = static_cast<int>(log10(abs(sizeOfLargestElement()))) + 2; // Dynamically adjust column display width 

    while (curr->getNext() != head) {
        curr = curr->getNext();
    }
    tail = curr;

    // Reset curr to head before starting recursion
    curr = head;
    // Start recursion from the head node and pass the tail node
    printReverseHelper(curr, tail, true, index, colWidth);
    std::cout << std::fixed;
    std::cout << "-------------------------*END REVERSE LIST*-------------------------" << std::endl;
}

int List::sizeOfLargestElement() const
{
    String * curr = head;
    int size = 0;
    while(curr->getNext() != head) {
        if (curr->size() > size){
            size = curr->size();
        }
        curr = curr->getNext();
    }
    return size;
}


bool List::find(String * target)
{
    curr = head;
    bool found = false;
    int position = 0;
    std::cout << "POSITION" << '\t' << "DATA" << std::endl;
    while(curr->getNext() != head) {
        if(strcmp(curr->getData(), target->getData()) == 0)
        {	
            found = true;
            std::cout << position << '\t' << '\t' << curr->getData() << std::endl;
        }
        curr = curr->getNext();
        position++;
    }
    return found;   
}

// ------------------------------------------------- Operator Overloads
List & List::operator=(const List &other)         // Copy assignment operator
{
    std::cout << "copy assignment called" << std::endl;
    if (this != &other) {
        this->clear();                            // Clear the current list
        String *otherCurr = other.head;           // Copy elements from the other list
        if(otherCurr != nullptr) {
            do {
                this->insert(new String(*otherCurr)); // Copy the String element
                otherCurr = otherCurr->getNext();
            } while (otherCurr != other.head);
        } 
    }
    return *this;
}

List & List::operator=(List &&other)              // Move assignment operator
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

List List::operator+(const List &other) const    // Addition Operator
{
    List newList(*this);                   // Create a new list by copying the current list 
    String *otherCurr = other.head;        // Initialize otherCurr to the head of the other list 
    if (otherCurr != nullptr) {            // Traverse the circular linked list
        do {
            // Create a new String object with the same data as otherCurr
            String *newString = new String(otherCurr->getData());
            newList.insert(newString);     // Insert the new String into the new list
            otherCurr = otherCurr->getNext();
        } while (otherCurr != other.head); // Loop until we reach the head again
    }
    return newList;                        // Return the new list with concatenated elements
}    

bool List::operator==(const List &other) const   // Equality operator
{
    if (this == &other)                    // Check if it's the same object
        return true;

    String *thisCurr = head;
    String *otherCurr = other.head;

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
         do                                     // Traverse the circular linked lists
         {    
             if (!(strcmp(thisCurr->getData(), otherCurr->getData()) == 0)) {
                 return false;                  // If any node doesn't match or reaches the end, lists are not equal
             }
             thisCurr = thisCurr->getNext();
             otherCurr = otherCurr->getNext();
             if (thisCurr == head && otherCurr == other.head)
                 break;                         // If we reach the head again, we've completed a full loop, exit the loop

         } while (thisCurr != head && otherCurr != other.head);
    }

    return true;                           // Lists are equal if both lists complete a full loop
}
bool List::operator!=(const List &other) const 
{
    return !(*this == other);
}

// Stream output operator for a circular linked list
std::ostream & operator<<(std::ostream &out, List &list)
{
    String *curr = list.getHead();
    if (curr != nullptr) {
        do {
            if (curr->getNext() != list.getHead())
                 out <<"\""<< *curr << "\","; // Call the String's stream output operator
            else out <<"\""<< *curr << "\"";  
            curr = curr->getNext();
        } while (curr != list.getHead());
    }
    return out;
}
