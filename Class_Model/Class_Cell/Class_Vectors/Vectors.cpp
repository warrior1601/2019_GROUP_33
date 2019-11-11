#include <iostream>
#include "Vectors.h"
using namespace std;


Vectors::Vectors()
{
    Coordinates = new float[3];
}

Vectors::~Vectors()
{
    delete[] Coordinates;
}

float Vectors::GetVector(float *Coord)
{
    Coord[0] = this->Coordinates[0];
    Coord[1] = this->Coordinates[1];
    Coord[2] = this->Coordinates[2];

        return (*Coord);
}

float Vectors::SeeVector()
{
    for (int i =0; i< 3; i++)
    {
        cout<<Coordinates[i]<<endl;
    }
}

void Vectors::SetVector(float *Coord)
{
    this->Coordinates[0] = Coord[0];
    this->Coordinates[1] = Coord[1];
    this->Coordinates[2] = Coord[2];
}

Vectors Vectors::operator+(const Vectors& add)
{

    Vectors added;

    added.Coordinates[0] = this->Coordinates[0] + add.Coordinates[0];
    added.Coordinates[1] = this->Coordinates[1] + add.Coordinates[1];
    added.Coordinates[2] = this->Coordinates[2] + add.Coordinates[2];

    return added;

}

Vectors Vectors::operator-(const Vectors& subtract)
{

    Vectors subtracted;

    subtracted.Coordinates[0] = this->Coordinates[0] - subtract.Coordinates[0];
    subtracted.Coordinates[1] = this->Coordinates[1] - subtract.Coordinates[1];
    subtracted.Coordinates[2] = this->Coordinates[2] - subtract.Coordinates[2];

    return subtracted;

}

float Vectors::Scalar_Product(const Vectors& a)
{

    float Scalar;

    Scalar =   this->Coordinates[0] * a.Coordinates[0]
              + this->Coordinates[1] * a.Coordinates[1]
              + this->Coordinates[2] * a.Coordinates[2];

    return Scalar;

}

Vectors Vectors::Vector_Product(const Vectors& a)
{


    Vectors Vector_Prduct;

    Vector_Prduct.Coordinates[0] = (this->Coordinates[1] * a.Coordinates[2]) - (this->Coordinates[2] * a.Coordinates[1]);
    Vector_Prduct.Coordinates[1] = (this->Coordinates[2] * a.Coordinates[0]) - (this->Coordinates[0] * a.Coordinates[2]);
    Vector_Prduct.Coordinates[2] = (this->Coordinates[0] * a.Coordinates[1]) - (this->Coordinates[1] * a.Coordinates[0]);

    return Vector_Prduct;

}
