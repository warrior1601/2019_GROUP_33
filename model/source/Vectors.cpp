//
//  Vectors.cpp
//  Computing Project
//
//  Created by Jedidiah Paterson on 27/11/2019.
//  Copyright � 2019 Jedidiah Paterson. All rights reserved.
//  This file contains the definitions of functions for the Class
//  Vectors.
//

#include <cmath>
#include <iostream>
#include "Vectors.h"
#include <windows.h>

//-------------Constructors------------//

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

//--------------Destructor-------------//

Vectors::~Vectors() {}

//-------------Set Functions-----------//

void Vectors::SetX_Vector(double aX_Coord)
{
    this->X_Coord = aX_Coord;
}

void Vectors::SetY_Vector(double aY_Coord)
{
    this->Y_Coord = aY_Coord;
}

void Vectors::SetZ_Vector(double aZ_Coord)
{
    this->Z_Coord = aZ_Coord;
}

void Vectors::SetVector(double aX_Coord, double aY_Coord, double aZ_Coord)
{
    this->X_Coord = aX_Coord;
    this->Y_Coord = aY_Coord;
    this->Z_Coord = aZ_Coord;
}

//-------------Get Functions-----------//

double Vectors::GetXVector()
{
    return (this->X_Coord);
}

double Vectors::GetYVector()
{
    return (this->Y_Coord);
}

double Vectors::GetZVector()
{
    return (this->Z_Coord);
}

//-----Operator Overload Functions-----//


Vectors Vectors::operator=(const Vectors& Copy)
{
    this->X_Coord = Copy.X_Coord;
    this->Y_Coord = Copy.Y_Coord;
    this->Z_Coord = Copy.Z_Coord;

    return (*this);
}

Vectors Vectors::operator+(const Vectors& add)
{
    Vectors Added;
    Added.X_Coord = this->X_Coord + add.X_Coord;
    Added.Y_Coord = this->Y_Coord + add.Y_Coord;
    Added.Z_Coord = this->Z_Coord + add.Z_Coord;

    return Added;
}

Vectors Vectors::operator-(const Vectors& subtract)
{
    Vectors Subtraced;
    Subtraced.X_Coord = this->X_Coord - subtract.X_Coord;
    Subtraced.Y_Coord = this->Y_Coord - subtract.Y_Coord;
    Subtraced.Z_Coord = this->Z_Coord - subtract.Z_Coord;

    return Subtraced;
}

Vectors Vectors::operator/(const double& Divide)
{
    Vectors Divided;
    if ( Divide != 0 )
    {
    Divided.X_Coord = this->X_Coord / Divide;
    Divided.Y_Coord = this->Y_Coord / Divide;
    Divided.Z_Coord = this->Z_Coord / Divide;

    return Divided;
    }
    else
    {
    std::cout << "This is not a valid operation" << std::endl;
    std::cout << "Can not divide by 0" << std::endl;
    MessageBox(0,"Can not Divide by 0", "Error", MB_OK);
    return (*this);
    }
}

Vectors Vectors::operator*(const double& Multiply_By)
{
    Vectors Multiplied;
    Multiplied.X_Coord = this->X_Coord * Multiply_By;
    Multiplied.Y_Coord = this->Y_Coord * Multiply_By;
    Multiplied.Z_Coord = this->Z_Coord * Multiply_By;

    return Multiplied;
}

Vectors Vectors::operator*(const Vectors& aVectors)
{
    Vectors Vector_Prduct;

    Vector_Prduct.X_Coord = (this->Y_Coord * aVectors.Z_Coord) - (this->Z_Coord * aVectors.Y_Coord);
    Vector_Prduct.Y_Coord = (this->Z_Coord * aVectors.X_Coord) - (this->X_Coord * aVectors.Z_Coord);
    Vector_Prduct.Z_Coord = (this->X_Coord * aVectors.Y_Coord) - (this->Y_Coord * aVectors.X_Coord);

    return Vector_Prduct;
}

//-------Special Member Functions------//

double Vectors::Scalar_Product(const Vectors& aVectors)
{
    double Scalar;

    Scalar =    this->X_Coord * aVectors.X_Coord
              + this->Y_Coord * aVectors.Y_Coord
              + this->Z_Coord * aVectors.Z_Coord;

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

std::ostream& operator<< (std::ostream& Output,const Vectors& aVectors)
{
    Output << "X = " << aVectors.X_Coord;
    Output << " Y = " << aVectors.Y_Coord;
    Output << " Z = " << aVectors.Z_Coord << std::endl;

    return std::cout;
}
