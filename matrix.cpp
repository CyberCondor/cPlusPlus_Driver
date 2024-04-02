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
Matrix::Matrix() : next(nullptr), name("NULL")
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
    this->setName(other->getName());
    
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
    this->setName(other.getName());
    
    numRows = other.getNumRows();
    numCols = other.getNumCols();
    this->X       = new Positions[numRows];
    this->Y       = new Positions[numCols];
    this->rows    = new List[numRows];
    this->columns = new List[numCols];

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


Matrix::Matrix(const char* filePath) : Matrix()
{
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        std::cerr << "Error opening file: " << filePath << std::endl;
    }

    this->setName(Element(filePath)); 
    
    const int bufferSize = 4095;  // Assuming a max line length
    char buffer[bufferSize + 1];
   
    int rowNumbers = 0;
    int colNumbers = 1;

    while (file.getline(buffer, bufferSize))
    {
        if(rowNumbers == 1)
        { 
            for (int i = 0; i < bufferSize && buffer[i] != '\0'; i++)
            {
                if (buffer[i] == ',' && buffer[i - 1] == '"' && buffer[i + 1] == '"')
                {
                    colNumbers++;
                }
            }
        }
        rowNumbers++;
    }

    file.clear();                 // Clear any end-of-file flags
    file.seekg(0, std::ios::beg); // Move the file pointer back to the beginning


    this->resize(rowNumbers,colNumbers);

    char* value = new char[bufferSize + 1]; // Allocate buffer
    int valueIndex = 0; // Index for current position in 'value'
    int currentRow = 0; // Current row index
    int currentColumn = 0; // Current column index

    bool new_Element = false;
    char c;
    while (file.get(c))
    { // Read one character at a time
        if ((new_Element == true && c == ',') || c == '\n' || file.eof()) { // Check for end of file here as well
            value[valueIndex] = '\0'; // Null-terminate the current value

            if (valueIndex > 0) { // Only add non-empty values
                Element newElement(value); // Create new Element with parsed value
                this->setValue(currentRow, currentColumn, newElement); // Set value in matrix
            }

            valueIndex = 0; // Reset index for next value
            value[0] = '\0'; // Reset buffer for next value
            currentColumn++; // Move to next column

            if (c == '\n')
            { // If end of line, process next row
                currentRow++; // Move to next row
                currentColumn = 0; // Reset column index for new row
            }
            new_Element = false;
        }
        else if (valueIndex < bufferSize && c != '"') {
            value[valueIndex++] = c; // Store character and move to next position
            new_Element = false;
        }
        else{new_Element = true;}
    }

    // No need for a separate EOF check after the loop because it's handled within the loop

    delete[] value; // Clean up dynamically allocated array

    file.close();
}


bool Matrix::importCsv(const char* filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        std::cerr << "Error opening file: " << filePath << std::endl;
        return false;
    }
    
    this->setName(Element(filePath)); 
    
    const int bufferSize = 4095;  // Assuming a max line length
    char buffer[bufferSize + 1];
   
    int rowNumbers = 0;
    int colNumbers = 1;

    while (file.getline(buffer, bufferSize))
    {
        if(rowNumbers == 1)
        { 
            for (int i = 0; i < bufferSize && buffer[i] != '\0'; i++)
            {
                if (buffer[i] == ',' && buffer[i - 1] == '"' && buffer[i + 1] == '"')
                {
                    colNumbers++;
                }
            }
        }
        rowNumbers++;
    }

    file.clear();                 // Clear any end-of-file flags
    file.seekg(0, std::ios::beg); // Move the file pointer back to the beginning


    this->resize(rowNumbers,colNumbers);

    char* value = new char[bufferSize + 1]; // Allocate buffer
    int valueIndex = 0; // Index for current position in 'value'
    int currentRow = 0; // Current row index
    int currentColumn = 0; // Current column index

    bool new_Element = false;
    char c;
    while (file.get(c))
    { // Read one character at a time
        if ((new_Element == true && c == ',') || c == '\n' || file.eof()) { // Check for end of file here as well
            value[valueIndex] = '\0'; // Null-terminate the current value

            if (valueIndex > 0) { // Only add non-empty values
                Element newElement(value); // Create new Element with parsed value
                this->setValue(currentRow, currentColumn, newElement); // Set value in matrix
            }

            valueIndex = 0; // Reset index for next value
            value[0] = '\0'; // Reset buffer for next value
            currentColumn++; // Move to next column

            if (c == '\n')
            { // If end of line, process next row
                currentRow++; // Move to next row
                currentColumn = 0; // Reset column index for new row
            }
            new_Element = false;
        }
        else if (valueIndex < bufferSize && c != '"') {
            value[valueIndex++] = c; // Store character and move to next position
            new_Element = false;
        }
        else{new_Element = true;}
    }

    // No need for a separate EOF check after the loop because it's handled within the loop

    delete[] value; // Clean up dynamically allocated array

    file.close();

    return true;
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



Positions Matrix::getPositions(const Element & element) const
{
    Positions positions;
    Position position;
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
        
            if(this->getValue(i, j) == element) {
                position.setX(i);
                position.setY(j);
                positions.insert(position);
            }
        }
    }
    return positions;
}



Matrix Matrix::getMatrixWhereElementIs(const Element & element) const 
{
    if(this->numRows == 0 && this->numCols == 0) { return Matrix(); }
    if(this->rows == nullptr || this->columns == nullptr) {return Matrix();}
    Positions positions;
    for (int i = 0; i < this->numRows; i++) {
        if(this->rows[i].findMatch(element) || i == 0){
            positions.insert(Position(i,0));
        }
    }
    int positionsSize = positions.size();
    Matrix matrix(positionsSize, this->getNumCols());
    for(int i = 0; i <= positionsSize; i++) {
        Position position(positions.getPos(i).getX(), positions.getPos(i).getY()); 
        for(int j = 0; j < this->getNumCols(); j++) {
            matrix.setValue(i, j, this->getValue(position.getX(),j));
        }
    }
    matrix.setName(this->getName());
    return matrix;
}
Matrix Matrix::getMatrixWhereElementIs_i(const Element & element) const
{
    if(this->numRows == 0 && this->numCols == 0) { return Matrix(); }
    if(this->rows == nullptr || this->columns == nullptr) {return Matrix();}
    Positions positions;
    for (int i = 0; i < this->numRows; i++) {
        if(this->rows[i].findMatch_i(element) || i == 0){
            positions.insert(Position(i,0));
        }
    }
    int positionsSize = positions.size();
    Matrix matrix(positionsSize, this->getNumCols());
    for(int i = 0; i <= positionsSize; i++) {
        Position position(positions.getPos(i).getX(), positions.getPos(i).getY()); 
        for(int j = 0; j < this->getNumCols(); j++) {
            matrix.setValue(i, j, this->getValue(position.getX(),j));
        }
    }
    matrix.setName(this->getName());
    return matrix;
}

Matrix Matrix::getMatrixWhereElementLike(const Element & element) const
{
    if(this->numRows == 0 && this->numCols == 0) { return Matrix(); }
    if(this->rows == nullptr || this->columns == nullptr) {return Matrix();}
    Positions positions;
    for (int i = 0; i < this->numRows; i++) {
        if(this->rows[i].wildcardSearch(element) || i == 0){
            positions.insert(Position(i,0));
        }
    }
    int positionsSize = positions.size();
    Matrix matrix(positionsSize, this->getNumCols());
    for(int i = 0; i <= positionsSize; i++) {
        Position position(positions.getPos(i).getX(), positions.getPos(i).getY()); 
        for(int j = 0; j < this->getNumCols(); j++) {
            matrix.setValue(i, j, this->getValue(position.getX(),j));
        }
    }
    matrix.setName(this->getName());
    return matrix;
}

Matrix Matrix::getMatrixWhereElementLike_i(const Element & element) const
{
    if(this->numRows == 0 && this->numCols == 0) { return Matrix(); }
    if(this->rows == nullptr || this->columns == nullptr) {return Matrix();}
    Positions positions;
    for (int i = 0; i < this->numRows; i++) {
        if(this->rows[i].wildcardSearch_i(element) || i == 0){
            positions.insert(Position(i,0));
        }
    }
    int positionsSize = positions.size();
    Matrix matrix(positionsSize, this->getNumCols());
    for(int i = 0; i <= positionsSize; i++) {
        Position position(positions.getPos(i).getX(), positions.getPos(i).getY()); 
        for(int j = 0; j < this->getNumCols(); j++) {
            matrix.setValue(i, j, this->getValue(position.getX(),j));
        }
    }
    matrix.setName(this->getName());
    return matrix;
}

Matrix Matrix::getMatrixWhereElementContains(const Element & element) const
{
    if(this->numRows == 0 && this->numCols == 0) { return Matrix(); }
    if(this->rows == nullptr || this->columns == nullptr) {return Matrix();}
    Positions positions;
    for (int i = 0; i < this->numRows; i++) {
        if(this->rows[i].containsSequence(element) || i == 0){
            positions.insert(Position(i,0));
        }
    }
    int positionsSize = positions.size();
    Matrix matrix(positionsSize, this->getNumCols());
    for(int i = 0; i <= positionsSize; i++) {
        Position position(positions.getPos(i).getX(), positions.getPos(i).getY()); 
        for(int j = 0; j < this->getNumCols(); j++) {
            matrix.setValue(i, j, this->getValue(position.getX(),j));
        }
    }
    matrix.setName(this->getName());
    return matrix;
}

Matrix Matrix::getMatrixWhereElementContains_i(const Element & element) const
{
    if(this->numRows == 0 && this->numCols == 0) { return Matrix(); }
    if(this->rows == nullptr || this->columns == nullptr) {return Matrix();}
    Positions positions;
    for (int i = 0; i < this->numRows; i++) {
        if(this->rows[i].containsSequence_i(element) || i == 0){
            positions.insert(Position(i,0));
        }
    }
    int positionsSize = positions.size();
    Matrix matrix(positionsSize, this->getNumCols());
    for(int i = 0; i <= positionsSize; i++) {
        Position position(positions.getPos(i).getX(), positions.getPos(i).getY()); 
        for(int j = 0; j < this->getNumCols(); j++) {
            matrix.setValue(i, j, this->getValue(position.getX(),j));
        }
    }
    matrix.setName(this->getName());
    return matrix;
}

Matrix Matrix::getMatrixWhereElementInPositions(Positions positions) const
{
    int positionsSize = positions.size();
    Matrix matrix(positionsSize, this->getNumCols());
    for(int i = 0; i <= positionsSize; i++) {
        Position position(positions.getPos(i).getX(), positions.getPos(i).getY()); 
        matrix.setValue(i, position.getY(), this->getValue(position.getX(),position.getY()));
    }
    //matrix.print();
    matrix.setName(this->getName());
    return matrix;
}

Matrix Matrix::getPropertyFrequencies() const
{
    if(this->numRows == 0 && this->numCols == 0) { return Matrix(); }
    if(this->rows == nullptr || this->columns == nullptr) {return Matrix();}
    Matrix propertyFrequencies;

    propertyFrequencies.resize(this->numRows, this->numCols * 3);

    for(int pos = 0; pos < this->numCols; pos++) {

            Element propertyName(this->rows[0].getDataAtPosition(pos));

            propertyFrequencies.setValue(0, (pos * 3)    , Element(propertyName));
            propertyFrequencies.setValue(0, (pos * 3) + 1, Element("Count"));
            propertyFrequencies.setValue(0, (pos * 3) + 2, Element("Frequency"));

            for(int i = 1; i < this->numRows; i++) {
                int count = 1;
                int frequency = 0;
                float countBuff1 = 0;
                float countBuff = 0;
                Element value(this->columns[pos].getDataAtPosition(i));
                Positions positions2(this->columns[pos].findMatch_i_p(value));
               
                if(this->numRows == positions2.size()) { // all values == propertyKey
                    count = positions2.size() - 1;
                    frequency = 100; 
                }
                else if(this->columns[pos].getDataAtPosition(0) == value) { // propertyKey == value
                    count = positions2.size() - 1;
                    countBuff1 = this->numRows - 1;
                    countBuff = (count / countBuff1) * 100; 
                    frequency = countBuff; 
                }
                else{
                    count = positions2.size();
                    countBuff1 = this->numRows - 1;
                    countBuff = (count / countBuff1) * 100; 
                    frequency = countBuff; 
                }
                Element count2(intToString(count));
                Element frequency2(intToString(frequency));
                frequency2 += Element("%");


                //if(propertyFrequencies.getColumns()[pos * 3].findMatch_i(value) != true || (propertyFrequencies.getColumns()[pos * 3].findMatch_i_p(value).getPos(0).getX() == 0 && propertyFrequencies.getColumns()[pos * 3].findMatch_i_p(value).size() > 1) ){
                if(propertyFrequencies.getColumns()[pos * 3].findMatch_i(value) != true || (propertyName == value && propertyFrequencies.getColumns()[pos * 3].findMatch_i_p(value).size() < 2) ){
                    propertyFrequencies.setValue(i, (pos * 3), value);
                    propertyFrequencies.setValue(i, (pos * 3) + 1, count2);
                    propertyFrequencies.setValue(i, (pos * 3) + 2, frequency2);
                }
            }
    }
   // Positions positionsToRemove;

   // for(int pos = 0; pos < this->numCols; pos++) {
   //     //Element propertyName(this->rows[0].getDataAtPosition(pos));
   //     for(int i = 1; i < this->numRows; i++) {
   //       Element value(this->columns[pos].getDataAtPosition(i));
   //         if(propertyFrequencies.getRows()[i].findMatch_i(value) != true){
   //             positionsToRemove.insert(Position(i, (pos * 3)));
   //         }
   //     } 
   // }
   //     positionsToRemove.print();

   // if(propertyFrequencies.getNumCols() > 3) {
   //     Positions positionsToRemove2;
   //     int count = 0;
   //     for(int i = 0; i < positionsToRemove.size(); i++){
   //         if(positionsToRemove.getPos(i).getX() ==  positionsToRemove.getPos(i + 1).getX()) {
   //             count++;
   //         }
   //         else{count = 0;}
   //         if(count == propertyFrequencies.getNumRows() - 1) {
   //             positionsToRemove2.insert(Position(positionsToRemove.getPos(i).getX(),0));
   //         }
   //     }
   //     for(int i = 0; i < positionsToRemove2.size();i++) {
   //         propertyFrequencies.removeRow(positionsToRemove2.getPos(i).getX() - i);
   //     }

   //     positionsToRemove2.print();

   // }
   // else{
   //     for(int i = 0; i < positionsToRemove.size();i++) {
   //         propertyFrequencies.removeRow(positionsToRemove.getPos(i).getX() - i);
   //     }
   // }

    propertyFrequencies.removeEmptyRows();
    propertyFrequencies.consolidateEmptyPositions();
    propertyFrequencies.removeEmptyRows();

    propertyFrequencies.setName(this->getName());
    return propertyFrequencies;
}





Matrix Matrix::getPropertyFrequencies(const Element & propertyKey) const
{
    if(this->numRows == 0 && this->numCols == 0) { return Matrix(); }
    if(this->rows == nullptr || this->columns == nullptr) {return Matrix();}
    Matrix propertyFrequencies;
    Position  position;
    Positions positions;

    if(this->rows[0].findMatch_i(propertyKey)) {
        positions = this->rows[0].findMatch_i_p(propertyKey); // Calls Move Assignment Operator Not Copy Assignment 

    }
    else{return Matrix();} // Property Key Not Found in Matrix

    int posSize = positions.size();
    propertyFrequencies.resize(this->numRows, posSize * 3);

    for(int pos = 0; pos < posSize; pos++) {
        
        position.setX(positions.getPos(pos).getX());

        if(position.getX() <= this->numCols) {
            Element propertyName(this->rows[0].findMatch_i_z(propertyKey).getDataAtPosition(pos));
            
            propertyFrequencies.setValue(0, (pos * 3)    , Element(propertyName));
            propertyFrequencies.setValue(0, (pos * 3) + 1, Element("Count"));
            propertyFrequencies.setValue(0, (pos * 3) + 2, Element("Frequency"));

            for(int i = 1; i < this->numRows; i++) {
                int count = 1;
                int frequency = 0;
                float countBuff1 = 0;
                float countBuff = 0;
                Element value(this->columns[position.getX()].getDataAtPosition(i));
                Positions positions2(this->columns[position.getX()].findMatch_i_p(value));
               
                if(this->numRows == positions2.size()) { // all values == propertyKey
                    count = positions2.size() - 1;
                    frequency = 100; 
                }
                else if(this->columns[position.getX()].getDataAtPosition(0) == value) { // propertyKey == value
                    count = positions2.size() - 1;
                    countBuff1 = this->numRows - 1;
                    countBuff = (count / countBuff1) * 100; 
                    frequency = countBuff; 
                }
                else{
                    count = positions2.size();
                    countBuff1 = this->numRows - 1;
                    countBuff = (count / countBuff1) * 100; 
                    frequency = countBuff; 
                }
                Element count2(intToString(count));
                Element frequency2(intToString(frequency));
                frequency2 += Element("%");
                //if(propertyFrequencies.getColumns()[pos * 3].findMatch_i(value) != true){
                if(propertyFrequencies.getColumns()[pos * 3].findMatch_i(value) != true || (propertyName == value && propertyFrequencies.getColumns()[pos * 3].findMatch_i_p(value).size() < 2) ){
                    propertyFrequencies.setValue(i, (pos * 3), value);
                    propertyFrequencies.setValue(i, (pos * 3) + 1, count2);
                    propertyFrequencies.setValue(i, (pos * 3) + 2, frequency2);
                }
            }
        }
    }
    
    propertyFrequencies.removeEmptyRows();
    propertyFrequencies.consolidateEmptyPositions();
    propertyFrequencies.removeEmptyRows();

    propertyFrequencies.setName(this->getName());
    return propertyFrequencies;
}

void Matrix::consolidateEmptyPositions()
{
    if(this->numRows == 0 && this->numCols == 0) { return; }
    if(this->rows == nullptr || this->columns == nullptr) {return;}
    
    Positions positions;
    
     for(int i = 0; i < this->numRows; i++) {
        Positions positions2(this->rows[i].findMatch_i_p(Element()));

        for(int j = 0; j < positions2.size(); j++) {
            positions.insert(Position(i, positions2.getPos(j).getX()));

        }
    }

    for(int i = 0; i < positions.size(); i++) {

        for(int j = 0; j < this->numCols; j++) {
            
            if(positions.getPos(i).getY() == j) {

                for(int k = positions.getPos(i).getX(); k < this->numRows; k++) {
                    
                        this->setValue(k, j, this->getValue(k + 1, j)); 
                }
            }
        }
    }
}

int Matrix::removeEmptyRows()
{
    int removed = 0;
    if(this->numRows == 0 && this->numCols == 0) { return removed; }
    if(this->rows == nullptr || this->columns == nullptr) {return removed;}
    
     for(int i = 0; i < this->numRows; i++) {
        if(this->rows[i].findMatch_i_p(Element()).size() == this->getNumCols()){
            this->removeRow(i);
            i--;
            removed++;
        }
    } 
    return removed;
}

bool Matrix::removeRow(int row)
{
    bool foundRow = false;
    if (row >= 0 && row < numRows) {
        for(int i = 0; i < numRows; i++) {
            if(i >= row) {
                if(i == numRows - 1) {
                     for(int j = 0; j < numCols; j++) {
                         //std::cout << this->rows[i].getDataAtPosition(j) << " I,J " << i << "," << j << std::endl;
                        this->setValue(i,j,this->getValue(i,j));
                     }
                }
                else{
                     for(int j = 0; j < numCols; j++) {
                         //std::cout << this->rows[i].getDataAtPosition(j) << " I,J " << i << "," << j << std::endl;
                        this->setValue(i,j,this->getValue(i + 1,j));
                     }
                }
                foundRow = true;
            }
        }
        this->resize(this->getNumRows() - 1, this->getNumCols());
    }
    return foundRow;
}
bool Matrix::removeColumn(int column)
{
    bool foundColumn = false;
    if (column >= 0 && column < numCols) {
        for(int j = 0; j < numCols; j++) {
            if(j >= column) {
                if(j == numCols - 1) {
                     for(int i = 0; i < numRows; i++) {
                        this->setValue(i,j,this->getValue(i,j));
                     }
                }
                else{
                     for(int i = 0; i < numRows; i++) {
                        this->setValue(i,j,this->getValue(i,j + 1));
                     }
                }
                foundColumn = true;
            }
        }
    }

    this->resize(this->getNumRows(), this->getNumCols() - 1);

    return foundColumn;
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

Matrix & Matrix::operator=(const Matrix &other)  
{
    //std::cout << "copy assignment called" << std::endl;
    if (this != &other) {
        
        this->resize(other.getNumRows(), other.getNumCols());
        this->setPosition(other.getPosition());

        this->setName(other.getName());
        
        for (int i = 0; i < numRows; i++) {
            this->rows[i].clear();
        }

        for (int j = 0; j < numCols; j++) {
            this->columns[j].clear();
        }

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
    return *this;
}

bool Matrix::operator==(const Matrix &other) const  
{
    if (this == &other)                    // Check if it's the same object
        return true;

    if(this->numRows == 0 && this->numCols == 0 && other.getNumRows() == 0 && other.getNumCols() == 0) { return true; }
    if((this->rows == nullptr || this->columns == nullptr) && (other.getRows() == nullptr || other.getColumns() == nullptr)) {return true;}

    if(this->numRows == other.getNumRows() && this->numCols == other.getNumCols()) {

        for(int i = 0; i <  this->numRows; i++) {
            if(this->rows[i] != other.getRows()[i]) {
                return false;
            }
        }
    }
    else{
        return false;
    }

    return true;                           // Strings are equal if both strings complete a full loop
}

bool Matrix::operator!=(const Matrix &other) const  
{
    return !(*this == other); 
}
