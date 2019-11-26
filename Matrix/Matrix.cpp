//
//  Matrix.cpp
//  Computing Project
//
//  Created by Junaid Afzal on 24/11/2019.
//  Copyright © 2019 Junaid Afzal. All rights reserved.
//
//  This source file contains the implementation of the object Matrix3x3
//

#include "Matrix.hpp"
#include <cmath>

//Constructors and destructors
Matrix3x3::Matrix3x3(const float& One, const float& Two, const float& Three, const float& Four, const float& Five, const float& Six, const float& Seven, const float& Eight, const float& Nine)
{    
    MatrixData[0].push_back(One);
    MatrixData[0].push_back(Two);
    MatrixData[0].push_back(Three);
    
    MatrixData[1].push_back(Four);
    MatrixData[1].push_back(Five);
    MatrixData[1].push_back(Six);
    
    MatrixData[2].push_back(Seven);
    MatrixData[2].push_back(Eight);
    MatrixData[2].push_back(Nine);
}

Matrix3x3::Matrix3x3(const Matrix3x3& aMatrix3x3) { MatrixData = aMatrix3x3.MatrixData; }

Matrix3x3::Matrix3x3(void)
{
    //Add 0 to all rows so no indexing errors occur
    for (unsigned int i = 0; i < 3; i++)        //Loops through all rows
        for(unsigned int j = 0; j < 3; j++)     //Loops through all columns
            MatrixData[i].push_back(0);
}

Matrix3x3::~Matrix3x3(void) { }





//Custom std::cout function
std::ostream& operator<< (std::ostream& Output, const Matrix3x3& aMatrix3x3)
{
    Output << aMatrix3x3.MatrixData[0][0] << "\t" << aMatrix3x3.MatrixData[0][1] << "\t" << aMatrix3x3.MatrixData[0][2] << std::endl;
    Output << aMatrix3x3.MatrixData[1][0] << "\t" << aMatrix3x3.MatrixData[1][1] << "\t" << aMatrix3x3.MatrixData[1][2] << std::endl;
    Output << aMatrix3x3.MatrixData[2][0] << "\t" << aMatrix3x3.MatrixData[2][1] << "\t" << aMatrix3x3.MatrixData[2][2] << std::endl;
    
    return Output;
}





//Custom operator functions
Matrix3x3& Matrix3x3::operator = (const Matrix3x3& aMatrix3x3)
{
    if (&aMatrix3x3 == this)
        return *this;
    
    else
    {
        MatrixData = aMatrix3x3.MatrixData;
        
        return *this;
    }
}





Matrix3x3 Matrix3x3::operator+ (const Matrix3x3& aMatrix3x3)
{
    Matrix3x3 MatrixAddition;
    
    for (unsigned int i = 0; i < 3; i++)
        for(unsigned int j = 0; j < 3; j++)
            MatrixAddition.MatrixData[i][j] = MatrixData[i][j] + aMatrix3x3.MatrixData[i][j];
    
    return MatrixAddition;
}

Matrix3x3 Matrix3x3::operator- (const Matrix3x3& aMatrix3x3)
{
    Matrix3x3 MatrixSubtraction;
    
    for (unsigned int i = 0; i < 3; i++)
        for(unsigned int j = 0; j < 3; j++)
            MatrixSubtraction.MatrixData[i][j] = MatrixData[i][j] - aMatrix3x3.MatrixData[i][j];
    
    return MatrixSubtraction;
}

Matrix3x3 Matrix3x3::operator* (const Matrix3x3& aMatrix3x3)
{
    Matrix3x3 MatrixMultiplication;
    
    for(unsigned int i = 0; i < 3; i++)
        for(unsigned int j = 0; j < 3; j++)
            MatrixMultiplication.MatrixData[i][j] = MatrixData[i][0] * aMatrix3x3.MatrixData[0][j] +
                                                    MatrixData[i][1] * aMatrix3x3.MatrixData[1][j] +
                                                    MatrixData[i][2] * aMatrix3x3.MatrixData[2][j];
    
    return MatrixMultiplication;
}

Vectors Matrix3x3::operator* (const Vectors& aVectors)
{
    Vectors VectorsMultiplication;
    
    VectorsMultiplication.SetX_Vector( MatrixData[0][0]*aVectors.X_Coord + MatrixData[0][1]*aVectors.Y_Coord + MatrixData[0][2]*aVectors.Z_Coord );
    VectorsMultiplication.SetY_Vector( MatrixData[1][0]*aVectors.X_Coord + MatrixData[1][1]*aVectors.Y_Coord + MatrixData[1][2]*aVectors.Z_Coord );
    VectorsMultiplication.SetZ_Vector( MatrixData[2][0]*aVectors.X_Coord + MatrixData[2][1]*aVectors.Y_Coord + MatrixData[2][2]*aVectors.Z_Coord );
    
    return VectorsMultiplication;
}





Matrix3x3 Matrix3x3::operator+ (const float& aNumber)
{
    Matrix3x3 NumberAddition;
    
    for (unsigned int i = 0; i < 3; i++)
        for(unsigned int j = 0; j < 3; j++)
            NumberAddition.MatrixData[i][j] = MatrixData[i][j] + aNumber;
    
    return NumberAddition;
}

Matrix3x3 Matrix3x3::operator- (const float& aNumber)
{
    Matrix3x3 NumberSubtraction;
    
    for (unsigned int i = 0; i < 3; i++)
        for(unsigned int j = 0; j < 3; j++)
            NumberSubtraction.MatrixData[i][j] = MatrixData[i][j] - aNumber;
    
    return NumberSubtraction;
}

Matrix3x3 Matrix3x3::operator* (const float& aNumber)
{
    Matrix3x3 NumberMultiplication;
    
    for (unsigned int i = 0; i < 3; i++)
        for(unsigned int j = 0; j < 3; j++)
            NumberMultiplication.MatrixData[i][j] = MatrixData[i][j] * aNumber;
    
    return NumberMultiplication;
}

Matrix3x3 Matrix3x3::operator/ (const float& aNumber)
{
    Matrix3x3 NumberDivision;
    
    for (unsigned int i = 0; i < 3; i++)
        for(unsigned int j = 0; j < 3; j++)
            NumberDivision.MatrixData[i][j] = MatrixData[i][j] / aNumber;
    
    return NumberDivision;
}





Matrix3x3& Matrix3x3::operator+= (const Matrix3x3& aMatrix3x3)
{
    for (unsigned int i = 0; i < 3; i++)
        for(unsigned int j = 0; j < 3; j++)
            MatrixData[i][j] += aMatrix3x3.MatrixData[i][j];
    
    return *this;
}

Matrix3x3& Matrix3x3::operator-= (const Matrix3x3& aMatrix3x3)
{
    for (unsigned int i = 0; i < 3; i++)
        for(unsigned int j = 0; j < 3; j++)
            MatrixData[i][j] -= aMatrix3x3.MatrixData[i][j];
    
    return *this;
}

Matrix3x3& Matrix3x3::operator*= (const Matrix3x3& aMatrix3x3)
{
    Matrix3x3 temp = *this;
    
    for(unsigned int i = 0; i < 3; i++)
        for(unsigned int j = 0; j < 3; j++)
            MatrixData[i][j] = temp.MatrixData[i][0] * aMatrix3x3.MatrixData[0][j] +
                               temp.MatrixData[i][1] * aMatrix3x3.MatrixData[1][j] +
                               temp.MatrixData[i][2] * aMatrix3x3.MatrixData[2][j];
    
    return *this;
}





Matrix3x3 Matrix3x3::operator+= (const float& aNumber)
{
    for (unsigned int i = 0; i < 3; i++)
        for(unsigned int j = 0; j < 3; j++)
            MatrixData[i][j] += aNumber;
    
    return *this;
}

Matrix3x3 Matrix3x3::operator-= (const float& aNumber)
{
    for (unsigned int i = 0; i < 3; i++)
        for(unsigned int j = 0; j < 3; j++)
            MatrixData[i][j] -= aNumber;
    
    return *this;
}

Matrix3x3 Matrix3x3::operator*= (const float& aNumber)
{
    for (unsigned int i = 0; i < 3; i++)
        for(unsigned int j = 0; j < 3; j++)
            MatrixData[i][j] *= aNumber;
    
    return *this;
}

Matrix3x3 Matrix3x3::operator/= (const float& aNumber)
{
    for (unsigned int i = 0; i < 3; i++)
        for(unsigned int j = 0; j < 3; j++)
            MatrixData[i][j] /= aNumber;
    
    return *this;
}





//Set and get functions
void Matrix3x3::Set_MatrixData(std::vector< std::vector<float> >& aMatrixData) { MatrixData = aMatrixData; }

void Matrix3x3::Set_Matrix_Data_1(const float& aMatrixNumber) { MatrixData[0][0] = aMatrixNumber; }

void Matrix3x3::Set_Matrix_Data_2(const float& aMatrixNumber) { MatrixData[0][1] = aMatrixNumber; }

void Matrix3x3::Set_Matrix_Data_3(const float& aMatrixNumber) { MatrixData[0][2] = aMatrixNumber; }

void Matrix3x3::Set_Matrix_Data_4(const float& aMatrixNumber) { MatrixData[1][0] = aMatrixNumber; }

void Matrix3x3::Set_Matrix_Data_5(const float& aMatrixNumber) { MatrixData[1][1] = aMatrixNumber; }

void Matrix3x3::Set_Matrix_Data_6(const float& aMatrixNumber) { MatrixData[1][2] = aMatrixNumber; }

void Matrix3x3::Set_Matrix_Data_7(const float& aMatrixNumber) { MatrixData[2][0] = aMatrixNumber; }

void Matrix3x3::Set_Matrix_Data_8(const float& aMatrixNumber) { MatrixData[2][1] = aMatrixNumber; }

void Matrix3x3::Set_Matrix_Data_9(const float& aMatrixNumber) { MatrixData[2][2] = aMatrixNumber; }



std::vector< std::vector<float> > Matrix3x3::Get_MatrixData(void) { return MatrixData; }

float Matrix3x3::Get_Matrix_Data_1(void) { return MatrixData[0][0]; }

float Matrix3x3::Get_Matrix_Data_2(void) { return MatrixData[0][1]; }

float Matrix3x3::Get_Matrix_Data_3(void) { return MatrixData[0][2]; }

float Matrix3x3::Get_Matrix_Data_4(void) { return MatrixData[1][0]; }

float Matrix3x3::Get_Matrix_Data_5(void) { return MatrixData[1][1]; }

float Matrix3x3::Get_Matrix_Data_6(void) { return MatrixData[1][2]; }

float Matrix3x3::Get_Matrix_Data_7(void) { return MatrixData[2][0]; }

float Matrix3x3::Get_Matrix_Data_8(void) { return MatrixData[2][1]; }

float Matrix3x3::Get_Matrix_Data_9(void) { return MatrixData[2][2]; }





//Matrix3x3 specific functions
void Matrix3x3::Initialise_As_Rotation_Matrix(float Rotation_In_Degrees, char Axis_Of_Rotation)
{
    //For column vectors, each of these basic vector rotations appears counterclockwise
    //when the axis about which they occur points toward the observer, the coordinate system
    //is right-handed, and the angle θ is positive.
     
    float Rotation_In_Radians = Rotation_In_Degrees * M_PI / 180.0;
    
    float cosineValue = std::cos(Rotation_In_Radians);
    if(cosineValue < 0.0001)
        cosineValue = 0;
    
    float sineValue = std::sin(Rotation_In_Radians);
    if(sineValue < 0.0001)
        sineValue = 0;
    
    switch (Axis_Of_Rotation) {
        case 'x':
            MatrixData[0][0] = 1;
            MatrixData[0][1] = 0;
            MatrixData[0][2] = 0;
            
            MatrixData[1][0] = 0;
            MatrixData[1][1] = cosineValue;
            MatrixData[1][2] = -sineValue;
            
            MatrixData[2][0] = 0;
            MatrixData[2][1] = sineValue;
            MatrixData[2][2] = cosineValue;
            break;
            
        case 'y':
            MatrixData[0][0] = cosineValue;
            MatrixData[0][1] = 0;
            MatrixData[0][2] = sineValue;
            
            MatrixData[1][0] = 0;
            MatrixData[1][1] = 1;
            MatrixData[1][2] = 0;
            
            MatrixData[2][0] = -sineValue;
            MatrixData[2][1] = 0;
            MatrixData[2][2] = cosineValue;
            break;
            
        case 'z':
            MatrixData[0][0] = cosineValue;
            MatrixData[0][1] = -sineValue;
            MatrixData[0][2] = 0;
            
            MatrixData[1][0] = sineValue;
            MatrixData[1][1] = cosineValue;
            MatrixData[1][2] = 0;
            
            MatrixData[2][0] = 0;
            MatrixData[2][1] = 0;
            MatrixData[2][2] = 1;
            break;
            
        default:
            std::cout << "Error due to invalid axis of rotation" << std::endl;
            break;
    }
}

void Matrix3x3::Transpose_Matrix(void)
{
    std::vector< std::vector<float> > CopyOfMatrixData = MatrixData;
    
    for (unsigned int i = 0; i < 3; i++)
        for (unsigned int j = 0; j < 3; j++)
            MatrixData[i][j] = CopyOfMatrixData[j][i];
}

float Matrix3x3::Get_Determinant(void)
{
    return MatrixData[0][0]*MatrixData[1][1]*MatrixData[2][2] +
           MatrixData[0][1]*MatrixData[1][2]*MatrixData[2][0] +
           MatrixData[0][2]*MatrixData[1][0]*MatrixData[2][1] -
           MatrixData[0][2]*MatrixData[1][1]*MatrixData[2][0] -
           MatrixData[0][0]*MatrixData[1][2]*MatrixData[2][1] -
           MatrixData[0][1]*MatrixData[1][0]*MatrixData[2][2];
}

void Matrix3x3::Inverse_Matrix(void)
{
    float DeterminantofMatrix = Get_Determinant(); //Store value now as matrix data will be changed
    
    if (DeterminantofMatrix == 0)
    {
        std::cout << "Error, determinant of matrix is 0, therefore matrix is not invertible" << std::endl;
        return;
    }
    
    else
    {
        std::vector< std::vector<float> > CopyOfMatrixData = MatrixData; //CopyOfMatrixData
        
        //Replace each element in matrix by it's co-factor
        MatrixData[0][0] = +(CopyOfMatrixData[1][1]*CopyOfMatrixData[2][2] - CopyOfMatrixData[1][2]*CopyOfMatrixData[2][1]);
        MatrixData[0][1] = -(CopyOfMatrixData[1][0]*CopyOfMatrixData[2][2] - CopyOfMatrixData[1][2]*CopyOfMatrixData[2][0]);
        MatrixData[0][2] = +(CopyOfMatrixData[1][0]*CopyOfMatrixData[2][1] - CopyOfMatrixData[1][1]*CopyOfMatrixData[2][0]);
        
        MatrixData[1][0] = -(CopyOfMatrixData[0][1]*CopyOfMatrixData[2][2] - CopyOfMatrixData[0][2]*CopyOfMatrixData[2][1]);
        MatrixData[1][1] = +(CopyOfMatrixData[0][0]*CopyOfMatrixData[2][2] - CopyOfMatrixData[0][2]*CopyOfMatrixData[2][0]);
        MatrixData[1][2] = -(CopyOfMatrixData[0][0]*CopyOfMatrixData[2][1] - CopyOfMatrixData[0][1]*CopyOfMatrixData[2][0]);
        
        MatrixData[2][0] = +(CopyOfMatrixData[0][1]*CopyOfMatrixData[1][2] - CopyOfMatrixData[0][2]*CopyOfMatrixData[1][1]);
        MatrixData[2][1] = -(CopyOfMatrixData[0][0]*CopyOfMatrixData[1][2] - CopyOfMatrixData[0][2]*CopyOfMatrixData[1][0]);
        MatrixData[2][2] = +(CopyOfMatrixData[0][0]*CopyOfMatrixData[1][1] - CopyOfMatrixData[0][1]*CopyOfMatrixData[1][0]);
        
        //Trasnpose the matirx
        Transpose_Matrix();
        
        //Divide matrix data by determinant
        *this /= DeterminantofMatrix;
    }
}
