#include "matrix.h"

Matrix::~Matrix()
{
    delete[] X;
    delete[] Y;
    delete[] rows;
    delete[] columns;
    numRows = 0;
    numCols = 0;
    setPosition(Position(0,0,0));
    next = nullptr;
}
Matrix::Matrix() : next(nullptr)
{
    X       = nullptr;
    Y       = nullptr;
    rows    = nullptr;
    columns = nullptr;
    numRows = 0;
    numCols = 0;
    setPosition(Position(0,0,0));
}
Matrix::Matrix(Matrix * other) : next(other->getNext())
{
    this->setPosition(other->getPosition());
    
    numRows = other->getNumRows();
    numCols = other->getNumCols();
    this->X       = new Positions[numRows];
    this->Y       = new Positions[numCols];
    this->rows    = new List[numRows];
    this->columns = new List[numCols];
    
    if(other->getNext() != nullptr) {
        Matrix * next = other->getNext();
        this->setNext(next);
    }

    for (int i = 0; i < numRows; i++)        {
        for (int j = 0; j < numCols; j++) {
            Element buffer = other->getValue(i,j);
            this->rows[i].insert(   buffer, j);
            this->columns[j].insert(buffer, i);
            this->X[i].insert(Position(i,j,other->getPosition().getZ()));
            this->Y[j].insert(Position(i,j,other->getPosition().getZ()));
        }
    }
}
Matrix::Matrix(const Matrix & other) : next(nullptr)
{
    this->setPosition(other.getPosition());
    
    numRows = other.getNumRows();
    numCols = other.getNumCols();
    this->X       = new Positions[numRows];
    this->Y       = new Positions[numCols];
    this->rows    = new List[numRows];
    this->columns = new List[numCols];

    //if(other.getNext() != nullptr) {
    //    Matrix * next = other.getNext();
    //    this->setNext(next);
    //}

    for (int i = 0; i < numRows; i++)        {
        for (int j = 0; j < numCols; j++) {
            Element buffer = other.getValue(i,j);
            this->rows[i].insert(   buffer, j);
            this->columns[j].insert(buffer, i);
            this->X[i].insert(Position(i,j,other.getPosition().getZ()));
            this->Y[j].insert(Position(i,j,other.getPosition().getZ()));
        }
    }
}
Matrix::Matrix(const Position & pos) : next(nullptr)
{
    numRows = pos.getX();
    numCols = pos.getY();
    this->X       = new Positions[numRows];
    this->Y       = new Positions[numCols];
    this->rows    = new List[numRows];
    this->columns = new List[numCols];

    this->setPosition(pos);

    for (int i = 0; i < numRows; i++)        {
        for (int j = 0; j < numCols; j++) {
            Element buffer = Element("(");
            buffer += i;
            buffer += Element(",");
            buffer += j;
            buffer += Element(")->");
            buffer += pos.getZ();
            this->rows[i].insert(   buffer, j);
            this->columns[j].insert(buffer, i);
            this->X[i].insert(Position(i,j,pos.getZ()));
            this->Y[j].insert(Position(i,j,pos.getZ()));
        }
    } 
}
Matrix::Matrix(int z) : next(nullptr)
{
    numRows = 3;
    numCols = 3;
    this->X       = new Positions[numRows];
    this->Y       = new Positions[numCols];
    this->rows    = new List[numRows];
    this->columns = new List[numCols];
    
    this->position.setZ(z);

    for (int i = 0; i < numRows; i++)        {
        for (int j = 0; j < numCols; j++) {
            Element buffer = Element("(");
            buffer += i;
            buffer += Element(",");
            buffer += j;
            buffer += Element(")->");
            buffer += z;
            this->rows[i].insert(   buffer, j);
            this->columns[j].insert(buffer, i);
            this->X[i].insert(Position(i,j,z));
            this->Y[j].insert(Position(i,j,z));
        }
    } 
}
Matrix::Matrix(int rows, int columns) : next(nullptr)
{
    this->X       = new Positions[rows];
    this->Y       = new Positions[columns];
    this->rows    = new List[rows];
    this->columns = new List[columns];
   
    numRows = rows;
    numCols = columns;

    for (int i = 0; i < rows; i++)        {
        for (int j = 0; j < columns; j++) {
            Element buffer = intToString(i);
            buffer += Element(",");
            buffer += j;
            this->rows[i].insert(   buffer, j);
            this->columns[j].insert(buffer, i);
            this->X[i].insert(Position(i,j));
            this->Y[j].insert(Position(i,j));
        }
    } 
}
Matrix::Matrix(int rows, int columns, int z) : next(nullptr)
{
    this->X       = new Positions[rows];
    this->Y       = new Positions[columns];
    this->rows    = new List[rows];
    this->columns = new List[columns];

    this->position.setZ(z);
    numRows = rows;
    numCols = columns;

    for (int i = 0; i < rows; i++)        {
        for (int j = 0; j < columns; j++) {
            Element buffer = Element("(");
            buffer += i;
            buffer += Element(",");
            buffer += j;
            buffer += Element(")->");
            buffer += z;
            this->rows[i].insert(   buffer, j);
            this->columns[j].insert(buffer, i);
            this->X[i].insert(Position(i,j,z));
            this->Y[j].insert(Position(i,j,z));
        }
    } 
}
Matrix::Matrix(int rows, int columns, const Element & value) : next(nullptr)
{
    this->X       = new Positions[rows];
    this->Y       = new Positions[columns];
    this->rows    = new List[rows];
    this->columns = new List[columns];
   
    numRows = rows;
    numCols = columns;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            Element element = value;
            this->rows[i].insert(   element, j);
            this->columns[j].insert(element, i);
            this->X[i].insert(Position(i,j));
            this->Y[j].insert(Position(i,j));
        }
    }
}
Matrix::Matrix(int rows, int columns, int z, const Element & value) : next(nullptr)
{
    this->X       = new Positions[rows];
    this->Y       = new Positions[columns];
    this->rows    = new List[rows];
    this->columns = new List[columns];
   
    numRows = rows;
    numCols = columns;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            Element element = value;
            this->X[i].insert(Position(i,j,z));
            this->Y[j].insert(Position(i,j,z));
            this->rows[i].insert(element, j);
            this->columns[j].insert(element, i);
        }
    }
}

void Matrix::resize(int rows, int columns)
{
    if(rows == this->numRows && columns == this->numCols) { return; }

    if(rows != 0 && columns != 0) {
        if(this->rows == nullptr || this->columns == nullptr) {
            if(this->X       != nullptr) { delete [] this->X;       }
            if(this->Y       != nullptr) { delete [] this->Y;       }
            if(this->rows    != nullptr) { delete [] this->rows;    }
            if(this->columns != nullptr) { delete [] this->columns; }
            this->X       = new Positions[rows];
            this->Y       = new Positions[columns];
            this->rows    = new List[rows];
            this->columns = new List[columns];
            this->numRows = rows;
            this->numCols = columns;
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < columns; j++) {
                    this->X[i].insert(Position(i,j));
                    this->Y[j].insert(Position(i,j));
                    this->rows[i].insert(Element(), j);
                    this->columns[j].insert(Element(), i);
                }
            }
        }
        else{
            List * newRows    = new List[rows];
            List * newColumns = new List[columns];

            if(this->X != nullptr) { delete [] this->X; }
            if(this->Y != nullptr) { delete [] this->Y; }
            this->X       = new Positions[rows];
            this->Y       = new Positions[columns];

            for (int i = 0; i < rows; i++)        {
                for (int j = 0; j < columns; j++) {
                    Element valToCopy = this->getValue(i, j);
                    if (valToCopy.getData() == nullptr) {
                        Element buffer = intToString(i);
                        buffer += Element(",");
                        buffer += j;
                        newRows[i].insert(buffer, j);
                        newColumns[j].insert(buffer, i);
                        this->X[i].insert(Position(i,j));
                        this->Y[j].insert(Position(i,j));
                    
                    }
                    else{
                        newRows[i].insert(valToCopy, j);
                        newColumns[j].insert(valToCopy, i);
                        this->X[i].insert(Position(i,j));
                        this->Y[j].insert(Position(i,j));
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
            return Element();
        }
    }
    return Element(); // Return an empty Element if the indices are out of bounds || Element @ row != Element @ col
}
Element Matrix::getValue_i(int i, int j) const               // Get the value at a specific position (i, j) in the matrix
{
    if (i >= numRows && j >= numCols) { return getValue(this->getNumRows() - 1,this->getNumCols() - 1); }
    if (i <  0       && j <  0)       { return getValue(0,0); }
    if (i <  0) { return getValue(0,j); }
    if (j <  0) { return getValue(i,0); }
    if (i >= numRows) { return getValue(this->getNumRows() - 1,j); }
    if (j >= numCols) { return getValue(i,this->getNumCols() - 1); }
    
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
            return Element();
        }
    }
    return Element(); 
}

// Set the value at a specific position (i, j) in the matrix
void Matrix::setValue(int i, int j, const Element & element)
{
    if (i >= 0 && i < numRows && j >= 0 && j < numCols) {
        Element value = element;
        if (this->getValue(i, j).getData() != nullptr || this->getValue(i, j) != Element()) {
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
   
    int k = 0;
    int nodeSize = static_cast<int>(log10(abs(numRows))) + 1;
    for (int i = 0; i < numRows; i++) {         // Print the matrix with aligned columns
        if(0 == i){
            bool ff = false;
            for (int j = 0; j < numCols; j++) {
               
                int colS = static_cast<int>(log10(abs(k))) + 2;
                if(k == 0){ colS = 1;}

                if (j == 0){
                    std::cout << std::setw(maxColumnWidth[j] + nodeSize - 2) << "" <<  k++;
                }
                else if(maxColumnWidth[j] == colS && ff == false){
                    std::cout << std::setw(2) << "" << k++;
                    ff = true;
                }
                else if(maxColumnWidth[j] == colS){
                    std::cout << std::setw(1) << "" << k++;

                }
                else{
                    std::cout << std::setw((maxColumnWidth[j] - colS) + 1) << "" << k++;
                }
                if (j < numCols - 1) {
                    std::cout << ' ';
                }
            }
            std::cout << std::endl;
            //for (int j = 0; j < numCols; j++) {
            //    if (j == 0){
            //        std::cout << std::setw(maxColumnWidth[j] + nodeSize - 2)<< "_";
            //    }
            //    else{
            //        std::cout << std::setw(maxColumnWidth[j])<< "_";
            //    }

            //}
            //std::cout << std::endl;
        }
        std::cout << std::setw(nodeSize)<< i << ":";
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
void Matrix::printPositions() const
{
    int maxRowWidth = static_cast<int>(log10(numRows - 1)) + 1;
    int maxColWidth = static_cast<int>(log10(numCols - 1)) + 1;

    std::cout << "Row Positions (X):" << std::endl;
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            std::cout << "(" << std::setw(maxRowWidth) << X[i].getPos(Position(i,j)).getX() << "," << std::setw(maxColWidth) << X[i].getPos(Position(i,j)).getY() << ")";
        }
        std::cout << std::endl;
    }
    for (int i = 0; i < numRows; i++) {
        std::cout << this->X[i] << std::endl;
    }
    std::cout << "Column Positions (Y):" << std::endl;
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            std::cout << "(" << std::setw(maxRowWidth) << Y[j].getPos(Position(i,j)).getX() << "," << std::setw(maxColWidth) << Y[j].getPos(Position(i,j)).getY() << ")";
        }
        std::cout << std::endl;
    }
    for (int j = 0; j < numCols; j++) {
        std::cout << this->Y[j] << std::endl;
    }
}
void Matrix::printEachPosition() const
{
    std::cout << "Row Positions (X):" << std::endl;
    for (int i = 0; i < numRows; i++) {
        std::cout << "Row " << i << ": ";
        this->X[i].print(); 
        std::cout << std::endl;
    }

    std::cout << "Column Positions (Y):" << std::endl;
    for (int j = 0; j < numCols; j++) {
        std::cout << "Column " << j << ": ";
        this->Y[j].print(); 
        std::cout << std::endl;
    }
}
void Matrix::printRowPositions() const
{
    int maxRowWidth = static_cast<int>(log10(numRows - 1)) + 1;
    int maxColWidth = static_cast<int>(log10(numCols - 1)) + 1;

    std::cout << "Row Positions (X):" << std::endl;
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            std::cout << "(" << std::setw(maxRowWidth) << X[i].getPos(Position(i,j)).getX() << "," << std::setw(maxColWidth) << X[i].getPos(Position(i,j)).getY() << ")";
        }
        std::cout << std::endl;
    }
}
void Matrix::printColPositions() const
{
    int maxRowWidth = static_cast<int>(log10(numRows - 1)) + 1;
    int maxColWidth = static_cast<int>(log10(numCols - 1)) + 1;

    std::cout << "Column Positions (Y):" << std::endl;
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            std::cout << "(" << std::setw(maxRowWidth) << Y[j].getPos(Position(i,j)).getX() << "," << std::setw(maxColWidth) << Y[j].getPos(Position(i,j)).getY() << ")";
        }
        std::cout << std::endl;
    }
}
void Matrix::printRowPositionsRaw() const
{
    for (int i = 0; i < numRows; i++) {
        std::cout << this->X[i] << std::endl;
    }
}
void Matrix::printColPositionsRaw() const
{
    for (int j = 0; j < numCols; j++) {
        std::cout << this->Y[j] << std::endl;
    }
}
void Matrix::printPositionsCrawlLeft() const
{
    int maxRowWidth = static_cast<int>(log10(numRows - 1)) + 1;
    std::cout << "Row Positions Crawl Left (X):" << std::endl;
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            std::cout << std::setw(maxRowWidth + j - maxRowWidth + i - j) << " " << X[i].getPos(Position(i,j)).getX() << "," << X[i].getPos(Position(i,j)).getY() << "->";
        }
        std::cout << std::endl;
    }
    std::cout << "Column Positions Crawl Left (Y):" << std::endl;
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            std::cout << std::setw(maxRowWidth + j - maxRowWidth + i - j) << " " << Y[j].getPos(Position(i,j)).getX() << "," << Y[j].getPos(Position(i,j)).getY() << "->";
        }
        std::cout << std::endl;
    }
}
void Matrix::printPositionsCrawlRight() const
{
    int maxRowWidth = static_cast<int>(log10(numRows - 1)) + 1;
    std::cout << "Row Positions Crawl Right (X):" << std::endl;
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            std::cout << std::setw(maxRowWidth + i) << " " << X[i].getPos(Position(i,j)).getX() << "," << X[i].getPos(Position(i,j)).getY() << "->";
        }
        std::cout << std::endl;
    }
    std::cout << "Column Positions Crawl Right (Y):" << std::endl;
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            std::cout << std::setw(maxRowWidth + i) << " " << Y[j].getPos(Position(i,j)).getX() << "," << Y[j].getPos(Position(i,j)).getY() << "->";
        }
        std::cout << std::endl;
    }
}
void Matrix::printPositionsSlopeLeft() const
{
    int maxRowWidth = static_cast<int>(log10(numRows - 1)) + 1;
    std::cout << "Row Positions Crawl Left (X):" << std::endl;
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            std::cout << std::setw(maxRowWidth + j - maxRowWidth) << " " << X[i].getPos(Position(i,j)).getX() << "," << X[i].getPos(Position(i,j)).getY() << "->";
        }
        std::cout << std::endl;
    }
    std::cout << "Column Positions Crawl Left (Y):" << std::endl;
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            std::cout << std::setw(maxRowWidth + j - maxRowWidth) << " " << Y[j].getPos(Position(i,j)).getX() << "," << Y[j].getPos(Position(i,j)).getY() << "->";
        }
        std::cout << std::endl;
    }
}
void Matrix::printPositionsSlopeRight() const
{
    int maxRowWidth = static_cast<int>(log10(numRows - 1)) + 1;
    std::cout << "Row Positions Crawl Left (X):" << std::endl;
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            std::cout << std::setw(maxRowWidth + i - j) << " " << X[i].getPos(Position(i,j)).getX() << "," << X[i].getPos(Position(i,j)).getY() << "->";
        }
        std::cout << std::endl;
    }
    std::cout << "Column Positions Crawl Left (Y):" << std::endl;
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            std::cout << std::setw(maxRowWidth + i - j) << " " << Y[j].getPos(Position(i,j)).getX() << "," << Y[j].getPos(Position(i,j)).getY() << "->";
        }
        std::cout << std::endl;
    }
}


void Matrix::printRow(int row) const                    // Print a specific row
{
    if (row >= 0 && row < numRows) {
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
        for (int i = 0; i < numRows; i++) {
            std::cout << this->getValue(i, column) << std::endl;
        }
    }
}
void Matrix::prettyRow(int row) const                    // Print a specific row
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
void Matrix::prettyColumn(int column) const              // Print a specific column
{
    if (column >= 0 && column < numCols) {
        this->columns[column].getDeets();
        for (int i = 0; i < numRows; i++) {
            std::cout << this->getValue(i, column) << std::endl;
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
            //this->print();
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
            //this->print();
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
            //this->print();
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
            //this->print();
            i--;
        }
    }
}
