#include "main.h"

/*
While the C++ language standard provides minimum size requirements for data types, 
the exact size of data types is determined by a combination of factors, 
including the compiler, target hardware, compiler flags, and platform-specific considerations. 
*/

int main(int argc, char **argv, char **envp) {

    List list;
    list.insert(Element("Item A"));                  // Sorted Insertion Mutator
    list.insert(Element("IteM A"));                  // Sorted Insertion Mutator
    list.insert(Element("ItEm A"));                  // Sorted Insertion Mutator
    list.insert(Element("ITem B"));                  // Sorted Insertion Mutator
    list.insert(Element("ITem 1"));                  // Sorted Insertion Mutator

    list.print();
    list.getDeets();

    for(auto idx = 0; idx < argc; idx++)                  // For the Argument Count 
    {                                                     // Put the parameterized arguments into an organized list
        list.insert(Element(argv[idx]));                  // And the Sorted Insertion Mutator for previously created list
    }
    for(auto idx = 0; envp[idx] != nullptr; idx++)        // Until the end of environment variables (nullptr)
    {                                                     // Put the environment variables into an organized list 
        list.insert(Element(envp[idx]));                  // And the Sorted Insertion Mutator for previously created list
    }

    list.print();

    list.getDeets();

    list.remove(35);

    list.getDeets();

    list.print();

    for (int i = 0; i < 100; i++) {
        Element e = "item";
        e += i;
        list.insert(e);    
    }
    
    Element e = "item";
    int i = 91920;
    Element f = e + i ;

    Element p = "tailpid";

    std::cout<<p + "tailpod" + i + "pong" + f + p + i + f<<std::endl;
    
    list.insert(Element(p + "tailpod" + i + "pong" + f + p + i + f));

    list.insert(f);

    list.printReverse();

    list.find(Element("Item A"));
    list.remove(23);
    if (!(list.find(Element("Item A")))) {
        std::cout<<"not found!"<<std::endl;
    }

    list.print();

    if (list.wildcardMatch(Element("*9"))) {
        std::cout << "yes this exists- WILDCARDmATCH" << std::endl;
    }
    
    if (list.contains(Element("tem"))) {
        std::cout << "yes tem exists - CONTAINS" << std::endl;
    }


    if (list.contains(Element("21"))) {
        std::cout << "yes 21 exists - CONTAINS" << std::endl;
    }

    list.contains(Element("condor"));
    list.contains(Element("z"));
    list.contains(Element("2"));
    list.contains(Element("9"));
    list.contains(Element("dor"));
    list.contains(Element("CyberCondor"));

    for (int i = 0; i < 105; i++) {
        Element e = "item";
        e += i;
        list.remove(e);    
    }

    if (list.contains(new Element("tem"))) {
        std::cout << "yes tem exists POINTER USED - CONTAINS" << std::endl;
    }

    list.insert(Element(p + "tailpod" + i + "pong" + f + p + i + f));
//    list.insert(Element("tailpod" + i + "ping" + "pong" + f + p + i + f)); make this work!
    list.getDeets();

    list.print();

    return 0;
}
