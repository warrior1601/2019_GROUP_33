//
//  CellTestCode.cpp
//  Computing Project
//
//  Created by Junaid Afzal on 22/11/2019.
//  Copyright © 2019 Junaid Afzal. All rights reserved.
//
//  This source files contains all the test code for
//  the object the sub objects of Cell - Tetrahedron,
//  Pyramid, and Hexahedron - and demonstrates all the
//  functionality of the object
//

#include "Materail.h"
#include "Vectors.h"
#include "Cell.hpp"

int main()
{
    std::cout << "------------------------------Cell.hpp Test Code------------------------------" << std::endl;

    Vectors aVectors;
    aVectors.SetVector(1,2,3);
    Vectors bVectors;
    bVectors.SetVector(4,5,6);
    Vectors cVectors;
    cVectors.SetVector(7,8,9);
    Vectors dVectors;
    dVectors.SetVector(10,11,12);
    Vectors eVectors;
    eVectors.SetVector(13,14,15);
    Vectors fVectors;
    fVectors.SetVector(16,17,18);
    Vectors gVectors;
    gVectors.SetVector(19,20,21);
    Vectors hVectors;
    hVectors.SetVector(22,23,24);
    Material Aluminium(5650, "Aluminium", "99A1FF", 0);
    
    
    
    
    
    std::cout << "----------Tetrahedron Test Code----------" << std::endl;
    
    Tetrahedron someTetrahedron;
    std::cout << "Blank constructor and cout\n" << someTetrahedron << std::endl;

    someTetrahedron.Set_V0(aVectors);
    someTetrahedron.Set_V1(bVectors);
    someTetrahedron.Set_V2(cVectors);
    someTetrahedron.Set_V3(dVectors);
    someTetrahedron.Set_Material(Aluminium);

    std::cout << "Set and get functions\nV0 = " << someTetrahedron.Get_V0() << "V1 = " << someTetrahedron.Get_V1() << "V2 = " << someTetrahedron.Get_V2() << "V3 = " << someTetrahedron.Get_V3() << std::endl;
    //std::cout << "Material " << someTetrahedron.Get_Material() << "\n" << std::endl;
    
    Tetrahedron TetraCopyConstructor(someTetrahedron);
    std::cout << "Copy constructor\n" << TetraCopyConstructor << std::endl;

    Vectors V0_Tetra;
    V0_Tetra.SetVector(2,0,1);
    Vectors V1_Tetra;
    V1_Tetra.SetVector(-1,1,1);
    Vectors V2_Tetra;
    V2_Tetra.SetVector(1,0,2);
    Vectors V3_Tetra;
    V3_Tetra.SetVector(3,1,4);
    Material Titanium(1500, "Titanium", "64FF15", 1);

    Tetrahedron anotherTetrahedron(V0_Tetra, V1_Tetra, V2_Tetra, V3_Tetra, Titanium);
    std::cout << "Non blank constructor\n" << anotherTetrahedron << std::endl;

    someTetrahedron = anotherTetrahedron;
    std::cout << "Operator=\n" << someTetrahedron << std::endl;

    std::cout << "Volume of tetrahedron\t" << someTetrahedron.Get_Volume() << std::endl;

    std::cout << "Weight of tetrahedron\t" << someTetrahedron.Get_Weight() << std::endl;

    std::cout << "Centre of gravity of tetrahedron\t\t" << someTetrahedron.Get_Centre_Of_Gravity();

    

    std::cout << "\n\n\n\n" << std::endl;


    
    std::cout << "----------Pyramid Test Code----------" << std::endl;
    
    Pyramid somePyramid;
    std::cout << "Blank constructor and cout\n" << somePyramid << std::endl;

    somePyramid.Set_V0(aVectors);
    somePyramid.Set_V1(bVectors);
    somePyramid.Set_V2(cVectors);
    somePyramid.Set_V3(dVectors);
    somePyramid.Set_V4(eVectors);
    somePyramid.Set_Material(Aluminium);

    std::cout << "Set and get functions\nV0 = " << somePyramid.Get_V0() << "V1 = " << somePyramid.Get_V1() << "V2 = " << somePyramid.Get_V2() << "V3 = " << somePyramid.Get_V3() << "V4 = " << somePyramid.Get_V4() << std::endl;
    //std::cout << "Material " << somePyramid.Get_Material() << "\n" << std::endl;
    
    Pyramid PyraCopyConstructor(somePyramid);
    std::cout << "Copy constructor\n" << PyraCopyConstructor << std::endl;

    Vectors V0_Pyra;
    V0_Pyra.SetVector(0,0,0);
    Vectors V1_Pyra;
    V1_Pyra.SetVector(5,0,0);
    Vectors V2_Pyra;
    V2_Pyra.SetVector(5,0,5);
    Vectors V3_Pyra;
    V3_Pyra.SetVector(0,0,5);
    Vectors V4_Pyra;
    V4_Pyra.SetVector(2.5,6,2.5);
    Material Iron(7310, "Iron", "EF5690", 2);

    Pyramid anotherPyramid(V0_Pyra, V1_Pyra, V2_Pyra, V3_Pyra, V4_Pyra, Iron);
    std::cout << "Non blank constructor\n" << anotherPyramid << std::endl;

    somePyramid = anotherPyramid;
    std::cout << "Operator=\n" << somePyramid << std::endl;

    std::cout << "Volume of pyramid\t" << somePyramid.Get_Volume() << std::endl;

    std::cout << "Weight of pyramid\t" << somePyramid.Get_Weight() << std::endl;

    std::cout << "Centre of gravity of pyramid\t\t" << somePyramid.Get_Centre_Of_Gravity();

    
    
    std::cout << "\n\n\n\n" << std::endl;
    
    
    
    std::cout << "----------Hexahedron Test Code----------" << std::endl;

    Hexahedron someHexahedron;
    std::cout << "Blank constructor and cout\n" << someHexahedron << std::endl;

    someHexahedron.Set_V0(aVectors);
    someHexahedron.Set_V1(bVectors);
    someHexahedron.Set_V2(cVectors);
    someHexahedron.Set_V3(dVectors);
    someHexahedron.Set_V4(eVectors);
    someHexahedron.Set_V5(fVectors);
    someHexahedron.Set_V6(gVectors);
    someHexahedron.Set_V7(hVectors);
    someHexahedron.Set_Material(Aluminium);

    std::cout << "Set and get functions\nV0 = " << someHexahedron.Get_V0() << "V1 = " << someHexahedron.Get_V1() << "V2 = " << someHexahedron.Get_V2() << "V3 = " << someHexahedron.Get_V3() << "V4 = " << someHexahedron.Get_V4() << "V5 = " << someHexahedron.Get_V5() << "V6 = " << someHexahedron.Get_V6() << "V7 = " << someHexahedron.Get_V7() << std::endl;
    //std::cout << "Material " << someHexahedron.Get_Material() << "\n" << std::endl;
    
    Hexahedron HexaCopyConstructor(someHexahedron);
    std::cout << "Copy constructor\n" << HexaCopyConstructor << std::endl;

    Vectors V0_Hex;
    V0_Hex.SetVector(0,0,0);
    Vectors V1_Hex;
    V1_Hex.SetVector(10,0,0);
    Vectors V2_Hex;
    V2_Hex.SetVector(10,0,10);
    Vectors V3_Hex;
    V3_Hex.SetVector(0,0,10);
    Vectors V4_Hex;
    V4_Hex.SetVector(0,10,0);
    Vectors V5_Hex;
    V5_Hex.SetVector(10,10,0);
    Vectors V6_Hex;
    V6_Hex.SetVector(10,10,10);
    Vectors V7_Hex;
    V7_Hex.SetVector(0,10,10);
    Material Steel(9980, "Steel", "AC64AC", 3);

    Hexahedron anotherHexahedron(V0_Hex, V1_Hex, V2_Hex, V3_Hex, V4_Hex, V5_Hex, V6_Hex, V7_Hex, Steel);
    std::cout << "Non blank constructor\n" << anotherHexahedron << std::endl;

    someHexahedron = anotherHexahedron;
    std::cout << "Operator=\n" << someHexahedron << std::endl;

    std::cout << "Volume of hexahedron\t" << someHexahedron.Get_Volume() << std::endl;
    
    std::cout << "Weight of hexahedron\t" << someHexahedron.Get_Weight() << std::endl;

    std::cout << "Centre of gravity of hexahedron\t\t" << someHexahedron.Get_Centre_Of_Gravity();
    
    return 0;
}
