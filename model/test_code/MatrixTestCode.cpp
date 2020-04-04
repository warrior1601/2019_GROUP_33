//
//  MatrixTestCode.cpp
//  Computing Project
//
//  Created by Junaid Afzal on 24/11/2019.
//  Copyright © 2019 Junaid Afzal. All rights reserved.
//
//  This source files contains all the test code for
//  the object Matrix3x3 and demonstrates all the
//  functionality of the object
//

#include <iostream>
#include "Matrix.hpp"
#include "Testing_File_Functions.h"
#include <cmath>

int main()
{
    unsigned int Testing_For_Error = 0;
    unsigned int Error = 0;
    std::cout << "------------------------------Matrix.hpp Test Code------------------------------" << std::endl;
    // First we test the constuctots and the get functions
    Matrix3x3 Blank_Matrix;

    Testing_For_Error = Testing(Blank_Matrix, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

    if (Testing_For_Error == 0)
        std::cout << "Blank Constructor and Get Functions Work Properly" << std::endl;
    else
    {
        std::cout << "Blank Constructor and Get Functions Do Not Work Properly" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }

    Matrix3x3 Non_Blank_Matrix(-5.0, 0.0, 2.0, 2.36, -9.56, 0.0005, -0.00005, 9.62, 15623.0235);

    Testing_For_Error = Testing(Non_Blank_Matrix, -5.0, 0.0, 2.0, 2.36, -9.56, 0.0005, -0.00005, 9.62, 15623.0235);

    if (Testing_For_Error == 0)
        std::cout << "Non Blank Constructor Works Properly" << std::endl;
    else
    {
        std::cout << "Non Blank Constructor Does Not Work Properly" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }

    Matrix3x3 Copy(Non_Blank_Matrix);

    Testing_For_Error = Testing(Copy, Non_Blank_Matrix);

    if (Testing_For_Error == 0)
        std::cout << "Copy Constructor Works Properly" << std::endl;
    else
    {
        std::cout << "Copy Constructor Does Not Work Properly" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }
    // Now we test set functions
    // there are two ways to set the Matrix data the first, individually then all at once with a vector

    Copy.Set_Matrix_Data_1(1.0);
    Copy.Set_Matrix_Data_2(1.5);
    Copy.Set_Matrix_Data_3(0.0);
    Copy.Set_Matrix_Data_4(-1.0);
    Copy.Set_Matrix_Data_5(-1.5);
    Copy.Set_Matrix_Data_6(0.00025);
    Copy.Set_Matrix_Data_7(-0.00025);
    Copy.Set_Matrix_Data_8(789.235);
    Copy.Set_Matrix_Data_9(-456.000001);

    Testing_For_Error = Testing(Copy, 1.0, 1.5, 0.0, -1.0, -1.5, 0.00025, -0.00025, 789.235, -456.000001);

    if (Testing_For_Error == 0)
        std::cout << "Individually Set Functions Work Properly" << std::endl;
    else
    {
        std::cout << "Individually Set Functions Do Not Work Properly" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }

    std::vector< std::vector<double> > aMatrixData;
    std::vector< double > Rows;

    aMatrixData.push_back(Rows);
    aMatrixData.push_back(Rows);
    aMatrixData.push_back(Rows);

    aMatrixData[0].push_back(4.0);
    aMatrixData[0].push_back(-4.0);
    aMatrixData[0].push_back(0.0);

    aMatrixData[1].push_back(12.32);
    aMatrixData[1].push_back(0.000052);
    aMatrixData[1].push_back(123456.321654);

    aMatrixData[2].push_back(52.02);
    aMatrixData[2].push_back(-5623.0);
    aMatrixData[2].push_back(520.02);

    Copy.Set_MatrixData(aMatrixData);

    Testing_For_Error = Testing(Copy, 4.0, -4.0, 0.0, 12.32, 0.000052, 123456.321654, 52.02, -5623.0, 520.02);

    if (Testing_For_Error == 0)
        std::cout << "Vector Set Functions Works Properly" << std::endl;
    else
    {
        std::cout << "Vector Set Function Does Not Work Properly" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }

    // Now we test the Overloaded operators

    Copy = Blank_Matrix;

    Testing_For_Error = Testing(Copy, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);

    if (Testing_For_Error == 0)
        std::cout << "Operator Overload for '=' Works Properly" << std::endl;
    else
    {
        std::cout << "Operator Overload for '=' Does Not Work Properly" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }

    // I am going to create a Matrix3x3 that will be used for most of the Operator Overload operations

    Matrix3x3 For_Operator_Operations(-7.5, -5.0, -2.5, -0.25, 0.0, 0.25, 2.5 , 5.0, 7.5);

    Copy = Copy + For_Operator_Operations;

    Testing_For_Error = Testing(Copy, -7.5, -5.0, -2.5, -0.25, 0.0, 0.25, 2.5 , 5.0, 7.5);

    if (Testing_For_Error == 0)
        std::cout << "Operator Overload for '+' A Matrix3x3 Works Properly" << std::endl;
    else
    {
        std::cout << "Operator Overload for '+' A Matrix3x3 Does Not Work Properly" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }
    // We also need to test that the Matrix3x3 For_Operator_Operations was unchanged
    // This will be done after each Operator test

    Testing_For_Error = Testing(For_Operator_Operations, -7.5, -5.0, -2.5, -0.25, 0.0, 0.25, 2.5 , 5.0, 7.5);

    if (Testing_For_Error == 0)
        std::cout << "For_Operator_Operations Was Unchanged" << std::endl;
    else
    {
        std::cout << "For_Operator_Operations Was Changed" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }

   Copy = Copy * For_Operator_Operations;

   Testing_For_Error = Testing(Copy, 51.25, 25.0, -1.25, 2.5, 2.5, 2.5, -1.25 , 25.0, 51.25);

   if (Testing_For_Error == 0)
       std::cout << "Operator Overload for '*' A Matrix3x3 Works Properly" << std::endl;
   else
   {
       std::cout << "Operator Overload for '*' A Matrix3x3 Does Not Work Properly" << std::endl;
       Error = 1;
       Testing_For_Error = 0;
   }

   Testing_For_Error = Testing(For_Operator_Operations, -7.5, -5.0, -2.5, -0.25, 0.0, 0.25, 2.5 , 5.0, 7.5);

   if (Testing_For_Error == 0)
       std::cout << "For_Operator_Operations Was Unchanged" << std::endl;
   else
   {
       std::cout << "For_Operator_Operations Was Changed" << std::endl;
       Error = 1;
       Testing_For_Error = 0;
   }

   Copy = Copy - For_Operator_Operations;

   Testing_For_Error = Testing(Copy, 58.75, 30.0, 1.25, 2.75, 2.5, 2.25, -3.75, 20.0, 43.75);

   if (Testing_For_Error == 0)
       std::cout << "Operator Overload for '-' A Matrix3x3 Works Properly" << std::endl;
   else
   {
       std::cout << "Operator Overload for '-' A Matrix3x3 Does Not Work Properly" << std::endl;
       Error = 1;
       Testing_For_Error = 0;
   }

   Testing_For_Error = Testing(For_Operator_Operations, -7.5, -5.0, -2.5, -0.25, 0.0, 0.25, 2.5 , 5.0, 7.5);

   if (Testing_For_Error == 0)
       std::cout << "For_Operator_Operations Was Unchanged" << std::endl;
   else
   {
       std::cout << "For_Operator_Operations Was Changed" << std::endl;
       Error = 1;
       Testing_For_Error = 0;
   }

    Copy += For_Operator_Operations;

    Testing_For_Error = Testing(Copy, 51.25, 25.0, -1.25, 2.5, 2.5, 2.5, -1.25, 25.0, 51.25);

    if (Testing_For_Error == 0)
        std::cout << "Operator Overload for '+=' A Matrix3x3 Works Properly" << std::endl;
    else
    {
        std::cout << "Operator Overload for '+=' A Matrix3x3 Does Not Work Properly" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }

    Testing_For_Error = Testing(For_Operator_Operations, -7.5, -5.0, -2.5, -0.25, 0.0, 0.25, 2.5 , 5.0, 7.5);

    if (Testing_For_Error == 0)
        std::cout << "For_Operator_Operations Was Unchanged" << std::endl;
    else
    {
        std::cout << "For_Operator_Operations Was Changed" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }

    Copy *= For_Operator_Operations;

    Testing_For_Error = Testing(Copy, -393.75, -262.5, -131.25, -13.125, 0.0, 13.125, 131.25, 262.5, 393.75);

    if (Testing_For_Error == 0)
        std::cout << "Operator Overload for '*=' A Matrix3x3 Works Properly" << std::endl;
    else
    {
        std::cout << "Operator Overload for '*=' A Matrix3x3 Does Not Work Properly" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }

    Testing_For_Error = Testing(For_Operator_Operations, -7.5, -5.0, -2.5, -0.25, 0.0, 0.25, 2.5 , 5.0, 7.5);

    if (Testing_For_Error == 0)
        std::cout << "For_Operator_Operations Was Unchanged" << std::endl;
    else
    {
        std::cout << "For_Operator_Operations Was Changed" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }

    Copy -= For_Operator_Operations;

    Testing_For_Error = Testing(Copy, -386.25, -257.5, -128.75, -12.875, 0.0, 12.875, 128.75, 257.5, 386.25);

    if (Testing_For_Error == 0)
        std::cout << "Operator Overload for '-=' A Matrix3x3 Works Properly" << std::endl;
    else
    {
        std::cout << "Operator Overload for '-=' A Matrix3x3 Does Not Work Properly" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }

    Testing_For_Error = Testing(For_Operator_Operations, -7.5, -5.0, -2.5, -0.25, 0.0, 0.25, 2.5 , 5.0, 7.5);

    if (Testing_For_Error == 0)
        std::cout << "For_Operator_Operations Was Unchanged" << std::endl;
    else
    {
        std::cout << "For_Operator_Operations Was Changed" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }

    Vectors For_Multipling(-1.25, 1.25, 5.0);

    Vectors Product_of_Matrix_and_Vectors = Copy * For_Multipling;

    Testing_For_Error = Testing(Product_of_Matrix_and_Vectors, -482.8125, 80.46875, 2092.1875);

    if (Testing_For_Error == 0)
        std::cout << "Operator Overload for '*' by Vectors Works Properly" << std::endl;
    else
    {
        std::cout << "Operator Overload for '*' by Vectors Does Not Work Properly" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }

    Testing_For_Error = Testing(For_Multipling, -1.25, 1.25, 5.0);

    if (Testing_For_Error == 0)
        std::cout << "For_Multipling Was Unchanged" << std::endl;
    else
    {
        std::cout << "For_Multipling Was Changed" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }

    Testing_For_Error = Testing(Copy, -386.25, -257.5, -128.75, -12.875, 0.0, 12.875, 128.75, 257.5, 386.25);

    if (Testing_For_Error == 0)
        std::cout << "Copy Matrix Was Unchanged" << std::endl;
    else
    {
        std::cout << "Copy Matrix Was Changed" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }

    Matrix3x3 Subtracted = Copy - 4.5;

    Testing_For_Error = Testing(Subtracted, -390.75, -262.0, -133.25, -17.375, -4.5, 8.375, 124.25, 253.0, 381.75);

    if (Testing_For_Error == 0)
        std::cout << "Operator Overload for '-' A Number Works Properly" << std::endl;
    else
    {
        std::cout << "Operator Overload for '-' A Number Does Not Work Properly" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }

    Testing_For_Error = Testing(Copy, -386.25, -257.5, -128.75, -12.875, 0.0, 12.875, 128.75, 257.5, 386.25);

    if (Testing_For_Error == 0)
        std::cout << "Orginal Matrix Was Unchanged" << std::endl;
    else
    {
        std::cout << "Orginal Matrix Was Changed" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }

    Matrix3x3 Added = Copy + 4.5;

    Testing_For_Error = Testing(Added, -381.75, -253.0, -124.25, -8.375, 4.5, 17.375, 133.25, 262.0, 390.75);

    if (Testing_For_Error == 0)
        std::cout << "Operator Overload for '+' A Number Works Properly" << std::endl;
    else
    {
        std::cout << "Operator Overload for '+' A Number Does Not Work Properly" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }

    Testing_For_Error = Testing(Copy, -386.25, -257.5, -128.75, -12.875, 0.0, 12.875, 128.75, 257.5, 386.25);

    if (Testing_For_Error == 0)
        std::cout << "Orginal Matrix Was Unchanged" << std::endl;
    else
    {
        std::cout << "Orginal Matrix Was Changed" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }

    Matrix3x3 Multiplied = Copy * 0.25;

    Testing_For_Error = Testing(Multiplied, -96.5625, -64.375, -32.1875, -3.21875, 0.0, 3.21875, 32.1875, 64.375, 96.5625);

    if (Testing_For_Error == 0)
        std::cout << "Operator Overload for '*' A Number Works Properly" << std::endl;
    else
    {
        std::cout << "Operator Overload for '*' A Number Does Not Work Properly" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }

    Testing_For_Error = Testing(Copy, -386.25, -257.5, -128.75, -12.875, 0.0, 12.875, 128.75, 257.5, 386.25);

    if (Testing_For_Error == 0)
        std::cout << "Orginal Matrix Was Unchanged" << std::endl;
    else
    {
        std::cout << "Orginal Matrix Was Changed" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }

    Matrix3x3 Divided = Copy / 4.0;

    Testing_For_Error = Testing(Divided, -96.5625, -64.375, -32.1875, -3.21875, 0.0, 3.21875, 32.1875, 64.375, 96.5625);

    if (Testing_For_Error == 0)
        std::cout << "Operator Overload for '/' A Number Works Properly" << std::endl;
    else
    {
        std::cout << "Operator Overload for '/' A Number Does Not Work Properly" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }

    Testing_For_Error = Testing(Copy, -386.25, -257.5, -128.75, -12.875, 0.0, 12.875, 128.75, 257.5, 386.25);

    if (Testing_For_Error == 0)
        std::cout << "Orginal Matrix Was Unchanged" << std::endl;
    else
    {
        std::cout << "Orginal Matrix Was Changed" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }

    Copy -= 4.05;

    Testing_For_Error = Testing(Copy, -390.3, -261.55, -132.8, -16.925, -4.05, 8.825, 124.7, 253.45, 382.2);

    if (Testing_For_Error == 0)
        std::cout << "Operator Overload for '-=' A Number Works Properly" << std::endl;
    else
    {
        std::cout << "Operator Overload for '-=' A Number Does Not Work Properly" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }

    Copy += 0.05;

    Testing_For_Error = Testing(Copy, -390.25, -261.50, -132.75, -16.875, -4.0, 8.875, 124.75, 253.5, 382.25);

    if (Testing_For_Error == 0)
        std::cout << "Operator Overload for '+=' A Number Works Properly" << std::endl;
    else
    {
        std::cout << "Operator Overload for '+=' A Number Does Not Work Properly" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }

    Copy *= 0.05;

    Testing_For_Error = Testing(Copy, -19.5125, -13.075, -6.6375, -0.84375, -0.2, 0.44375, 6.2375, 12.675, 19.1125);

    if (Testing_For_Error == 0)
        std::cout << "Operator Overload for '*=' A Number Works Properly" << std::endl;
    else
    {
        std::cout << "Operator Overload for '*=' A Number Does Not Work Properly" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }

    Copy /= -2.0;

    Testing_For_Error = Testing(Copy, 9.75625, 6.5375, 3.31875, 0.421875, 0.1, -0.221875, -3.11875, -6.3375, -9.55625);

    if (Testing_For_Error == 0)
        std::cout << "Operator Overload for '/=' A Number Works Properly" << std::endl;
    else
    {
        std::cout << "Operator Overload for '/=' A Number Does Not Work Properly" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }

    Copy.Transpose_Matrix();

    Testing_For_Error = Testing(Copy, 9.75625, 0.421875, -3.11875, 6.5375, 0.1, -6.3375, 3.31875, -0.221875, -9.55625);

    if (Testing_For_Error == 0)
        std::cout << "Transpose Matrix Function Works Properly" << std::endl;
    else
    {
        std::cout << "Transpose Matrix Function Does Not Work Properly" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }

    Matrix3x3 For_Determinat_and_Inverse(2.0, 1.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0);

    double Determinant = For_Determinat_and_Inverse.Get_Determinant();
    Testing_For_Error = Testing(Determinant, -9.0);

    if (Testing_For_Error == 0)
        std::cout << "Determinant Function Works Properly" << std::endl;
    else
    {
        std::cout << "Determinant Function Does Not Work Properly" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }

    Testing_For_Error = Testing(For_Determinat_and_Inverse, 2.0, 1.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0);
    if (Testing_For_Error == 0)
        std::cout << "Orginal Matrix Was Unchanged" << std::endl;
    else
    {
        std::cout << "Orginal Matrix Was Changed" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }

    For_Determinat_and_Inverse.Inverse_Matrix();

    Testing_For_Error = Testing(For_Determinat_and_Inverse, (1.0/3.0), (-5.0/3.0), (1.0), (-2.0/3.0), (1.0/3.0),(0.0), (1.0/3.0), (1.0), (-2.0/3.0) );

    if (Testing_For_Error == 0)
        std::cout << "Inverse Matrix Function Works Properly" << std::endl;
    else
    {
        std::cout << "Inverse Matrix Function Does Not Work Properly" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }

    Matrix3x3 X_Rotation;
    X_Rotation.Initialise_As_Rotation_Matrix(45.0, 'x');

    Testing_For_Error = Testing(X_Rotation, 1.0, 0.0, 0.0, 0.0, (1.0/sqrt(2)), (-1.0/sqrt(2)), 0.0, (1.0/sqrt(2)), (1.0/sqrt(2)) );

    if (Testing_For_Error == 0)
        std::cout << "Initialise As Rotation Matrix 'x' Function Works Properly" << std::endl;
    else
    {
        std::cout << "Initialise As Rotation Matrix 'x' Does Not Work Properly" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }

    Matrix3x3 Y_Rotation;
    Y_Rotation.Initialise_As_Rotation_Matrix(90.0, 'y');

    Testing_For_Error = Testing(Y_Rotation, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0, -1.0, 0.0, 0.0);

    if (Testing_For_Error == 0)
        std::cout << "Initialise As Rotation Matrix 'y' Function Works Properly" << std::endl;
    else
    {
        std::cout << "Initialise As Rotation Matrix 'y' Does Not Work Properly" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }

    Matrix3x3 Z_Rotation;
    Z_Rotation.Initialise_As_Rotation_Matrix(135.0, 'z');

    Testing_For_Error = Testing(Z_Rotation, (-1.0/sqrt(2)), (-1.0/sqrt(2)), 0.0, (1.0/sqrt(2)), (-1.0/sqrt(2)), 0.0, 0.0, 0.0, 1.0);

    if (Testing_For_Error == 0)
        std::cout << "Initialise As Rotation Matrix 'z' Function Works Properly" << std::endl;
    else
    {
        std::cout << "Initialise As Rotation Matrix 'z' Does Not Work Properly" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }

    std::cout << "************************" << std::endl;
    if (Error == 0 )
        std::cout << "End of Test: Success" << std::endl;
    else
        std::cout << "End of Test: Failure" << std::endl;
    std::cout << "************************" << std::endl;

    return (Error == 0) ? 0 : 1;
};
