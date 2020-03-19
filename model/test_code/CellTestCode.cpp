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

#include "Material.h"
#include "Vectors.h"
#include "Cell.hpp"

int main()
{
    std::cout << "------------------------------Cell.hpp Test Code------------------------------" << std::endl;

    Vectors aVectors(1,2,3);
    Vectors bVectors(4,5,6);
    Vectors cVectors(7,8,9);
    Vectors dVectors(10,11,12);
    Vectors eVectors(13,14,15);
    Vectors fVectors(16,17,18);
    Vectors gVectors(19,20,21);
    Vectors hVectors(22,23,24);
    std::vector<int> anIrrelevantVectorOrder;
    Material Aluminium(0, 5650, "99A1FF", "Aluminium");
    
    
    
    
    
    std::cout << "----------Tetrahedron Test Code----------" << std::endl;
    
    Tetrahedron someTetrahedron;
    std::cout << "Blank constructor and cout\n" << someTetrahedron << std::endl;

    std::vector<Vectors> TetraVertices = { aVectors, bVectors, cVectors, dVectors };

    someTetrahedron.Set_Vertices(TetraVertices);
    someTetrahedron.Set_Vertices_Order(anIrrelevantVectorOrder);
    someTetrahedron.Set_Material(Aluminium);
    
    std::vector<Vectors> TetraGetVertices = someTetrahedron.Get_Vertices();

    std::cout << "Set and get functions\nV0 " << TetraGetVertices[0] << "V1 " << TetraGetVertices[1] << "V2 " << TetraGetVertices[2] << "V3 " << TetraGetVertices[3] << "Material " << someTetrahedron.Get_Material() << std::endl;
    
    Tetrahedron TetraCopyConstructor(someTetrahedron);
    std::cout << "Copy constructor\n" << TetraCopyConstructor << std::endl;

    Vectors V0_Tetra(2,0,1);
    Vectors V1_Tetra(-1,1,1);
    Vectors V2_Tetra(1,0,2);
    Vectors V3_Tetra(3,1,4);
    std::vector<Vectors> moreTetraVertices = { V0_Tetra, V1_Tetra, V2_Tetra, V3_Tetra };
    Material Titanium(1, 1500, "64FF15", "Titanium");

    Tetrahedron anotherTetrahedron(moreTetraVertices, anIrrelevantVectorOrder, Titanium);
    std::cout << "Non blank constructor\n" << anotherTetrahedron << std::endl;

    someTetrahedron = anotherTetrahedron;
    std::cout << "Operator=\n" << someTetrahedron << std::endl;

    std::cout << "Volume of tetrahedron = " << someTetrahedron.Get_Volume() << std::endl;

    std::cout << "Weight of tetrahedron = " << someTetrahedron.Get_Weight() << std::endl;

    std::cout << "Centre of gravity of tetrahedron " << someTetrahedron.Get_Centre_Of_Gravity();
    
    anotherTetrahedron.Rotate(90, 'y', anotherTetrahedron.Get_Centre_Of_Gravity());
    std::cout << "\nRotation of operator= output tetrahedron 90 degrees along the y axis and around the geometric centre\n" << anotherTetrahedron << "\n\n\n\n\n\n" << std::endl;

    


    
    std::cout << "----------Pyramid Test Code----------" << std::endl;
    
    Pyramid somePyramid;
    std::cout << "Blank constructor and cout\n" << somePyramid << std::endl;

    std::vector<Vectors> PyraVertices = { aVectors, bVectors, cVectors, dVectors, eVectors };

    somePyramid.Set_Vertices(PyraVertices);
    somePyramid.Set_Vertices_Order(anIrrelevantVectorOrder);
    somePyramid.Set_Material(Aluminium);

    std::vector<Vectors> PyraGetVertices = somePyramid.Get_Vertices();

    std::cout << "Set and get functions\nV0 " << PyraGetVertices[0] << "V1 " << PyraGetVertices[1] << "V2 " << PyraGetVertices[2] << "V3 " << PyraGetVertices[3] << "V4 " << PyraGetVertices[4] << "Material " << somePyramid.Get_Material() << "\n" << std::endl;
    
    Pyramid PyraCopyConstructor(somePyramid);
    std::cout << "Copy constructor\n" << PyraCopyConstructor << std::endl;

    Vectors V0_Pyra(0,0,0);
    Vectors V1_Pyra(5,0,0);
    Vectors V2_Pyra(5,0,5);
    Vectors V3_Pyra(0,0,5);
    Vectors V4_Pyra(2.5,6,2.5);
    std::vector<Vectors> morePyraGetVertices = { V0_Pyra, V1_Pyra, V2_Pyra, V3_Pyra, V4_Pyra };
    Material Iron(2, 7310, "EF5690", "Iron");

    Pyramid anotherPyramid(morePyraGetVertices, anIrrelevantVectorOrder, Iron);
    std::cout << "Non blank constructor\n" << anotherPyramid << std::endl;

    somePyramid = anotherPyramid;
    std::cout << "Operator=\n" << somePyramid << std::endl;

    std::cout << "Volume of pyramid = " << somePyramid.Get_Volume() << std::endl;

    std::cout << "Weight of pyramid = " << somePyramid.Get_Weight() << std::endl;

    std::cout << "Centre of gravity of pyramid " << somePyramid.Get_Centre_Of_Gravity();
    
    anotherPyramid.Rotate(90, 'y', anotherPyramid.Get_Centre_Of_Gravity());
    std::cout << "\nRotation of operator= output pyramid 90 degrees along the y axis and around the geometric centre\n" << anotherPyramid << "\n\n\n\n\n\n" << std::endl;

    
    
    
    
    std::cout << "----------Hexahedron Test Code----------" << std::endl;

    Hexahedron someHexahedron;
    std::cout << "Blank constructor and cout\n" << someHexahedron << std::endl;

    std::vector<Vectors> HexaVertices = { aVectors, bVectors, cVectors, dVectors, eVectors, fVectors, gVectors, hVectors };

    someHexahedron.Set_Vertices(HexaVertices);
    someHexahedron.Set_Vertices_Order(anIrrelevantVectorOrder);
    someHexahedron.Set_Material(Aluminium);

    std::vector<Vectors> HexaGetVertices = someHexahedron.Get_Vertices();

    std::cout << "Set and get functions\nV0 " << HexaGetVertices[0] << "V1 " << HexaGetVertices[1] << "V2 " << HexaGetVertices[2] << "V3 " << HexaGetVertices[3] << "V4 " << HexaGetVertices[4] << "V5 " << HexaGetVertices[5] << "V6 " << HexaGetVertices[6] << "V7 " << HexaGetVertices[7] << "Material " << someHexahedron.Get_Material() << std::endl;
    
    Hexahedron HexaCopyConstructor(someHexahedron);
    std::cout << "Copy constructor\n" << HexaCopyConstructor << std::endl;

    Vectors V0_Hex(0,0,0);
    Vectors V1_Hex(10,0,0);
    Vectors V2_Hex(10,0,10);
    Vectors V3_Hex(0,0,10);
    Vectors V4_Hex(0,10,0);
    Vectors V5_Hex(10,10,0);
    Vectors V6_Hex(10,10,10);
    Vectors V7_Hex(0,10,10);
    std::vector<Vectors> moreHexaGetVertices = { V0_Hex, V1_Hex, V2_Hex, V3_Hex, V4_Hex, V5_Hex, V6_Hex, V7_Hex };
    Material Steel(3, 9980, "AC64AC", "Steel");

    Hexahedron anotherHexahedron(moreHexaGetVertices, anIrrelevantVectorOrder, Steel);
    std::cout << "Non blank constructor\n" << anotherHexahedron << std::endl;

    someHexahedron = anotherHexahedron;
    std::cout << "Operator=\n" << someHexahedron << std::endl;

    std::cout << "Volume of hexahedron = " << someHexahedron.Get_Volume() << std::endl;
    
    std::cout << "Weight of hexahedron = " << someHexahedron.Get_Weight() << std::endl;

    std::cout << "Centre of gravity of hexahedron " << someHexahedron.Get_Centre_Of_Gravity();
    
    anotherHexahedron.Rotate(90, 'y', anotherHexahedron.Get_Centre_Of_Gravity());
    std::cout << "\nRotation of operator= output hexahedron 90 degrees along the y axis and around the geometric centre\n" << anotherHexahedron << std::endl;

    std::cout << "Finished running Script" << std::endl;
    return 0;
}
