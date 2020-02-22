//
//  Model.cpp
//  Computing Project
//
//  Created by Junaid Afzal on 16/11/2019.
//  Copyright © 2019 Junaid Afzal. All rights reserved.
//
//  This source file contains the implementation of the object Model
//

#include "../Include/Model.hpp"
#include <fstream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <iostream>


//Constructors and destructors
Model::Model(const Model& aModel)
{
    manyMaterials = aModel.manyMaterials;
    manyVectors = aModel.manyVectors;
    manyTetrahedrons = aModel.manyTetrahedrons;
    manyPyramids = aModel.manyPyramids;
    manyHexahedrons = aModel.manyHexahedrons;
    cellOrder = aModel.cellOrder;
}

Model::Model(void) { }

Model::~Model(void) { }





//Custom std::cout function
std::ostream& operator<< (std::ostream& Output, const Model& aModel)
{
    //std::left left aligns text; std::setw() sets the width for the next variable; and std::right right aligns text
    Output << "Materials" << std::endl;
    for (unsigned int i = 0; i < aModel.manyMaterials.size(); i++)
        Output << aModel.manyMaterials[i];

    Output << "\nVectors" << std::endl;
    for (unsigned int i = 0; i < aModel.manyVectors.size(); i++)
        Output << std::right << "V" << std::setw(4) << i << "   " << aModel.manyVectors[i];

    Output << "\nCells " << std::endl;

    for (unsigned int i = 0; i < aModel.cellOrder.size(); i++)
    {
        Output << std::right << "C" << std::setw(3) << i << " = ";

        if (aModel.cellOrder[i] == 't')
            Output << "Tetrahedron" << std::endl;

        if (aModel.cellOrder[i] == 'p')
            Output << "Pyramid" << std::endl;

        if (aModel.cellOrder[i] == 'h')
            Output << "Hexahedron" << std::endl;
    }

    Output << "\nTotal number of cells = " << aModel.manyTetrahedrons.size() + aModel.manyPyramids.size() + aModel.manyHexahedrons.size() << std::endl;

    Output << "Total number of Vectors = " << aModel.manyVectors.size() << std::endl;

    return Output;
}





//Custom operator function
Model& Model::operator = (const Model& aModel)
{
    if(&aModel == this)
        return(*this);

    else
    {
        manyMaterials = aModel.manyMaterials;
        manyVectors = aModel.manyVectors;
        manyTetrahedrons = aModel.manyTetrahedrons;
        manyPyramids = aModel.manyPyramids;
        manyHexahedrons = aModel.manyHexahedrons;
        cellOrder = aModel.cellOrder;

        return(*this);
    }
}





//Set and get functions
void Model::Load_Model(const std::string& FilePath)
{
    std::ifstream myFile(FilePath.c_str());

    if (myFile.is_open()) //Check if file has been opened sucessfully, if so returns true
    {
        std::string currentLine;

        while ( getline (myFile,currentLine) ) //getline will get a new line, starting from the beginning of the file, until the end of file is reached
        {
            if (currentLine[0] == '#') //Ignore comments
                continue;

            else if (currentLine[0] == 'm') //Read in material
            {
                Material temp; //This will temporarily hold material variables until all variables have been read in, at which point it will be added to the material list
                std::string Placeholder; //This will temporarily hold values from the current line

                for (unsigned int currentPosition = 0, spaceCount = 0; currentPosition < currentLine.size(); currentPosition++) //Iterate across the line
                {
                    if (currentLine[currentPosition] == ' ') //If a space is reached then whatever is in 'Placeholder' must be read in
                    {
                        switch (spaceCount) {
                            case 0: //Do nothing as first space represents an 'm' being read in
                                break;

                            case 1: { //Read in material ID
                                int MaterialID = std::stoi(Placeholder, nullptr, 10);

                                if (MaterialID < 0)
                                {
                                    std::cout << "Error due to negative material ID\n" << currentLine << "\n" << std::endl;
                                    exit(1);
                                }

                                if (MaterialID < manyMaterials.size())
                                {
                                    std::cout << "Error due to duplicate material ID\n" << currentLine << "   is trying to overwrite   " << "m " << MaterialID << " " << manyMaterials[MaterialID].GetDensity() << " " << manyMaterials[MaterialID].GetColour() << " " << manyMaterials[MaterialID].GetName() << "\n" << std::endl;
                                    exit(1);
                                }

                                if (MaterialID > manyMaterials.size())
                                {
                                    std::cout << "Error due to non sequential material ID\n" << currentLine << "\n" << std::endl;
                                    exit(1);
                                }

                                temp.SetID(MaterialID); //If material ID is valid, store in temp
                                break;
                            }

                            case 2: { //Read in density
                                double Density = std::stof(Placeholder, nullptr);

                                if (Density <= 0)
                                {
                                    std::cout << "Error due to invalid denisty\n" << currentLine << "\n" << std::endl;
                                    exit(1);
                                }

                                temp.SetDensity(Density); //If density is valid, store in temp
                                break;
                            }

                            case 3: { //Read in colour
                                if (Placeholder.size() != 6) //If colour is not 6 digits long, then invalid
                                {
                                    std::cout << "Error due to invalid colour\n" << currentLine << "\n" << std::endl;
                                    exit(1);
                                }

                                temp.SetColour(Placeholder);
                                break;
                            }

                            default:
                                break;
                        }

                        spaceCount++; //Increment space count
                        Placeholder.clear(); //Clear contents of 'Placeholder' so next variable can be read in
                        continue; //Go to next iteration
                    }

                    else
                        Placeholder.push_back(currentLine[currentPosition]); //If current position in current line is NOT a space then read in the value
                }

                temp.SetName(Placeholder); //Last value is not proceeded by a space and so will remain in 'Placeholder' after for loop

                manyMaterials.push_back(temp); //All variables of temp have been assigned and so can be added to materials list
            }

            else if (currentLine[0] == 'v') //Read in Vectors
            {
                Vectors temp; //This will temporarily hold Vectors variables until all variables have been read in, at which point it will be added to the Vectors list
                std::string Placeholder; //This will temporarily hold values from the current line

                for (unsigned int currentPosition = 0, spaceCount = 0; currentPosition < currentLine.size(); currentPosition++) //Iterate across the line
                {
                    if (currentLine[currentPosition] == ' ') //If a space is reached then whatever is in 'Placeholder' must be read in
                    {
                        switch (spaceCount) {
                            case 0: //Do nothing as first space represents an 'v' being read in
                                break;

                            case 1: { //Read in Vectors ID
                                int VectorsID = std::stoi(Placeholder, nullptr, 10);

                                //Check if the Vectors ID is valid
                                if (VectorsID < 0)
                                {
                                    std::cout << "Error due to negative Vectors ID\n" << currentLine << "\n" << std::endl;
                                    exit(1);
                                }

                                if (VectorsID < manyVectors.size())
                                {
                                    std::cout << "Error due to duplicate Vectors ID\n" << currentLine << "   is trying to overwrite   " << "v " << VectorsID << " " << manyVectors[VectorsID].GetXVector() << " " << manyVectors[VectorsID].GetYVector() << " " << manyVectors[VectorsID].GetZVector() << "\n" << std::endl;
                                    exit(1);
                                }

                                if (VectorsID > manyVectors.size())
                                {
                                    std::cout << "Error due to non sequential Vectors ID\n" << currentLine << "\n" << std::endl;
                                    exit(1);
                                }

                                break;
                            }

                            case 2: //Read in X value
                                temp.SetX_Vector(std::stof(Placeholder, nullptr));
                                break;

                            case 3: //Read in Y value
                                temp.SetY_Vector(std::stof(Placeholder, nullptr));
                                break;

                            default:
                                break;
                        }

                        spaceCount++; //Increment space count
                        Placeholder.clear(); //Clear contents of 'Placeholder' so next variable can be read in
                        continue; //Go to next iteration
                    }

                    Placeholder.push_back(currentLine[currentPosition]); //If current position in current line is NOT a space then read in the value
                }

                temp.SetZ_Vector(std::stof(Placeholder, nullptr)); //Last value is not proceeded by a space and so will remain in 'Placeholder' after for loop

                manyVectors.push_back(temp); //All variables of temp have been assigned and so can be added to Vectors list
            }

            else if (currentLine[0] == 'c') //Read in a shape
            {
                int tempCellOrder = 0;
                unsigned char currentCellType = '\0';
                std::string Placeholder; //This will temporarily hold values from the current line

                for (unsigned int currentPosition = 0, spaceCount = 0; currentPosition < currentLine.size(); currentPosition++) //Iterate across the line
                {
                    if (currentLine[currentPosition] == ' ') //If a space is reached then whatever is in 'Placeholder' must be read in
                    {
                        switch (spaceCount) {
                            case 0: //Do nothing as first space represents an 'c' being read in
                                break;

                            case 1: {
                                tempCellOrder = std::stoi(Placeholder, nullptr, 10);
                                //Cell order is checked and NOT read in as it is something inherent to the array std::string cellOrder, e.g. if cellOrder[5] = 't'; then cell 5 is a tetrahedron

                                if (tempCellOrder < 0)
                                {
                                    std::cout << "Error due to negative cell ID\n" << currentLine << "\n" << std::endl;
                                    exit(1);
                                }

                                if (tempCellOrder < cellOrder.size())
                                {
                                    std::cout << "Error due to duplicate cell ID\n" << currentLine << "   is trying to overwrite   " << "c " << tempCellOrder << " " << cellOrder[tempCellOrder] << " ";

                                    //NOTE: The code below just displays the cell that is trying to be overwritten
                                    int whichShapeNumber = -1;
                                    for (int i = 0; i <= tempCellOrder; i++)
                                    {
                                        if (cellOrder[i] == cellOrder[tempCellOrder])
                                            whichShapeNumber++;
                                    }

                                    switch (cellOrder[tempCellOrder]) {
                                        case 't':
                                            std::cout << manyTetrahedrons[whichShapeNumber].Get_Material().GetID() << " " << manyTetrahedrons[whichShapeNumber].Get_Vectors_Order()[0] << " " << manyTetrahedrons[whichShapeNumber].Get_Vectors_Order()[1] << " " << manyTetrahedrons[whichShapeNumber].Get_Vectors_Order()[2] << " " << manyTetrahedrons[whichShapeNumber].Get_Vectors_Order()[3] << "\n" << std::endl;
                                            break;

                                        case 'p':
                                            std::cout << manyPyramids[whichShapeNumber].Get_Material().GetID() << " " << manyPyramids[whichShapeNumber].Get_Vectors_Order()[0] << " " << manyPyramids[whichShapeNumber].Get_Vectors_Order()[1] << " " << manyPyramids[whichShapeNumber].Get_Vectors_Order()[2] << " " << manyPyramids[whichShapeNumber].Get_Vectors_Order()[3] << " " << manyPyramids[whichShapeNumber].Get_Vectors_Order()[4] << "\n" << std::endl;
                                            break;

                                        case 'h':
                                            std::cout << manyHexahedrons[whichShapeNumber].Get_Material().GetID() << " " << manyHexahedrons[whichShapeNumber].Get_Vectors_Order()[0] << " " << manyHexahedrons[whichShapeNumber].Get_Vectors_Order()[1] << " " << manyHexahedrons[whichShapeNumber].Get_Vectors_Order()[2] << " " << manyHexahedrons[whichShapeNumber].Get_Vectors_Order()[3] << " " << manyHexahedrons[whichShapeNumber].Get_Vectors_Order()[4] << " " << manyHexahedrons[whichShapeNumber].Get_Vectors_Order()[5] << " " << manyHexahedrons[whichShapeNumber].Get_Vectors_Order()[6] << " " << manyHexahedrons[whichShapeNumber].Get_Vectors_Order()[7] << "\n" << std::endl;
                                            break;

                                        default:
                                            break;
                                    }

                                    exit(1);
                                }

                                if (tempCellOrder > cellOrder.size())
                                {
                                    std::cout << "Error due to non sequential cell ID\n" << currentLine << "\n" << std::endl;
                                    exit(1);
                                }

                                break;
                            }

                            case 2: { //Read in cell type
                                currentCellType = Placeholder[0];

                                if (currentCellType == 't' || currentCellType == 'p' || currentCellType == 'h')
                                {
                                    cellOrder.push_back(currentCellType); //Here the cell type is recorded (and cell ID as the position in the array)
                                    break;
                                }

                                else
                                {
                                    std::cout << "Error due to invalid cell type\n" << currentLine << "\n" << std::endl;
                                    exit(1);
                                }

                                break;
                            }

                            default:
                                break;
                        }

                        Placeholder.clear(); //Clear contents of 'Placeholder' so next variable can be read in

                        if (spaceCount == 2) //This terminates the for loop so that cell specific code can be executed
                            break;

                        spaceCount++; //Increment space count

                        continue; //Go to next iteration
                    }

                    Placeholder.push_back(currentLine[currentPosition]); //If current position in current line is NOT a space then read in the value
                }

                if (currentCellType == 't') //Read in tetrahedron
                {
                    Tetrahedron temp; //This will temporarily hold tetrahedron variables until all variables have been read in, at which point it will be added to the tetrahedron list
                    std::vector<int> aVectorsOrder; //The Vectors being used by the tetrahedron from the models perspective

                    for (unsigned int currentPosition = 0, spaceCount = 0; currentPosition < currentLine.size(); currentPosition++) //Iterate across the line
                    {
                        if (currentLine[currentPosition] == ' ') //If a space is reached then whatever is in 'Placeholder' must be read in
                        {
                            switch (spaceCount) {
                                case 3: { //Read in material ID
                                    int MaterialID = std::stoi(Placeholder, nullptr, 10);

                                    if (MaterialID < 0 || MaterialID > ( manyMaterials.size() - 1)) //Check if material ID actually exists
                                    {
                                        std::cout << "Error due to invalid material ID\n" << currentLine << "\n" << std::endl;
                                        exit(1);
                                    }

                                    temp.Set_Material(manyMaterials[MaterialID]); //If valid, store material ID
                                    break;
                                }

                                case 4: { //Read in V0
                                    int VectorsID = std::stoi(Placeholder, nullptr, 10);

                                    if (VectorsID < 0 || VectorsID > (manyVectors.size() - 1)) //Check if Vectors ID actually exists
                                    {
                                        std::cout << "Error due to invalid Vectors ID\n" << currentLine << "\n" << std::endl;
                                        exit(1);
                                    }

                                    temp.Set_V0(manyVectors[VectorsID]); //Set Vectors
                                    aVectorsOrder.push_back(VectorsID); //Store Vectors ID for when saving model
                                    break;
                                }

                                case 5: { //Read in V1
                                    int VectorsID = std::stoi(Placeholder, nullptr, 10);

                                    if (VectorsID < 0 || VectorsID > (manyVectors.size() - 1)) //Check if Vectors ID actually exists
                                    {
                                        std::cout << "Error due to invalid Vectors ID\n" << currentLine << "\n" << std::endl;
                                        exit(1);
                                    }

                                    temp.Set_V1(manyVectors[VectorsID]); //Set Vectors
                                    aVectorsOrder.push_back(VectorsID); //Store Vectors ID for when saving model
                                    break;
                                }

                                case 6: { //Read in V2
                                    int VectorsID = std::stoi(Placeholder, nullptr, 10);

                                    if (VectorsID < 0 || VectorsID > (manyVectors.size() - 1)) //Check if Vectors ID actually exists
                                    {
                                        std::cout << "Error due to invalid Vectors ID\n" << currentLine << "\n" << std::endl;
                                        exit(1);
                                    }

                                    temp.Set_V2(manyVectors[VectorsID]); //Set Vectors
                                    aVectorsOrder.push_back(VectorsID); //Store Vectors ID for when saving model
                                    break;
                                }

                                default:
                                    break;
                            }

                            spaceCount++; //Increment space count
                            Placeholder.clear(); //Clear contents of 'Placeholder' so next variable can be read in
                            continue; //Go to next iteration
                        }

                        Placeholder.push_back(currentLine[currentPosition]); //If current position in current line is NOT a space then read in the value
                    }

                    int VectorsID = std::stoi(Placeholder, nullptr, 10); //Read in V3

                    if (VectorsID < 0 || VectorsID > (manyVectors.size() - 1)) //Check if Vectors ID actually exists
                    {
                        std::cout << "Error due to invalid Vectors ID\n" << currentLine << "\n" << std::endl;
                        exit(1);
                    }

                    temp.Set_V3(manyVectors[VectorsID]); //Set Vectors

                    aVectorsOrder.push_back(VectorsID); //Store Vectors ID for when saving model
                    temp.Set_Vectors_Order(aVectorsOrder);

                    manyTetrahedrons.push_back(temp); //All variables of temp have been assigned and so can be added to tetrahedron list
                }

                if (currentCellType == 'p') //Read in pyramid
                {
                    Pyramid temp; //This will temporarily hold pyramid variables until all variables have been read in, at which point it will be added to the pyramid list
                    std::vector<int> aVectorsOrder; //The Vectors being used by the tetrahedron from the models perspective

                    for (int currentPosition = 0, spaceCount = 0; currentPosition < currentLine.size(); currentPosition++) //Iterate across the line
                    {
                        if (currentLine[currentPosition] == ' ') //If a space is reached then whatever is in 'Placeholder' must be read in
                        {
                            switch (spaceCount) {
                                case 3: { //Read in material ID
                                    int MaterialID = std::stoi(Placeholder, nullptr, 10);

                                    if (MaterialID < 0 || MaterialID > ( manyMaterials.size() - 1)) //Check if material ID actually exists
                                    {
                                        std::cout << "Error due to invalid material ID\n" << currentLine << "\n" << std::endl;
                                        exit(1);
                                    }

                                    temp.Set_Material(manyMaterials[MaterialID]);
                                    break;
                                }

                                case 4:  { //Read in V0
                                    int VectorsID = std::stoi(Placeholder, nullptr, 10);

                                    if (VectorsID < 0 || VectorsID > (manyVectors.size() - 1)) //Check if Vectors ID actually exists
                                    {
                                        std::cout << "Error due to invalid Vectors ID\n" << currentLine << "\n" << std::endl;
                                        exit(1);
                                    }

                                    temp.Set_V0(manyVectors[VectorsID]);
                                    aVectorsOrder.push_back(VectorsID);
                                    break;
                                }

                                case 5: { //Read in V1
                                    int VectorsID = std::stoi(Placeholder, nullptr, 10);

                                    if (VectorsID < 0 || VectorsID > (manyVectors.size() - 1)) //Check if Vectors ID actually exists
                                    {
                                        std::cout << "Error due to invalid Vectors ID\n" << currentLine << "\n" << std::endl;
                                        exit(1);
                                    }

                                    temp.Set_V1(manyVectors[VectorsID]);
                                    aVectorsOrder.push_back(VectorsID);
                                    break;
                                }

                                case 6: { //Read in V2
                                    int VectorsID = std::stoi(Placeholder, nullptr, 10);

                                    if (VectorsID < 0 || VectorsID > (manyVectors.size() - 1)) //Check if Vectors ID actually exists
                                    {
                                        std::cout << "Error due to invalid Vectors ID\n" << currentLine << "\n" << std::endl;
                                        exit(1);
                                    }

                                    temp.Set_V2(manyVectors[VectorsID]);
                                    aVectorsOrder.push_back(VectorsID);
                                    break;
                                }

                                case 7: { //Read in V3
                                    int VectorsID = std::stoi(Placeholder, nullptr, 10);

                                    if (VectorsID < 0 || VectorsID > (manyVectors.size() - 1)) //Check if Vectors ID actually exists
                                    {
                                        std::cout << "Error due to invalid Vectors ID\n" << currentLine << "\n" << std::endl;
                                        exit(1);
                                    }

                                    temp.Set_V3(manyVectors[VectorsID]);
                                    aVectorsOrder.push_back(VectorsID);
                                    break;
                                }

                                default:
                                    break;
                            }

                            spaceCount++; //Increment space count
                            Placeholder.clear(); //Clear contents of 'Placeholder' so next variable can be read in
                            continue; //Go to next iteration
                        }

                        Placeholder.push_back(currentLine[currentPosition]); //If current position in current line is NOT a space then read in the value
                    }

                    int VectorsID = std::stoi(Placeholder, nullptr, 10); //Read in V4

                    if (VectorsID < 0 || VectorsID > (manyVectors.size() - 1)) //Check if Vectors ID actually exists
                    {
                        std::cout << "Error due to invalid Vectors ID\n" << currentLine << "\n" << std::endl;
                        exit(1);
                    }

                    temp.Set_V4(manyVectors[VectorsID]); //Set Vectors

                    aVectorsOrder.push_back(VectorsID); //Store Vectors ID for when saving model
                    temp.Set_Vectors_Order(aVectorsOrder);

                    manyPyramids.push_back(temp); //All variables of temp have been assigned and so can be added to pyramid list
                }

                if (currentCellType == 'h') //Read in hexahedron
                {
                    Hexahedron temp; //This will temporarily hold hexahedron variables until all variables have been read in, at which point it will be added to the hexahedron list
                    std::vector<int> aVectorsOrder; //The Vectors being used by the hexahedron from the models perspective

                    for (unsigned int currentPosition = 0, spaceCount = 0; currentPosition < currentLine.size(); currentPosition++) //Iterate across the line
                    {
                        if (currentLine[currentPosition] == ' ') //If a space is reached then whatever is in 'Placeholder' must be read in
                        {
                            switch (spaceCount) {
                                case 3: { //Read in material ID
                                    int MaterialID = std::stoi(Placeholder, nullptr, 10);

                                    if (MaterialID < 0 || MaterialID > ( manyMaterials.size() - 1)) //Check if material ID actually exists
                                    {
                                        std::cout << "Error due to invalid material ID\n" << currentLine << "\n" << std::endl;
                                        exit(1);
                                    }

                                    temp.Set_Material(manyMaterials[MaterialID]); //If valid, store material ID
                                    break;
                                }

                                case 4: { //Read in V0
                                    int VectorsID = std::stoi(Placeholder, nullptr, 10);

                                    if (VectorsID < 0 || VectorsID > (manyVectors.size() - 1)) //Check if Vectors ID actually exists
                                    {
                                        std::cout << "Error due to invalid Vectors ID\n" << currentLine << "\n" << std::endl;
                                        exit(1);
                                    }

                                    temp.Set_V0(manyVectors[VectorsID]);
                                    aVectorsOrder.push_back(VectorsID);
                                    break;
                                }

                                case 5: { //Read in V1
                                    int VectorsID = std::stoi(Placeholder, nullptr, 10);

                                    if (VectorsID < 0 || VectorsID > (manyVectors.size() - 1)) //Check if Vectors ID actually exists
                                    {
                                        std::cout << "Error due to invalid Vectors ID\n" << currentLine << "\n" << std::endl;
                                        exit(1);
                                    }

                                    temp.Set_V1(manyVectors[VectorsID]); //Set Vectors
                                    aVectorsOrder.push_back(VectorsID); //Store Vectors ID for when saving model
                                    break;
                                }

                                case 6: { //Read in V2
                                    int VectorsID = std::stoi(Placeholder, nullptr, 10);

                                    if (VectorsID < 0 || VectorsID > (manyVectors.size() - 1)) //Check if Vectors ID actually exists
                                    {
                                        std::cout << "Error due to invalid Vectors ID\n" << currentLine << "\n" << std::endl;
                                        exit(1);
                                    }

                                    temp.Set_V2(manyVectors[VectorsID]); //Set Vectors
                                    aVectorsOrder.push_back(VectorsID); //Store Vectors ID for when saving model
                                    break;
                                }

                                case 7: { //Read in V3
                                    int VectorsID = std::stoi(Placeholder, nullptr, 10);

                                    if (VectorsID < 0 || VectorsID > (manyVectors.size() - 1)) //Check if Vectors ID actually exists
                                    {
                                        std::cout << "Error due to invalid Vectors ID\n" << currentLine << "\n" << std::endl;
                                        exit(1);
                                    }

                                    temp.Set_V3(manyVectors[VectorsID]); //Set Vectors
                                    aVectorsOrder.push_back(VectorsID); //Store Vectors ID for when saving model
                                    break;
                                }

                                case 8: { //Read in V4
                                    int VectorsID = std::stoi(Placeholder, nullptr, 10);

                                    if (VectorsID < 0 || VectorsID > (manyVectors.size() - 1)) //Check if Vectors ID actually exists
                                    {
                                        std::cout << "Error due to invalid Vectors ID\n" << currentLine << "\n" << std::endl;
                                        exit(1);
                                    }

                                    temp.Set_V4(manyVectors[VectorsID]); //Set Vectors
                                    aVectorsOrder.push_back(VectorsID); //Store Vectors ID for when saving model
                                    break;
                                }

                                case 9: { //Read in V5
                                    int VectorsID = std::stoi(Placeholder, nullptr, 10);

                                    if (VectorsID < 0 || VectorsID > (manyVectors.size() - 1)) //Check if Vectors ID actually exists
                                    {
                                        std::cout << "Error due to invalid Vectors ID\n" << currentLine << "\n" << std::endl;
                                        exit(1);
                                    }

                                    temp.Set_V5(manyVectors[VectorsID]); //Set Vectors
                                    aVectorsOrder.push_back(VectorsID); //Store Vectors ID for when saving model
                                    break;
                                }

                                case 10: { //Read in V6
                                    int VectorsID = std::stoi(Placeholder, nullptr, 10);

                                    if (VectorsID < 0 || VectorsID > (manyVectors.size() - 1)) //Check if Vectors ID actually exists
                                    {
                                        std::cout << "Error due to invalid Vectors ID\n" << currentLine << "\n" << std::endl;
                                        exit(1);
                                    }

                                    temp.Set_V6(manyVectors[VectorsID]); //Set Vectors
                                    aVectorsOrder.push_back(VectorsID); //Store Vectors ID for when saving model
                                    break;
                                }

                                default:
                                    break;
                            }

                            spaceCount++; //Increment space count
                            Placeholder.clear(); //Clear contents of 'Placeholder' so next variable can be read in
                            continue; //Go to next iteration
                        }

                        Placeholder.push_back(currentLine[currentPosition]); //If current position in current line is NOT a space then read in the value
                    }

                    int VectorsID = std::stoi(Placeholder, nullptr, 10); //Read in V7

                    if (VectorsID < 0 || VectorsID > (manyVectors.size() - 1)) //Check if Vectors ID actually exists
                    {
                        std::cout << "Error due to invalid Vectors ID\n" << currentLine << "\n" << std::endl;
                        exit(1);
                    }

                    temp.Set_V7(manyVectors[VectorsID]); //Set Vectors

                    aVectorsOrder.push_back(VectorsID); //Store Vectors ID for when saving model
                    temp.Set_Vectors_Order(aVectorsOrder);

                    manyHexahedrons.push_back(temp); //All variables of temp have been assigned and so can be added to hexahedron list
                }
            }
        }

        myFile.close(); //Close file; free up space; and stop reading
    }

	else //If file did not open correctly then returns false
	{
		std::cout << "Unable to open file for reading: " << FilePath << "\n" << std::endl;
		exit(1);
	}
}

void Model::Save_Model(const std::string& FilePath)
{
    std::ofstream myFile (FilePath);

    if (myFile.is_open()) //Check if file has been opened sucessfully, if so returns true
    {
        myFile << "# Materials (m, Material ID, Density, RGB, Name)" << std::endl;

        for (unsigned int i = 0; i < manyMaterials.size(); i++)
        {
            //std::dec to display variable as decimal number and std::hex to display variable as std::hex
            myFile << "m " << manyMaterials[i].GetID() << " " << manyMaterials[i].GetDensity() << " " << manyMaterials[i].GetColour() <<  " " << manyMaterials[i].GetName() << std::endl;
        }

        myFile << "\n# Vectors (v, Vectors ID, X, Y, Z)" << std::endl;

        for (unsigned int i = 0; i < manyVectors.size(); i++)
        {
            myFile << "v " << i << " " << std::dec <<  manyVectors[i].GetXVector() << " " << manyVectors[i].GetYVector() << " " << manyVectors[i].GetZVector() << std::endl;
        }

        myFile << "\n# Cells (c, Cell ID, Cell Type, Material ID, Vectors ID, Vectors ID, Vectors ID, Vectors ID...)" << std::endl;

        for (unsigned int i = 0, numberOfTetra = 0, numberOfPyra = 0, numberOfHexa = 0; i < cellOrder.size(); i++)
        {
            myFile << "c " << i << " " << cellOrder[i] << " ";

            if (cellOrder[i] == 't')
            {
                myFile << manyTetrahedrons[numberOfTetra].Get_Material().GetID() << " " << manyTetrahedrons[numberOfTetra].Get_Vectors_Order()[0] << " " << manyTetrahedrons[numberOfTetra].Get_Vectors_Order()[1] << " " << manyTetrahedrons[numberOfTetra].Get_Vectors_Order()[2] << " " << manyTetrahedrons[numberOfTetra].Get_Vectors_Order()[3] << std::endl;

                numberOfTetra++;
            }

            if (cellOrder[i] == 'p')
            {
                myFile << manyPyramids[numberOfPyra].Get_Material().GetID() << " " << manyPyramids[numberOfPyra].Get_Vectors_Order()[0] << " " << manyPyramids[numberOfPyra].Get_Vectors_Order()[1] << " " << manyPyramids[numberOfPyra].Get_Vectors_Order()[2] << " " << manyPyramids[numberOfPyra].Get_Vectors_Order()[3] << " " << manyPyramids[numberOfPyra].Get_Vectors_Order()[4] << std::endl;

                numberOfPyra++;
            }

            if (cellOrder[i] == 'h')
            {
                myFile << manyHexahedrons[numberOfHexa].Get_Material().GetID() << " " << manyHexahedrons[numberOfHexa].Get_Vectors_Order()[0] << " " << manyHexahedrons[numberOfHexa].Get_Vectors_Order()[1] << " " << manyHexahedrons[numberOfHexa].Get_Vectors_Order()[2] << " " << manyHexahedrons[numberOfHexa].Get_Vectors_Order()[3] << " " << manyHexahedrons[numberOfHexa].Get_Vectors_Order()[4] << " " << manyHexahedrons[numberOfHexa].Get_Vectors_Order()[5] << " " << manyHexahedrons[numberOfHexa].Get_Vectors_Order()[6] << " " << manyHexahedrons[numberOfHexa].Get_Vectors_Order()[7] << std::endl;

                numberOfHexa++;
            }
        }

        myFile.close(); //Close file; free up space; and stop reading
    }

    else //If file did not open correctly then returns false
        std::cout << "Unable to open file for writing: " << FilePath << "\n" << std::endl;
}





void Model::Set_Materials(const std::vector<Material>& someMaterials) { manyMaterials = someMaterials; }

void Model::Set_Vectors(const std::vector<Vectors>& someVectors) { manyVectors = someVectors; }

void Model::Set_Tetrahedrons(const std::vector<Tetrahedron>& someTetrahedrons) { manyTetrahedrons = someTetrahedrons; }

void Model::Set_Pyramids(const std::vector<Pyramid>& somePyramids) { manyPyramids = somePyramids; }

void Model::Set_Hexahedrons(const std::vector<Hexahedron>& someHexahedrons) { manyHexahedrons = someHexahedrons; }

void Model::Set_Cell_Order(const std::string& someCellOrder) { cellOrder = someCellOrder; }





std::vector<Material> Model::Get_Materials(void) { return manyMaterials; }

std::vector<Vectors> Model::Get_Vectors(void) { return manyVectors; }

std::vector<Tetrahedron> Model::Get_Tetrahedrons(void) { return manyTetrahedrons; }

std::vector<Pyramid> Model::Get_Pyramids(void) { return manyPyramids; }

std::vector<Hexahedron> Model::Get_Hexahedrons(void) { return manyHexahedrons; }

std::string Model::Get_Cell_Order(void) { return cellOrder; }





//Model specific functions
double Model::Get_Volume(void)
{
    double totalVolume = 0;

    for (unsigned int i = 0; i < manyTetrahedrons.size(); i++)
        totalVolume += manyTetrahedrons[i].Get_Volume();

    for (unsigned int i = 0; i < manyPyramids.size(); i++)
        totalVolume += manyPyramids[i].Get_Volume();

    for (unsigned int i = 0; i < manyHexahedrons.size(); i++)
        totalVolume += manyHexahedrons[i].Get_Volume();

    return totalVolume;
}

double Model::Get_Weight(void)
{
    double totalWeight = 0;

    for (unsigned int i = 0; i < manyTetrahedrons.size(); i++)
        totalWeight += manyTetrahedrons[i].Get_Weight();

    for (unsigned int i = 0; i < manyPyramids.size(); i++)
        totalWeight += manyPyramids[i].Get_Weight();

    for (unsigned int i = 0; i < manyHexahedrons.size(); i++)
        totalWeight += manyHexahedrons[i].Get_Weight();

    return totalWeight;
}

Vectors Model::Get_Centre_Of_Gravity(void)
{
    std::vector<Vectors> CentresOfGravities;
    std::vector<double> CentresOfGravitiesWeights;

    //The next three for loops stores all centres of gravities of all object and its weight
    //at the same point in two arrays

    for (unsigned int i = 0; i < manyTetrahedrons.size(); i++)
    {
        CentresOfGravities.push_back(manyTetrahedrons[i].Get_Centre_Of_Gravity());
        CentresOfGravitiesWeights.push_back(manyTetrahedrons[i].Get_Weight());
    }

    for (unsigned int i = 0; i < manyPyramids.size(); i++)
    {
        CentresOfGravities.push_back(manyPyramids[i].Get_Centre_Of_Gravity());
        CentresOfGravitiesWeights.push_back(manyPyramids[i].Get_Weight());
    }

    for (unsigned int i = 0; i < manyHexahedrons.size(); i++)
    {
        CentresOfGravities.push_back(manyHexahedrons[i].Get_Centre_Of_Gravity());
        CentresOfGravitiesWeights.push_back(manyHexahedrons[i].Get_Weight());
    }

    //This while loop reduces the COGs by combining pairs of COGs until only one remains

    while (CentresOfGravities.size() != 1)
    {
        std::vector<Vectors> newCentresOfGravities;
        std::vector<double> newCentresOfGravitiesWeights;

        if ((CentresOfGravities.size() % 2) == 0) //If even then there will be pairs for all COGs
        {
            for (unsigned int i = 0, j = 1; j < CentresOfGravities.size(); i += 2, j += 2)
            {
                double TotalDistance = CentresOfGravities[i].Get_Distance_To(CentresOfGravities[j]);

                double iDistance = TotalDistance / (CentresOfGravitiesWeights[i]/CentresOfGravitiesWeights[j] + 1);

                Vectors iToj = CentresOfGravities[j] - CentresOfGravities[i];

                Vectors newCOG = CentresOfGravities[i] + ( iToj * (iDistance/TotalDistance) );

                newCentresOfGravities.push_back(newCOG);
                newCentresOfGravitiesWeights.push_back(CentresOfGravitiesWeights[i] + CentresOfGravitiesWeights[j]);
            }
        }

        else
        {
            for (unsigned int i = 0, j = 1; j < CentresOfGravities.size() - 1; i += 2, j += 2) //If odd then there will be n pairs + 1
            {

                double TotalDistance = CentresOfGravities[i].Get_Distance_To(CentresOfGravities[j]);

                double iDistance = TotalDistance / (CentresOfGravitiesWeights[i]/CentresOfGravitiesWeights[j] + 1);

                Vectors iToj = CentresOfGravities[j] - CentresOfGravities[i];

                Vectors newCOG = CentresOfGravities[i] + ( iToj * (iDistance/TotalDistance) );

                newCentresOfGravities.push_back(newCOG);
                newCentresOfGravitiesWeights.push_back(CentresOfGravitiesWeights[i] + CentresOfGravitiesWeights[j]);

                //Below is an example of how 7 COGs are converted in to 4 COGs
                // 0 1  2 3  4 5  6
                //  0    1    2   3

                if (j == (CentresOfGravities.size() - 2)) //If statement to deal with odd amount of COGs
                {
                    newCentresOfGravities.push_back(CentresOfGravities[j+1]);
                    newCentresOfGravitiesWeights.push_back(CentresOfGravitiesWeights[j+1]);
                }
            }
        }

        CentresOfGravities = newCentresOfGravities;
        CentresOfGravitiesWeights = newCentresOfGravitiesWeights;
    }

    return CentresOfGravities[0];
}

Vectors Model::Get_Geometric_Centre(void)
{
    std::vector<Vectors> MinMax = Get_Min_Max();
    return ((MinMax[0] + MinMax[1]) / 2.0); //Geometric centre = midpoint of min and max values

}

Vectors Model::Get_Overall_Dimensions(void)
{
    std::vector<Vectors> MinMax = Get_Min_Max();

    return MinMax[1] - MinMax[0]; //Overall dimensions = difference between min and max values
}

void Model::Rotate(double Rotation_In_Degrees, char Axis_Of_Rotation, Vectors Centre_Of_Rotation)
{
    //Rotate all object with respect to centre of rotation and update manyVectors
    //list with new Vectors
    for(unsigned int i = 0; i < manyTetrahedrons.size(); i++)
    {
        manyTetrahedrons[i].Rotate(Rotation_In_Degrees, Axis_Of_Rotation, Centre_Of_Rotation);

        std::vector<int> CurrentVectorsOrder = manyTetrahedrons[i].Get_Vectors_Order();
        manyVectors[CurrentVectorsOrder[0]] = manyTetrahedrons[i].Get_V0();
        manyVectors[CurrentVectorsOrder[1]] = manyTetrahedrons[i].Get_V1();
        manyVectors[CurrentVectorsOrder[2]] = manyTetrahedrons[i].Get_V2();
        manyVectors[CurrentVectorsOrder[3]] = manyTetrahedrons[i].Get_V3();
    }

    for(unsigned int i = 0; i < manyPyramids.size(); i++)
    {
        manyPyramids[i].Rotate(Rotation_In_Degrees, Axis_Of_Rotation, Centre_Of_Rotation);

        std::vector<int> CurrentVectorsOrder = manyPyramids[i].Get_Vectors_Order();
        manyVectors[CurrentVectorsOrder[0]] = manyPyramids[i].Get_V0();
        manyVectors[CurrentVectorsOrder[1]] = manyPyramids[i].Get_V1();
        manyVectors[CurrentVectorsOrder[2]] = manyPyramids[i].Get_V2();
        manyVectors[CurrentVectorsOrder[3]] = manyPyramids[i].Get_V3();
        manyVectors[CurrentVectorsOrder[4]] = manyPyramids[i].Get_V4();
    }

    for(unsigned int i = 0; i < manyHexahedrons.size(); i++)
    {
        manyHexahedrons[i].Rotate(Rotation_In_Degrees, Axis_Of_Rotation, Centre_Of_Rotation);

        std::vector<int> CurrentVectorsOrder = manyHexahedrons[i].Get_Vectors_Order();
        manyVectors[CurrentVectorsOrder[0]] = manyHexahedrons[i].Get_V0();
        manyVectors[CurrentVectorsOrder[1]] = manyHexahedrons[i].Get_V1();
        manyVectors[CurrentVectorsOrder[2]] = manyHexahedrons[i].Get_V2();
        manyVectors[CurrentVectorsOrder[3]] = manyHexahedrons[i].Get_V3();
        manyVectors[CurrentVectorsOrder[4]] = manyHexahedrons[i].Get_V4();
        manyVectors[CurrentVectorsOrder[5]] = manyHexahedrons[i].Get_V5();
        manyVectors[CurrentVectorsOrder[6]] = manyHexahedrons[i].Get_V6();
        manyVectors[CurrentVectorsOrder[7]] = manyHexahedrons[i].Get_V7();
    }
}




//Private Member Functions
std::vector<int> Model::Get_Vectors_Being_Used(void)
{
    //The next three for loops determines which vectors are being used by cycling through each type of cell and
    //the vector IDs for each cell
    std::vector<int> VectorsBeingUsed;

    for (unsigned int i = 0; i < manyTetrahedrons.size(); i++) //Cycle through tetrahedrons
    {
        for (unsigned int j = 0; j < manyTetrahedrons[i].Get_Vectors_Order().size(); j++) //Cycle through the Vectors being used for that particular tetrahedron
        {
            int currentVectorsID = manyTetrahedrons[i].Get_Vectors_Order()[j];

            //If currentVectorsID has already been recorded in VectorsBeingUsed then continue to next iteration
            if (std::find( VectorsBeingUsed.begin(), VectorsBeingUsed.end(), currentVectorsID ) != VectorsBeingUsed.end())
                continue;

            else
                VectorsBeingUsed.push_back(currentVectorsID);
        }
    }

    for (unsigned int i = 0; i < manyPyramids.size(); i++) //Cycle through pyramids
    {
        for (unsigned int j = 0; j < manyPyramids[i].Get_Vectors_Order().size(); j++) //Cycle through the Vectors being used for that particular pyramid
        {
            int currentVectorsID = manyPyramids[i].Get_Vectors_Order()[j];

            if (std::find(VectorsBeingUsed.begin(), VectorsBeingUsed.end(), currentVectorsID) != VectorsBeingUsed.end())
                continue;

            else
                VectorsBeingUsed.push_back(currentVectorsID);
        }
    }

    for (unsigned int i = 0; i < manyHexahedrons.size(); i++) //Cycle through hexahedrons
    {
        for (unsigned int j = 0; j < manyHexahedrons[i].Get_Vectors_Order().size(); j++) //Cycle through the Vectors being used for that particular hexahedron
        {
            int currentVectorsID = manyHexahedrons[i].Get_Vectors_Order()[j];

            if (std::find(VectorsBeingUsed.begin(), VectorsBeingUsed.end(), currentVectorsID) != VectorsBeingUsed.end())
                continue;

            else
                VectorsBeingUsed.push_back(currentVectorsID);
        }
    }

    return VectorsBeingUsed;
}


std::vector<Vectors> Model::Get_Min_Max(void)
{
    //This function returns two Vectors that represent the opposing corners of a hexahedron that contains the model
    //or in other words the most positive and most negative co-ordinates of the model

    Vectors Minimum(0,0,0), Maximum(0,0,0);
    std::vector<Vectors> MinMax;
    MinMax.push_back(Minimum);
    MinMax.push_back(Maximum);
    std::vector<int> VectorsBeingUsed = Get_Vectors_Being_Used();

    //This for loop cycles through all Vectors (that are being used) and finds the min and max values of
    //X, Y, and Z and assign them to the correct Vectors

    for (unsigned int i = 0; i < VectorsBeingUsed.size(); i++)
    {
        Vectors CurrentVectors = manyVectors[VectorsBeingUsed[i]];

        if (CurrentVectors.GetXVector() < MinMax[0].GetXVector())
            MinMax[0].SetX_Vector(CurrentVectors.GetXVector());

        else if (CurrentVectors.GetXVector() > MinMax[1].GetXVector())
            MinMax[1].SetX_Vector(CurrentVectors.GetXVector());

        if (CurrentVectors.GetYVector() < MinMax[0].GetYVector())
            MinMax[0].SetY_Vector(CurrentVectors.GetYVector());

        else if (CurrentVectors.GetYVector() > MinMax[1].GetYVector())
            MinMax[1].SetY_Vector(CurrentVectors.GetYVector());

        if (CurrentVectors.GetZVector() < MinMax[0].GetZVector())
            MinMax[0].SetZ_Vector(CurrentVectors.GetZVector());

        else if (CurrentVectors.GetZVector() > MinMax[1].GetZVector())
            MinMax[1].SetZ_Vector(CurrentVectors.GetZVector());
    }

    return MinMax;
}
