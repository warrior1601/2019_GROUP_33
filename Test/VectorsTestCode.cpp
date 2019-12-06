
#include <iostream>
#include "../Include/Vectors.h"

//
//  VectorsTestCode.cpp
//  Computing Project
//
//  Created by Jedidiah Paterson on 27/11/2019.
//  Copyright © 2019 Jedidiah Paterson. All rights reserved.
//  This File contains a suitable test for all functions declared
//  in the "Vectors.h" header file. The correct way to implement
//  the functions is demonstrated in this test file.


using namespace std;

int main()
{
    Vectors Test;
    cout<<"Blank Constructor"<<endl;
    cout<<Test<<endl;

    Vectors Test_1(1);
    cout<<"X Only Constructor"<<endl;
    cout<<Test_1<<endl;

    Vectors Test_2(1,2);
    cout<<"X and Y Only Constructor"<<endl;
    cout<<Test_2<<endl;

    Vectors Test_3(1, 2, 3);
    cout<<"X, Y, and Z Constructor"<<endl;
    cout<<Test_3<<endl;

    Test.SetVector(4,5,6);
    cout<<"X, Y, and Z Set Function"<<endl;
    cout<<Test<<endl;

    Vectors Test_4;
    Test_4.SetX_Vector(7);
    Test_4.SetY_Vector(8);
    Test_4.SetZ_Vector(9);
    cout<<"Set Functions Individual Test"<<endl;
    cout<<Test_4<<endl;

    double X = Test_4.GetXVector();
    double Y = Test_4.GetYVector();
    double Z = Test_4.GetZVector();
    cout<<"Testing Get Functions"<<endl;
    cout<<"X = "<<X<<" Y = "<<Y<<" Z = "<<Z<<endl;

    cout<<"Testing operator = " <<endl;
    cout<<Test<<endl;
    cout<<Test_4<<endl;
    cout<<"This Sets the First Vector Equal To The Second Vector"<<endl;
    Test = Test_4;
    cout<<Test<<endl;


    cout<<"Testing operator +"<<endl;
    cout<<Test<<endl;
    cout<<Test_4<<endl;
    cout<<"Add Together The Two Vectors Above"<<endl;
    Test_2 = Test + Test_4;
    cout<<Test_2<<endl;

    cout<<"Testing operator -"<<endl;
    cout<<Test_4<<endl;
    cout<<Test_2<<endl;
    cout<<"Subtract The Two Vectors Above"<<endl;
    Test_3 = Test_4 - Test_2;
    cout<<Test_3<<endl;

    cout<<"Testing Dividing By A Number"<<endl;
    cout<<Test_4<<endl;
    cout<<"Divide Above By 7"<<endl;
    Test_2 = Test_4/7;
    cout<<Test_2<<endl;

    cout<<"Testing Multiplying By A Number"<<endl;
    cout<<Test_2<<endl;
    cout<<"Multiply Above By 7"<<endl;
    Test_2 = Test_2*7;
    cout<<Test_2<<endl;

    cout<<"Cross Product Polymorphism"<<endl;
    Test_3.SetVector(4,5,6);
    cout<<Test_4<< Test_3<<endl;
    cout<<"Below is the Cross Product of the Above Two"<<endl;
    Test_2 = Test_4*Test_3;
    cout<<Test_2<<endl;

    cout<<"Scalar Product Testing"<<endl;
    cout<<Test_3 << Test_4<<endl;
    cout<<"Below is the Scalar Product of the Above Two"<<endl;
    double Scalar = Test_3.Scalar_Product(Test_4);
    cout<<Scalar<<endl;
}
