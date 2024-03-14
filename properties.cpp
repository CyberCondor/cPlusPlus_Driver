#include "properties.h"

Properties::~Properties()
{
    if (head != nullptr){
        Property* current = head;
        do
        {
            Property* next = current->getNext();
            delete current;
            current = next;
        } while (current != head);
    }
}

Properties::Properties(Property * property) : Properties()
{
    this->insert(property);
}

Properties::Properties(Property property) : Properties()
{
    this->insert(property);
}

Properties::Properties(const Properties & other) : Properties()
{
    // Initialize head and curr pointers for the new list
    head = nullptr;
    Property * curr = head;

    // Copy each element from the other list to the new list
    if (other.head != nullptr) {
        Property *otherCurr = other.head;

        do
        {   // Create a new Element instance with the data from 'otherCurr'
            Property *newNode = new Property(*otherCurr);                       
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
    }
}

void Properties::insert(Property *target, int pos)   
{
    if(head == nullptr) {      // If no List 
        head = target;		   // Create List
        target->setNext(head); // Point head to itself
    }                         
    else
    {   
        Property * curr = head;
        Property * prev = nullptr;
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
            curr->setNext(target);        // Add to end of List
            target->setNext(head);        // Point end of List back to head
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

bool Properties::insert(Property * value)   // Sorted Insertion Mutator
{
    int  position = 0;
    bool found    = false;

    if (head == nullptr)            // If no List
    {
        head = value;               // Create the List
        value->setNext(head);       // Point head to itself  
    }
    else
    {	Property * curr = head;
        do
        {
            if(strcmp_i(curr->getKey().getData(), value->getKey().getData()) == 0) {
                found = true;      // Don't add to the list. Duplicate was found.
                
                curr->appendValue(value->getValue());
                

                delete value;
                break;
            }
            if(strcmp_i(curr->getKey().getData(), value->getKey().getData()) > 0) {
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

bool Properties::insert(const Property& property)
{
    Property* newProperty = new Property(property);
    return insert(newProperty);
}

bool Properties::insert(const Element & key)
{
    Property* newProperty = new Property(key);
    return insert(newProperty);
}

bool Properties::insert(const Element & key, const Element & value)
{
    Property* newProperty = new Property(key, value);
    return insert(newProperty);
}

bool Properties::insert(const Element & key, const String & value)
{
    Property* newProperty = new Property(key, value);
    return insert(newProperty);
}


bool Properties::findMatch(const Element & key, const Element & target)
{
    bool found = false;
    if (head != nullptr) {
        Property * curr = head;
        do
        {   
            if(key == curr->getKey()) {
                if(curr->getValue().findMatch(target)) {
                    found = true;
                }
            }
            curr = curr->getNext();
        } while(curr != head);
    } 
    return found;   
}
Properties Properties::findMatch(const Element & target)
{
    Properties properties;
    if (head != nullptr) {
        Property * curr = head;
        do
        {
            String string(curr->getValue().findMatch_z(target));
            if(string != String()) {
                properties.insert(curr->getKey(), curr->getValue().findMatch_z(target));
            }
            curr = curr->getNext();
        } while(curr != head);
    } 
    return properties;   
}
Properties Properties::findMatch_i(const Element & target)
{
    Properties properties;
    int  position = 0;
    if (head != nullptr) {
        Property * curr = head;
        do
        {
            properties.insert(curr->getKey(), curr->getValue().findMatch_i_z(target));
            curr = curr->getNext();
            position++;
        } while(curr != head);
    } 
    return properties;   
}

Properties Properties::containsSequence(const Element & target)
{
    Properties properties;
    int  position = 0;
    if (head != nullptr) {
        Property * curr = head;
        do
        {
            properties.insert(curr->getKey(), curr->getValue().containsSequence_z(target));
            curr = curr->getNext();
            position++;
        } while(curr != head);
    } 
    return properties;   
}
Properties Properties::containsSequence_i(const Element & target)
{
    Properties properties;
    int  position = 0;
    if (head != nullptr) {
        Property * curr = head;
        do
        {
            properties.insert(curr->getKey(), curr->getValue().containsSequence_i_z(target));
            curr = curr->getNext();
            position++;
        } while(curr != head);
    } 
    return properties;   
}
Properties Properties::wildcardSearch(const Element & target)
{
    Properties properties;
    int  position = 0;
    if (head != nullptr) {
        Property * curr = head;
        do
        {
            properties.insert(curr->getKey(), curr->getValue().wildcardSearch_z(target));
            curr = curr->getNext();
            position++;
        } while(curr != head);
    } 
    return properties;   
}
Properties Properties::wildcardSearch_i(const Element & target)
{
    Properties properties;
    int  position = 0;
    if (head != nullptr) {
        Property * curr = head;
        do
        {
            properties.insert(curr->getKey(), curr->getValue().wildcardSearch_i_z(target));
            curr = curr->getNext();
            position++;
        } while(curr != head);
    } 
    return properties;   
}

Properties Properties::getKeys() const
{
    Properties properties;
    if (head == nullptr) {
        std::cout << "No properties to display." << std::endl;
        return properties;
    }

    Property* curr = head;
    do
    {
        properties.insert(curr->getKey());

        curr = curr->getNext();
    } while (curr != head);

    return properties;
}

Properties Properties::getProperties() const
{
    Properties properties;
    if (head == nullptr) {
        std::cout << "No properties to display." << std::endl;
        return properties;
    }

    Property* curr = head;
    do
    {
        properties.insert(curr->getKey(), curr->getValue());

        curr = curr->getNext();
    } while (curr != head);

    return properties;
}

void Properties::print() const
{
    if (head == nullptr) {
        std::cout << "No properties to display." << std::endl;
        return;
    }
    
    std::cout << "Properties:" << std::endl;
    Property* current = head;
    int maxWidth = 0;
    do {
        int width = current->getKey().size();
        if(width > maxWidth) {
            maxWidth = width;
        }
        current = current->getNext();
    } while (current != head);


    do {
        std::cout<< std::setw(maxWidth);
        current->print();
        current = current->getNext();
    } while (current != head);
    std::cout << "------------------" << std::endl;
}

void Properties::setDefault()
{
    Property description(Element("Description"));
    Property uuid       (Element("UUID"));
    //Property position   (Element("Position"));

    this->insert(description); 
    this->insert(uuid); 
    //this->insert(position); 
}

int Properties::size() const
{
    int result = 1;
    if (head != nullptr) {
        Property * curr = head;
        while(curr->getNext() != head)
        {
            result++;
            curr = curr->getNext();
        }
    }
    else {return 0;}
    return result;
} 

void Properties::clear()                                   // Completely clear a Properties
{
    if (head != nullptr) {
        Property *curr = head;
        Property *next = nullptr;
        do 
        {   // Traverse the circular linked string and delete nodes
            next = curr->getNext();
            delete curr;
            curr = next;
        }while (curr != head);
        head = nullptr; // Reset the head pointer
    }
}



//Properties Properties::operator+(const Properties &other) const 
//{
//    Properties newProperties(*this);                   // Create a new string by copying the current string 
//    Properties *otherCurr = other.getHead();       // Initialize otherCurr to the head of the other string 
//    if (otherCurr != nullptr) {            // Traverse the circular linked string
//        do 
//        {   // Create a new Element object with the same data as otherCurr
//            Property *newProperty = new Property(*otherCurr);
//            newProperties.insert(newProperty);     // Insert the new Element into the new string
//            otherCurr = otherCurr->getNext();
//        } while (otherCurr != other.head); // Loop until we reach the head again
//    }
//    return newProperties;                        // Return the new string with concatenated elements
//}    


Properties & Properties::operator=(const Properties &other)  
{
    //std::cout << "copy assignment called" << std::endl;
    if (this != &other) {
        this->clear();                                 // Clear the current string
        Property *otherCurr = other.head;               // Copy elements from the other string
        if(otherCurr != nullptr) {
            do 
            {
                this->insert(new Property(otherCurr->getKey(), otherCurr->getValue())); // Copy the Element element
                otherCurr = otherCurr->getNext();
            } while (otherCurr != other.head);
        } 
    }
    return *this;
}
