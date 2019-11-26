#ifndef VECTORS_H_INCLUDED
#define VECTORS_H_INCLUDED

#include <iostream>

class Vectors
{

private:

    float X_Coord;
    float Y_Coord;
    float Z_Coord;



public:
    Vectors(); //Constructor
    ~Vectors(); //destructor
    void SetVector(float aX_Coord, float aY_Coord, float aZ_Coord);
    void SetX_Vector(float aX_Coord);
    void SetY_Vector(float aY_Coord);
    void SetZ_Vector(float aZ_Coord);
    float GetXVector();
    float GetYVector();
    float GetZVector();
    Vectors operator=(const Vectors& Copy);
    Vectors operator+(const Vectors& add);
    Vectors operator-(const Vectors& subtract);
    float Scalar_Product(const Vectors& aVectors);
    Vectors Vector_Product(const Vectors& aVectors);
    Vectors Vector_Divide_By_Number(float My_Number);
    friend std::ostream& operator<< (std::ostream&, const Vectors& aVectors);
    friend class Matrix3x3;
};

#endif // VECTORS_H_INCLUDED
