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

#include "Material.h"
#include "Vectors.h"
#include "Matrix.hpp"
#include "Cell.hpp"

int main()
{
	std::cout << "------------------------------Matrix.hpp Test Code------------------------------" << std::endl;
    
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
    
    OutputMatrix = someMatrix - BlankMatrix;
    std::cout << "Matrix subtraction\n" << OutputMatrix << std::endl;
    
    OutputMatrix = someMatrix * BlankMatrix;
    std::cout << "Matrix multiplication\n" << OutputMatrix << std::endl;
    
    BlankMatrix += someMatrix;
    std::cout << "Matrix addition using +=\n" << BlankMatrix << std::endl;
    
    BlankMatrix -= someMatrix;
    std::cout << "Matrix subtraction using -=\n" << BlankMatrix << std::endl;
    
    BlankMatrix *= someMatrix;
    std::cout << "Matrix multiplication using *=\n" << BlankMatrix << std::endl;
    
    
    Vectors someVector(1,2,3);
    Vectors OutputVectors = someMatrix * someVector;
    std::cout << "\nMatrix and Vectors multiplication\n" << OutputVectors << std::endl;
    
    
    OutputMatrix = someMatrix + 10;
    std::cout << "\nMatrix addition with a number\n" << OutputMatrix << std::endl;
    
    OutputMatrix = someMatrix - 10;
    std::cout << "Matrix subtraction with a number\n" << OutputMatrix << std::endl;
    
    OutputMatrix = someMatrix * 10;
    std::cout << "Matrix multiplication with a number\n" << OutputMatrix << std::endl;
    
    OutputMatrix = someMatrix / 10;
    std::cout << "Matrix division with a number\n" << OutputMatrix << std::endl;

    someMatrix += 10;
    std::cout << "Matrix addition with a number using +=\n" << someMatrix << std::endl;
    
    someMatrix -= 10;
    std::cout << "Matrix subtraction with a number using -=\n" << someMatrix << std::endl;
    
    someMatrix *= 10;
    std::cout << "Matrix multiplication with a number using *=\n" << someMatrix << std::endl;
    
    someMatrix /= 10;
    std::cout << "Matrix division with a number using /=\n" << someMatrix << std::endl;
    
    
    BlankMatrix.Initialise_As_Rotation_Matrix(90, 'y');
    std::cout << "\nInitialising a matrix as a rotation matrix\n" << BlankMatrix << std::endl;
    
    Matrix3x3 anotherMatrix(1,2,3,4,5,5,6,7,8);
    anotherMatrix.Transpose_Matrix();
    std::cout << "\nTransposing a matrix\n" << anotherMatrix << std::endl;
    
    std::cout << "\nDeterminant of matrix = " << anotherMatrix.Get_Determinant() << std::endl;
    
    anotherMatrix.Inverse_Matrix();
    std::cout << "\nInverse of a matrix\n" << anotherMatrix << std::endl;
    
    return 0;
}
