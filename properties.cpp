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
                
                curr->setValue(value->getValue());
                

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

void Properties::print() const
{
    if (head == nullptr) {
        std::cout << "No properties to display." << std::endl;
        return;
    }

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
    Property position   (Element("Position"));

    this->insert(description); 
    this->insert(uuid); 
    this->insert(position); 
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
