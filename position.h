#pragma once
#include <iostream>

class Position {
private:
    int x;
    int y;
    int z;
    Position * next;
public:
    inline Position() : x(0), y(0), z(0) {};                          // Default constructor

    inline Position(int xVal, int yVal)           : x(xVal), y(yVal), z(0)    {};  // Parameterized constructor
    inline Position(int xVal, int yVal, int zVal) : x(xVal), y(yVal), z(zVal) {};  // Parameterized constructor

    inline int  getX() const   {return x;};                     // Getter for x coordinate
    inline int  getY() const   {return y;};                     // Getter for y coordinate
    inline int  getZ() const   {return z;};                     // Getter for y coordinate
     
    inline void setX(int xVal) {x = xVal;};                     // Setter for x coordinate
    inline void setY(int yVal) {y = yVal;};                     // Setter for y coordinate
    inline void setZ(int zVal) {z = zVal;};                     // Setter for y coordinate
     
    inline void move(int xOffset, int yOffset)              { x += xOffset;  // Move the position by given offsets in x and y
                                                              y += yOffset;};
    
    inline void move(int xOffset, int yOffset, int zOffset) { x += xOffset;  // Move the position by given offsets in x, y, and z
                                                              y += yOffset;
                                                              z += zOffset;}; 
     
    inline double distanceTo(const Position& other) const {  int dx = x - other.x; // Calculate the Euclidean distance between two positions
                                                             int dy = y - other.y;
                                                             int dz = z - other.z;   
                                                             return std::sqrt(static_cast<double>(dx * dx + dy * dy + dz * dz));};
     
    inline Position absoluteDifference(const Position& other) const {                                   // Calculate the absolute difference in x and y coordinates
         return Position(std::abs(x - other.x), std::abs(y - other.y), std::abs(z - other.z));};

    inline Position operator+(const Position& other) const {return Position(x + other.x, y + other.y, z + other.z);}; // Overloaded + operator for adding two positions
    inline Position operator-(const Position& other) const {return Position(x - other.x, y - other.y, z - other.z);}; // Overloaded - operator for subtracting two positions

    inline bool operator==(const Position& other) const {return x == other.x && y == other.y && z == other.z; };          // Overloaded == operator for checking equality of positions
    inline bool operator!=(const Position& other) const {return !(*this == other);};                     // Overloaded != operator for checking inequality of positions
     
    inline void display() const {std::cout << "(" << x << "," << y << ")->" << z;};                            // Display the position
    inline void print(  ) const {std::cout << "(" << x << "," << y << ")->" << z << std::endl;};               // Display the position

    inline const Position * getNext()      const{return next;};
    inline       Position * getNext()           {return next;};
    inline       Position * setNext(Position * direction)   // Setter for the next Position in the linked list
                    {this->next = direction;return this;};
    
    inline friend std::ostream & operator<<(std::ostream &out, const Position &position) {
        out <<"(" << position.getX() << "," << position.getY() << ")->" << position.getZ();
        return out;
    }; 
};
