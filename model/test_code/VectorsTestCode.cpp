//
//  VectorsTestCode.cpp
//  Computing Project
//
//  Created by Jedidiah Paterson on 27/11/2019.
//  Copyright @ 2019 Jedidiah Paterson. All rights reserved.
//  This File contains a suitable test for all functions declared
//  in the "Vectors.h" header file. The correct way to implement
//  the functions is demonstrated in this test file.
//

#include <iostream>
#include "Vectors.h"

template <class T>
unsigned int Testing (T aVectors,  T bVectors)
{
  return (aVectors==bVectors) ? 0 : 1;
}

template <class T, class U>
unsigned int Testing (T aVectors,  U X, U Y, U  Z)
{
    unsigned int Error = 0;
    if (aVectors.GetXVector() != X)
        Error++;
    if (aVectors.GetYVector() != Y)
        Error++;
    if (aVectors.GetZVector() != Z)
        Error++;
    return (Error==0) ? 0 : 1;

}
int main()
{
    unsigned int Testing_For_Error = 0;
    //Testing Constructors and Get functions
    Vectors Test;
    Testing_For_Error = Testing(Test, 0., 0., 0.);

    Vectors Test_1(1.0);
    Testing_For_Error = Testing(Test_1, 1.0, 0., 0.);

    Vectors Test_2(1.25, 5);
    Testing_For_Error = Testing(Test_2, 1.25, 5., 0.);

    Vectors Test_3(1.25, 5, -12.3);
    Testing_For_Error = Testing(Test_3, 1.25, 5., -12.3);
    //Testing Set Functions
    Vectors Test_4;
    Test_4.SetX_Vector(7);
    Test_4.SetY_Vector(8);
    Test_4.SetZ_Vector(9);
    Testing_For_Error = Testing(Test_4, 7., 8., 9.);
    //Testing operator=
    Test = Test_4;
    Testing_For_Error = Testing(Test, Test_4);
    //Testing operator+
    Vectors Test_5 = Test + Test_4;
    Testing_For_Error = Testing(Test_5, 14., 16., 18.);

    //Need to ensure that both Test and Test_4 were unchanged
    Testing_For_Error = Testing(Test, 7.,8.,9.);
    Testing_For_Error = Testing(Test_4, 7.,8.,9.);

    //Testing operator-
    Vectors Test_6 = Test_4 - Test;
    Testing_For_Error = Testing(Test_6, 7., 8., 9.);

    //Need to ensure that both Test and Test_4 were unchanged
    Testing_For_Error = Testing(Test, 7.,8.,9.);
    Testing_For_Error = Testing(Test_4, 7.,8.,9.);

    //Testing operator/
    Vectors Test_7 = Test_6/7;
    Testing_For_Error = Testing(Test_7, (7/7), (8/7), (9/7));

    //Need to ensure that Test_6 was unchanged
    Testing_For_Error = Testing(Test_6, 7.,8.,9.);

    //Testing operator*
    Vectors Test_8 = Test_7*7;
    Testing_For_Error = Testing(Test_8, 7., 8., 9.);

    //Need to ensure that Test_7 was unchanged
    Testing_For_Error = Testing(Test_7, (7/7), (8/7), (9/7));

    //Testing operator* (Vectors by Vectors) ie cross product
    Vectors Test_9 = Test_8 * Test_6;
    Testing_For_Error = Testing(Test_9, 0.,0.,0.);

    //Need to ensure that both Test_8 and Test_6 were unchanged
    Testing_For_Error = Testing(Test_6, 7., 8., 9.);
    Testing_For_Error = Testing(Test_8, 7., 8., 9.);

    //Testing Scalar_Product
    double Scalar_Result = Test_6.Scalar_Product(Test_8);
    Testing_For_Error = Testing(Scalar_Result, 194.);

    //Need to ensure that both Test_8 and Test_6 were unchanged
    Testing_For_Error = Testing(Test_6, 7., 8., 9.);
    Testing_For_Error = Testing(Test_8, 7., 8., 9.);

    //Tesing Get_Magnitude
    Vectors Test_10(10,10,5);
    double Magnitude = Test_10.Get_Magnitude();
    Testing_For_Error = Testing(Magnitude, 15.);

    //Need to ensure that Test_10 was unchanged
    Testing_For_Error = Testing(Test_10, 10.,10.,5.);

    //Testing Get_Distance_To
    Vectors Test_11(2,10,5);
    double Distance = Test_10.Get_Distance_To(Test_11);
    Testing_For_Error = Testing(Distance,8.);

    //Need to ensure that Test_10 and Test_11 were unchanged
    Testing_For_Error = Testing(Test_10, 10.,10.,5.);
    Testing_For_Error = Testing(Test_11, 2.,10.,5.);

    //Testing Divide by 0 check
    //This need to produce an error
    //current returns the object being divided
    Vectors Test_12 =  Test/0;
    Testing_For_Error = Testing(Test_12, 7., 8., 9.);

    return (Testing_For_Error == 0) ? 0 : 1;
}
