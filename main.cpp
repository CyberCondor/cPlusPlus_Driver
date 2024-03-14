#include "main.h"

int main(int argc, char **argv, char **envp)
{
    Objects CSVs;                           // Init Main Object of Objects to hold information from CSVs

    List list;                              // Init list to hold argument values
    for(auto idx = 0; idx < argc; idx++)    // For the Argument Count 
    {                                       // Put the parameterized arguments into an organized list
        Element buffer(argv[idx]);          // Using the Element Constructor to copy argv into Element
        list.insert(buffer);                // And the Sorted Insertion Mutator to insert the Element into the list
    }

    CSVs.importCSVs(list);                  // Import CSVs into objects
    CSVs.print();                           // Display the objects

    return 0;
}
