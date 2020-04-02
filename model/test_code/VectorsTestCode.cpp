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

#include <cmath>
#include <iostream>
#include "Vectors.h"
#include "Testing_File_Functions.h"

int main()
{
    unsigned int Testing_For_Error = 0;
    unsigned int Error = 0;
    //Testing Constructors and Get functions

    Vectors Test;
    Testing_For_Error = Testing(Test, 0., 0., 0.);

    if (Testing_For_Error == 0 )
        std::cout << "Blank Constructor and Get Functions Work Properly" << std::endl;
    else
    {
        std::cout << "Blank Constructor and Get Functions Do Not Working Properly" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }

    Vectors Test_1(1.0);
    Testing_For_Error = Testing(Test_1, 1.0, 0., 0.);

    if (Testing_For_Error == 0 )
        std::cout << "X Constructor Works Properly" << std::endl;
    else
    {
        std::cout << "X Constructor Does Not Work Properly" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }

    Vectors Test_2(1.25, 5);
    Testing_For_Error = Testing(Test_2, 1.25, 5., 0.);

    if (Testing_For_Error == 0 )
        std::cout << "X/Y Constructor Works Properly" << std::endl;
    else
    {
        std::cout << "X/Y Constructor Does Not Work Properly" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }

    Vectors Test_3(1.25, 5.5, -12.3);
    Testing_For_Error = Testing(Test_3, 1.25, 5.5, -12.3);

    if (Testing_For_Error == 0 )
        std::cout << "X/Y/Z Constructor Works Properly" << std::endl;
    else
    {
        std::cout << "X/Y/Z Constructor Does Not Work Properly" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }

    //Testing Set Functions
    Vectors Test_4;
    Test_4.SetX_Vector(7);
    Test_4.SetY_Vector(8);
    Test_4.SetZ_Vector(9);
    Testing_For_Error = Testing(Test_4, 7., 8., 9.);

    if (Testing_For_Error == 0 )
        std::cout << "Set Functions Work Properly" << std::endl;
    else
    {
        std::cout << "Set Functions Do Not Work Properly" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }

    //Testing operator=
    Test = Test_4;
    Testing_For_Error = Testing(Test, Test_4);

    if (Testing_For_Error == 0 )
        std::cout << "operator= Function Works Properly" << std::endl;
    else
    {
        std::cout << "operator= Function Does Not Work Properly" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }

    //Testing operator+
    Vectors Test_5 = Test + Test_4;
    Testing_For_Error = Testing(Test_5, 14., 16., 18.);

    if (Testing_For_Error == 0 )
        std::cout << "operator+ Function Works Properly" << std::endl;
    else
    {
        std::cout << "operator+ Function Does Not Work Properly" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }

    //Need to ensure that both Test and Test_4 were unchanged
    Testing_For_Error = Testing(Test, 7.,8.,9.);

    if (Testing_For_Error != 0 )
    {
        std::cout << "Vector Properties Were Changed During Operation" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }

    Testing_For_Error = Testing(Test_4, 7.,8.,9.);

    if (Testing_For_Error != 0 )
    {
        std::cout << "Vector Properties Were Changed During Operation" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }

    //Testing operator-
    Vectors Test_6 = Test_4 - Test;
    Testing_For_Error = Testing(Test_6, 0., 0., 0.);

    if (Testing_For_Error == 0 )
        std::cout << "operator- Function Works Properly" << std::endl;
    else
    {
        std::cout << "operator- Function Does Not Work Properly" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }

    //Need to ensure that both Test and Test_4 were unchanged
    Testing_For_Error = Testing(Test, 7.,8.,9.);

    if (Testing_For_Error != 0 )
    {
        std::cout << "Vector Properties Were Changed During Operation" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }

    Testing_For_Error = Testing(Test_4, 7.,8.,9.);

    if (Testing_For_Error != 0 )
    {
        std::cout << "Vector Properties Were Changed During Operation" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }

    //Testing operator/
    Vectors Test_7 = Test_4/7.;
    Testing_For_Error = Testing(Test_7, (7./7.), (8./7.), (9./7.));

    if (Testing_For_Error == 0 )
        std::cout << "operator/ Function Works Properly" << std::endl;
    else
    {
        std::cout << "operator/ Function Does Not Work Properly" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }

    //Need to ensure that Test_4 was unchanged
    Testing_For_Error = Testing(Test_4, 7.,8.,9.);

    if (Testing_For_Error != 0 )
    {
        std::cout << "Vector Properties Were Changed During Operation" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }

    //Testing operator*
    Vectors Test_8 = Test_7*7.;
    Testing_For_Error = Testing(Test_8, 7., 8., 9.);

    if (Testing_For_Error == 0 )
        std::cout << "operator* Function Works Properly" << std::endl;
    else
    {
        std::cout << "operator* Function Does Not Work Properly" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }

    //Need to ensure that Test_7 was unchanged
    Testing_For_Error = Testing(Test_7, (7./7.), (8./7.), (9./7.));

    if (Testing_For_Error != 0 )
    {
        std::cout << "Vector Properties Were Changed During Operation" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }
    //Testing operator* (Vectors by Vectors) ie cross product
    Vectors Test_9;
    Vectors Example_Model_2_Vector_4 (0.00195, 0.00115, -0.00121429);
    Vectors Example_Model_2_Vector_19 (0.00295, 0.00215, -0.00935714);
    Test_9 = Example_Model_2_Vector_4 * Example_Model_2_Vector_19;
    Testing_For_Error = Testing(Test_9, -8.1499875e-6, 1.46642675e-5 , 0.00000080);

    if (Testing_For_Error == 0 )
        std::cout << "Cross Product Function Works Properly" << std::endl;
    else
    {
        std::cout << "Cross Product Function Does Not Work Properly" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }

    //Need to ensure that both Vectors were unchanged
    Testing_For_Error = Testing(Example_Model_2_Vector_4, 0.00195, 0.00115, -0.00121429);

    if (Testing_For_Error != 0 )
    {
        std::cout << "Vector Properties Were Changed During Operation" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }

    Testing_For_Error = Testing(Example_Model_2_Vector_19, 0.00295, 0.00215, -0.00935714);

    if (Testing_For_Error != 0 )
    {
        std::cout << "Vector Properties Were Changed During Operation" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }

    //Testing Scalar_Product
    double Scalar_Result = Test.Scalar_Product(Test_8);
    Testing_For_Error = Testing(Scalar_Result, 194.);

    if (Testing_For_Error == 0 )
        std::cout << "Scalar Product Function Works Properly" << std::endl;
    else
    {
        std::cout << "Scalar Product Function Does Not Work Properly" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }

    //Need to ensure that both Test and Test_6 were unchanged
    Testing_For_Error = Testing(Test, 7., 8., 9.);

    if (Testing_For_Error != 0 )
    {
        std::cout << "Vector Properties Were Changed During Operation" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }

    Testing_For_Error = Testing(Test_8, 7., 8., 9.);

    if (Testing_For_Error != 0 )
    {
        std::cout << "Vector Properties Were Changed During Operation" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }

    //Tesing Get_Magnitude
    Vectors Test_10(10,10,5);
    double Magnitude = Test_10.Get_Magnitude();
    Testing_For_Error = Testing(Magnitude, 15.);

    if (Testing_For_Error == 0 )
        std::cout << "Get Magnitude Function Works Properly" << std::endl;
    else
    {
        std::cout << "Get Magnitude Function Does Not Work Properly" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }

    //Need to ensure that Test_10 was unchanged
    Testing_For_Error = Testing(Test_10, 10.,10.,5.);

    if (Testing_For_Error != 0 )
    {
        std::cout << "Vector Properties Were Changed During Operation" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }

    //Testing Get_Distance_To
    Vectors Test_11(2,10,5);
    double Distance = Test_10.Get_Distance_To(Test_11);
    Testing_For_Error = Testing(Distance,8.);

    if (Testing_For_Error == 0 )
        std::cout << "Get Distance To Function Works Properly" << std::endl;
    else
    {
        std::cout << "Get Distance To Function Does Not Work Properly" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }

    //Need to ensure that Test_10 and Test_11 were unchanged
    Testing_For_Error = Testing(Test_10, 10.,10.,5.);

    if (Testing_For_Error != 0 )
    {
        std::cout << "Vector Properties Were Changed During Operation" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }

    Testing_For_Error = Testing(Test_11, 2.,10.,5.);

    if (Testing_For_Error != 0 )
    {
        std::cout << "Vector Properties Were Changed During Operation" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }

    //Testing Divide by 0 check
    //This need to produce an error
    //current returns the object being divided
    Vectors Test_12 =  Test/0;
    Testing_For_Error = Testing(Test_12, 7., 8., 9.);

    if (Testing_For_Error != 0 )
    {
        std::cout << "Vector Properties Were Changed During Operation" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }

    std::cout << "************************" << std::endl;
    if (Error == 0 )
        std::cout << "End of Test: Successful" << std::endl;
    else
        std::cout << "End of Test: Failure" << std::endl;
    std::cout << "************************" << std::endl;

    return (Error == 0) ? 0 : 1;
}
