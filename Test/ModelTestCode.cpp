//
//  ModelTestCode.cpp
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
    std::vector<int> anIrrelevantVectorsOrder;
    Material Steel (0, 9980, "1A6428" , "Steel");
    Hexahedron someHexahedron(V0_Hex, V1_Hex, V2_Hex, V3_Hex, V4_Hex, V5_Hex, V6_Hex, V7_Hex, anIrrelevantVectorsOrder, Steel);
    std::vector<Material> manyMaterials = {Steel};
    std::vector<Vectors> manyVectors = {V0_Hex, V1_Hex, V2_Hex, V3_Hex, V4_Hex, V5_Hex, V6_Hex, V7_Hex};
    std::vector<Tetrahedron> manyTetrahedrons;
    std::vector<Pyramid> manyPyramids;
    std::vector<Hexahedron> manyHexahedrons = {someHexahedron};
    std::string cellOrder = {'h'};

    ManualModel.Set_Materials(manyMaterials);
    ManualModel.Set_Vectors(manyVectors);
    ManualModel.Set_Tetrahedrons(manyTetrahedrons);
    ManualModel.Set_Pyramids(manyPyramids);
    ManualModel.Set_Hexahedrons(manyHexahedrons);
    ManualModel.Set_Cell_Order(cellOrder);
    std::cout << "\n\n---Set functions---\n" << ManualModel << std::endl;
    //Get functions just return what has been set above


    Model CopyConstructor(ManualModel);
    std::cout << "\n\n---Copy constructor---\n" << CopyConstructor << std::endl;


    Model ModelOne;
    ModelOne.Load_Model("/Users/Git/Computing_Project/2019_GROUP_33/Model_Files/Model_One.txt");
    std::cout << "\n\n---Load Model function---\n" << ModelOne << std::endl;


    Model BlankModel = ModelOne;
    std::cout << "\n\n---Operator=---\n" << BlankModel << std::endl;


    std::cout << "\n\n---Model properties of ModelOne---" << "\nVolume of model = " << ModelOne.Get_Volume() << "\nWeight of model = " << ModelOne.Get_Weight() << "\nCentre of gravity of model = " << ModelOne.Get_Centre_Of_Gravity() << "Geometric centre of model = " << ModelOne.Get_Geometric_Centre() << "Overall dimensions of model = " << ModelOne.Get_Overall_Dimensions() << std::endl;


    ModelOne.Save_Model("Save_File_Of_Model_One.txt");
    std::cout << "\n\nCheck directory for Save_File_Of_Model_One.txt which contains all model info, in the propriety\nformat, of the loaded model from the file Model_One.txt\n(Note that any comments from loaded file will be discarded)\n" << std::endl;
        
        
        
    Model ModelTwo;
    ModelTwo.Load_Model("/Users/Git/Computing_Project/2019_GROUP_33/Model_Files/Model_Two.txt");
    std::cout << "\n\n---Model_Two.txt model before rotation---\n" << ModelTwo << std::endl;
    std::cout << "Centre of gravity =\t" << ModelTwo.Get_Centre_Of_Gravity() << "Geometric centre =\t" << ModelTwo.Get_Geometric_Centre() << "Overall dimensions =\t" << ModelTwo.Get_Overall_Dimensions() << std::endl;
        
        
        
    ModelTwo.Rotate(90, 'y', ModelTwo.Get_Geometric_Centre());
    std::cout << "\n\n---Model_Two.txt model after rotation---\n" << ModelTwo << std::endl;
    std::cout << "Centre of gravity =\t" << ModelTwo.Get_Centre_Of_Gravity() << "Geometric centre =\t" << ModelTwo.Get_Geometric_Centre() << "Overall dimensions =\t" << ModelTwo.Get_Overall_Dimensions() << std::endl;

    ModelTwo.Save_Model("Save_File_Of_Model_Two_Rotated.txt");
    std::cout << "\n\nCheck directory for Save_File_Of_Model_Two_Rotated.txt which contains all model info, in the propriety\nformat, of the loaded model from the file Model_Two.txt after rotation" << std::endl;
        

        
    ModelTwo.Rotate(-90, 'y', ModelTwo.Get_Geometric_Centre());
    std::cout << "\n\n\n---Model_Two.txt model after un-rotation---\n" << ModelTwo << std::endl;
    std::cout << "Centre of gravity =\t" << ModelTwo.Get_Centre_Of_Gravity() << "Geometric centre =\t" << ModelTwo.Get_Geometric_Centre() << "Overall dimensions =\t" << ModelTwo.Get_Overall_Dimensions() << std::endl;

    ModelTwo.Save_Model("Save_File_Of_Model_Two_UnRotated.txt");
    std::cout << "\n\nCheck directory for Save_File_Of_Model_Two_UnRotated.txt which contains all model info, in the propriety\nformat, of the loaded model from the file Model_Two.txt after rotation and then un rotation\n" << std::endl;
    
    return 0;
}