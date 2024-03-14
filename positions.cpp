#include "positions.h"

Positions::Positions()                                         // Default Constructor
{
    head         = nullptr;
    curr         = nullptr;
}
Positions::Positions(Position *value) : Positions()            // Param Constructor
{
    this->insert(value);
    //curr          = value;
    //head          = value;
}
Positions::Positions(const Position & value) : Positions()     // Param Constructor
{
    this->insert(value);
    //Position * p = new Position(value);
    //curr         = p;
    //head         = p;
}
Positions::~Positions()                                        // Destructor!
{
    if (head != nullptr)
    {
        curr = head;
        Position * next = nullptr;
        do
        {
            next = curr->getNext();
            delete curr;
            curr = next;
        } while (curr != head);
        head = nullptr;
    }
}
Positions::Positions(const Positions &other) : Positions()   // Copy Constructor 
{                               
    // Initialize head and curr pointers for the new positions
    head = nullptr;
    curr = nullptr;

    // Copy each position from the other positions to the new positions
    if (other.head != nullptr) {
        Position *otherCurr = other.head;

        do
        {   // Create a new Position instance with the data from 'otherCurr'
            Position *newNode = new Position(*otherCurr);                       
            if (head == nullptr) {            // Insert the new node into the new positions
                head = newNode;
                newNode->setNext(head);
            } else {
                curr->setNext(newNode);
                newNode->setNext(head);
            }

            curr = newNode;                   // Update curr pointer

            otherCurr = otherCurr->getNext(); // Move to the next node in 'other'
        } while (otherCurr != other.head);
    }
}

void Positions::clear()                                   // Completely clear a Positions
{
    if (head != nullptr) {
        Position *curr = head;
        Position *next = nullptr;
        do 
        {   // Traverse the circular linked positions and delete nodes
            next = curr->getNext();
            delete curr;
            curr = next;
        }while (curr != head);
        head = nullptr; // Reset the head pointer
    }
    //else{std::cout << "cannot clear empty Positions" <<std::endl;}
}

/* This function inserts an Position at a specfied position.
 * Insert target @ position
 *
 * Function: insert
 * Param:  Position *, int, value and position to insert into Positions
 * return: void
 */
void Positions::insert(Position *target, int pos)   
{
    if(head == nullptr) {      // If no Positions 
        head = target;		   // Create Positions
        target->setNext(head); // Point head to itself
    }                         
    else
    {   
        curr = head;
        Position * prev = nullptr;
        int counter = 0;
        if (pos <= 0) {                   // Insert at head
            while(curr->getNext() != head)
                curr = curr->getNext();    
            curr->setNext(target);
            target->setNext(head);        // Set next pointer
            head = target;                // Reset head
        } 
        else if (pos >= this->size()) {   // Insert at tail
            while(curr->getNext() != head) 
                curr = curr->getNext();   // Find end
            curr->setNext(target);        // Add to end of Positions
            target->setNext(head);        // Point end of Positions back to head
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
        }
    }
}
/* This function is a sorted insertion mutator.
 * Used to insert an Position to the positions.
 * No duplicate Positions are allowed in this insertion.
 * 
 * Function: insert
 * Param:  Position *, value to insert into positions
 * return: bool
 */
bool Positions::insert(Position *value)   // Sorted Insertion Mutator
{
    int  position = 0;
    bool found    = false;

    if (head == nullptr)            // If no Positions
    {
        head = value;               // Create the Positions
        value->setNext(head);       // Point head to itself  
    }
    else
    {	curr = head;
        do
        {
            if(*curr == *value) {
                found = true;      // Don't add to the positions. Duplicate was found.
                delete value;
                break;
            }
            if(curr->getX() > value->getX() || curr->getY() > value->getY() || curr->getZ() > value->getZ()) {
            //if(curr->getX() > value->getX() || curr->getY() > value->getY()) {
                found = false;    // Sort positions by title. Break and insert at position.
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
 * Param:  Position &, int, value and position to insert into Positions
 * return: void
 */
void Positions::insert(const Position &targetRef, int pos) 
{
    Position *target = new Position(targetRef);  // Create a copy of the target Position
    insert(target, pos);                      // Delegate to the existing insert function
}
/* Delegate to existing insert function ^
 * 
 * Function: insert
 * Param:  Position &, value to insert into positions
 * return: bool
 */
bool Positions::insert(const Position &targetRef)         
{
    Position *target = new Position(targetRef);
    return insert(target);
}

/* This function deletes an Position at a specified position in the Positions
 * Position Deletion Mutator
 * 
 * Function: getDeets
 * Param:  int, position of Position to remove from Positions
 * return: void
 */
void Positions::remove(int pos) 
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
    if(head != nullptr) // If no Positions, nothing to remove. Redundant from above check.
    {
        curr = head;
        Position * prev = nullptr;
        int counter = 0;
        if(pos <= 0)                // Remove head
        {    
            head = head->getNext();
            prev = head;
            while (prev->getNext() != curr)
            {
                prev = prev->getNext();
            }
            prev->setNext(head);
            delete curr;
            //std::cout << "Removed Position: 0" << std::endl;
        }
        else if(pos >= this->size()) // Remove tail
        {  
            while(curr->getNext() != head)
            {
                prev = curr;
                curr = curr->getNext();
            }
            prev->setNext(head);    // New end of the Positions
            delete curr;            // Delete last position
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
            delete curr;
        }
    }
}
/* This function deletes an Position from the positions by value
 * Specific Deletion Mutator -> Delegates to Position Deletion Mutator.^
 *
 * Function: remove
 * Param:  Position *, value of Position to remove from Positions 
 * return: bool
 */
bool Positions::remove(Position *target)
{
    int position = 0;
    if(head != nullptr) { // If no Positions, nothing to remove.
        curr = head;
        while(curr->getNext() != head)
        {
            if(curr->getX() == target->getX() && curr->getY() == target->getY())
            {
                remove(position);
                delete target;
                return true;
            }
            curr = curr->getNext();
            position++;
        }
    }
    std::cout << "Target '" << target->getX() << " , " << target->getY() << "' NOT FOUND.\n";
    delete target;
    return false;
}
/* Delegates to existing remove function ^
 *
 * Function: remove
 * Param:  Position , value of Position to remove from Positions 
 * return: bool
 */
bool Positions::remove(const Position &targetRef)
{
    Position * target = new Position(targetRef);
    return remove(target);
}

/* This function is a size accessor. It returns the size of the positions.
 * If positions is empty, returns 0, else returns size of the positions.
 * Suggest re-writing this into a part of the class that is always tracked.*
 *
 *
 * Function: size
 * Param:  null
 * return: int
 */
int Positions::size() const
{
    int result = 1;
    if (head != nullptr) {
        Position * curr = head;
        while(curr->getNext() != head)
        {
            result++;
            curr = curr->getNext();
        }
    }
    else {return 0;}
    return result;
}  

/* This function prints the Positions to standard out
 * 
 * Function: print
 * Param:  null
 * return: void
 */
void Positions::print()
{ 
    if (head == nullptr) {
        //std::cout << "Positions is empty." << std::endl;
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
        std::cout << "-Data: "<< *curr << std::endl;
		curr = curr->getNext();
        count++;
    } while(curr != head);
    std::cout << "-------------------------*END FORWARD LIST*-------------------------" << std::endl;
}
void Positions::print(const Position & pos) 
{ 
    if (head == nullptr) {
        //std::cout << "Positions is empty." << std::endl;
        return;
    } 
    curr = head;
    do 
    {   if (curr->getX() == pos.getX() && curr->getY() == pos.getY()) {
            std::cout << *curr;
        }
		curr = curr->getNext();
    } while(curr != head);
    std::cout << std::endl;
}
bool Positions::findPos(const Position & pos) 
{ 
    if (head == nullptr) {
        //std::cout << "Positions is empty." << std::endl;
        return false;
    }
    bool found = false;
    curr = head;
    do 
    {   if (curr->getX() == pos.getX() && curr->getY() == pos.getY()) {
            found = true;
            break;
        }
		curr = curr->getNext();
    } while(curr != head);
    return found;
}

Position Positions::getPos(const Position & pos) 
{ 
    if (head == nullptr) {
        //std::cout << "Positions is empty." << std::endl;
        return Position();
    } 
    curr = head;
    do 
    {   if (curr->getX() == pos.getX() && curr->getY() == pos.getY()) {
            return Position(curr->getX(),curr->getY());
        }
		curr = curr->getNext();
    } while(curr != head);
    return Position();
}
Position Positions::getPos(int position) 
{ 
    if (head == nullptr) {
        //std::cout << "Positions is empty." << std::endl;
        return Position();
    } 
    curr = head;
    int pos = 0;
    do 
    {   if (pos == position) {
            return Position(curr->getX(),curr->getY());
        }
        pos++;
		curr = curr->getNext();
    } while(curr != head);
    return Position();
}

// vvvvvvvvvvvvvvvvvvvvvvvvvvv--------------------------------------------------------------------------- 
//
// Operator Overload Functions
//
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^---------------------------------------------------------------------------

/* This function copies the contents of one Positions to another Positions. COPY assignment operator
 * 
 * Operator: =
 * Param:  const Positions & other, The positions to be copied FROM
 * return: Positions &,             The positions to be copied to
 * e.g. 
 *  positions1 = positions2
 */
Positions & Positions::operator=(const Positions &other)  
{
    //std::cout << "copy assignment called" << std::endl;
    if (this != &other) {
        this->clear();                                 // Clear the current positions
        Position *otherCurr = other.head;               // Copy positions from the other positions
        if(otherCurr != nullptr) {
            do 
            {
                this->insert(new Position(*otherCurr)); // Copy the Position position
                otherCurr = otherCurr->getNext();
            } while (otherCurr != other.head);
        } 
    }
    return *this;
}

/* This operator moves the contents of one Positions to another Positions. MOVE assignment operator
 * This operation moves the ownership of memory of the data to this Positions from other Positions.
 * Results in the other positions being cleared 
 *
 * Operator: =
 * Param:  const Positions && other, The positions to be moved FROM
 * return: Positions &,              The positions to be moved to
 * e.g. 
 *  positions1 = std::move(positions2)
 */
Positions & Positions::operator=(Positions &&other)  
{
    //std::cout << "move assignment called" << std::endl;
    if (this != &other) {
        this->clear();                     // Clear the current positions
        this->head = other.head;           // Move positions from the other positions
        this->totalMemUsed = other.getMemUsed();
        other.head = nullptr;              // Dereference other's head
        other.clear();                     // Clear other to an empty positions to prevent unexpected behavior
        //std::cout << this << " " << &other << std::endl;
    }
    return *this;
}

/* This operator adds one positions to another positions and returns a new positions
 * Addition Operator
 *
 * Operator: +
 * Param:  const Positions && other, The positions to be added from
 * return: Positions &,              The positions to be added to
 * e.g. 
 *  positions1 = positions2 + positions3 + positions4 + positions5
 */
Positions Positions::operator+(const Positions &other) const 
{
    Positions newPositions(*this);                   // Create a new positions by copying the current positions 
    Position *otherCurr = other.head;       // Initialize otherCurr to the head of the other positions 
    if (otherCurr != nullptr) {            // Traverse the circular linked positions
        do 
        {   // Create a new Position object with the same data as otherCurr
            Position *newPosition = new Position(otherCurr->getX(), otherCurr->getY());
            newPositions.insert(newPosition);     // Insert the new Position into the new positions
            otherCurr = otherCurr->getNext();
        } while (otherCurr != other.head); // Loop until we reach the head again
    }
    return newPositions;                        // Return the new positions with concatenated positions
}    

/* This operator compares equality of Positionss
 * Equality operator
 *
 * Operator: ==
 * Param:  const Positions & other, rvalue
 * return: bool
 * e.g. 
 *  positions1 == positions2
 */
bool Positions::operator==(const Positions &other) const  
{
    if (this == &other)                    // Check if it's the same object
        return true;

    Position *thisCurr = head;
    Position *otherCurr = other.head;

    if (thisCurr == nullptr && otherCurr == nullptr) {
        return true;                       // Both positionss are empty, consider them equal
    }
    if (thisCurr != nullptr && otherCurr == nullptr) {
        return false;
    }
    if (thisCurr == nullptr && otherCurr != nullptr) {
        return false;
    }
    if (thisCurr != nullptr && otherCurr != nullptr) {
         do                                // Traverse the circular linked positionss
         {    
             if (!(curr->getX() == otherCurr->getX() && curr->getY() == otherCurr->getY())) {
                 return false;             // If any node doesn't match or reaches the end, positionss are not equal
             }
             thisCurr = thisCurr->getNext();
             otherCurr = otherCurr->getNext();
             if (thisCurr == head && otherCurr == other.head)
                 break;                    // If we reach the head again, we've completed a full loop, exit the loop

         } while (thisCurr != head && otherCurr != other.head);
    }
    return true;                           // Positionss are equal if both positionss complete a full loop
}

/* This operator compares inequality of Positionss
 * inequality operator -> delegates to equality operator
 *
 * Operator: !=
 * Param:  const Positions & other, rvalue
 * return: bool
 * e.g. 
 *  positions1 != positions2
 */
bool Positions::operator!=(const Positions &other) const 
{
    return !(*this == other);
}

/* This operator prints to std::ostream
 * Delegates to Position's stream output operator
 * CSV style format
 *
 * Operator: <<
 * Param:  Positions &
 * return: std::ostream
 */
std::ostream & operator<<(std::ostream &out, Positions &positions) // Stream output operator Comma Sepperated Values (CSV format)
{
    Position *curr = positions.getHead();
    if (curr != nullptr) {
        do 
        {
            out <<"(" << curr->getX() << "," << curr->getY() << ")->" << curr->getZ() << ")"; // Call the Position's stream output operator
            curr = curr->getNext();
        } while (curr != positions.getHead());
    }
    return out;
}
