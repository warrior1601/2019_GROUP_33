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

float Vectors::GetXVector()
{
    float Coord = 0;

    Coord = this->Coordinates[0];

    return (Coord);
}

float Vectors::GetYVector()
{
    float Coord = 0;

    Coord = this->Coordinates[1];

    return (Coord);
}

float Vectors::GetZVector()
{
    float Coord = 0;

    Coord = this->Coordinates[2];

    return (Coord);
}

/*void Vectors::SeeVector()
{

    cout<<"X ="<<Coordinates[0]<<" Y ="<<Coordinates[1]<<" Z ="<<Coordinates[2]<<endl;
}*/

void Vectors::SetVector(float *Coord)
{
    this->Coordinates[0] = Coord[0];
    this->Coordinates[1] = Coord[1];
    this->Coordinates[2] = Coord[2];
}

Vectors Vectors::operator=(const Vectors& Copy)
{

    this->Coordinates[0] = Copy.Coordinates[0];
    this->Coordinates[1] = Copy.Coordinates[1];
    this->Coordinates[2] = Copy.Coordinates[2];

    return Copy;
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

float Vectors::Scalar_Product(const Vectors& aVectors)
{
    float Scalar;

    Scalar =         this->Coordinates[0] * aVectors.Coordinates[0]
                   + this->Coordinates[1] * aVectors.Coordinates[1]
                   + this->Coordinates[2] * aVectors.Coordinates[2];

    return Scalar;
}

Vectors Vectors::Vector_Product(const Vectors& aVectors)
{
    Vectors Vector_Prduct;

    Vector_Prduct.Coordinates[0] = (this->Coordinates[1] * aVectors.Coordinates[2]) - (this->Coordinates[2] * aVectors.Coordinates[1]);
    Vector_Prduct.Coordinates[1] = (this->Coordinates[2] * aVectors.Coordinates[0]) - (this->Coordinates[0] * aVectors.Coordinates[2]);
    Vector_Prduct.Coordinates[2] = (this->Coordinates[0] * aVectors.Coordinates[1]) - (this->Coordinates[1] * aVectors.Coordinates[0]);

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

    Divided.Coordinates[0] = this->Coordinates[0] / My_Number;
    Divided.Coordinates[1] = this->Coordinates[1] / My_Number;
    Divided.Coordinates[2] = this->Coordinates[2] / My_Number;

    return Divided;
}
