#include "main.h"

/*
While the C++ language standard provides minimum size requirements for data types, 
the exact size of data types is determined by a combination of factors, 
including the compiler, target hardware, compiler flags, and platform-specific considerations. 
*/

int main(int argc, char **argv, char **envp) {

    Object object(Element("Pie"), 4,3);

    object.setDefaultProperties();

    object.print();

    object.rename(Element("Booooooooooooo!"));

    object.addProperty(Element("Length"),        String(Element("9 lawn gnomes")));
    object.addProperty(Element("Wanted Level"),  Element("6 stars"));
    object.addProperty(Element("Freedom Points"),Element("Wanted"));
    object.addProperty(Element("longness"),      Element("6 longlongs"));
    object.addProperty(Element("Status"),        Element("On the run"));
    object.setProperty(Element("Description"),   Element("Not a Ghost"));

    object.setPosition(Position(0,0,1));

    object.print();

    object.getMatrix().transpose();

    object.print();

    return 0;
}
