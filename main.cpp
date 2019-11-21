#include <iostream>
#include "Materail.h"

using namespace std;

int main()
{

std::string name =  "Copper";
std::string col =  "bcbcbc";


    Material test;
    test.setMaterial(8679 , name, col , 1);
    test.getcolour();
    test.getdensity();
    test.getid();
    test.getname();

    return 0;
}
