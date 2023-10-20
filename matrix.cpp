#include "matrix.h"

Matrix::~Matrix()
{
    delete[] rows;
    delete[] columns;
    numRows = 0;
    numCols = 0;
}
Matrix::Matrix()
{
    rows    = nullptr;
    columns = nullptr;
    numRows = 0;
    numCols = 0;
}
Matrix::Matrix(int rows, int columns)
{
    this->rows    = new List[rows];
    this->columns = new List[columns];
   
    numRows = rows;
    numCols = columns;

    for (int i = 0; i < rows; i++)     {// Set values in the matrix
        for (int j = 0; j < columns; j++) {
            Element buffer = intToString(i);
            buffer += Element(",");
            buffer += j;
            this->setValue(i, j, buffer);
        }
    } 

}
Matrix::Matrix(int rows, int columns, const Element & value)
{
    this->rows    = new List[rows];
    this->columns = new List[columns];
   
    numRows = rows;
    numCols = columns;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            Element element = value;
            this->rows[i].insert(element, j);
            this->columns[j].insert(element, i);
        }
    }
}

void Matrix::resize(int rows, int columns)
{
    if(rows != 0 && columns != 0) {
        if(this->rows == nullptr || this->columns == nullptr) {
            if(this->rows    != nullptr) { delete [] this->rows;    }
            if(this->columns != nullptr) { delete [] this->columns; }
            this->rows    = new List[rows];
            this->columns = new List[columns];
            this->numRows = rows;
            this->numCols = columns;
        }
        else{
            List * newRows    = new List[rows];
            List * newColumns = new List[columns];
            for (int i = 0; i < rows; i++)        {
                for (int j = 0; j < columns; j++) {
                    Element valToCopy = this->getValue(i, j);
                    if (valToCopy.getData() == nullptr) {
                        Element buffer = intToString(i);
                        buffer += Element(",");
                        buffer += j;
                        newRows[i].insert(buffer, j);
                        newColumns[j].insert(buffer, i);
                    
                    }
                    else{
                        newRows[i].insert(valToCopy, j);
                        newColumns[j].insert(valToCopy, i);
                    }
                }
            }
            if(this->rows    != nullptr) { delete [] this->rows;    }
            if(this->columns != nullptr) { delete [] this->columns; }
            this->numRows = rows;
            this->numCols = columns;
            this->rows    = newRows;
            this->columns = newColumns;
        }
    }
}

Element Matrix::getValue(int i, int j) const               // Get the value at a specific position (i, j) in the matrix
{
    if (i >= numRows || j >= numCols) { return Element(); }
    if (i >= 0 && i < numRows && j >= 0 && j < numCols) {
        Element * row = this->rows[i].getHead();
        Element * col = this->columns[j].getHead();
        if(row != nullptr && col != nullptr) {
            for (int k = 0; k < j; k++) { row = row->getNext(); }
            for (int k = 0; k < i; k++) { col = col->getNext(); }
            if (*row == *col) {
                return *row;
            }
        }
        else{
            //std::cout << "Value at: '"<<i << "," << j<<"' is empty." << std::endl;
            return Element();
        }
    }
    return Element(); // Return an empty Element if the indices are out of bounds || Element @ row != Element @ col
}

// Set the value at a specific position (i, j) in the matrix
void Matrix::setValue(int i, int j, const Element & element)
{
    if (i >= 0 && i < numRows && j >= 0 && j < numCols) {
        Element value = element;
        if (this->getValue(i, j) != Element()) {
            this->rows[i].remove(j);
            this->columns[j].remove(i);
        }
        this->rows[i].insert(value, j);
        this->columns[j].insert(value, i);
    }
}
void Matrix::setValues(const Element & element)
{
    this->setValues_UpperLeftToBottomRight(element);
}

void Matrix::print() const                                 // Print the matrix with column alignment
{
    if(numCols == 0 || numRows == 0)         {std::cout << "\tMatrix Empty. No Data Yet."<< std::endl;return;}
    if(rows == nullptr || columns == nullptr){std::cout << "\tMatrix Empty. No Data Yet."<< std::endl;return;}

    int* maxColumnWidth = new int[numCols];     // Initialize an array to store the maximum width for each column

    for (int j = 0; j < numCols; j++) {
        maxColumnWidth[j] = 0;
    }

    for (int j = 0; j < numCols; j++) {         // Find the maximum width for each column
        for (int i = 0; i < numRows; i++) {
            int elementWidth = this->getValue(i, j).size();
            if (elementWidth > maxColumnWidth[j]) {
                maxColumnWidth[j] = elementWidth;
            }
        }
    }

    for (int i = 0; i < numRows; i++) {         // Print the matrix with aligned columns
        for (int j = 0; j < numCols; j++) {
            std::cout << std::setw(maxColumnWidth[j]) << this->getValue(i, j);
            if (j < numCols - 1) {
                std::cout << ' ';
            }
        }
        std::cout << std::endl;
    }

    delete[] maxColumnWidth;                    // Clean up memory
}

void Matrix::printRow(int row) const                    // Print a specific row
{
    if (row >= 0 && row < numRows) {
        this->rows[row].getDeets();
        for (int j = 0; j < numCols; j++) {
            std::cout << this->getValue(row, j);
            if (j < numCols - 1) {
                std::cout << ' ';
            }
        }
        std::cout << std::endl;
    }
}
void Matrix::printColumn(int column) const              // Print a specific column
{
    if (column >= 0 && column < numCols) {
        this->columns[column].getDeets();
        for (int i = 0; i < numRows; i++) {
            std::cout << this->getValue(i, column) <<std::endl;
        }
    }
}

void Matrix::printIntersection(int row, int column) const
{
    if (row >= 0 && row < numRows && column >= 0 && column < numCols) {
        Element element = this->getValue(row, column);
        
        int width = 0;
        for (int j = 0; j < numCols; j++) {
            if (j == column) {
                
                break;

            } else {
                Element colElement = this->getValue(row, j);
                int colElementWidth = colElement.length();
                width += colElementWidth + 1;
            }
        }
        int elementWidth = element.length();

        // Print the values in the specified column above the intersection point
        for (int i = 0; i < row; i++) {
            Element rowElement = this->getValue(i, column);
            //std::cout << std::setw(elementWidth * column + column) << " " << rowElement << std::endl;
            if (column != 0){
                std::cout << std::setw(width) << " " << rowElement << std::endl;
            }
            else{std::cout << rowElement << std::endl;}
        }

        // Print the values in the specified row with space padding
        for (int j = 0; j < numCols; j++) {
            if (j == column) {
                std::cout << std::setw(elementWidth + 1) << element;
            } else {
                Element colElement = this->getValue(row, j);
                int colElementWidth = colElement.length();
                std::cout << std::setw(colElementWidth + 1) << colElement;
            }
        }
        std::cout << std::endl;

        // Print the values in the specified column below the intersection point
        for (int i = row + 1; i < numRows; i++) {
            Element rowElement = this->getValue(i, column);
            if (column != 0){
                std::cout << std::setw(width) << " " << rowElement << std::endl;
            }
            else{std::cout << rowElement << std::endl;}
        }
    }
}

void Matrix::printIntersections() const
{
    int row = this->getNumRows();
    int col = this->getNumCols();

    if(row == col){
        for (int i = 0;i < row; i++) {
            this->printIntersection(i, i); 
        }
    }
    else if(col > row){
        for (int i = 0;i < col; i++) {
            for (int j = 0;j < row; j++) {
                this->printIntersection(j, i); 
            }
        }
    }
    else{
        for (int j = 0;j < col; j++) {
            for (int i = 0;i < row; i++) {
                this->printIntersection(i, j);  
            }
        }
    }
}

// Print the matrix without any consideration for Element value length
//void Matrix::printMess() {
//    if(this->rows == nullptr || this-> columns == nullptr) {
//
//        std::cout << "Matrix is empty." << std::endl;
//
//    }
//    for (int i = 0; i < numRows; i++) {
//        for (int j = 0; j < numCols; j++) {
//            std::cout << this->getValue(i,j) << ' ';
//        }
//        std::cout << std::endl;
//    }
//}

void Matrix::transpose()                        // Transpose the matrix
{   // Swap rows and columns
    std::swap(this->rows, this->columns);
    std::swap(this->numRows, this->numCols);
}



void Matrix::setValues_BottomRightToUpperLeft(const Element & value)
{ 
    int row = this->getNumRows();
    int col = this->getNumCols();
    for (int i = row;i >= 0; i--)     {
        for (int j = col;j >= 0; j--) {
            this->setValue(j, i, value);    
            //this->print();
        }
    }
}
void Matrix::setValues_BottomLeftToUpperRight(const Element & value)
{ 
    int row = this->getNumRows();
    int col = this->getNumCols();
    for (int i = (row - 1); i >= 0; i--) {
        for (int j = 0;j < col; j++)     {
            this->setValue(i, j, value);
            //this->print();
        }
    }
}
void Matrix::setValues_UpperLeftToBottomRight(const Element & value)
{ 
    int row = this->getNumRows();
    int col = this->getNumCols();
    for (int i = 0;i < row; i++)     {
        for (int j = 0;j < col; j++) {
            this->setValue(i, j, value);    
            //this->print();
        }
    }
}
void Matrix::setValues_UpperRightToBottomLeft(const Element & value)
{ 
    int row = this->getNumRows();
    int col = this->getNumCols();
    for (int i = (row - 1);i >= 0; i--) {
        for (int j = 0;j < col; j++)    {
            this->setValue(j, i, value);    
            //this->print();
        }
    }
}

void Matrix::setValuesDiagonal_BottomRightToUpperLeft(const Element & value)
{ 
    int row = this->getNumRows();
    int col = this->getNumCols();
    for (int i = row;i >= 0; i--)     {
        for (int j = col;j >= 0; j--) {
            this->setValue(j, i, value);    
            this->print();
            i--;
        }
    }
}
void Matrix::setValuesDiagonal_BottomLeftToUpperRight(const Element & value)
{ 
    int row = this->getNumRows();
    int col = this->getNumCols();
    for (int i = (row - 1); i >= 0; i--) {
        for (int j = 0;j < col; j++)     {
            this->setValue(i, j, value);
            this->print();
            i--;
        }
    }
}
void Matrix::setValuesDiagonal_UpperLeftToBottomRight(const Element & value)
{ 
    int row = this->getNumRows();
    int col = this->getNumCols();
    for (int i = 0;i < row; i++)     {
        for (int j = 0;j < col; j++) {
            this->setValue(i, j, value);    
            this->print();
            i++;
        }
    }
}
void Matrix::setValuesDiagonal_UpperRightToBottomLeft(const Element & value)
{ 
    int row = this->getNumRows();
    int col = this->getNumCols();
    for (int i = (row - 1);i >= 0; i--) {
        for (int j = 0;j < col; j++)    {
            this->setValue(j, i, value);    
            this->print();
            i--;
        }
    }
}
