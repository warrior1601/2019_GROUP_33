#include <iostream>
#include "Vectors.h"
using namespace std;


Vectors::Vectors()
{
    X_Coord = 0;
    Y_Coord = 0;
    Z_Coord = 0;
}

Vectors::~Vectors()
{
    //delete X_Coord;
    //delete Y_Coord;
    //delete Z_Coord;
}

float Vectors::GetXVector()
{
    return (this->X_Coord);
}

float Vectors::GetYVector()
{
    return (this->Y_Coord);
}

float Vectors::GetZVector()
{
    return (this->Z_Coord);
}

void Vectors::SetVector(float aX_Coord, float aY_Coord, float aZ_Coord)
{
    this->X_Coord = aX_Coord;
    this->Y_Coord = aY_Coord;
    this->Z_Coord = aZ_Coord;
}

void Vectors::SetX_Vector(float aX_Coord)
{
    this->X_Coord = aX_Coord;
}

void Vectors::SetY_Vector(float aY_Coord)
{
    this->Y_Coord = aY_Coord;
}

void Vectors::SetZ_Vector(float aZ_Coord)
{
    this->Z_Coord = aZ_Coord;
}

Vectors Vectors::operator=(const Vectors& Copy)
{
    this->X_Coord = Copy.X_Coord;
    this->Y_Coord = Copy.Y_Coord;
    this->Z_Coord = Copy.Z_Coord;

    return (*this);
}

Vectors Vectors::operator+(const Vectors& add)
{
    Vectors added;

    added.X_Coord = this->X_Coord + add.X_Coord;
    added.Y_Coord = this->Y_Coord + add.Y_Coord;
    added.Z_Coord = this->Z_Coord + add.Z_Coord;

    return added;
}

Vectors Vectors::operator-(const Vectors& subtract)
{
    Vectors subtracted;

    subtracted.X_Coord = this->X_Coord - subtract.X_Coord;
    subtracted.Y_Coord = this->Y_Coord - subtract.Y_Coord;
    subtracted.Z_Coord = this->Z_Coord - subtract.Z_Coord;

    return subtracted;
}

float Vectors::Scalar_Product(const Vectors& aVectors)
{
    float Scalar;

    Scalar =   this->X_Coord * aVectors.X_Coord
             + this->Y_Coord * aVectors.Y_Coord
             + this->Z_Coord * aVectors.Z_Coord;

    return Scalar;
}

Vectors Vectors::Vector_Product(const Vectors& aVectors)
{
    Vectors Vector_Prduct;

    Vector_Prduct.X_Coord = (this->Y_Coord * aVectors.Z_Coord) - (this->Z_Coord * aVectors.Y_Coord);
    Vector_Prduct.Y_Coord = (this->Z_Coord * aVectors.X_Coord) - (this->X_Coord * aVectors.Z_Coord);
    Vector_Prduct.Z_Coord = (this->X_Coord * aVectors.Y_Coord) - (this->Y_Coord * aVectors.X_Coord);

    return Vector_Prduct;
}

std::ostream& operator<< (std::ostream&, Vectors& aVectors)
{
    std::cout << "X = "<<aVectors.GetXVector();
    std::cout << " Y = "<<aVectors.GetYVector();
    std::cout << " Z = "<<aVectors.GetZVector();

    return std::cout;
}

Vectors Vectors::Vector_Divide_By_Number(float My_Number)
{
    Vectors Divided;

    Divided.X_Coord = this->X_Coord / My_Number;
    Divided.Y_Coord = this->Y_Coord / My_Number;
    Divided.Z_Coord = this->Z_Coord / My_Number;

    return Divided;
}
