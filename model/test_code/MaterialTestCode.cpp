//  MaterialTestCode.cpp
//  Computing Project
//
//  Created by Chayanis Kulanumphol on 27/11/2019.
//  This File contains a suitable test for all functions declared
//  in the "Material.h" header file. The correct way to implement
//  the functions is demonstrated in this test file.

#include <iostream>
#include "Material.h"
#include "Testing_File_Functions.h"

int main()
{
    std::cout << "------------------------------Material.hpp Test Code------------------------------" << std::endl;
    unsigned int Testing_For_Error = 0;
    unsigned int Error = 0;


    Material test;
    Testing_For_Error = Testing(test, 0, 0.0, "N/A", "N/A");

    if (Testing_For_Error == 0 )
        std::cout << "Blank Constructor and Get Functions Work properly" << std::endl;
    else
    {
        std::cout << "Blank Constructor and Get Functions Do Not Working Properly" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }

    Material test_2(1);
    Testing_For_Error = Testing(test_2, 1, 0.0, "N/A", "N/A");

    if (Testing_For_Error == 0 )
        std::cout << "ID Constructor Works properly" << std::endl;
    else
    {
        std::cout << "ID Constructor Does Not Working Properly" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }

    Material test_3(2,78.36);
    Testing_For_Error = Testing(test_3, 2, 78.36, "N/A", "N/A");

    if (Testing_For_Error == 0 )
        std::cout << "ID/Density Constructor Works properly" << std::endl;
    else
    {
        std::cout << "ID/Density Constructor Does Not Working Properly" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }

    Material test_4(3, 95.63, "FFAAFF");
    Testing_For_Error = Testing(test_4, 3, 95.63, "FFAAFF", "N/A");

    if (Testing_For_Error == 0 )
        std::cout << "ID/Density/Colour Constructor Works properly" << std::endl;
    else
    {
        std::cout << "ID/Density/Colour Constructor Does Not Working Properly" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }

    Material test_5(4, 8960, "b87373", "Copper");
    Testing_For_Error = Testing(test_5, 4, 8960., "b87373", "Copper");

    if (Testing_For_Error == 0 )
        std::cout << "ID/Density/Colour/Name Constructor Works properly" << std::endl;
    else
    {
        std::cout << "ID/Density/Colour/Name Constructor Does Not Working Properly" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }

    test.SetID(5);
    test.SetDensity(7654);
    test.SetColour("B7C4AA");
    test.SetName("Gold");

    Testing_For_Error = Testing(test, 5, 7654., "B7C4AA", "Gold");

    if (Testing_For_Error == 0 )
        std::cout << "Set Functions Works properly" << std::endl;
    else
    {
        std::cout << "Set Functions Do Not Working Properly" << std::endl;
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
