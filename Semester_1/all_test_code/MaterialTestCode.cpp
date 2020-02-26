//
//  MaterialTestCode.cpp
//  Computing Project
//
//  Created by Chayanis Kulanumphol on 27/11/2019.
//  This File contains a suitable test for all functions declared
//  in the "Material.h" header file. The correct way to implement
//  the functions is demonstrated in this test file.
//

#include <iostream>
#include "../inc/Material.h"

int main()
{
    std::cout << "Testing Blank Constructor" << std::endl;
    Material test;
    std::cout << test << std::endl;

    std::cout << "Testing ID Only Constructor" << std::endl;
    Material test_2(1);
    std::cout << test_2 << std::endl;

    std::cout << "Testing ID and Density Constructor" << std::endl;
    Material test_3(2,78.36);
    std::cout << test_3 << std::endl;

    std::cout << "Testing ID, Density, and Colour Constructor" << std::endl;
    Material test_4(3, 95.63, "FFAAFF");
    std::cout << test_4 << std::endl;

    std::cout << "Testing ID, Density, Colour, and Name Constructor" << std::endl;
    Material test_5(3, 8960, "b87373", "Copper");
    std::cout << test_5 << std::endl;

    std::cout << "Testing Set Functions" << std::endl;
    test.SetID(4);
    test.SetDensity(7654);
    test.SetColour("B7C4AA");
    test.SetName("Gold");
    std::cout << test << std::endl;

    int ID = 0;
    double Density = 0;
    std::string Colour = "N/A";
    std::string Name = "N/A";

    std::cout << "Testing Get Functions" << std::endl;
    std::cout << "Variables are : " << std::endl;
    std::cout << "ID = " << ID << " Density = " << Density << " Colour = " << Colour << " Name = " << Name << std::endl << std::endl;
    std::cout << "Get Functions Pull From Material with Members:" << std::endl;
    std::cout << test << std::endl;

    ID = test.GetID();
    Density = test.GetDensity();
    Colour = test.GetColour();
    Name = test.GetName();
    std::cout << "After Get Functions Variable are : "  << std::endl;
    std::cout << "ID = " << ID << " Density = " << Density << " Colour = " << Colour << " Name = " << Name << std::endl;

    return 0;
}
