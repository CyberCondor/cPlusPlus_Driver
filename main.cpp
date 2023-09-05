#include "main.h"

/*
While the C++ language standard provides minimum size requirements for data types, 
the exact size of data types is determined by a combination of factors, 
including the compiler, target hardware, compiler flags, and platform-specific considerations. 
- ChatGPT - Sep 3, 2023
*/

int main(int argc, char **argv, char **envp) {

    String randString = String("this new string");

    std::cout <<"MemSize of randString: "<<randString.getMemUsed()<<std::endl;
    std::cout <<"Size of randString   : "<<randString.size()<<std::endl;

    String randString2;

    std::cout <<"MemSize of randString2: "<<randString2.getMemUsed()<<std::endl;
    std::cout <<"Size of randString2   : "<<randString2.size()<<std::endl;
    

        // Display the size of Data Types used in the program.
    std::cout <<"----*START - Size of Data Types in Bytes*----"<<std::endl;
    std::cout <<"Size of size_t : "<<sizeof(size_t) <<std::endl;
    std::cout <<"Size of char   : "<<sizeof(char)   <<std::endl;
    std::cout <<"Size of char*  : "<<sizeof(char*)  <<std::endl;
    std::cout <<"Size of nullptr: "<<sizeof(nullptr)<<std::endl;
    std::cout <<"Size of List   : "<<sizeof(List)   <<std::endl;
    std::cout <<"Size of List*  : "<<sizeof(List*)  <<std::endl;
    std::cout <<"Size of String : "<<sizeof(String) <<std::endl;
    std::cout <<"Size of String*: "<<sizeof(String*)<<std::endl;
    std::cout <<"----*END -   Size of Data Types in Bytes*----"<<std::endl;

        // Define some List objects to use for testing the List class.
    List * list  = new List; // This is just a pointer to memory allocated to a new list - this memory is managed here in main.
    List * list2 = new List; // This is just a pointer to memory allocated to a new list - this memory is managed here in main.
    List * list3 = new List; // This is just a pointer to memory allocated to a new list - this memory is managed here in main.
    List   list4;            // This is just a new list. All memory is handled in List Class.
    List   list5;            // This is just a new list. All memory is handled in List Class.
    List   list6;            // This is just a new list. All memory is handled in List Class.


       // Put some dynamic runtime variables into the main List from argc and envp. 
    for(auto idx = 0; idx < argc; idx++)                  // For the Argument Count 
    {                                                     // Put the parameterized arguments into an organized list
        String * buffer = new String(argv[idx]);          // Using the String Constructor to copy argv as string
        list->insert(buffer);                             // And the Sorted Insertion Mutator for previously created list
    }
    for(auto idx = 0; envp[idx] != nullptr; idx++)        // Until the end of environment variables (nullptr)
    {                                                     // Put the environment variables into an organized list 
        String * buffer = new String(envp[idx]);          // Using the String Constructor to copy envp as String
        list->insert(buffer);                             // And the Sorted Insertion Mutator for previously created list
    }

        // Put stuff in list2.
    list2->insert(new String("Item A"));                  // Sorted Insertion Mutator
    list2->insert(new String("IteM A"));                  // Sorted Insertion Mutator
    list2->insert(new String("ItEm A"));                  // Sorted Insertion Mutator
    list2->insert(new String("ITem B"));                  // Sorted Insertion Mutator
    list2->insert(new String("ITem 1"));                  // Sorted Insertion Mutator
    
    std::cout <<"----*START - list2*----"<<std::endl;
    list2->getDeets();                                    // Display Details of List 
    std::cout <<"----*END -   list2*----"<<std::endl;
    std::cout <<"----*START - list3*----"<<std::endl;
    list3->getDeets();                                    // Display Details of List 
    std::cout <<"----*END -   list3*----"<<std::endl;
    std::cout <<"----*START - list4*----"<<std::endl;
    list4.getDeets();                                     // Display Details of List 
    std::cout <<"----*END -   list4*----"<<std::endl;
    std::cout <<"----*START - list5*----"<<std::endl;
    list5.getDeets();                                     // Display Details of List 
    std::cout <<"----*END -   list5*----"<<std::endl;
    std::cout <<"----*START - list6*----"<<std::endl;
    list6.getDeets();                                     // Display Details of List 
    std::cout <<"----*END -   list6*----"<<std::endl;
    
    *list3 = *list2;                                      // Copy Assignment
     list4 = *list3;                                      // Copy Assignment
     list5 =  list4;                                      // Copy Assignment
    *list3 =  list5;                                      // Copy Assignment



    std::cout <<"----*START - list5*----"<<std::endl;
    list5.getDeets();                                     // Display Details of List 
    std::cout <<"----*END -   list5*----"<<std::endl;
    std::cout <<"----*START - list6*----"<<std::endl;
    list6.getDeets();                                     // Display Details of List 
    std::cout <<"----*END -   list6*----"<<std::endl;


    if (*list2 == *list3) {std::cout << "list2 is equal to list3" << std::endl;}    // Equality Operator
    if (list5 == list6) {std::cout << "list5 is equal to list6" << std::endl;}      // Equality Operator
    if (list6 == list5) {std::cout << "list6 is equal to list5" << std::endl;}      // Equality Operator
    list5.insert(new String("random string1"));                                     // List insertion
    list6.insert(new String("random string1"));                                     // List insertion

    std::cout <<"----*START - list5*----"<<std::endl;
    list5.getDeets();                                     // Display Details of List 
    std::cout <<"----*END -   list5*----"<<std::endl;
    std::cout <<"----*START - list6*----"<<std::endl;
    list6.getDeets();                                     // Display Details of List 
    std::cout <<"----*END -   list6*----"<<std::endl;

    if (list5 == list6) {std::cout << "list5 is equal to list6" << std::endl;}      // Equality Operator
    if (list6 == list5) {std::cout << "list6 is equal to list5" << std::endl;}      // Equality Operator
    if (*list3 != *list2) {std::cout << "list3 is not equal to list2" << std::endl;}// Inequality Operator
    std::cout << "Copying list 2 to list 3" << std::endl;
    *list3 = *list2;                                                               // Copy List2 to List3
    if (list5 != *list3) {std::cout << "list5 is not equal to list3" << std::endl;}// Inequality Operator


    std::cout <<"----*START - list2*----"<<std::endl;
    list2->getDeets();                                    // Display Details of List 
    std::cout <<"----*END -   list2*----"<<std::endl;
    std::cout <<"----*START - list3*----"<<std::endl;
    list3->getDeets();                                    // Display Details of List 
    std::cout <<"----*END -   list3*----"<<std::endl;
    std::cout <<"----*START - list4*----"<<std::endl;
    list4.getDeets();                                     // Display Details of List 
    std::cout <<"----*END -   list4*----"<<std::endl;
    std::cout <<"----*START - list5*----"<<std::endl;
    list5.getDeets();                                     // Display Details of List 
    std::cout <<"----*END -   list5*----"<<std::endl;
    
    // Output-Stream Operator
    std::cout << "Memory Address of List " << &list2 << " |List2PTR: " << list2 << *list2 << std::endl;
    std::cout << "Memory Address of List " << &list3 << " |List3PTR: " << list3 << *list3 << std::endl;
    std::cout << "Memory Address of List " << &list4 << " |List4:    " << list4 <<  list4 << std::endl;
    std::cout << "Memory Address of List " << &list5 << " |List5:    " << list5 <<  list5 << std::endl;
    std::cout << "Memory Address of List " << &list6 << " |List6:    " << list6 <<  list6 << std::endl;

    *list3 = std::move(*list2);                       // Move Assignment operator                                        
    list4  = std::move(*list3);                       // Move Assignment operator  
    list5  = std::move( list4);                       // Move Assignment operator  
    *list3 = std::move( list5);                       // Move Assignment operator    





    std::cout <<"----*START - list5*----"<<std::endl;
    list5.getDeets();                                     // Display Details of List 
    std::cout <<"----*END -   list5*----"<<std::endl;
    std::cout <<"----*START - list6*----"<<std::endl;
    list6.getDeets();                                     // Display Details of List 
    std::cout <<"----*END -   list6*----"<<std::endl;



    if (*list2 == *list3) {std::cout << "list2 is equal to list3" << std::endl;}    // Equality Operator
    if (list5 == list6) {std::cout << "list5 is equal to list6" << std::endl;}      // Equality Operator
    list5.insert(new String("random string1"));                                     // List insertion
    list6.insert(new String("random string1"));                                     // List insertion
    if (list5 == list6) {std::cout << "list5 is equal to list6" << std::endl;}      // Equality Operator
    if (*list3 != *list2) {std::cout << "list3 is not equal to list2" << std::endl;}// Inequality Operator
    std::cout << "Copying list 2 to list 3" << std::endl;
    *list3 = *list2;                                                               // Copy an EMPTY List2 to List3
    if (list5 != *list3) {std::cout << "list5 is not equal to list3" << std::endl;}// Inequality Operator


    std::cout <<"----*START - list2*----"<<std::endl;
    list2->getDeets();                                    // Display Details of List 
    std::cout <<"----*END -   list2*----"<<std::endl;
    std::cout <<"----*START - list3*----"<<std::endl;
    list3->getDeets();                                    // Display Details of List 
    std::cout <<"----*END -   list3*----"<<std::endl;
    std::cout <<"----*START - list4*----"<<std::endl;
    list4.getDeets();                                     // Display Details of List 
    std::cout <<"----*END -   list4*----"<<std::endl;
    std::cout <<"----*START - list5*----"<<std::endl;
    list5.getDeets();                                     // Display Details of List 
    std::cout <<"----*END -   list5*----"<<std::endl;

    // Output-Stream Operators
    std::cout << "Memory Address of List: " << &list2 << " |List2PTR: " << list2 << *list2 << std::endl;
    std::cout << "Memory Address of List: " << &list3 << " |List3PTR: " << list3 << *list3 << std::endl;
    std::cout << "Memory Address of List: " << &list4 << " |List4:    " << list4 <<  list4 << std::endl;
    std::cout << "Memory Address of List: " << &list5 << " |List5:    " << list5 <<  list5 << std::endl;
    std::cout << "Memory Address of List: " << &list6 << " |List6:    " << list6 <<  list6 << std::endl;



    std::cout <<"----*START - list5*----"<<std::endl;
    list5.getDeets();                                     // Display Details of List 
    std::cout <<"----*END -   list5*----"<<std::endl;
    std::cout <<"----*START - list6*----"<<std::endl;
    list6.getDeets();                                     // Display Details of List 
    std::cout <<"----*END -   list6*----"<<std::endl;



    list2->insert(new String("C++ is for understanding memory"));



    list->getDeets();



    *list = (*list) + (*list2) + (*list3);

    list->getDeets();

    List list7 = *list;

    list7.getDeets();

    std::cout << "Memory Address of List " << &list  << " |ListPTR:  " << list  << *list  << std::endl;
    std::cout << "Memory Address of List " << &list2 << " |List2PTR: " << list2 << *list2 << std::endl;
    std::cout << "Memory Address of List " << &list3 << " |List3PTR: " << list3 << *list3 << std::endl;
    std::cout << "Memory Address of List " << &list4 << " |List4:    " << list4 <<  list4 << std::endl;
    std::cout << "Memory Address of List " << &list5 << " |List5:    " << list5 <<  list5 << std::endl;
    std::cout << "Memory Address of List " << &list6 << " |List6:    " << list6 <<  list6 << std::endl;
    std::cout << "Memory Address of List " << &list7 << " |List7:    " << list7 <<  list7 << std::endl;


    std::cout <<"SIZE OF LIST:" << list->size() << std::endl;
    std::cout <<"SIZE OF LARGEST ELEMENT IN LIST:" << list->sizeOfLargestElement() << std::endl;


    std::cout <<"SIZE OF LIST :" << list->size()   <<" "<<sizeof(*list)  << std::endl;
    std::cout <<"SIZE OF LIST2:" << list2->size()  <<" "<<sizeof(*list2) << std::endl;
    std::cout <<"SIZE OF LIST3:" << list3->size()  <<" "<<sizeof(*list3) << std::endl;
    std::cout <<"SIZE OF LIST4:" << list4.size()   <<" "<<sizeof(list4) << std::endl;
    std::cout <<"SIZE OF LIST5:" << list5.size()   <<" "<<sizeof(list5) << std::endl;
    std::cout <<"SIZE OF LIST6:" << list6.size()   <<" "<<sizeof(list6) << std::endl;
    std::cout <<"SIZE OF LIST7:" << list7.size()   <<" "<<sizeof(list7) << std::endl;


    List list10;

    std::cout <<list10.getMemUsed()<<std::endl;


    delete list;
    delete list2;
    delete list3;
    return 0;
}
