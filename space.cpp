#include "space.h"

Space::~Space()                                        // Destructor!
{
    if (head != nullptr)
    {
        curr = head;
        Matrix * next = nullptr;
        do
        {
            next = curr->getNext();
            delete curr;
            curr = next;
        } while (curr != head);
        head = nullptr;
    }
}

Space::Space()                                         // Default Constructor
{
    head = nullptr;
    curr = nullptr;
}

Space::Space(Matrix *value) : Space()                  // Param Constructor
{
    this->insert(value);
    //curr = value;
    //head = value;
}

Space::Space(Matrix value) : Space()                   // Param Constructor
{
    this->insert(value);
    //Matrix * p = new Matrix(value);
    //curr       = p;
    //head       = p;
}

Space::Space(const Element & value) : Space()          // Param Constructor
{
    for (int i = 1; i <= 3;i++){
        Matrix matrix(3, 3,Element(value));
        matrix.setPosition(Position(0,0,i));
        this->insert(matrix);
    }
}
Space::Space(int z, const Element & value) : Space()   // Param Constructor
{
    for (int i = 1; i <= z;i++){
        Matrix matrix(z, z, Element(value));
        matrix.setPosition(Position(0,0,i));
        this->insert(matrix);
    }
}

Space::Space(int x, int y, const Element & value)      : Space()                 // Param Constructor
{
    for (int i = 1; i <= 3;i++){
        Matrix matrix(x, y, Element(value));
        matrix.setPosition(Position(x,y,i));
        this->insert(matrix);
    }
}

Space::Space(int x, int y, int z, const Element & value)     : Space()                  // Param Constructor
{
    for (int i = 1; i < z;i++){
        Matrix matrix(x, y, Element(value));
        matrix.setPosition(Position(x,y,i));
        this->insert(matrix);
    }
}

Space::Space(int z)             : Space()          // Param Constructor
{
    for (int i = 1; i <= z;i++){
        Matrix matrix(i, i, Element("+"));
        matrix.setPosition(Position(0,0,i));
        this->insert(matrix);
    }
}

Space::Space(int x, int y)          : Space()             // Param Constructor
{
    for (int i = 1; i <= 3;i++){
        Matrix matrix(x, y, Element("+"));
        matrix.setPosition(Position(x,y,i));
        this->insert(matrix);
    }
}

Space::Space(int x, int y, int z)        : Space()               // Param Constructor
{
    for (int i = 1; i <= z;i++){
        Matrix matrix(x, y, Element("+"));
        matrix.setPosition(Position(x,y,i));
        this->insert(matrix);
    }
}

Space::Space(const Space &other)             : Space()              // Copy Constructor 
{                               
    //// Initialize head and curr pointers for the new space
    //head = nullptr;
    //curr = nullptr;

    // Copy each matrix from the other space to the new space
    if (other.head != nullptr) {
        Matrix *otherCurr = other.head;

        do
        {   // Create a new Matrix instance with the data from 'otherCurr'
            Matrix *newNode = new Matrix(*otherCurr);                       
            if (head == nullptr) {            // Insert the new node into the new space
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

void Space::clear()                                   // Completely clear a Space
{
    if (head != nullptr) {
        Matrix *curr = head;
        Matrix *next = nullptr;
        do 
        {   // Traverse the circular linked space and delete nodes
            next = curr->getNext();
            delete curr;
            curr = next;
        }while (curr != head);
        head = nullptr; // Reset the head pointer
    }
    else{std::cout << "cannot clear empty Space" <<std::endl;}
}

/* This function inserts an Matrix at a specfied matrix.
 * Insert target @ matrix
 *
 * Function: insert
 * Param:  Matrix *, int, value and matrix to insert into Space
 * return: void
 */
void Space::insert(Matrix *target, int pos)   
{
    if(head == nullptr) {      // If no Space 
        head = target;		   // Create Space
        target->setNext(head); // Point head to itself
    }                         
    else
    {   
        curr = head;
        Matrix * prev = nullptr;
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
            curr->setNext(target);        // Add to end of Space
            target->setNext(head);        // Point end of Space back to head
        }
        else                              // Insert at matrix
        {
            while(curr->getNext() != head && counter < pos)
            {
                prev = curr;            // Save trailing ptr
                curr = curr->getNext(); // Point to next ptr
                counter++;              // Increment counter
            }
            target->setNext(curr);  // Target goes at matrix occupied by curr
            prev->setNext(target);  // prev points to target
        }
    }
}
/* This function is a sorted insertion mutator.
 * Used to insert an Matrix to the space.
 * No duplicate Space are allowed in this insertion.
 * 
 * Function: insert
 * Param:  Matrix *, value to insert into space
 * return: bool
 */
bool Space::insert(Matrix *value)   // Sorted Insertion Mutator
{
    int  pos      = 0;
    bool found    = false;

    if (head == nullptr)            // If no Space
    {
        head = value;               // Create the Space
        value->setNext(head);       // Point head to itself  
    }
    else
    {	curr = head;
        do
        {
            if(curr->getPosition().getZ() == value->getPosition().getZ()) {
                found = true;      // Don't add to the space. Duplicate was found.
                delete value;
                break;
            }
            //if(curr->getPosition().distanceTo(curr->getNext()->getPosition()) > value->getPosition().distanceTo(curr->getPosition())) {
            if(curr->getPosition().getZ() > value->getPosition().getZ()) {
                found = false;    // Sort space by title. Break and insert at matrix.
                break;
            }
            curr = curr->getNext();
            pos++;
        }while(curr != head);
        if(found == false) {
            insert(value,pos);
            return true;	
        }
        else { return false; }
    }
    return true;	
}
/* This function delegates insert @ matrix to the main insertion function
 * Insert target @ matrix
 *
 * Function: insert
 * Param:  Matrix &, int, value and matrix to insert into Space
 * return: void
 */
void Space::insert(const Matrix &targetRef, int pos) 
{
    Matrix *target = new Matrix(targetRef);  // Create a copy of the target Matrix
    insert(target, pos);                      // Delegate to the existing insert function
}
/* Delegate to existing insert function ^
 * 
 * Function: insert
 * Param:  Matrix &, value to insert into space
 * return: bool
 */
bool Space::insert(const Matrix &targetRef)         
{
    Matrix *target = new Matrix(targetRef);
    return insert(target);
}

/* This function deletes an Matrix at a specified matrix in the Space
 * Matrix Deletion Mutator
 * 
 * Function: getDeets
 * Param:  int, matrix of Matrix to remove from Space
 * return: void
 */
void Space::remove(int pos) 
{
    if (head == nullptr || size() == 0) {
        std::cout << "Nospace to remove." << std::endl;
        return; // Exit the method without doing anyspace
    }
    if (size() == 1) {  // If head.next points to self, nospace to traverse
        delete head;
        head = nullptr; 
        //std::cout << "Delete Head." << std::endl;
        return;
    }
    if(head != nullptr) // If no Space, nospace to remove. Redundant from above check.
    {
        curr = head;
        Matrix * prev = nullptr;
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
            //std::cout << "Removed Matrix: 0" << std::endl;
        }
        else if(pos >= this->size()) // Remove tail
        {  
            while(curr->getNext() != head)
            {
                prev = curr;
                curr = curr->getNext();
            }
            prev->setNext(head);    // New end of the Space
            delete curr;            // Delete last matrix
            //std::cout << "Removed Matrix: " << this->size() + 1 << std::endl;
        }
        else
        { 
            while(curr->getNext() != head && counter < pos)
            {
                prev    = curr;
                curr    = curr->getNext();
                counter++;
            }
            //std::cout << "Removed Matrix: " << counter << std::endl;
            prev->setNext(curr->getNext()); 
            delete curr;
        }
    }
}
/* This function deletes an Matrix from the space by value
 * Specific Deletion Mutator -> Delegates to Matrix Deletion Mutator.^
 *
 * Function: remove
 * Param:  Matrix *, value of Matrix to remove from Space 
 * return: bool
 */
bool Space::remove(Matrix *target)
{
    int matrix = 0;
    if(head != nullptr) { // If no Space, nospace to remove.
        curr = head;
        while(curr->getNext() != head)
        {
            if(curr->getPosition() == target->getPosition())
            {
                remove(matrix);
                delete target;
                return true;
            }
            curr = curr->getNext();
            matrix++;
        }
    }
    std::cout << "Target '" << target->getPosition() << "' NOT FOUND.\n";
    delete target;
    return false;
}
/* Delegates to existing remove function ^
 *
 * Function: remove
 * Param:  Matrix , value of Matrix to remove from Space 
 * return: bool
 */
bool Space::remove(const Matrix &targetRef)
{
    Matrix * target = new Matrix(targetRef);
    return remove(target);
}

/* This function is a size accessor. It returns the size of the space.
 * If space is empty, returns 0, else returns size of the space.
 * Suggest re-writing this into a part of the class that is always tracked.*
 *
 *
 * Function: size
 * Param:  null
 * return: int
 */
int Space::size() const
{
    int result = 1;
    if (head != nullptr) {
        Matrix * curr = head;
        while(curr->getNext() != head)
        {
            result++;
            curr = curr->getNext();
        }
    }
    else {return 0;}
    return result;
}  

/* This function prints the Space to standard out
 * 
 * Function: print
 * Param:  null
 * return: void
 */
void Space::print() const
{ 
    if (head == nullptr) {
        std::cout << "Space is empty." << std::endl;
        return;
    } 
    
    Matrix * curr = head;
    //int count        = 0;
    //int indexSize    = 1;
    //int maxIndexSize = static_cast<int>(log10(abs(size()))) + 2;
    std::cout << "-------------------------*BEGIN SPACE*-------------------------" << std::endl;
    do 
    {   
        
        int* maxW_inner     = new int[curr->getNumCols() + this->size()];     // Initialize an array to store the maximum width for each column
        int* maxColumnWidth = new int[curr->getNumCols()];     // Initialize an array to store the maximum width for each column
    
        for (int j = 0; j < curr->getNumCols(); j++) {
            maxColumnWidth[j] = 0;
        }
   
        for (int j = 0; j < curr->getNumCols(); j++) {         // Find the maximum width for each column
            for (int i = 0; i < curr->getNumRows(); i++) {
                int elementWidth = curr->getValue(i, j).size();
                if (elementWidth > maxColumnWidth[j]) {
                    maxColumnWidth[j] = elementWidth;
                }
            }
        }

        int RightCols = 0;


        for (int i = 0; i < curr->getNumRows(); i++) {         // Print the matrix with aligned columns
               
            if(0 == i) {
                Matrix matrix(this->size(),curr->getNumCols() + this->size());

                std::cout << "\n";
                
                int rowSeparator = this->size();

                Matrix * curr2 = curr;

                int ii = 0;
                do
                {
                    if(0 == ii) {
                        for (int j = 0; j < curr->getNumCols(); j++) {
                            matrix.setValue(0,j,curr->getValue(i, j) );
                        }
                    }
                    else{
                        for (int j = 0; j < curr->getNumCols(); j++) {
                            matrix.setValue(this->size() - ii, j, curr2->getValue(i, j) );
                        }
                        Matrix * curr3 = curr2;
                        //for (int j = curr->getNumCols(); j < curr->getNumCols() + this->size(); j++) {
                        int j = curr->getNumCols();
                        int jj = 1;
                            do
                            {
                                matrix.setValue(this->size() - ii, j, curr3->getNext()->getValue(jj, curr3->getNext()->getNumCols() - 1) );
                                j++;
                                jj++;
                                curr3 = curr3->getNext();
                            }while(curr3 != curr2);

                        //}

                    }
                    ii++;
                    curr2 = curr2->getNext();
                } while (curr2 != curr);


                
    
                for (int j = 0; j < curr->getNumCols() + this->size(); j++) {
                    maxW_inner[j] = 0;
                }
   
                for (int j = 0; j < curr->getNumCols() + this->size(); j++) {         // Find the maximum width for each column
                    for (ii = 0; ii < this->size(); ii++) {
                        int elementWidth = matrix.getValue_i(ii, j).size();
                        if (elementWidth > maxW_inner[j]) {
                            maxW_inner[j] = elementWidth;
                        }
                    }
                }


                //matrix.print();
                for (ii = 0; ii < this->size(); ii++) {
                    for (int jj = 0; jj < curr->getNumCols() + ii; jj++) {
                      
                        if(matrix.getValue(ii, jj).getData() == nullptr) {
                            std::cout << std::setw(maxW_inner[jj] + 1) << "-";
                        }


                        
                        if(0 == jj){std::cout << std::setw((rowSeparator-- * maxW_inner[jj]) + curr->getNumCols() + (this->size() - ii) - maxW_inner[jj] - 1) << "|";}
                        //if(0 == jj){std::cout << std::setw((rowSeparator-- * maxW_inner[jj]) + maxColumnWidth[0] - maxW_inner[jj]) << "|";}
                        //if(0 == jj){std::cout << std::setw((rowSeparator-- * maxW_inner[jj])) << "|";}
                       

                        if(jj == curr->getNumCols()) {
                            std::cout << "|";
                        }
                        if (matrix.getNumCols() <= (curr->getNumCols() - matrix.getNumCols()) - jj) {
                            std::cout << std::setw(maxW_inner[jj] + 1) << jj;
                        }
                        else if(jj >= curr->getNumCols()) {
                            std::cout << std::setw(maxW_inner[jj] + 1) << matrix.getValue(ii, jj);
                        }
                        else if(curr2->getNumCols() >= curr->getNumCols()){
                            std::cout << std::setw(maxW_inner[jj]) << matrix.getValue(ii, jj);
                        }
                        else{
                            std::cout << std::setw(maxW_inner[jj] + 1) << matrix.getValue(ii, jj);
                        }
                        if (jj < curr->getNumCols() - 1) {
                            std::cout << ' ';
                        }
                    }
                    std::cout << std::endl;
                }
                for (int j = 0; j < curr->getNumCols(); j++) {
                    std::cout << std::setw(maxColumnWidth[j]) << "__";
                    if (j < curr->getNumCols() - 1) {
                        std::cout << ' ';
                    }
                }
                std::cout << std::endl;
            }

            for (int j = 0; j < curr->getNumCols(); j++) {
                

                if(j + 1 == curr->getNumCols() && i < curr->getNumRows() - 1){
                    std::cout << std::setw(maxColumnWidth[j]) << curr->getValue(i, j) << "|";
                    
                    
                    Matrix * curr2 = curr;
                    int jj = 0; 
                    do
                    {
                            if (curr2->getNext()->getValue(i + 1 + jj ,curr2->getNext()->getNumCols() - 1).getData() == nullptr){
                                //std::cout << std::setw(maxW_inner[jj]) << "-";  
                                std::cout << std::setw(maxW_inner[jj] + (jj/this->size()) + 1) << "-";  
                            }
                            else{
                                std::cout << std::setw(maxW_inner[jj] + (jj/this->size()) + 1) << curr2->getNext()->getValue(i + 1 + jj ,curr2->getNext()->getNumCols() - 1);
                            }
                        jj++;
                        curr2 = curr2->getNext();
                    }while(curr2 != curr);
                }
                else{
                    std::cout << std::setw(maxColumnWidth[j]) << curr->getValue(i, j);
                }

                if (j < curr->getNumCols() - 1) {
                    std::cout << ' ';
                }
            }
            std::cout << std::endl;
        }
    
        delete [] maxW_inner;
        delete[] maxColumnWidth;                    // Clean up memory

        //if(curr->getNext() == head){
        //    curr->print();
		//}
        curr = curr->getNext();
        //count++;
        RightCols++;
    } while(curr != head);
    std::cout << "-------------------------*END SPACE*---------------------------" << std::endl;
}
void Space::print(const Matrix & pos) 
{ 
    if (head == nullptr) {
        std::cout << "Space is empty." << std::endl;
        return;
    } 
    curr = head;
    do 
    {   if (curr->getPosition() == pos.getPosition()) {
            curr->print();
        }
		curr = curr->getNext();
    } while(curr != head);
}
bool Space::findPos(const Matrix & pos) 
{ 
    if (head == nullptr) {
        std::cout << "Space is empty." << std::endl;
        return false;
    }
    bool found = false;
    curr = head;
    do 
    {   if (curr->getPosition() == pos.getPosition()) {
            found = true;
            break;
        }
		curr = curr->getNext();
    } while(curr != head);
    return found;
}

Matrix Space::getPos(const Matrix & pos) 
{ 
    if (head == nullptr) {
        std::cout << "Space is empty." << std::endl;
        return Matrix();
    } 
    curr = head;
    do 
    {   if (curr->getPosition() == pos.getPosition()) {
            return Matrix(curr->getPosition());
        }
		curr = curr->getNext();
    } while(curr != head);
    return Matrix();
}

// vvvvvvvvvvvvvvvvvvvvvvvvvvv--------------------------------------------------------------------------- 
//
// Operator Overload Functions
//
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^---------------------------------------------------------------------------

/* This function copies the contents of one Space to another Space. COPY assignment operator
 * 
 * Operator: =
 * Param:  const Space & other, The space to be copied FROM
 * return: Space &,             The space to be copied to
 * e.g. 
 *  space1 = space2
 */
Space & Space::operator=(const Space &other)  
{
    std::cout << "copy assignment called" << std::endl;
    if (this != &other) {
        this->clear();                                 // Clear the current space
        Matrix *otherCurr = other.head;               // Copy space from the other space
        if(otherCurr != nullptr) {
            do 
            {
                this->insert(new Matrix(*otherCurr)); // Copy the Matrix matrix
                otherCurr = otherCurr->getNext();
            } while (otherCurr != other.head);
        } 
    }
    return *this;
}

/* This operator moves the contents of one Space to another Space. MOVE assignment operator
 * This operation moves the ownership of memory of the data to this Space from other Space.
 * Results in the other space being cleared 
 *
 * Operator: =
 * Param:  const Space && other, The space to be moved FROM
 * return: Space &,              The space to be moved to
 * e.g. 
 *  space1 = std::move(space2)
 */
Space & Space::operator=(Space &&other)  
{
    std::cout << "move assignment called" << std::endl;
    if (this != &other) {
        this->clear();                     // Clear the current space
        this->head = other.head;           // Move space from the other space
        this->totalMemUsed = other.getMemUsed();
        other.head = nullptr;              // Dereference other's head
        other.clear();                     // Clear other to an empty space to prevent unexpected behavior
        std::cout << this << " " << &other << std::endl;
    }
    return *this;
}

/* This operator adds one space to another space and returns a new space
 * Addition Operator
 *
 * Operator: +
 * Param:  const Space && other, The space to be added from
 * return: Space &,              The space to be added to
 * e.g. 
 *  space1 = space2 + space3 + space4 + space5
 */
Space Space::operator+(const Space &other) const 
{
    Space newSpace(*this);                   // Create a new space by copying the current space 
    Matrix *otherCurr = other.head;       // Initialize otherCurr to the head of the other space 
    if (otherCurr != nullptr) {            // Traverse the circular linked space
        do 
        {   // Create a new Matrix object with the same data as otherCurr
            Matrix *newMatrix = new Matrix(*otherCurr);
            newSpace.insert(newMatrix);     // Insert the new Matrix into the new space
            otherCurr = otherCurr->getNext();
        } while (otherCurr != other.head); // Loop until we reach the head again
    }
    return newSpace;                        // Return the new space with concatenated space
}    

/* This operator compares equality of Spaces
 * Equality operator
 *
 * Operator: ==
 * Param:  const Space & other, rvalue
 * return: bool
 * e.g. 
 *  space1 == space2
 */
bool Space::operator==(const Space &other) const  
{
    if (this == &other)                    // Check if it's the same object
        return true;

    Matrix *thisCurr = head;
    Matrix *otherCurr = other.head;

    if (thisCurr == nullptr && otherCurr == nullptr) {
        return true;                       // Both spaces are empty, consider them equal
    }
    if (thisCurr != nullptr && otherCurr == nullptr) {
        return false;
    }
    if (thisCurr == nullptr && otherCurr != nullptr) {
        return false;
    }
    if (thisCurr != nullptr && otherCurr != nullptr) {
         do                                // Traverse the circular linked spaces
         {    
             if (!(curr->getPosition() == otherCurr->getPosition())) {
                 return false;             // If any node doesn't match or reaches the end, spaces are not equal
             }
             thisCurr = thisCurr->getNext();
             otherCurr = otherCurr->getNext();
             if (thisCurr == head && otherCurr == other.head)
                 break;                    // If we reach the head again, we've completed a full loop, exit the loop

         } while (thisCurr != head && otherCurr != other.head);
    }
    return true;                           // Spaces are equal if both spaces complete a full loop
}

/* This operator compares inequality of Spaces
 * inequality operator -> delegates to equality operator
 *
 * Operator: !=
 * Param:  const Space & other, rvalue
 * return: bool
 * e.g. 
 *  space1 != space2
 */
bool Space::operator!=(const Space &other) const 
{
    return !(*this == other);
}

/* This operator prints to std::ostream
 * Delegates to Matrix's stream output operator
 * CSV style format
 *
 * Operator: <<
 * Param:  Space &
 * return: std::ostream
 */
std::ostream & operator<<(std::ostream &out, Space &space) // Stream output operator Comma Sepperated Values (CSV format)
{
    Matrix *curr = space.getHead();
    if (curr != nullptr) {
        do 
        {
            out << curr->getPosition(); // Call the Matrix's stream output operator
            curr = curr->getNext();
        } while (curr != space.getHead());
    }
    return out;
}
