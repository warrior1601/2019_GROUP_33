//
//  testCode.cpp
//  Computing Project
//
//  Created by Junaid Afzal on 22/11/2019.
//  Copyright © 2019 Junaid Afzal. All rights reserved.
//
//  This source file contains the implementation of
//  test code for all objects

#include "Material.h"
#include "Vectors.h"
#include "Matrix.hpp"
#include "Cell.hpp"
#include "Model.hpp"

int main()
{
    std::cout << "------------------------------Model.hpp Test Code------------------------------" << std::endl;

    Model ManualModel;
    std::cout << "Blank constructor and cout\n" << ManualModel << std::endl;

    Vectors V0_Hex(0, 0, 0);
    Vectors V1_Hex(10, 0, 0);
    Vectors V2_Hex(10, 0, 10);
    Vectors V3_Hex(0, 0, 10);
    Vectors V4_Hex(0, 10, 0);
    Vectors V5_Hex(10, 10, 0);
    Vectors V6_Hex(10, 10, 10);
    Vectors V7_Hex(0, 10, 10);
    std::vector<int> anIrrelaventVectorsOrder;
    Material Steel (0, 9980, "1A6428" , "Steel");
    Hexahedron someHexahedron(V0_Hex, V1_Hex, V2_Hex, V3_Hex, V4_Hex, V5_Hex, V6_Hex, V7_Hex, anIrrelaventVectorsOrder, Steel);
    std::vector<Material> manyMaterials = {Steel};
    std::vector<Vectors> manyVertices = {V0_Hex, V1_Hex, V2_Hex, V3_Hex, V4_Hex, V5_Hex, V6_Hex, V7_Hex};
    std::vector<Tetrahedron> manyTetrahedrons;
    std::vector<Pyramid> manyPyramids;
    std::vector<Hexahedron> manyHexahedrons = {someHexahedron};
    std::string cellOrder = {'h'};

    ManualModel.Set_Materials(manyMaterials);
    ManualModel.Set_Vertices(manyVertices);
    ManualModel.Set_Tetrahedrons(manyTetrahedrons);
    ManualModel.Set_Pyramids(manyPyramids);
    ManualModel.Set_Hexahedrons(manyHexahedrons);
    ManualModel.Set_Cell_Order(cellOrder);
    std::cout << "\n\nSet functions\n" << ManualModel << std::endl;
    //Get functions just return what has been set above


    Model CopyConstructor(ManualModel);
    std::cout << "\n\nCopy constructor\n" << CopyConstructor << std::endl;


    Model aModelOfThreeHexahedrons;
    aModelOfThreeHexahedrons.Load_Model("aModelOfThreeHexahedrons.txt");
    std::cout << "\n\nLoad Model function\n" << aModelOfThreeHexahedrons << std::endl;


	Model BlankModel = aModelOfThreeHexahedrons;
    std::cout << "\n\nOperator=\n" << BlankModel << std::endl;


    std::cout << "Model properties" << "\nVolume of model = " << aModelOfThreeHexahedrons.Get_Volume() << "\nWeight of model = " << aModelOfThreeHexahedrons.Get_Weight() << "\nCentre of gravity of model = " << aModelOfThreeHexahedrons.Get_Centre_Of_Gravity() << "Geometric centre of model = " << aModelOfThreeHexahedrons.Get_Geometric_Centre() << "Overall dimensions of model = " << aModelOfThreeHexahedrons.Get_Overall_Dimensions() << std::endl;


    aModelOfThreeHexahedrons.Save_Model("SaveFileOfaModelOfThreeHexahedrons.txt");
    std::cout << "\n\nCheck debug directory for SaveFileOfLoadFile.txt which contains all model info, in the propriety\nformat, of the loaded model from the file aModelOfThreeHexahedrons.txt\n(Note that any comments from loaded file will be discarded)\n" << std::endl;
    
    
    
    Model anotherModel;
    anotherModel.Load_Model("anotherModel.txt");
    std::cout << "\nanotherModel.txt model before rotation\n" << anotherModel << std::endl;
    std::cout << "Centre of gravity =\t" << anotherModel.Get_Centre_Of_Gravity() << "Geometric centre =\t" << anotherModel.Get_Geometric_Centre() << "Overall dimensions =\t" << anotherModel.Get_Overall_Dimensions() << std::endl;
    
    
    
    anotherModel.Rotate(90, 'y', anotherModel.Get_Geometric_Centre());
    std::cout << "\n\n\n\anotherModel.txt model after rotation\n" << anotherModel << std::endl;
    std::cout << "Centre of gravity =\t" << anotherModel.Get_Centre_Of_Gravity() << "Geometric centre =\t" << anotherModel.Get_Geometric_Centre() << "Overall dimensions =\t" << anotherModel.Get_Overall_Dimensions() << std::endl;
    
    anotherModel.Save_Model("SaveFileOfanotherModelRotated.txt");
    std::cout << "\nCheck debug directory for SaveFileOfanotherModelRotated.txt which contains all model info, in the propriety\nformat, of the loaded model from the file RotationFile.txt after rotation" << std::endl;
    

    
    anotherModel.Rotate(-90, 'y', anotherModel.Get_Geometric_Centre());
    std::cout << "\nRotationFile.txt model after un-rotation\n" << anotherModel << std::endl;
    std::cout << "Centre of gravity =\t" << anotherModel.Get_Centre_Of_Gravity() << "Geometric centre =\t" << anotherModel.Get_Geometric_Centre() << "Overall dimensions =\t" << anotherModel.Get_Overall_Dimensions() << std::endl;

    anotherModel.Save_Model("SaveFileOfanotherModelUnRotated.txt");
    std::cout << "\nCheck debug directory for SaveFileOfanotherModelUnRotated.txt which contains all model info, in the propriety\nformat, of the loaded model from the file RotationFile.txt after rotation and then un rotation" << std::endl;
}
