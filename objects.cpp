#include "objects.h"

Objects::Objects()                                         // Default Constructor
{
    head         = nullptr;
    curr         = nullptr;
}

Objects::Objects(Object *value) : Objects()                // Param Constructor
{
    this->insert(value);
}

Objects::Objects(Object object) : Objects()
{
    this->insert(object);
}

Objects::~Objects()                                        // Destructor!
{
    if (head != nullptr)
    {
        curr = head;
        Object * next = nullptr;
        do
        {
            next = curr->getNext();
            delete curr;
            curr = next;
        } while (curr != head);
        head = nullptr;
    }
}

Objects::Objects(const Objects &other)  : Objects()         // Copy Constructor 
{                               
    // Initialize head and curr pointers for the new objects
    head = nullptr;
    curr = nullptr;

    // Copy each object from the other objects to the new objects
    if (other.head != nullptr) {
        Object *otherCurr = other.head;

        do
        {   // Create a new Object instance with the data from 'otherCurr'
            Object * newNode = new Object(*otherCurr);                       
            if (head == nullptr) {            // Insert the new node into the new objects
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

void Objects::clear()                                   // Completely clear a Objects
{
    if (head != nullptr) {
        Object *curr = head;
        Object *next = nullptr;
        do 
        {   // Traverse the circular linked objects and delete nodes
            next = curr->getNext();
            delete curr;
            curr = next;
        }while (curr != head);
        head = nullptr; // Reset the head pointer
    }
}

/* This function inserts an Object at a specfied position.
 * Insert target @ position
 *
 * Function: insert
 * Param:  Object *, int, value and position to insert into Objects
 * return: void
 */
void Objects::insert(Object *target, int pos)
{
    if(head == nullptr) {      // If no Objects 
        head = target;		   // Create Objects
        target->setNext(head); // Point head to itself
    }                         
    else
    {   
        curr = head;
        Object * prev = nullptr;
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
            curr->setNext(target);        // Add to end of Objects
            target->setNext(head);        // Point end of Objects back to head
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
 * Used to insert an Object to the objects.
 * No duplicate Objects are allowed in this insertion.
 * 
 * Function: insert
 * Param:  Object *, value to insert into objects
 * return: bool
 */
bool Objects::insert(Object *value) // Insertion Mutator
{
    int  position = 0;
    bool found    = false;
    
    if (head == nullptr)            // If no Objects
    {
        head = value;               // Create the Objects
        value->setNext(head);       // Point head to itself  
    }
    else
    {	curr = head;
        do
        {
            if(strcmp(curr->getName().getData(), value->getName().getData()) == 0) {
                found = true;      // Don't add to the list. Duplicate was found.
                delete value;
                break;
            }
            if(strcmp(curr->getName().getData(), value->getName().getData()) > 0) {
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
 * Param:  Object &, int, value and position to insert into Objects
 * return: void
 */
void Objects::insert(const Object &targetRef, int pos) 
{
    Object *target = new Object(targetRef);  // Create a copy of the target Object
    insert(target, pos);                      // Delegate to the existing insert function
}
/* Delegate to existing insert function ^
 * 
 * Function: insert
 * Param:  Object &, value to insert into objects
 * return: bool
 */
bool Objects::insert(const Object &targetRef)         
{
    Object *target = new Object(targetRef);
    return insert(target);
}

/* This function deletes an Object at a specified position in the Objects
 * Position Deletion Mutator
 * 
 * Function: remove
 * Param:  int, position of Object to remove from Objects
 * return: void
 */
void Objects::remove(int pos) 
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
    if(head != nullptr) // If no Objects, nothing to remove. Redundant from above check.
    {
        curr = head;
        Object * prev = nullptr;
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
           // head = head->getNext(); // New head is next object
            std::cout << "Removed Position: 0" << std::endl;
        }
        else if(pos >= this->size()) // Remove tail
        {  
            while(curr->getNext() != head)
            {
                prev = curr;
                curr = curr->getNext();
            }
            prev->setNext(head);    // New end of the Objects
            delete curr;            // Delete last object
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
/* This function deletes an Object from the objects by value
 * Specific Deletion Mutator -> Delegates to Position Deletion Mutator.^
 *
 * Function: remove
 * Param:  Object *, value of Object to remove from Objects 
 * return: bool
 */
bool Objects::remove(Object *target)
{
    int position = 0;
    if(head != nullptr) { // If no Objects, nothing to remove.
        curr = head;
        while(curr->getNext() != head)
        {
            if(curr->getName() == target->getName())
            {
                //std::cout << "Removed " << target->getData() << " from the objects.\n";
                remove(position);
                delete target;
                return true;
            }
            curr = curr->getNext();
            position++;
        }
    }
    std::cout << "Target '" << target->getName() << "' NOT FOUND.\n";
    delete target;
    return false;
}
/* Delegates to existing remove function ^
 *
 * Function: remove
 * Param:  Object , value of Object to remove from Objects 
 * return: bool
 */
bool Objects::remove(const Object &targetRef)
{
    Object * target = new Object(targetRef);
    return remove(target);
}

/* This function is a size accessor. It returns the size of the objects.
 * If objects is empty, returns 0, else returns size of the objects.
 *
 * Function: size
 * Param:  null
 * return: int
 */
int Objects::size() const
{
    int result = 1;
    if (head != nullptr) {
        Object * curr = head;
        while(curr->getNext() != head)
        {
            result++;
            curr = curr->getNext();
        }
    }
    else {return 0;}
    return result;
} 

void Objects::importObjects(const Matrix & matrix)
{
    if(matrix.getNumRows() == 0 && matrix.getNumCols() == 0) { return; }
    if(matrix.getRows() == nullptr || matrix.getColumns() == nullptr) {return;}
    
    this->clear();


    for(int i = 1; i < matrix.getNumRows(); i++) {
        Object object(matrix.getValue(i,0));
        
        object.setMatrix(matrix.getMatrixWhereElementIs(matrix.getValue(i, 0)));
        
        //Space space;
        //space.setPropertyFrequencies(object.getMatrix());

        object.setSpace(Space());
        Properties properties;
        for(int k = 1; k < object.getMatrix().getNumRows(); k ++) {
            for(int j = 0; j < matrix.getNumCols(); j++) {
                properties.insert(object.getMatrix().getValue(0,j), object.getMatrix().getValue(k, j));
            }
        }
        properties.insert(Element("Found In"), matrix.getName()); 
        object.setProperties(properties);

        this->insert(object);
    }
    this->print();
}

void Objects::importObjects(const Matrix & matrix, const Element & propertyName)
{
    if(matrix.getNumRows() == 0 && matrix.getNumCols() == 0) { return; }
    if(matrix.getRows() == nullptr || matrix.getColumns() == nullptr) {return;}
    
    this->clear();
    
    int propertyNamePos = matrix.getRows()[0].findMatch_i_p(propertyName).getPos(0).getX();
    
    for(int i = 1; i < matrix.getNumRows(); i++) {
        Object object(matrix.getValue(i, propertyNamePos));
        
        object.setMatrix(matrix.getMatrixWhereElementIs(matrix.getValue(i, propertyNamePos)));
        
       // Space space;
      //  space.setPropertyFrequencies(object.getMatrix());

        object.setSpace(Space());
        Properties properties;
        for(int k = 1; k < object.getMatrix().getNumRows(); k ++) {
            for(int j = 0; j < matrix.getNumCols(); j++) {
                properties.insert(object.getMatrix().getValue(0,j), object.getMatrix().getValue(k, j));
            }
        }
        properties.insert(Element("Found In"), matrix.getName()); 
        object.setProperties(properties);

        this->insert(object);
    }
    this->print();
}

void Objects::importObjects(const Space & space)
{
    int spaceSize = space.size();
    if(spaceSize == 0) { return; }
    
    Positions positions;

    for(int spSz = 0; spSz < spaceSize; spSz++) {
        
        Matrix matrix(space.getPos(spSz));

        for(int i = 1; i < matrix.getNumRows(); i++) {

            bool foundObj = false;
            
            Object object(matrix.getValue(i, 0));
            
            curr = head;
            if (!(head == nullptr)) {
                do 
                {
                    if(curr->getName() == object.getName()) {
                        foundObj = true;
                        break;
                    }
	            	curr = curr->getNext();
                } while(curr != head);
            }

            if(foundObj == false) {
               
                Properties properties;
                
                for(int spSz2 = 0; spSz2 < spaceSize; spSz2++) {
                    Matrix matrix2(space.getPos(spSz2).getMatrixWhereElementIs(matrix.getValue(i, 0)));

                    if(matrix2.getNumRows() > 1){
                        object.setMatrix(matrix2);
                    }

                    for(int k = 1; k < object.getMatrix().getNumRows(); k ++) {
                        for(int j = 0; j < object.getMatrix().getNumCols(); j++) {

                            if(!(properties.findMatch(object.getMatrix().getValue(0,j), object.getMatrix().getValue(k, j)))) {
                                properties.insert(object.getMatrix().getValue(0,j), object.getMatrix().getValue(k, j));
                            }
                        }
                    }
                }
                object.setSpace(Space());
                object.setProperties(properties);

                this->insert(object);
            }
        }
    }
    if (!(head == nullptr)) {
        curr = head;
        do 
        {
            Space space2(curr->getSpace());
            for(int spSz2 = 0; spSz2 < spaceSize; spSz2++) {
                Matrix matrix2(space.getPos(spSz2).getMatrixWhereElementIs(curr->getName()));
                if(matrix2.getNumRows() > 1){
                    matrix2.setPosition(Position(0,0,spSz2));
                    space2.insert(matrix2);
                    curr->addProperty(Element("Found In"), matrix2.getName()); 
                }
            }
            if(curr->getMatrix().getNumRows() == 2) {
                curr->setMatrix(Matrix(1,1));
            }
            curr->setSpace(space2);
	    	curr = curr->getNext();
        } while(curr != head);
    }
}

void Objects::importObjects(const Space & space, const List & propertyNames)
{
    int spaceSize = space.size();
    if(spaceSize == 0) { return; }
    
    Positions positions;

    for(int spSz = 0; spSz < spaceSize; spSz++) {
        
        Matrix matrix(space.getPos(spSz));
    
        int propertyNamePos = 0;
        for(int i = 0; i < propertyNames.size(); i++) {

            if(matrix.getRows()[0].findMatch_i(propertyNames.getDataAtPosition(i))) {
                propertyNamePos = matrix.getRows()[0].findMatch_i_p(propertyNames.getDataAtPosition(i)).getPos(0).getX();
                break;
            }
        }

        for(int i = 1; i < matrix.getNumRows(); i++) {

            bool foundObj = false;
            
            Object object(matrix.getValue(i, propertyNamePos));
            
            curr = head;
            if (!(head == nullptr)) {
                do 
                {
                    if(curr->getName() == object.getName()) {
                        foundObj = true;
                        break;
                    }
	            	curr = curr->getNext();
                } while(curr != head);
            }

            if(foundObj == false) {
               
                Properties properties;
                
                for(int spSz2 = 0; spSz2 < spaceSize; spSz2++) {
                    Matrix matrix2(space.getPos(spSz2).getMatrixWhereElementIs(matrix.getValue(i, propertyNamePos)));

                    if(matrix2.getNumRows() > 1){
                        object.setMatrix(matrix2);
                    }

                    for(int k = 1; k < object.getMatrix().getNumRows(); k ++) {
                        for(int j = 0; j < object.getMatrix().getNumCols(); j++) {

                            if(!(properties.findMatch(object.getMatrix().getValue(0,j), object.getMatrix().getValue(k, j)))) {
                                properties.insert(object.getMatrix().getValue(0,j), object.getMatrix().getValue(k, j));
                            }
                        }
                    }
                }
                object.setSpace(Space());
                object.setProperties(properties);

                this->insert(object);
            }
        }
    }
    if (!(head == nullptr)) {
        curr = head;
        do 
        {
            Space space2(curr->getSpace());
            for(int spSz2 = 0; spSz2 < spaceSize; spSz2++) {
                Matrix matrix2(space.getPos(spSz2).getMatrixWhereElementIs(curr->getName()));
                if(matrix2.getNumRows() > 1){
                    matrix2.setPosition(Position(0,0,spSz2));
                    space2.insert(matrix2);
                    curr->addProperty(Element("Found In"), matrix2.getName()); 
                }
            }
            if(curr->getMatrix().getNumRows() == 2) {
                curr->setMatrix(Matrix(1,1));
            }
            curr->setSpace(space2);
	    	curr = curr->getNext();
        } while(curr != head);
    }
}

void Objects::importAllObjects(const Space & space)
{
    int spaceSize = space.size();
    if(spaceSize == 0) { return; }
    
    Positions positions;

    for(int spSz = 0; spSz < spaceSize; spSz++) {
        
        Matrix matrix(space.getPos(spSz));

        for(int i = 1; i < matrix.getNumRows(); i++) {

            for(int col = 0; col < matrix.getNumCols(); col++) {

                bool foundObj = false;
                
                Object object(matrix.getValue(i, col));
                
                curr = head;
                if (!(head == nullptr)) {
                    do 
                    {
                        if(curr->getName() == object.getName()) {
                            foundObj = true;
                            break;
                        }
	                	curr = curr->getNext();
                    } while(curr != head);
                }

                if(foundObj == false) {
                   
                    Properties properties;
                    
                    for(int spSz2 = 0; spSz2 < spaceSize; spSz2++) {
                        Matrix matrix2(space.getPos(spSz2).getMatrixWhereElementIs(matrix.getValue(i, col)));

                        if(matrix2.getNumRows() > 1){
                            object.setMatrix(matrix2);
                        }

                        for(int k = 1; k < object.getMatrix().getNumRows(); k ++) {
                            for(int j = 0; j < object.getMatrix().getNumCols(); j++) {

                                if(!(properties.findMatch(object.getMatrix().getValue(0,j), object.getMatrix().getValue(k, j)))) {
                                    properties.insert(object.getMatrix().getValue(0,j), object.getMatrix().getValue(k, j));
                                }
                            }
                        }
                    }
                    object.setSpace(Space());
                    object.setProperties(properties);

                    this->insert(object);
                }
            }
        }
    }
    if (!(head == nullptr)) {
        curr = head;
        do 
        {
            Space space2(curr->getSpace());
            for(int spSz2 = 0; spSz2 < spaceSize; spSz2++) {
                Matrix matrix2(space.getPos(spSz2).getMatrixWhereElementIs(curr->getName()));
                if(matrix2.getNumRows() > 1){
                    matrix2.setPosition(Position(0,0,spSz2));
                    space2.insert(matrix2);
                    curr->addProperty(Element("Found In"), matrix2.getName()); 
                }
            }
            if(curr->getMatrix().getNumRows() == 2) {
                curr->setMatrix(Matrix(1,1));
            }
            curr->setSpace(space2);
	    	curr = curr->getNext();
        } while(curr != head);
    }
}

void Objects::importAllObjects_i(const Space & space)
{
    int spaceSize = space.size();
    if(spaceSize == 0) { return; }
    
    Positions positions;

    for(int spSz = 0; spSz < spaceSize; spSz++) {
        
        Matrix matrix(space.getPos(spSz));

        for(int i = 1; i < matrix.getNumRows(); i++) {

            for(int col = 0; col < matrix.getNumCols(); col++) {

                bool foundObj = false;
                
                Object object(matrix.getValue(i, col));
                
                curr = head;
                if (!(head == nullptr)) {
                    do 
                    {
                        if(curr->getName() == object.getName()) {
                            foundObj = true;
                            break;
                        }
	                	curr = curr->getNext();
                    } while(curr != head);
                }

                if(foundObj == false) {
                   
                    Properties properties;
                    
                    for(int spSz2 = 0; spSz2 < spaceSize; spSz2++) {
                        Matrix matrix2(space.getPos(spSz2).getMatrixWhereElementLike_i(matrix.getValue(i, col)));

                        if(matrix2.getNumRows() > 1){
                            object.setMatrix(matrix2);
                        }

                        for(int k = 1; k < object.getMatrix().getNumRows(); k ++) {
                            for(int j = 0; j < object.getMatrix().getNumCols(); j++) {

                                if(!(properties.findMatch(object.getMatrix().getValue(0,j), object.getMatrix().getValue(k, j)))) {
                                    properties.insert(object.getMatrix().getValue(0,j), object.getMatrix().getValue(k, j));
                                }
                            }
                        }
                    }
                    object.setSpace(Space());
                    object.setProperties(properties);

                    this->insert(object);
                }
            }
        }
    }
    if (!(head == nullptr)) {
        curr = head;
        do 
        {
            Space space2(curr->getSpace());
            for(int spSz2 = 0; spSz2 < spaceSize; spSz2++) {
                Matrix matrix2(space.getPos(spSz2).getMatrixWhereElementLike_i(curr->getName()));
                if(matrix2.getNumRows() > 1){
                    matrix2.setPosition(Position(0,0,spSz2));
                    space2.insert(matrix2);
                    curr->addProperty(Element("Found In"), matrix2.getName()); 
                }
            }
            if(curr->getMatrix().getNumRows() == 2) {
                curr->setMatrix(Matrix(1,1));
            }
            curr->setSpace(space2);
	    	curr = curr->getNext();
        } while(curr != head);
    }
}


void Objects::importCSVs(const List & list_c)
{
    List list(list_c);
    list = list.wildcardSearch_i_z("*.csv");                  // Consolidate list to only *.csv arguments
    Space allCSVs;                                            // Space to hold all CSV Values
    for(int idx = 0; idx < list.size(); idx++)                // For index less than the size of list where values like *.csv
    {   
        Matrix matrix;
        if(matrix.importCsv(list.getDataAtPosition(idx).getData())) { // Import the file CSV format with comma and string delimeters to a matrix
            Object object(list.getDataAtPosition(idx));           // Init an object with the name of whatever the wildcard value in *.csv is
            matrix.setPosition(Position(0,0,idx));                // Set Z value of the matrix's position to the index
            allCSVs.insert(matrix);                               // Insert the matrix into the main space
            Space space;                                          // Make some space to put the csv property frequencies inside
            space.setPropertyFrequencies(matrix);                 // Set the space to the property frequencies of matrix 
            object.setSpace(space);                               // Set the current object's space to the property frequencies of matrix
            object.setMatrix(matrix);                             // Set the current object's matrix to the imported csv
            this->insert(object);                                 // Insert the current object into the main list of objects
        }
    }
    if(allCSVs.size() > 0) {
        Object allFiles("All CSVs");                              // Create an Object with the name All CSVs
        allFiles.setSpace(allCSVs);                               // Set the Object's space to that of All CSVs
        this->insert(allFiles);                                   // Insert the object of All CSVs into the main list of objects
        this->importAllObjects_i(allCSVs);                        // Import All CSVs main values into individual objects and attach them to the main list of objects
    }
}



void Objects::importCSVs(const List & list_c, const List & propertyNames)
{
    List list(list_c);
    list = list.wildcardSearch_i_z("*.csv");                  // Consolidate list to only *.csv arguments
    Space allCSVs;                                            // Space to hold all CSV Values
    for(int idx = 0; idx < list.size(); idx++)                // For index less than the size of list where values like *.csv
    {   
        Matrix matrix;
        if(matrix.importCsv(list.getDataAtPosition(idx).getData())) { // Import the file CSV format with comma and string delimeters to a matrix
            Object object(list.getDataAtPosition(idx));           // Init an object with the name of whatever the wildcard value in *.csv is
            matrix.setPosition(Position(0,0,idx));                // Set Z value of the matrix's position to the index
            allCSVs.insert(matrix);                               // Insert the matrix into the main space
            Space space;                                          // Make some space to put the csv property frequencies inside
            space.setPropertyFrequencies(matrix);                 // Set the space to the property frequencies of matrix 
            object.setSpace(space);                               // Set the current object's space to the property frequencies of matrix
            object.setMatrix(matrix);                             // Set the current object's matrix to the imported csv
            this->insert(object);                                 // Insert the current object into the main list of objects
        }
    }
    if(allCSVs.size() > 0) {
        Object allFiles("All CSVs");                              // Create an Object with the name All CSVs
        allFiles.setSpace(allCSVs);                               // Set the Object's space to that of All CSVs
        this->insert(allFiles);                                   // Insert the object of All CSVs into the main list of objects
        this->importObjects(allCSVs, propertyNames);              // Import All CSVs main values into individual objects and attach them to the main list of objects
    }
}


void Objects::getDeets() 
{
    if(head == nullptr){return;}

    Properties foundIn;
    
 





    std::cout << "--------------------------------------------------------------------------------------------------------------------------------------------------"<< std::endl;



    // Get unique property valies for Found In
    List list(this->getListOfPropertyValues("Found In"));


    this->getObjectsFoundIn(list).print();
    std::cout << "--------------------------------------------------------------------------------------------------------------------------------------------------"<< std::endl;


    std::cout << "Total Objects: "<< this->size() << std::endl;
    std::cout << "Total Data Sources: "<< list.size() << std::endl;
    std::cout << "Data Sources: "<< list << std::endl;

    for(int i = list.size(); i >= 0; i--) {
        
        std::cout << "Total Objects Found in " << i << " Data Sources: "<< this->getObjectsFound(i).size() << std::endl;
    }

    
    //list.print();

    for(int i = 0; i < list.size(); i++) {
        Objects objectsFoundIn(this->getObjectsFoundIn(list.getDataAtPosition(i)));
        Objects objectsNotFoundIn(this->getObjectsNotFoundIn(list.getDataAtPosition(i)));

        std::cout << "\nTotal Objects in     '"<< list.getDataAtPosition(i) << "': "<< objectsFoundIn.size() << std::endl;
        std::cout << "Total Objects Not in '"<< list.getDataAtPosition(i) << "': "<< objectsNotFoundIn.size() << std::endl;
    
        for(int j = 0; j < list.size(); j++) {
            if(j != i) {
                std::cout << "Total Objects from'"<< list.getDataAtPosition(i) << "', in '"<< list.getDataAtPosition(j) << "': "<< objectsFoundIn.getObjectsFoundIn(list.getDataAtPosition(j)).size() << std::endl;
            //std::cout << "Total Objects in '"<< list.getDataAtPosition(i) << "', also in '"<< list.getDataAtPosition(j) << "': "<< objectsFoundIn.getObjectsFoundIn(list.getDataAtPosition(j)).size() << std::endl;
            }
        }

    }
}


Objects Objects::where(const Element & memberVar, const Element & verb, const Element & valueToSearchBy) 
{
    Objects objects;

    if(head == nullptr){return objects;}

    curr = head;

    if(strcmp_i(memberVar.getData(), Element("name").getData()) == 0) {
        if(strcmp_i(verb.getData(), Element("is").getData()) == 0) {
            do 
            {   
	            if(curr->getName() == valueToSearchBy) {
                    objects.insert(*curr);
                }
                curr = curr->getNext();
            } while(curr != head);
        }
       else if(strcmp_i(verb.getData(), Element("contains").getData()) == 0) {
            do 
            {   
                List list(curr->getName());
	            if(list.containsSequence_i(valueToSearchBy)) {
                    objects.insert(*curr);
                }
                curr = curr->getNext();
            } while(curr != head);
        }
        else if(strcmp_i(verb.getData(), Element("like").getData()) == 0) {
            do 
            {   
                List list(curr->getName());
	            if(list.wildcardSearch_i(valueToSearchBy)) {
                    objects.insert(*curr);
                }
                curr = curr->getNext();
            } while(curr != head);
        }
        else if(strcmp_i(verb.getData(), Element("not").getData()) == 0) {
            do 
            {   
                List list(curr->getName());
	            if(!(list.wildcardSearch_i(valueToSearchBy))) {
                    objects.insert(*curr);
                }
                curr = curr->getNext();
            } while(curr != head);
        }
        else if(strcmp_i(verb.getData(), Element("in").getData()) == 0) {
            do 
            {   
                if(curr->getProperties().wildcardSearch_i(valueToSearchBy, curr->getName())) {
                    objects.insert(*curr);
                }
                curr = curr->getNext();
            } while(curr != head);
        }
    }
    else if(strcmp_i(memberVar.getData(), Element("space").getData()) == 0) {
        if(strcmp_i(verb.getData(), Element("is").getData()) == 0) {
            do 
            {   
                for(int i = 0; i < curr->getSpace().size(); i++) {
	                if(strcmp_i(curr->getSpace().getPos(i).getName().getData(), valueToSearchBy.getData()) == 0) {
                        objects.insert(*curr);
                        break;
                    }
                }
                curr = curr->getNext();
            } while(curr != head);
        }
       else if(strcmp_i(verb.getData(), Element("contains").getData()) == 0) {
            do 
            {  
                for(int i = 0; i < curr->getSpace().size(); i++)
                {
                    List * list = curr->getSpace().getPos(i).getRows();
	                for(int i = 0; i < curr->getSpace().getPos(i).getNumRows(); i++)
                    {
                        if(list[i].containsSequence_i(valueToSearchBy)) {
                            objects.insert(*curr);
                            break;
                        }
                    }
                }
                curr = curr->getNext();
            } while(curr != head);
        }
        else if(strcmp_i(verb.getData(), Element("like").getData()) == 0) {
            do 
            {   
                for(int i = 0; i < curr->getSpace().size(); i++)
                {
                    List * list = curr->getSpace().getPos(i).getRows();
	                for(int i = 0; i < curr->getSpace().getPos(i).getNumRows(); i++)
                    {
                        if(list[i].wildcardSearch_i(valueToSearchBy)) {
                            objects.insert(*curr);
                            break;
                        }
                    }
                }
                curr = curr->getNext();
            } while(curr != head);
        }
    }
    else if(strcmp_i(memberVar.getData(), Element("matrix").getData()) == 0) {
        if(strcmp_i(verb.getData(), Element("is").getData()) == 0) {
            do 
            {   
	            if(strcmp_i(curr->getMatrix().getName().getData(), valueToSearchBy.getData()) == 0) {
                    objects.insert(*curr);
                }
                curr = curr->getNext();
            } while(curr != head);
        }
       else if(strcmp_i(verb.getData(), Element("contains").getData()) == 0) {
            do 
            {  
                List * list = curr->getMatrix().getRows();
	            for(int i = 0; i < curr->getMatrix().getNumRows(); i++)
                {
                    if(list[i].containsSequence_i(valueToSearchBy)) {
                        objects.insert(*curr);
                        break;
                    }
                }
                curr = curr->getNext();
            } while(curr != head);
        }
        else if(strcmp_i(verb.getData(), Element("like").getData()) == 0) {
            do 
            {   
                List * list = curr->getMatrix().getRows();
	            for(int i = 0; i < curr->getMatrix().getNumRows(); i++)
                {
                    if(list[i].wildcardSearch_i(valueToSearchBy)) {
                        objects.insert(*curr);
                        break;
                    }
                }
                curr = curr->getNext();
            } while(curr != head);
        }
    }
    else if(strcmp_i(memberVar.getData(), Element("property").getData()) == 0) {
        if(strcmp_i(verb.getData(), Element("is").getData()) == 0) {
            do 
            {   
                if(curr->getProperties().findMatch(valueToSearchBy).size() > 0) {
                    objects.insert(*curr);
                }
                curr = curr->getNext();
            } while(curr != head);
        }
       else if(strcmp_i(verb.getData(), Element("contains").getData()) == 0) {
            do 
            {  
                if(curr->getProperties().containsSequence_i(valueToSearchBy).size() > 0) {
                    objects.insert(*curr);
                }
                curr = curr->getNext();
            } while(curr != head);
        }
        else if(strcmp_i(verb.getData(), Element("like").getData()) == 0) {
            do 
            {   
                if(curr->getProperties().wildcardSearch_i(valueToSearchBy).size() > 0) {
                    objects.insert(*curr);
                }
                curr = curr->getNext();
            } while(curr != head);
        }
        else if(strcmp_i(verb.getData(), Element("not").getData()) == 0) {
            do 
            {   
                if(curr->getProperties().wildcardSearch_i(valueToSearchBy).size() == 0) {
                    objects.insert(*curr);
                }
                curr = curr->getNext();
            } while(curr != head);
        }
        else if(strcmp_i(verb.getData(), Element("exists").getData()) == 0) {
            do 
            {  
                if(curr->getProperties().findKey(valueToSearchBy)) {
                    objects.insert(*curr);
                }
                curr = curr->getNext();
            } while(curr != head);
        }
    }
    else if(this->getListOfPropertyKeys().findMatch_i(memberVar)) {
        if(strcmp_i(verb.getData(), Element("is").getData()) == 0) {
            do 
            {   
                if(curr->getProperties().findMatch(memberVar, valueToSearchBy)) {
                    objects.insert(*curr);
                }
                curr = curr->getNext();
            } while(curr != head);
        }
       else if(strcmp_i(verb.getData(), Element("contains").getData()) == 0) {
            do 
            {  
                if(curr->getProperties().containsSequence_i(memberVar, valueToSearchBy)) {
                    objects.insert(*curr);
                }
                curr = curr->getNext();
            } while(curr != head);
        }
        else if(strcmp_i(verb.getData(), Element("like").getData()) == 0) {
            do 
            {   
                if(curr->getProperties().wildcardSearch_i(memberVar, valueToSearchBy)) {
                    objects.insert(*curr);
                }
                curr = curr->getNext();
            } while(curr != head);
        }
        else if(strcmp_i(verb.getData(), Element("not").getData()) == 0) {
            do 
            {   
                if(!(curr->getProperties().wildcardSearch_i(memberVar, valueToSearchBy))) {
                    objects.insert(*curr);
                }
                curr = curr->getNext();
            } while(curr != head);
        }
    }
    //else{std::cout<<"Cannot search for object where: '" << memberVar << " " << verb << " " << valueToSearchBy << "'" << std::endl;}

    return objects;
}

List Objects::getSignificantPropertyKeys() 
{
    List list;

    if(head == nullptr){return list;}

    curr = head;

    do
    {
        Properties properties(curr->getProperties().findMatch_i(curr->getName()));

        if(properties.size() > 1 )
        {
            for(int i = 0; i < properties.size(); i++)
            {
                list.insert(properties.getProperty(i).getKey());
            }
        }

        curr = curr->getNext();
    } while(curr != head);

    // if list is empty, then there was a 1:1 ratio in property key names with all objects
    //  No objects containing Key: Value pairs had object name match property key value to other property key same value
    //  How to determine significant properties in 1:1 property keys where all keys of other objects are the same

    return list;
}



Object Objects::getObject(int pos)
{
    if(head == nullptr){return Object();}
    
    int position = 0;

    curr = head;

    do
    {   if(position == pos) {
            return *curr;
        }
        position++;
        curr = curr->getNext();
    } while(curr != head);

    return Object();
}


//void Objects::consolidateBySignificantPropertyKeys()
//{
//    
//    List list(this->getSignificantPropertyKeys());
//
//
//    Objects consolidated;
//    
//    for(int i = 0; i < list.size(); i++)
//    {
//        Objects objects(this->where("name", "in", list.getDataAtPosition(i)));        
//       
//        
//    }
//
//
//}


Objects Objects::consolidatedBySignificantPropertyKeys() 
{
    
    List list(this->getSignificantPropertyKeys());


    Objects consolidated;
    
    for(int i = 0; i < list.size(); i++)
    {
        Objects objects(this->where("name", "in", list.getDataAtPosition(i)));        
      
        for(int i = 0; i < objects.size(); i++) {

            Object object(objects.getObject(i));

            consolidated.insert(object);
        }
    }

    return consolidated;
}


Objects Objects::getObjectsFound(int numberOfTimesFound) 
{

    Objects objectsFoundNumberOfTimes;

    if(head == nullptr){return objectsFoundNumberOfTimes;}

    curr = head;

    do 
    {   
	    if(curr->getProperties().getProperty(Element("Found In")).getValue().size() == numberOfTimesFound) {

            //std::cout<<curr->getProperties().getProperty(Element("Found In")).getValue().size()<<std::endl;
            //std::cout<<curr->getProperties().getProperty(Element("Found In")).getValue()<<std::endl;
            objectsFoundNumberOfTimes.insert(*curr);
        }

        curr = curr->getNext();
    } while(curr != head);

    return objectsFoundNumberOfTimes;
}

Objects Objects::getObjectsFoundIn(const List & list) 
{

    Objects objectsFoundInAllListValues;

    if(head == nullptr){return objectsFoundInAllListValues;}


    curr = head;

    do 
    {   
        bool foundObjectInAllListValues = true;

        for(int j = 0; j < list.size(); j++) {
	        if(curr->getProperties().findMatch(Element("Found In"), list.getDataAtPosition(j))) {
            }
            else{foundObjectInAllListValues = false;}
        }
        if(foundObjectInAllListValues == true) {
            objectsFoundInAllListValues.insert(*curr);
        }

        curr = curr->getNext();
    } while(curr != head);

    return objectsFoundInAllListValues;
}

Objects Objects::getObjectsFoundIn(const Element & fileName) 
{

    Objects objectsFoundInFile;

    if(head == nullptr){return objectsFoundInFile;}

    curr = head;

    do 
    {
	    if(curr->getProperties().findMatch(Element("Found In"), fileName)) {
            objectsFoundInFile.insert(*curr);
        }

        curr = curr->getNext();
    } while(curr != head);

    return objectsFoundInFile;
}

Objects Objects::getObjectsNotFoundIn(const Element & fileName) 
{
    Objects objectsNotFoundInFile;

    if(head == nullptr){return objectsNotFoundInFile;}

    curr = head;

    do 
    {
	    if(!(curr->getProperties().findMatch(Element("Found In"), fileName))) {
            objectsNotFoundInFile.insert(*curr);
        }

        curr = curr->getNext();
    } while(curr != head);

    return objectsNotFoundInFile;
}

List Objects::getListOfPropertyValues(const Element & key)
{
    List list;
    if(head == nullptr){return list;}

    do 
    {
        String string(curr->getProperties().getProperty(key).getValue());

        for(int i = 0; i < string.size(); i++) {
            list.insert(string.getDataAtPosition(i));
        }
        curr = curr->getNext();
    } while(curr != head);
    return list;
}
List Objects::getListOfPropertyValues()
{
    List list;
    if(head == nullptr){return list;}

    do 
    {
        Properties properties(curr->getProperties());

        for(int i = 0; i < properties.size(); i++) {
            String string(properties.getProperty(i).getValue());
            
            for(int i = 0; i < string.size(); i++) {
                list.insert(string.getDataAtPosition(i));
            }
        }
        curr = curr->getNext();
    } while(curr != head);
    return list;
}
List Objects::getListOfPropertyKeys()
{
    List list;
    if(head == nullptr){return list;}

    do 
    {
        Properties properties(curr->getProperties().getKeys());
        
        for(int i = 0; i < properties.size(); i++) {
            list.insert(properties.getProperty(i).getKey());
        }
        curr = curr->getNext();
    } while(curr != head);
    return list;
}


/* This function prints the Objects to standard out
 * 
 * Function: print
 * Param:  null
 * return: void
 */
void Objects::print()
{ 
    if (head == nullptr) {
        std::cout << "Objects is empty." << std::endl;
        return;
    } 
    
    curr = head;
    int count        = 0;
    std::cout << "--------------------------------------*BEGIN OBJECTS*--------------------------------------" << std::endl;
    do 
    {
        std::cout << "\n---" << std::endl;
        curr->print();
		curr = curr->getNext();
        count++;
    } while(curr != head);
    std::cout << "--------------------------------------*END OBJECTS*--------------------------------------" << std::endl;
}

/* This function returns the size of the largest object in the Objects
 * 
 * Function: sizeOfLargestObject
 * Param:  null
 * return: int
 */
int Objects::sizeOfLargestObject() const
{
    if (head == nullptr) {
        return 0;                 // Return 0 for an empty objects
    }
    Object *curr = head;
    int      size = curr->size(); // Initialize with the size of the first object
    do                            // Traverse the objects
    {
        if (curr->size() > size) {
            size = curr->size();
        }
        curr = curr->getNext();
    } while (curr != head);
    return size;
}


// vvvvvvvvvvvvvvvvvvvvvvvvvvv--------------------------------------------------------------------------- 
//
// Operator Overload Functions
//
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^---------------------------------------------------------------------------

Objects & Objects::operator=(const Objects &other)  
{
    //std::cout << "copy assignment called" << std::endl;
    if (this != &other) {
        this->clear();                                // Clear the current objects
        Object *otherCurr = other.head;               // Copy objects from the other objects
        if(otherCurr != nullptr) {
            do 
            {
                this->insert(new Object(*otherCurr)); // Copy the Object object
                otherCurr = otherCurr->getNext();
            } while (otherCurr != other.head);
        } 
    }
    return *this;
}

Objects & Objects::operator=(Objects &&other)  
{
    std::cout << "move assignment called" << std::endl;
    if (this != &other) {
        this->clear();                     // Clear the current objects
        this->head = other.head;           // Move objects from the other objects
        other.head = nullptr;              // Dereference other's head
        other.clear();                     // Clear other to an empty objects to prevent unexpected behavior
        std::cout << this << " " << &other << std::endl;
    }
    return *this;
}

Objects Objects::operator+(const Objects &other) const 
{
    Objects newObjects(*this);             // Create a new objects by copying the current objects 
    Object *otherCurr = other.head;        // Initialize otherCurr to the head of the other objects 
    if (otherCurr != nullptr) {            // Traverse the circular linked objects
        do 
        {   // Create a new Object object with the same data as otherCurr
            Object *newObject = new Object(*otherCurr);
            newObjects.insert(newObject);     // Insert the new Object into the new objects
            otherCurr = otherCurr->getNext();
        } while (otherCurr != other.head);    // Loop until we reach the head again
    }
    return newObjects;                        // Return the new objects with concatenated objects
}    

bool Objects::operator==(const Objects &other) const  
{
    if (this == &other)                    // Check if it's the same object
        return true;

    Object *thisCurr = head;
    Object *otherCurr = other.head;

    if (thisCurr == nullptr && otherCurr == nullptr) {
        return true;                       // Both objectss are empty, consider them equal
    }
    if (thisCurr != nullptr && otherCurr == nullptr) {
        return false;
    }
    if (thisCurr == nullptr && otherCurr != nullptr) {
        return false;
    }
    if (thisCurr != nullptr && otherCurr != nullptr) {
         do                                // Traverse the circular linked objectss
         {    
             if (!(thisCurr->getName() == otherCurr->getName())) {
                 return false;             // If any node doesn't match or reaches the end, objectss are not equal
             }
             thisCurr = thisCurr->getNext();
             otherCurr = otherCurr->getNext();
             if (thisCurr == head && otherCurr == other.head)
                 break;                    // If we reach the head again, we've completed a full loop, exit the loop

         } while (thisCurr != head && otherCurr != other.head);
    }

    return true;                           // Objectss are equal if both objectss complete a full loop
}

bool Objects::operator!=(const Objects &other) const 
{
    return !(*this == other);
}
