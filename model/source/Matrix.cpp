//  Matrix.cpp
//  Computing Project
//  Created by Junaid Afzal on 24/11/2019.
//  This file contains the definitions of the member functions for the Matrix3x3 class

#include "Matrix.hpp"
#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>

//Constructors and destructor
Matrix3x3::Matrix3x3(const double& One, const double& Two, const double& Three,
                     const double& Four, const double& Five, const double& Six,
                     const double& Seven, const double& Eight, const double& Nine)
{
    std::vector<double> Rows;
    //Add 3 rows
    MatrixData.push_back(Rows);
    MatrixData.push_back(Rows);
    MatrixData.push_back(Rows);

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
    std::vector<double> Rows;
    //Add 3 rows
    MatrixData.push_back(Rows);
    MatrixData.push_back(Rows);
    MatrixData.push_back(Rows);

    //Add 0 to all rows so no indexing errors occur
    for (unsigned int i = 0; i < 3; i++)        //Loops through all rows
        for(unsigned int j = 0; j < 3; j++)     //Loops through all columns in this row
            MatrixData[i].push_back(0);
}

Matrix3x3::~Matrix3x3(void) { }





//Custom std::cout function
std::ostream& operator<< (std::ostream& Output, const Matrix3x3& aMatrix3x3)
{
    //Formatting of output so it resembles standard matrix notation
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
    Matrix3x3 MatrixAddition;//Addition is the addition of the corresponding matrix members

    for (unsigned int i = 0; i < 3; i++)        //Loops through all rows
        for(unsigned int j = 0; j < 3; j++)     //Loops through all columns in this row
            MatrixAddition.MatrixData[i][j] = MatrixData[i][j] + aMatrix3x3.MatrixData[i][j];
    //Add current value to corresponding aMatrix3x3 value and deposit result in MatrixAddition

    return MatrixAddition;
}

Matrix3x3 Matrix3x3::operator- (const Matrix3x3& aMatrix3x3)
{
    Matrix3x3 MatrixSubtraction;//Subtraction is the subtraaction of the corresponding matrix members

    for (unsigned int i = 0; i < 3; i++)        //Loops through all rows
        for(unsigned int j = 0; j < 3; j++)     //Loops through all columns in this row
            MatrixSubtraction.MatrixData[i][j] = MatrixData[i][j] - aMatrix3x3.MatrixData[i][j];
    //Minus current value by corresponding aMatrix3x3 value and deposit result in MatrixSubtraction

    return MatrixSubtraction;
}

Matrix3x3 Matrix3x3::operator* (const Matrix3x3& aMatrix3x3)
{
    Matrix3x3 MatrixMultiplication;

    for (unsigned int i = 0; i < 3; i++)        //Loops through all rows
        for(unsigned int j = 0; j < 3; j++)     //Loops through all columns in this row
            MatrixMultiplication.MatrixData[i][j] = MatrixData[i][0] * aMatrix3x3.MatrixData[0][j] + //Using standard matrix
                                                    MatrixData[i][1] * aMatrix3x3.MatrixData[1][j] + //multiplication formula
                                                    MatrixData[i][2] * aMatrix3x3.MatrixData[2][j];

    return MatrixMultiplication;
}

Vectors Matrix3x3::operator* (const Vectors& aVectors)
{
    Vectors VectorsMultiplication;

    VectorsMultiplication.SetX_Vector( MatrixData[0][0]*aVectors.X_Coord + MatrixData[0][1]*aVectors.Y_Coord + MatrixData[0][2]*aVectors.Z_Coord );
    VectorsMultiplication.SetY_Vector( MatrixData[1][0]*aVectors.X_Coord + MatrixData[1][1]*aVectors.Y_Coord + MatrixData[1][2]*aVectors.Z_Coord );
    VectorsMultiplication.SetZ_Vector( MatrixData[2][0]*aVectors.X_Coord + MatrixData[2][1]*aVectors.Y_Coord + MatrixData[2][2]*aVectors.Z_Coord );
    //Using the standard matrix multiplication formula

    return VectorsMultiplication;
}





Matrix3x3 Matrix3x3::operator+ (const double& aNumber)
{
    Matrix3x3 NumberAddition;

    for (unsigned int i = 0; i < 3; i++)        //Loops through all rows
        for(unsigned int j = 0; j < 3; j++)     //Loops through all columns in this row
            NumberAddition.MatrixData[i][j] = MatrixData[i][j] + aNumber;   //Add current value to aNumber and deposit result
                                                                            //in corresponding NumberSubtraction position
    return NumberAddition;
}

Matrix3x3 Matrix3x3::operator- (const double& aNumber)
{
    Matrix3x3 NumberSubtraction;

    for (unsigned int i = 0; i < 3; i++)        //Loops through all rows
        for(unsigned int j = 0; j < 3; j++)     //Loops through all columns in this row
            NumberSubtraction.MatrixData[i][j] = MatrixData[i][j] - aNumber;    //Minus current value by aNumber and deposit result
                                                                                //in corresponding NumberSubtraction position
    return NumberSubtraction;
}

Matrix3x3 Matrix3x3::operator* (const double& aNumber)
{
    Matrix3x3 NumberMultiplication;

    for (unsigned int i = 0; i < 3; i++)        //Loops through all rows
        for(unsigned int j = 0; j < 3; j++)     //Loops through all columns in this row
            NumberMultiplication.MatrixData[i][j] = MatrixData[i][j] * aNumber; //Multiply current value by aNumber and deposit result
                                                                                //in corresponding NumberMultiplication position
    return NumberMultiplication;
}

Matrix3x3 Matrix3x3::operator/ (const double& aNumber)
{
    Matrix3x3 NumberDivision;

    for (unsigned int i = 0; i < 3; i++)        //Loops through all rows
        for(unsigned int j = 0; j < 3; j++)     //Loops through all columns in this row
            NumberDivision.MatrixData[i][j] = MatrixData[i][j] / aNumber;   //Divide current value by aNumber and deposit result
                                                                            //in corresponding NumberDivision position
    return NumberDivision;
}





Matrix3x3& Matrix3x3::operator+= (const Matrix3x3& aMatrix3x3)
{
    for (unsigned int i = 0; i < 3; i++)        //Loops through all rows
        for(unsigned int j = 0; j < 3; j++)     //Loops through all columns in this row
            MatrixData[i][j] += aMatrix3x3.MatrixData[i][j];    //Add current value to corresponding aMatrix3x3 value
                                                                //and overwrite current value with result
    return *this;
}

Matrix3x3& Matrix3x3::operator-= (const Matrix3x3& aMatrix3x3)
{
    for (unsigned int i = 0; i < 3; i++)        //Loops through all rows
        for(unsigned int j = 0; j < 3; j++)     //Loops through all columns in this row
            MatrixData[i][j] -= aMatrix3x3.MatrixData[i][j];    //Minus current value by corresponding aMatrix3x3 value
                                                                //and overwrite current value with result
    return *this;
}

Matrix3x3& Matrix3x3::operator*= (const Matrix3x3& aMatrix3x3)
{
    std::vector< std::vector<double> > CopyOfMatrixData(MatrixData);

    for (unsigned int i = 0; i < 3; i++)        //Loops through all rows
        for(unsigned int j = 0; j < 3; j++)     //Loops through all columns in this row
            MatrixData[i][j] = CopyOfMatrixData[i][0] * aMatrix3x3.MatrixData[0][j] + //Using standard matrix
                               CopyOfMatrixData[i][1] * aMatrix3x3.MatrixData[1][j] + //multiplication formula
                               CopyOfMatrixData[i][2] * aMatrix3x3.MatrixData[2][j];  //But overwriting current matrix

    return *this;
}





Matrix3x3 Matrix3x3::operator+= (const double& aNumber)
{
    for (unsigned int i = 0; i < 3; i++)        //Loops through all rows
        for(unsigned int j = 0; j < 3; j++)     //Loops through all columns in this row
            MatrixData[i][j] += aNumber;        //Add current value to aNumber and overwrite
                                                //current value with result
    return *this;
}

Matrix3x3 Matrix3x3::operator-= (const double& aNumber)
{
    for (unsigned int i = 0; i < 3; i++)        //Loops through all rows
        for(unsigned int j = 0; j < 3; j++)     //Loops through all columns in this row
            MatrixData[i][j] -= aNumber;        //Minus current value by aNumber and overwrite
                                                //current value with result
    return *this;
}

Matrix3x3 Matrix3x3::operator*= (const double& aNumber)
{
    for (unsigned int i = 0; i < 3; i++)        //Loops through all rows
        for(unsigned int j = 0; j < 3; j++)     //Loops through all columns in this row
            MatrixData[i][j] *= aNumber;        //Multiply current value by aNumber and overwrite
                                                //current value with result
    return *this;
}

Matrix3x3 Matrix3x3::operator/= (const double& aNumber)
{
    for (unsigned int i = 0; i < 3; i++)        //Loops through all rows
        for(unsigned int j = 0; j < 3; j++)     //Loops through all columns in this row
            MatrixData[i][j] /= aNumber;        //Divide current value by aNumber and overwrite
                                                //current value with result
    return *this;
}





//Set functions
void Matrix3x3::Set_MatrixData(std::vector< std::vector<double> >& aMatrixData) { MatrixData = aMatrixData; }

void Matrix3x3::Set_Matrix_Data_1(const double& aMatrixNumber) { MatrixData[0][0] = aMatrixNumber; }

void Matrix3x3::Set_Matrix_Data_2(const double& aMatrixNumber) { MatrixData[0][1] = aMatrixNumber; }

void Matrix3x3::Set_Matrix_Data_3(const double& aMatrixNumber) { MatrixData[0][2] = aMatrixNumber; }

void Matrix3x3::Set_Matrix_Data_4(const double& aMatrixNumber) { MatrixData[1][0] = aMatrixNumber; }

void Matrix3x3::Set_Matrix_Data_5(const double& aMatrixNumber) { MatrixData[1][1] = aMatrixNumber; }

void Matrix3x3::Set_Matrix_Data_6(const double& aMatrixNumber) { MatrixData[1][2] = aMatrixNumber; }

void Matrix3x3::Set_Matrix_Data_7(const double& aMatrixNumber) { MatrixData[2][0] = aMatrixNumber; }

void Matrix3x3::Set_Matrix_Data_8(const double& aMatrixNumber) { MatrixData[2][1] = aMatrixNumber; }

void Matrix3x3::Set_Matrix_Data_9(const double& aMatrixNumber) { MatrixData[2][2] = aMatrixNumber; }





//Get functions
std::vector< std::vector<double> > Matrix3x3::Get_MatrixData(void) { return MatrixData; }

double Matrix3x3::Get_Matrix_Data_1(void) { return MatrixData[0][0]; }

double Matrix3x3::Get_Matrix_Data_2(void) { return MatrixData[0][1]; }

double Matrix3x3::Get_Matrix_Data_3(void) { return MatrixData[0][2]; }

double Matrix3x3::Get_Matrix_Data_4(void) { return MatrixData[1][0]; }

double Matrix3x3::Get_Matrix_Data_5(void) { return MatrixData[1][1]; }

double Matrix3x3::Get_Matrix_Data_6(void) { return MatrixData[1][2]; }

double Matrix3x3::Get_Matrix_Data_7(void) { return MatrixData[2][0]; }

double Matrix3x3::Get_Matrix_Data_8(void) { return MatrixData[2][1]; }

double Matrix3x3::Get_Matrix_Data_9(void) { return MatrixData[2][2]; }





//Matrix3x3 specific functions
void Matrix3x3::Initialise_As_Rotation_Matrix(double Rotation_In_Degrees, char Axis_Of_Rotation)
{
    //For column vectors, each of these basic vector rotations appears counterclockwise
    //when the axis about which they occur points toward the observer, the coordinate system is
    //right-handed, and the angle θ is positive. See https://en.wikipedia.org/wiki/Rotation_matrix for more info

    //Note that the rotation occurs with respect to the origin. Therefore, if rotation around the
    //objects centre is required, the object must be translated such that the centre of the object
    //is at the origin.

    double Rotation_In_Radians = Rotation_In_Degrees * M_PI / 180.0;

    //The next two if statements exist to round the value of cosine or sine down to 0 as otherwise the
    //values would be an extremely small number. This is probably due to rounding errors in M_PI and
    //std::cos/std::sin and only occur when the functions should be = 0.

    double cosineValue = std::cos(Rotation_In_Radians);
    if(cosineValue < 0.0001 && cosineValue > -0.0001)
        cosineValue = 0;

    double sineValue = std::sin(Rotation_In_Radians);
    if(sineValue < 0.0001 && sineValue > -0.0001)
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
    //Copy of matrix data is made as some values will be overwritten before they are used
    std::vector< std::vector<double> > CopyOfMatrixData = MatrixData;

    for (unsigned int i = 0; i < 3; i++)        //Loops through all rows
        for(unsigned int j = 0; j < 3; j++)     //Loops through all columns in this row
            MatrixData[i][j] = CopyOfMatrixData[j][i];
}

double Matrix3x3::Get_Determinant(void)
{
    //Using Sarrus' Rule, see https://en.wikipedia.org/wiki/Rule_of_Sarrus for more info

    return MatrixData[0][0]*MatrixData[1][1]*MatrixData[2][2] +
           MatrixData[0][1]*MatrixData[1][2]*MatrixData[2][0] +
           MatrixData[0][2]*MatrixData[1][0]*MatrixData[2][1] -
           MatrixData[0][2]*MatrixData[1][1]*MatrixData[2][0] -
           MatrixData[0][0]*MatrixData[1][2]*MatrixData[2][1] -
           MatrixData[0][1]*MatrixData[1][0]*MatrixData[2][2];
}

void Matrix3x3::Inverse_Matrix(void)
{
    double DeterminantofMatrix = Get_Determinant(); //Store value now as matrix data will be changed

    if (DeterminantofMatrix == 0)
    {
        std::cout << "Error, determinant of matrix is 0, therefore matrix is not invertible" << std::endl;
        return;
    }

    else
    {
        //Copy of matrix data is made as some values will be overwritten before they are used
        std::vector< std::vector<double> > CopyOfMatrixData = MatrixData;

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
