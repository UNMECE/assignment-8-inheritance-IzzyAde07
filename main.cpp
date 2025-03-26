#include <iostream>
#include <cmath>

// Constants
const double epsilon_0 = 8.854187817e-12; // Permittivity of free space 
const double mu_0 = 4 * M_PI * 1e-7;      // Permeability of free space 

// Base class Field
class Field {
private:
    double *value; // Array to store components (x, y, z)

public:
    // Default constructor
    Field() {
        value = new double[3];
        value[0] = 0.0; // x-component
        value[1] = 0.0; // y-component
        value[2] = 0.0; // z-component
    }

    // Parameterized constructor
    Field(double x, double y, double z) {
        value = new double[3];
        value[0] = x;
        value[1] = y;
        value[2] = z;
    }

    // Destructor
    virtual ~Field() {
        delete[] value;
    }

    // Public getters
    double getX() const { return value[0]; }
    double getY() const { return value[1]; }
    double getZ() const { return value[2]; }

    // Public setters
    void setX(double x) { value[0] = x; }
    void setY(double y) { value[1] = y; }
    void setZ(double z) { value[2] = z; }

    // Print magnitude (components)
    void printMagnitude() const {
        std::cout << "Components: (" << value[0] << ", " << value[1] << ", " << value[2] << ")" << std::endl;
    }
};

// Derived class Electric_Field
class Electric_Field : public Field {
private:
    double calculatedE; // Stores calculated electric field magnitude

public:
    // Constructors
    Electric_Field() : Field() {}
    Electric_Field(double x, double y, double z) : Field(x, y, z) {}

    // Copy constructor
    Electric_Field(const Electric_Field &other) : 
        Field(other.getX(), other.getY(), other.getZ()) {}

    // Calculate electric field
    void calculateElectricField(double Q, double r) {
        calculatedE = Q / (4 * M_PI * r * r * epsilon_0);
    }

    // Getter for calculatedE
    double getCalculatedE() const { return calculatedE; }

    // Overload + operator
    Electric_Field operator+(const Electric_Field &other) const {
        return Electric_Field(
            getX() + other.getX(),
            getY() + other.getY(),
            getZ() + other.getZ()
        );
    }

    // Overload << operator
    friend std::ostream& operator<<(std::ostream &os, const Electric_Field &e) {
        os << "Electric Field Components: (" << e.getX() << ", " << e.getY() << ", " << e.getZ() << ")";
        return os;
    }
};

// Derived class Magnetic_Field
class Magnetic_Field : public Field {
private:
    double calculatedB; // Stores calculated magnetic field magnitude

public:
    // Constructors
    Magnetic_Field() : Field() {}
    Magnetic_Field(double x, double y, double z) : Field(x, y, z) {}

    // Copy constructor
    Magnetic_Field(const Magnetic_Field &other) : 
        Field(other.getX(), other.getY(), other.getZ()) {}

    // Calculate magnetic field using Ampere's Law for a current-carrying wire
    void calculateMagneticField(double I, double r) {
        calculatedB = (mu_0 * I) / (2 * M_PI * r);
    }

    // Getter for calculatedB
    double getCalculatedB() const { return calculatedB; }

    // Overload + operator
    Magnetic_Field operator+(const Magnetic_Field &other) const {
        return Magnetic_Field(
            getX() + other.getX(),
            getY() + other.getY(),
            getZ() + other.getZ()
        );
    }

    // Overload << operator
    friend std::ostream& operator<<(std::ostream &os, const Magnetic_Field &b) {
        os << "Magnetic Field Components: (" << b.getX() << ", " << b.getY() << ", " << b.getZ() << ")";
        return os;
    }
};

int main() {
    // Create Electric_Field objects
    Electric_Field e1(1.0, 2.0, 3.0);
    Electric_Field e2(4.0, 5.0, 6.0);

    // Print components
    std::cout << "Electric Field e1: ";
    e1.printMagnitude();
    std::cout << "Electric Field e2: ";
    e2.printMagnitude();

    // Calculate electric field 
    double Q = 1e-9; 
    double r = 0.1;   
    e1.calculateElectricField(Q, r);
    std::cout << "Calculated Electric Field: " << e1.getCalculatedE() << " N/C" << std::endl;

    //+ operator
    Electric_Field e3 = e1 + e2;
    std::cout << "e3 = e1 + e2: " << e3 << std::endl;

    // Create Magnetic_Field objects
    Magnetic_Field b1(7.0, 8.0, 9.0);
    Magnetic_Field b2(10.0, 11.0, 12.0);

    // Print components
    std::cout << "Magnetic Field b1: ";
    b1.printMagnitude();
    std::cout << "Magnetic Field b2: ";
    b2.printMagnitude();

    // Calculate magnetic field 
    double I = 1.0; 
    r = 0.1;        
    b1.calculateMagneticField(I, r);
    std::cout << "Calculated Magnetic Field: " << b1.getCalculatedB() << " T" << std::endl;

    //+ operator
    Magnetic_Field b3 = b1 + b2;
    std::cout << "b3 = b1 + b2: " << b3 << std::endl;

    return 0;
}