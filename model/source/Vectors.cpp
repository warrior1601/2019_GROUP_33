//  Vectors.cpp
//  Computing Project
//  Created by Jedidiah Paterson on 27/11/2019.
//  This file contains the definitions of the member functions for the Vectors class

#include <cmath>
#include <iostream>
#include "Vectors.h"
#include "double_equality_function.h"

//-------------Constructors and Destructor------------//
Vectors::Vectors()
{
    X_Coord = 0.0;
    Y_Coord = 0.0;
    Z_Coord = 0.0;
}

Vectors::Vectors(double aX_Coord)
{
    X_Coord = aX_Coord;
    Y_Coord = 0.0;
    Z_Coord = 0.0;
}
Vectors::Vectors(double aX_Coord, double aY_Coord)
{
    X_Coord = aX_Coord;
    Y_Coord = aY_Coord;
    Z_Coord = 0.0;
}
Vectors::Vectors(double aX_Coord, double aY_Coord, double aZ_Coord)
{
    X_Coord = aX_Coord;
    Y_Coord = aY_Coord;
    Z_Coord = aZ_Coord;
}

Vectors::~Vectors() {}

//-------------Set Functions-----------//
void Vectors::SetX_Vector(double aX_Coord)
{
    X_Coord = aX_Coord;
}

void Vectors::SetY_Vector(double aY_Coord)
{
    Y_Coord = aY_Coord;
}

void Vectors::SetZ_Vector(double aZ_Coord)
{
    Z_Coord = aZ_Coord;
}

void Vectors::SetVector(double aX_Coord, double aY_Coord, double aZ_Coord)
{
    X_Coord = aX_Coord;
    Y_Coord = aY_Coord;
    Z_Coord = aZ_Coord;
}

//-------------Get Functions-----------//
double Vectors::GetXVector()
{
    return (X_Coord);
}

double Vectors::GetYVector()
{
    return (Y_Coord);
}

double Vectors::GetZVector()
{
    return (Z_Coord);
}

//-----Operator Overload Functions-----//
Vectors Vectors::operator=(const Vectors& Copy)
{
    if (&Copy == this)
        return *this;

    else
    {
        X_Coord = Copy.X_Coord;
        Y_Coord = Copy.Y_Coord;
        Z_Coord = Copy.Z_Coord;

        return *this;
    }
}

Vectors Vectors::operator+(const Vectors& add)
{
    Vectors Added;
    Added.X_Coord = X_Coord + add.X_Coord;
    Added.Y_Coord = Y_Coord + add.Y_Coord;
    Added.Z_Coord = Z_Coord + add.Z_Coord;

    return Added;
}

Vectors Vectors::operator-(const Vectors& subtract)
{
    Vectors Subtraced;
    Subtraced.X_Coord = X_Coord - subtract.X_Coord;
    Subtraced.Y_Coord = Y_Coord - subtract.Y_Coord;
    Subtraced.Z_Coord = Z_Coord - subtract.Z_Coord;

    return Subtraced;
}

Vectors Vectors::operator/(const double& Divide)
{
    Vectors Divided;

    if ( Divide != 0 )
    {
      Divided.X_Coord = X_Coord / Divide;
      Divided.Y_Coord = Y_Coord / Divide;
      Divided.Z_Coord = Z_Coord / Divide;
      return Divided;
    }

    else
    {
    std::cout << "Dividing a Vectors by 0 has occured.\n"
              << "This is not a valid operation.\n"
              << "The origanl Vectors will be returned."<< std::endl;
    return (*this);
    }
}

Vectors Vectors::operator*(const double& Multiply_By)
{
    Vectors Multiplied;
    Multiplied.X_Coord = X_Coord * Multiply_By;
    Multiplied.Y_Coord = Y_Coord * Multiply_By;
    Multiplied.Z_Coord = Z_Coord * Multiply_By;

    return Multiplied;
}

Vectors Vectors::operator*(const Vectors& aVectors)
{
    Vectors Vector_Product;

    Vector_Product.X_Coord =(Y_Coord * aVectors.Z_Coord - Z_Coord * aVectors.Y_Coord);
    Vector_Product.Y_Coord =(Z_Coord * aVectors.X_Coord - X_Coord * aVectors.Z_Coord);
    Vector_Product.Z_Coord =(X_Coord * aVectors.Y_Coord - Y_Coord * aVectors.X_Coord);

    return Vector_Product;
}

bool Vectors::operator==(const Vectors& aVectors)
{
    unsigned int Status = 0;

    if (Testing(X_Coord, aVectors.X_Coord) )
        Status++;
    if (Testing(Y_Coord, aVectors.Y_Coord) )
        Status++;
    if (Testing(Z_Coord, aVectors.Z_Coord) )
        Status++;

    if (Status==0)
        return true;
    else
    {
       return false;
    }
}

//-------Special Member Functions------//
double Vectors::Scalar_Product(const Vectors& aVectors)
{
    double Scalar;

    Scalar =    X_Coord * aVectors.X_Coord
              + Y_Coord * aVectors.Y_Coord
              + Z_Coord * aVectors.Z_Coord;

    return Scalar;
}

double Vectors::Get_Magnitude(void)
{
    return sqrt(X_Coord*X_Coord + Y_Coord*Y_Coord + Z_Coord*Z_Coord);
}

double Vectors::Get_Distance_To(const Vectors& aVectors)
{
    Vectors Difference;

    Difference.X_Coord = X_Coord - aVectors.X_Coord;
    Difference.Y_Coord = Y_Coord - aVectors.Y_Coord;
    Difference.Z_Coord = Z_Coord - aVectors.Z_Coord;

    return Difference.Get_Magnitude();
}

std::ostream& operator<< (std::ostream& Output, const Vectors& aVectors)
{
    Output << "X = " << aVectors.X_Coord;
    Output << " Y = " << aVectors.Y_Coord;
    Output << " Z = " << aVectors.Z_Coord << std::endl;

    return std::cout;
}
