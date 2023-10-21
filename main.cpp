#include "main.h"

/*
While the C++ language standard provides minimum size requirements for data types, 
the exact size of data types is determined by a combination of factors, 
including the compiler, target hardware, compiler flags, and platform-specific considerations. 
*/

int main(int argc, char **argv, char **envp) {

    int row = 34;
    int col = 34;

    Matrix matrix(row, col);
    
    std::cout << "Martix created" <<std::endl;
    matrix.print();
    std::cout << "Value at (1, 2): " << matrix.getValue(1, 2) << std::endl;

    matrix.transpose();

    std::cout << "Transposed Matrix:" << std::endl;
    matrix.print();

    matrix.transpose();

    std::cout << "Transposed back Matrix:" << std::endl;
    matrix.print();

    matrix.printRow(2);
    matrix.printColumn(4);

    List   list;
    list.insert(Element("This string "));
    list.insert(Element(",that string."));

    list.print();

    list.wildcardSearch("*n*");
    list.containsSequence("strin");
    list.findMatch("This string ");
    list.findMatch(",that string.");
    list.wildcardSearch_i("*n*");
    list.containsSequence_i("strin");
    list.findMatch_i("This string ");
    list.findMatch_i(",that string.");

    Matrix atrix(row, col, Element("tato"));

    matrix.printIntersections();  

    matrix.printIntersection(0, 0);  
    matrix.printIntersection(row - 1, col - 1);  

    matrix.printRow(2);
    matrix.printColumn(4);

    atrix.print();
    atrix.print();

    Object potato(Element("Potato!"), row, col);

    std::cout << "Value at (1, 2): " << potato.getMatrix().getValue(1, 2) << std::endl;
    std::cout << "Value at (6, 6): " << potato.getMatrix().getValue(6, 6) << std::endl;
    atrix.print();

    potato.setMatrixValue(6, 6, Element("potato"));    
    std::cout << "Value at (6, 6): " << potato.getMatrix().getValue(6, 6) << std::endl;
    atrix.print();

    potato.print();
    potato.setMatrixValue(1, 3, Element("drink"));    
    potato.print();
    potato.setMatrixValue(3, 3, Element("burger"));    
    potato.print();
    potato.setMatrixValue(3, 6, Element("salad"));    
    potato.print();
    potato.setMatrixValue(2, 11, Element("potato"));    
    potato.print();
    potato.setMatrixValue(4, 11, Element("potato"));    
    potato.print();
    potato.setMatrixValue(8, 11, Element("potato"));    
    potato.print();
    potato.setMatrixValue(8, 11, Element("loltato"));    
    potato.print();
    potato.setMatrixValue(8, 11, Element("taco"));    
    potato.print();

    potato.getMatrix().printRow(8);
    potato.getMatrix().printColumn(11);
    potato.setMatrixValues(Element("potato"));    
    
    potato.setMatrixValuesDiagonal_BottomRightToUpperLeft(Element("BR-UL"));
    potato.setMatrixValuesDiagonal_BottomLeftToUpperRight(Element("BL-UR"));
    potato.setMatrixValuesDiagonal_UpperLeftToBottomRight(Element("UL-BR"));
    potato.setMatrixValuesDiagonal_UpperRightToBottomLeft(Element("UR-BL"));

    Object pan;
    pan.print();

    matrix.setValues("Lato! lol");

    matrix.resize(11, 12);
    matrix.print();
    matrix.resize(102, 39);
    matrix.setValues("tolTato!");

    matrix.print();

    pan.rename(Element("pan"));
    pan.print();
    
    Object jan;

    jan.rename(Element("jan"));
    jan.print();

    potato.print();

    return 0;
}
