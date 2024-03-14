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




//void Position::TEST()
//{
//    // Create Position objects and demonstrate their usage
//    Position position1; // Default constructor
//    Position position2(8, 8); // Parameterized constructor
//
//    position1.display();
//    position2.display();
//
//    position1.move(4, 4);
//    position1.display();
//
//    double distance = position1.distanceTo(position2);
//    double distance2 = position2.distanceTo(position1);
//    std::cout << "Distance between position1 and position2: " << distance << std::endl;
//    std::cout << "Distance between position2 and position1: " << distance2 << std::endl;
//
//    Position sum = position1 + position2;
//    sum.display();
//
//    Position difference = position1 - position2;
//    difference.display();
//
//    if (position1 == position2) {
//        std::cout << "position1 and position2 are equal." << std::endl;
//    } else {
//        std::cout << "position1 and position2 are not equal." << std::endl;
//    }
//
//    std::cout << "Absolute difference between position1 and position2: ";
//    Position diff = position1.absoluteDifference(position2);
//    diff.display();
//}


// The Euclidean distance reflects the intuitive notion of distance that we learn in elementary geometry.
// It's the shortest path between two points in a plane, and it corresponds to what we perceive as the straight-line distance in physical space.

// The formula for Euclidean distance is derived from the Pythagorean theorem, which is a fundamental principle in geometry.
// This theorem states that in a right-angled triangle, the square of the length of the hypotenuse is equal to the sum of the squares of the other two sides.
// The Euclidean distance formula essentially applies this theorem to calculate distances in two-dimensional space.

// The Euclidean distance can be extended to higher dimensions (3D, 4D, etc.) and even to more abstract vector spaces.
// It serves as a basis for defining distances in various contexts, including physics, computer graphics, machine learning, and optimization.

// The Euclidean distance satisfies the properties of a metric space, which means it adheres to the three fundamental properties of a metric:
   //   Non-negativity: The distance between two points is always non-negative.
   //   Identity of indiscernibles: The distance between two points is zero if and only if the two points are the same.
   //   Triangle Inequality: The sum of the distances between three points is greater than or equal to the distance between any two of the three points
