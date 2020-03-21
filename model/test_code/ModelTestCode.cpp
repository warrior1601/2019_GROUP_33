//
//  ModelTestCode.cpp
//  Computing Project
//
//  Created by Junaid Afzal on 22/11/2019.
//  Copyright © 2019 Junaid Afzal. All rights reserved.
//
//  This source file contains the implementation of
//  test code for all objects
//

#include <iostream>
#include "Model.hpp"

int main()
{
    std::cout << "------------------------------Model.hpp Test Code------------------------------" << std::endl;

    Model ManualModel;
    std::cout << "Blank constructor and cout\n" << ManualModel << std::endl;

    std::vector<Material> manyMaterials;
    Material Steel(0, 9980, "1A6428", "Steel");
    manyMaterials.push_back(Steel);

    std::vector<Vectors> manyVectors;
    Vectors V0_Hex(0, 0, 0);
    Vectors V1_Hex(10, 0, 0);
    Vectors V2_Hex(10, 0, 10);
    Vectors V3_Hex(0, 0, 10);
    Vectors V4_Hex(0, 10, 0);
    Vectors V5_Hex(10, 10, 0);
    Vectors V6_Hex(10, 10, 10);
    Vectors V7_Hex(0, 10, 10);
    manyVectors.push_back(V0_Hex);
    manyVectors.push_back(V1_Hex);
    manyVectors.push_back(V2_Hex);
    manyVectors.push_back(V3_Hex);
    manyVectors.push_back(V4_Hex);
    manyVectors.push_back(V5_Hex);
    manyVectors.push_back(V6_Hex);
    manyVectors.push_back(V7_Hex);

    std::vector<Vectors> HexaVertices = { V0_Hex, V1_Hex, V2_Hex, V3_Hex, V4_Hex, V5_Hex, V6_Hex, V7_Hex };
    std::vector<int> anIrrelevantVectorsOrder;
    Cell* someHexahedron = new Hexahedron (HexaVertices, anIrrelevantVectorsOrder, Steel);
    std::vector<Cell*> manyCells;
    manyCells.push_back(someHexahedron);

    std::string cellOrder;
    cellOrder.push_back('h');

    ManualModel.Set_Materials(manyMaterials);
    ManualModel.Set_Vectors(manyVectors);
    ManualModel.Set_Cells(manyCells);
    ManualModel.Set_Cell_Order(cellOrder);
    std::cout << "\n\n---Set functions---\n" << ManualModel << std::endl;
    //Get functions just return what has been set above



    Model CopyConstructor(ManualModel);
    std::cout << "\n\n---Copy constructor---\n" << CopyConstructor << std::endl;



	Model ModelOne;
	ModelOne.Load_Model("Model_One.txt");
    std::cout << "\n\n---Load Model function---\n" << ModelOne << std::endl;

    Model BlankModel = ModelOne;
    std::cout << "\n\n---Operator=---\n" << BlankModel << std::endl;

    std::cout << "\n\n---Model properties of Model_One.txt---" << "\nVolume of model = " << ModelOne.Get_Volume() << "\nWeight of model = " << ModelOne.Get_Weight() << "\nCentre of gravity of model " << ModelOne.Get_Centre_Of_Gravity() << "Geometric centre of model " << ModelOne.Get_Geometric_Centre() << "Overall dimensions of model " << ModelOne.Get_Overall_Dimensions() << std::endl;

    ModelOne.Save_Model("Save_File_Of_Model_One.txt");
    std::cout << "\n\nCheck directory for the save file which contains all model info, in the propriety\nformat, of the loaded model Model_One.txt\n(Note that any comments from loaded file will be discarded)\n" << std::endl;



    Model ModelTwo;
    ModelTwo.Load_Model("Model_Two.txt");
    std::cout << "\n\n---Model_Two.txt model before rotation---\n" << ModelTwo << std::endl;
    std::cout << "Centre of gravity " << ModelTwo.Get_Centre_Of_Gravity() << "Geometric centre " << ModelTwo.Get_Geometric_Centre() << "Overall dimensions " << ModelTwo.Get_Overall_Dimensions() << std::endl;

    ModelTwo.Rotate(90, 'y', ModelTwo.Get_Geometric_Centre());
    std::cout << "\n\n---Model_Two.txt model after rotation---\n" << ModelTwo << std::endl;
    std::cout << "Centre of gravity " << ModelTwo.Get_Centre_Of_Gravity() << "Geometric centre " << ModelTwo.Get_Geometric_Centre() << "Overall dimensions " << ModelTwo.Get_Overall_Dimensions() << std::endl;

    ModelTwo.Save_Model("Save_File_Of_Model_Two_Rotated.txt");
    std::cout << "\n\nCheck directory for save file which contains all model info, in the propriety\nformat, of the loaded model Model_Two.txt after rotation" << std::endl;

    ModelTwo.Rotate(-90, 'y', ModelTwo.Get_Geometric_Centre());
    std::cout << "\n\n\n---Model_Two.txt model after un-rotation---\n" << ModelTwo << std::endl;
    std::cout << "Centre of gravity " << ModelTwo.Get_Centre_Of_Gravity() << "Geometric centre " << ModelTwo.Get_Geometric_Centre() << "Overall dimensions " << ModelTwo.Get_Overall_Dimensions() << std::endl;

    ModelTwo.Save_Model("Save_File_Of_Model_Two_Un-Rotated.txt");
    std::cout << "\n\nCheck directory for the save file which contains all model info, in the propriety\nformat, of the loaded model  Model_Two.txt after rotation and then un-rotation\n" << std::endl;

	std::cout << "Note that Model_Two.txt and the Save_File_Of_Model_Two_UnRotated.txt are the same model and thus contain the same information" << std::endl;



    Model Example1;
    Example1.Load_Model("ExampleModel1.mod");
    std::cout << "\n\n\n---ExampleModel1.mod Model---\n" << Example1 << std::endl;
    std::cout << "Centre of gravity " << Example1.Get_Centre_Of_Gravity() << "Geometric centre " << Example1.Get_Geometric_Centre() << "Overall dimensions " << Example1.Get_Overall_Dimensions() << "Overall Weight = " << Example1.Get_Weight() << std::endl;



    Model Example2;
    Example2.Load_Model("ExampleModel2.mod");
    std::cout << "\n\n\n---ExampleModel2.mod Model---\n" << Example2 << std::endl;
    std::cout << "Centre of gravity " << Example2.Get_Centre_Of_Gravity() << "Geometric centre " << Example2.Get_Geometric_Centre() << "Overall dimensions " << Example2.Get_Overall_Dimensions() << "Overall Weight = " << Example2.Get_Weight() << std::endl;



    Model Example3;
    Example3.Load_Model("ExampleModel3.mod");
    std::cout << "\n\n\n---ExampleModel3.mod Model---\n" << Example3 << std::endl;
    std::cout << "Geometric centre " << Example3.Get_Geometric_Centre() << "Centre of gravity " << Example3.Get_Centre_Of_Gravity() << "Overall dimensions " << Example3.Get_Overall_Dimensions() << "Overall Weight = " << Example3.Get_Weight() << std::endl;



    return 0;
}
