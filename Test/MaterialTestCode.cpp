#include <iostream>
#include "Material.h"
//
//  MaterialTestCode.cpp
//  Computing Project
//
//  Created by Chayanis Kulanumphol on 27/11/2019.
//  This File contains a suitable test for all functions declared
//  in the "Material.h" header file. The correct way to implement
//  the functions is demonstrated in this test file.

using namespace std;

int main()
{
    cout<<"Testing Blank Constructor"<<endl;
    Material test;
    cout<<test<<endl;

    cout<<"Testing ID Only Constructor"<<endl;
    Material test_2(1);
    cout<<test_2<<endl;

    cout<<"Testing ID and Density Constructor"<<endl;
    Material test_3(2,78.36);
    cout<<test_3<<endl;

    cout<<"Testing ID, Density, and Colour Constructor"<<endl;
    Material test_4(3, 95.63, "FFAAFF");
    cout<<test_4<<endl;

    cout<<"Testing ID, Density, Colour, and Name Constructor"<<endl;
    Material test_5(3, 8960, "b87373", "Copper");
    cout<<test_5<<endl;

    cout<<"Testing Set Functions"<<endl;
    test.SetID(4);
    test.SetDensity(7654);
    test.SetColour("B7C4AA");
    test.SetName("Gold");
    cout<<test<<endl;

    int ID = 0;
    float Density = 0;
    string Colour = "N/A";
    string Name = "N/A";

    cout<<"Testing Get Functions"<<endl;
    cout<<"Variables are : "<<endl;
    cout<<"ID = "<<ID<<" Density = "<<Density<<" Colour = "<<Colour<<" Name = "<<Name<<endl<<endl;
    cout<<"Get Functions Pull From Material with Members:"<<endl;
    cout<<test<<endl;

    ID = test.GetID();
    Density = test.GetDensity();
    Colour = test.GetColour();
    Name = test.GetName();
    cout<<"After Get Functions Variable are : " <<endl;
    cout<<"ID = "<<ID<<" Density = "<<Density<<" Colour = "<<Colour<<" Name = "<<Name<<endl;

    return 0;
}
