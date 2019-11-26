#include <iostream>
#include "Material.h"

using namespace std;

int main()
{

    std::string name =  "Copper";
    std::string col =  "bcbcbc";


    Material test;
    test.SetMaterial(8679, name, col, 1);
    test.GetColour();
    test.GetDensity();
    test.GetID();
    test.GetName();
    cout<<test<<endl;

    Material test_2(5555, "Gold", "BFFBBF", 2);
    cout<<test_2<<endl;

    Material test_3;
    test_3.SetColour("AFBABB");
    test_3.SetDensity(4567);
    test_3.SetID(3);
    test_3.SetName("Bricks");

    cout<<test_3<<endl;

    return 0;
}
