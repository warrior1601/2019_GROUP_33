#include <iostream>
#include <cmath>
#include "Vectors.h"

//
//  Vectors.cpp
//  Computing Project
//
//  Created by Jedidiah Paterson on 27/11/2019.
//  Copyright � 2019 Jedidiah Paterson. All rights reserved.
//  This file contains the definitions of functions for the Class
//  Vectors.


using namespace std;

//-------------Constructors------------//

Vectors::Vectors()
{
    X_Coord = 0;
    Y_Coord = 0;
    Z_Coord = 0;
}

Vectors::Vectors(float aX_Coord)
{
    X_Coord = aX_Coord;
    Y_Coord = 0;
    Z_Coord = 0;
}
Vectors::Vectors(float aX_Coord, float aY_Coord)
{
    X_Coord = aX_Coord;
    Y_Coord = aY_Coord;
    Z_Coord = 0;
}
Vectors::Vectors(float aX_Coord, float aY_Coord, float aZ_Coord)
{
    X_Coord = aX_Coord;
    Y_Coord = aY_Coord;
    Z_Coord = aZ_Coord;
}

//--------------Destructor-------------//

Vectors::~Vectors() {}

//-------------Set Functions-----------//

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

void Vectors::SetVector(float aX_Coord, float aY_Coord, float aZ_Coord)
{
    this->X_Coord = aX_Coord;
    this->Y_Coord = aY_Coord;
    this->Z_Coord = aZ_Coord;
}

//-------------Get Functions-----------//

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

Vectors Vectors::operator/(const float& Divide)
{
    Vectors Divided;

    Divided.X_Coord = this->X_Coord / Divide;
    Divided.Y_Coord = this->Y_Coord / Divide;
    Divided.Z_Coord = this->Z_Coord / Divide;

    return Divided;
}

Vectors Vectors::operator*(const float& Multiply_By)
{
    Vectors Multiply;

    Multiply.X_Coord = this->X_Coord * Multiply_By;
    Multiply.Y_Coord = this->Y_Coord * Multiply_By;
    Multiply.Z_Coord = this->Z_Coord * Multiply_By;

    return Multiply;
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

float Vectors::Scalar_Product(const Vectors& aVectors)
{
    float Scalar;

    Scalar =  this->X_Coord * aVectors.X_Coord
              + this->Y_Coord * aVectors.Y_Coord
              + this->Z_Coord * aVectors.Z_Coord;

    return Scalar;
}

float Vectors::Get_Magnitude(void)
{
    return sqrt(X_Coord*X_Coord + Y_Coord*Y_Coord + Z_Coord*Z_Coord);
}

float Vectors::Get_Distance_To(const Vectors& aVectors)
{
    Vectors Difference;
    
    Difference.X_Coord = X_Coord - aVectors.X_Coord;
    Difference.Y_Coord = Y_Coord - aVectors.Y_Coord;
    Difference.Z_Coord = Z_Coord - aVectors.Z_Coord;
    
    return Difference.Get_Magnitude();
}

std::ostream& operator<< (std::ostream&,const Vectors& aVectors)
{
    std::cout << "X = "<<aVectors.X_Coord;
    std::cout << " Y = "<<aVectors.Y_Coord;
    std::cout << " Z = "<<aVectors.Z_Coord<<std::endl;

    return std::cout;
}
