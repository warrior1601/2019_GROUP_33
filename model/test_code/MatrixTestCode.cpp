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

int main()
{
<<<<<<< HEAD
        std::cout << "------------------------------Matrix.hpp Test Code------------------------------" << std::endl;
=======
	std::cout << "------------------------------Matrix.hpp Test Code------------------------------" << std::endl;
>>>>>>> pr/43

    Matrix3x3 BlankMatrix;
    std::cout << "Blank constructor and cout\n" << BlankMatrix << std::endl;



    BlankMatrix.Set_Matrix_Data_1(1);
    BlankMatrix.Set_Matrix_Data_2(2);
    BlankMatrix.Set_Matrix_Data_3(3);
    BlankMatrix.Set_Matrix_Data_4(4);
    BlankMatrix.Set_Matrix_Data_5(5);
    BlankMatrix.Set_Matrix_Data_6(6);
    BlankMatrix.Set_Matrix_Data_7(7);
    BlankMatrix.Set_Matrix_Data_8(8);
    BlankMatrix.Set_Matrix_Data_9(9);



    std::cout << "Set and get functions\n" << BlankMatrix.Get_Matrix_Data_1() << "\t" << BlankMatrix.Get_Matrix_Data_2() << "\t" << BlankMatrix.Get_Matrix_Data_3() << std::endl;
    std::cout << BlankMatrix.Get_Matrix_Data_4() << "\t" << BlankMatrix.Get_Matrix_Data_5() << "\t" << BlankMatrix.Get_Matrix_Data_6() << std::endl;
    std::cout << BlankMatrix.Get_Matrix_Data_7() << "\t" << BlankMatrix.Get_Matrix_Data_8() << "\t" << BlankMatrix.Get_Matrix_Data_9() << std::endl;



    Matrix3x3 CopyConstructor(BlankMatrix);
    std::cout << "\nCopy constructor\n" << CopyConstructor << std::endl;

    Matrix3x3 someMatrix(9,8,7,6,5,4,3,2,1);
    std::cout << "Non blank constructor\n" << someMatrix << std::endl;



    Matrix3x3 OutputMatrix = someMatrix + BlankMatrix;
    std::cout << "\nMatrix addition (and operator=)\n" << OutputMatrix << std::endl;
    if (OutputMatrix.Get_Matrix_Data_1() != 10 || OutputMatrix.Get_Matrix_Data_2() != 10 || OutputMatrix.Get_Matrix_Data_3() != 10 ||
        OutputMatrix.Get_Matrix_Data_4() != 10 || OutputMatrix.Get_Matrix_Data_5() != 10 || OutputMatrix.Get_Matrix_Data_6() != 10 ||
        OutputMatrix.Get_Matrix_Data_7() != 10 || OutputMatrix.Get_Matrix_Data_8() != 10 || OutputMatrix.Get_Matrix_Data_9() != 10
        )
    {
        std::cout << "operator+ with another Matrix3x3 failed" << std::endl;
        exit(1);
    }

    OutputMatrix = someMatrix - BlankMatrix;
    std::cout << "Matrix subtraction\n" << OutputMatrix << std::endl;
    if (OutputMatrix.Get_Matrix_Data_1() != 8 || OutputMatrix.Get_Matrix_Data_2() != 6 || OutputMatrix.Get_Matrix_Data_3() != 4 ||
        OutputMatrix.Get_Matrix_Data_4() != 2 || OutputMatrix.Get_Matrix_Data_5() != 0 || OutputMatrix.Get_Matrix_Data_6() != -2 ||
        OutputMatrix.Get_Matrix_Data_7() != -4 || OutputMatrix.Get_Matrix_Data_8() != -6 || OutputMatrix.Get_Matrix_Data_9() != -8
        )
    {
        std::cout << "operator- with another Matrix3x3 failed" << std::endl;
        exit(2);
    }

    OutputMatrix = someMatrix * BlankMatrix;
    std::cout << "Matrix multiplication\n" << OutputMatrix << std::endl;
    if (OutputMatrix.Get_Matrix_Data_1() != 90 || OutputMatrix.Get_Matrix_Data_2() != 114 || OutputMatrix.Get_Matrix_Data_3() != 138 ||
        OutputMatrix.Get_Matrix_Data_4() != 54 || OutputMatrix.Get_Matrix_Data_5() != 69 || OutputMatrix.Get_Matrix_Data_6() != 84 ||
        OutputMatrix.Get_Matrix_Data_7() != 18 || OutputMatrix.Get_Matrix_Data_8() != 24 || OutputMatrix.Get_Matrix_Data_9() != 30
        )
    {
        std::cout << "operator* with another Matrix3x3 failed" << std::endl;
        exit(3);
    }

    BlankMatrix += someMatrix;
    std::cout << "Matrix addition using +=\n" << BlankMatrix << std::endl;
    if (BlankMatrix.Get_Matrix_Data_1() != 10 || BlankMatrix.Get_Matrix_Data_2() != 10 || BlankMatrix.Get_Matrix_Data_3() != 10 ||
        BlankMatrix.Get_Matrix_Data_4() != 10 || BlankMatrix.Get_Matrix_Data_5() != 10 || BlankMatrix.Get_Matrix_Data_6() != 10 ||
        BlankMatrix.Get_Matrix_Data_7() != 10 || BlankMatrix.Get_Matrix_Data_8() != 10 || BlankMatrix.Get_Matrix_Data_9() != 10
        )
    {
        std::cout << "operator+= with another Matrix3x3 failed" << std::endl;
        exit(4);
    }

    BlankMatrix -= someMatrix;
    std::cout << "Matrix subtraction using -=\n" << BlankMatrix << std::endl;
    if (BlankMatrix.Get_Matrix_Data_1() != 1 || BlankMatrix.Get_Matrix_Data_2() != 2 || BlankMatrix.Get_Matrix_Data_3() != 3 ||
        BlankMatrix.Get_Matrix_Data_4() != 4 || BlankMatrix.Get_Matrix_Data_5() != 5 || BlankMatrix.Get_Matrix_Data_6() != 6 ||
        BlankMatrix.Get_Matrix_Data_7() != 7 || BlankMatrix.Get_Matrix_Data_8() != 8 || BlankMatrix.Get_Matrix_Data_9() != 9
        )
    {
        std::cout << "operator-= with another Matrix3x3 failed" << std::endl;
        exit(5);
    }

    BlankMatrix *= someMatrix;
    std::cout << "Matrix multiplication using *=\n" << BlankMatrix << std::endl;
    if (BlankMatrix.Get_Matrix_Data_1() != 30 || BlankMatrix.Get_Matrix_Data_2() != 24 || BlankMatrix.Get_Matrix_Data_3() != 18 ||
        BlankMatrix.Get_Matrix_Data_4() != 84 || BlankMatrix.Get_Matrix_Data_5() != 69 || BlankMatrix.Get_Matrix_Data_6() != 54 ||
        BlankMatrix.Get_Matrix_Data_7() != 138 || BlankMatrix.Get_Matrix_Data_8() != 114 || BlankMatrix.Get_Matrix_Data_9() != 90
        )
    {
        std::cout << "operator*= with another Matrix3x3 failed" << std::endl;
        exit(7);
    }



    Vectors someVector(1,2,3);
    Vectors OutputVectors = someMatrix * someVector;
    std::cout << "\nMatrix and Vectors multiplication\n" << OutputVectors << std::endl;
    if (OutputVectors.GetXVector() != 46 || OutputVectors.GetYVector() != 28 || OutputVectors.GetZVector() != 10)
    {
        std::cout << "operator* with a vectors failed" << std::endl;
        exit(8);
    }



    OutputMatrix = someMatrix + 10;
    std::cout << "\nMatrix addition with a number\n" << OutputMatrix << std::endl;
    if (OutputMatrix.Get_Matrix_Data_1() != 19 || OutputMatrix.Get_Matrix_Data_2() != 18 || OutputMatrix.Get_Matrix_Data_3() != 17 ||
        OutputMatrix.Get_Matrix_Data_4() != 16 || OutputMatrix.Get_Matrix_Data_5() != 15 || OutputMatrix.Get_Matrix_Data_6() != 14 ||
        OutputMatrix.Get_Matrix_Data_7() != 13 || OutputMatrix.Get_Matrix_Data_8() != 12 || OutputMatrix.Get_Matrix_Data_9() != 11
        )
    {
        std::cout << "operator+ with a scalar failed" << std::endl;
        exit(9);
    }

    OutputMatrix = someMatrix - 10;
    std::cout << "Matrix subtraction with a number\n" << OutputMatrix << std::endl;
    if (OutputMatrix.Get_Matrix_Data_1() != -1 || OutputMatrix.Get_Matrix_Data_2() != -2 || OutputMatrix.Get_Matrix_Data_3() != -3 ||
        OutputMatrix.Get_Matrix_Data_4() != -4 || OutputMatrix.Get_Matrix_Data_5() != -5 || OutputMatrix.Get_Matrix_Data_6() != -6 ||
        OutputMatrix.Get_Matrix_Data_7() != -7 || OutputMatrix.Get_Matrix_Data_8() != -8 || OutputMatrix.Get_Matrix_Data_9() != -9
        )
    {
        std::cout << "operator- with a scalar failed" << std::endl;
        exit(10);
    }

    OutputMatrix = someMatrix * 10;
    std::cout << "Matrix multiplication with a number\n" << OutputMatrix << std::endl;
    if (OutputMatrix.Get_Matrix_Data_1() != 90 || OutputMatrix.Get_Matrix_Data_2() != 80 || OutputMatrix.Get_Matrix_Data_3() != 70 ||
        OutputMatrix.Get_Matrix_Data_4() != 60 || OutputMatrix.Get_Matrix_Data_5() != 50 || OutputMatrix.Get_Matrix_Data_6() != 40 ||
        OutputMatrix.Get_Matrix_Data_7() != 30 || OutputMatrix.Get_Matrix_Data_8() != 20 || OutputMatrix.Get_Matrix_Data_9() != 10
        )
    {
        std::cout << "operator* with a scalar failed" << std::endl;
        exit(11);
    }

    OutputMatrix = someMatrix / 10;
    std::cout << "Matrix division with a number\n" << OutputMatrix << std::endl;
    if (OutputMatrix.Get_Matrix_Data_1() != 0.9 || OutputMatrix.Get_Matrix_Data_2() != 0.8 || OutputMatrix.Get_Matrix_Data_3() != 0.7 ||
        OutputMatrix.Get_Matrix_Data_4() != 0.6 || OutputMatrix.Get_Matrix_Data_5() != 0.5 || OutputMatrix.Get_Matrix_Data_6() != 0.4 ||
        OutputMatrix.Get_Matrix_Data_7() != 0.3 || OutputMatrix.Get_Matrix_Data_8() != 0.2 || OutputMatrix.Get_Matrix_Data_9() != 0.1
        )
    {
        std::cout << "operator/ with a scalar failed" << std::endl;
        exit(12);
    }

    someMatrix += 10;
    std::cout << "Matrix addition with a number using +=\n" << someMatrix << std::endl;
    if (someMatrix.Get_Matrix_Data_1() != 19 || someMatrix.Get_Matrix_Data_2() != 18 || someMatrix.Get_Matrix_Data_3() != 17 ||
        someMatrix.Get_Matrix_Data_4() != 16 || someMatrix.Get_Matrix_Data_5() != 15 || someMatrix.Get_Matrix_Data_6() != 14 ||
        someMatrix.Get_Matrix_Data_7() != 13 || someMatrix.Get_Matrix_Data_8() != 12 || someMatrix.Get_Matrix_Data_9() != 11
        )
    {
        std::cout << "operator+= with a scalar failed" << std::endl;
        exit(11);
    }

    someMatrix -= 10;
    std::cout << "Matrix subtraction with a number using -=\n" << someMatrix << std::endl;
    if (someMatrix.Get_Matrix_Data_1() != 9 || someMatrix.Get_Matrix_Data_2() != 8 || someMatrix.Get_Matrix_Data_3() != 7 ||
        someMatrix.Get_Matrix_Data_4() != 6 || someMatrix.Get_Matrix_Data_5() != 5 || someMatrix.Get_Matrix_Data_6() != 4 ||
        someMatrix.Get_Matrix_Data_7() != 3 || someMatrix.Get_Matrix_Data_8() != 2 || someMatrix.Get_Matrix_Data_9() != 1
        )
    {
        std::cout << "operator-= with a scalar failed" << std::endl;
        exit(11);
    }

    someMatrix *= 10;
    std::cout << "Matrix multiplication with a number using *=\n" << someMatrix << std::endl;
    if (someMatrix.Get_Matrix_Data_1() != 90 || someMatrix.Get_Matrix_Data_2() != 80 || someMatrix.Get_Matrix_Data_3() != 70 ||
        someMatrix.Get_Matrix_Data_4() != 60 || someMatrix.Get_Matrix_Data_5() != 50 || someMatrix.Get_Matrix_Data_6() != 40 ||
        someMatrix.Get_Matrix_Data_7() != 30 || someMatrix.Get_Matrix_Data_8() != 20 || someMatrix.Get_Matrix_Data_9() != 10
        )
    {
        std::cout << "operator*= with a scalar failed" << std::endl;
        exit(11);
    }

    someMatrix /= 10;
    std::cout << "Matrix division with a number using /=\n" << someMatrix << std::endl;
    if (someMatrix.Get_Matrix_Data_1() != 9 || someMatrix.Get_Matrix_Data_2() != 8 || someMatrix.Get_Matrix_Data_3() != 7 ||
        someMatrix.Get_Matrix_Data_4() != 6 || someMatrix.Get_Matrix_Data_5() != 5 || someMatrix.Get_Matrix_Data_6() != 4 ||
        someMatrix.Get_Matrix_Data_7() != 3 || someMatrix.Get_Matrix_Data_8() != 2 || someMatrix.Get_Matrix_Data_9() != 1
        )
    {
        std::cout << "operator/= with a scalar failed" << std::endl;
        exit(11);
    }



    BlankMatrix.Initialise_As_Rotation_Matrix(90, 'y');
    std::cout << "\nInitialising a matrix as a rotation matrix\n" << BlankMatrix << std::endl;
    if (BlankMatrix.Get_Matrix_Data_1() != 0 || BlankMatrix.Get_Matrix_Data_2() != 0 || BlankMatrix.Get_Matrix_Data_3() != 1 ||
        BlankMatrix.Get_Matrix_Data_4() != 0 || BlankMatrix.Get_Matrix_Data_5() != 1 || BlankMatrix.Get_Matrix_Data_6() != 0 ||
        BlankMatrix.Get_Matrix_Data_7() != -1 || BlankMatrix.Get_Matrix_Data_8() != 0 || BlankMatrix.Get_Matrix_Data_9() != 0
        )
    {
        std::cout << "Initialise_As_Rotation_Matrix() failed" << std::endl;
        exit(17);
    }

    Matrix3x3 anotherMatrix(1,2,3,4,5,5,6,7,8);
    anotherMatrix.Transpose_Matrix();
    std::cout << "\nTransposing a matrix\n" << anotherMatrix << std::endl;
    if (anotherMatrix.Get_Matrix_Data_1() != 1 || anotherMatrix.Get_Matrix_Data_2() != 4 || anotherMatrix.Get_Matrix_Data_3() != 6 ||
        anotherMatrix.Get_Matrix_Data_4() != 2 || anotherMatrix.Get_Matrix_Data_5() != 5 || anotherMatrix.Get_Matrix_Data_6() != 7 ||
        anotherMatrix.Get_Matrix_Data_7() != 3 || anotherMatrix.Get_Matrix_Data_8() != 5 || anotherMatrix.Get_Matrix_Data_9() != 8
        )
    {
        std::cout << "Transpose_Matrix() failed" << std::endl;
        exit(18);
    }

    std::cout << "\nDeterminant of matrix = " << anotherMatrix.Get_Determinant() << std::endl;
    if (anotherMatrix.Get_Determinant() != -5)
    {
        std::cout << "Get_Determinant() failed" << std::endl;
        exit(19);
    }

    anotherMatrix.Inverse_Matrix();
    std::cout << "\nInverse of a matrix\n" << anotherMatrix << std::endl;
    if (anotherMatrix.Get_Matrix_Data_1() != -1 || anotherMatrix.Get_Matrix_Data_2() != 0.4 || anotherMatrix.Get_Matrix_Data_3() != 0.4 ||
        anotherMatrix.Get_Matrix_Data_4() != -1 || anotherMatrix.Get_Matrix_Data_5() != 2 || anotherMatrix.Get_Matrix_Data_6() != -1 ||
        anotherMatrix.Get_Matrix_Data_7() != 1 || anotherMatrix.Get_Matrix_Data_8() != -1.4 || anotherMatrix.Get_Matrix_Data_9() != 0.6
        )
    {
        std::cout << "Inverse_Matrix() failed" << std::endl;
        exit(20);
    }

    return 0;
}
