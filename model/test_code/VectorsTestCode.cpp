//
//  VectorsTestCode.cpp
//  Computing Project
//
//  Created by Jedidiah Paterson on 27/11/2019.
//  Copyright � 2019 Jedidiah Paterson. All rights reserved.
//  This File contains a suitable test for all functions declared
//  in the "Vectors.h" header file. The correct way to implement
//  the functions is demonstrated in this test file.
//

#include <iostream>
#include "Vectors.h"

int main()
{
    Vectors Test;
    std::cout << "Blank Constructor" << std::endl;
    std::cout << Test << std::endl;

    Vectors Test_1(1);
    std::cout << "X Only Constructor" << std::endl;
    std::cout << Test_1 << std::endl;

    Vectors Test_2(1,2);
    std::cout << "X and Y Only Constructor" << std::endl;
    std::cout << Test_2 << std::endl;

    Vectors Test_3(1, 2, 3);
    std::cout << "X, Y, and Z Constructor" << std::endl;
    std::cout << Test_3 << std::endl;

    Test.SetVector(4,5,6);
    std::cout << "X, Y, and Z Set Function" << std::endl;
    std::cout << Test << std::endl;
    
    Vectors Test_4;
    Test_4.SetX_Vector(7);
    Test_4.SetY_Vector(8);
    Test_4.SetZ_Vector(9);
    std::cout << "Set Functions Individual Test" << std::endl;
    std::cout << Test_4 << std::endl;

    double X = Test_4.GetXVector();
    double Y = Test_4.GetYVector();
    double Z = Test_4.GetZVector();
    std::cout << "Testing Get Functions" << std::endl;
    std::cout << "X = " << X << " Y = " << Y << " Z = " << Z << std::endl;

    std::cout << "Testing operator = " << std::endl;
    std::cout << Test << std::endl;
    std::cout << Test_4 << std::endl;
    std::cout << "This Sets the First Vector Equal To The Second Vector" << std::endl;
    Test = Test_4;
    std::cout << Test << std::endl;


    std::cout << "Testing operator +" << std::endl;
    std::cout << Test << std::endl;
    std::cout << Test_4 << std::endl;
    std::cout << "Add Together The Two Vectors Above" << std::endl;
    Test_2 = Test + Test_4;
    std::cout << Test_2 << std::endl;

    std::cout << "Testing operator -" << std::endl;
    std::cout << Test_4 << std::endl;
    std::cout << Test_2 << std::endl;
    std::cout << "Subtract The Two Vectors Above" << std::endl;
    Test_3 = Test_4 - Test_2;
    std::cout << Test_3 << std::endl;

    std::cout << "Testing Dividing By A Number" << std::endl;
    std::cout << Test_4 << std::endl;
    std::cout << "Divide Above By 7" << std::endl;
    Test_2 = (Test_4/7);
    std::cout << Test_2 << std::endl;

    std::cout << "Testing Multiplying By A Number" << std::endl;
    std::cout << Test_2 << std::endl;
    std::cout << "Multiply Above By 7" << std::endl;
    Test_2 = Test_2*7;
    std::cout << Test_2 << std::endl;

    std::cout << "Cross Product Polymorphism" << std::endl;
    Test_3.SetVector(4,5,6);
    std::cout << Test_4 << Test_3 << std::endl;
    std::cout << "Below is the Cross Product of the Above Two" << std::endl;
    Test_2 = Test_4 * Test_3;
    std::cout << Test_2 << std::endl;

    std::cout << "Scalar Product Testing" << std::endl;
    std::cout << Test_3 << Test_4 << std::endl;
    std::cout << "Below is the Scalar Product of the Above Two" << std::endl;
    double Scalar = Test_3.Scalar_Product(Test_4);
    std::cout << Scalar << std::endl;

    std::cout << "Testing Divide by 0 Error Message" << std::endl;
    Test/0;

    std::cout << "Finished running Script" << std::endl;
}
