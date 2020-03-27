//  Model.cpp
//  Computing Project
//  Created by Junaid Afzal on 16/11/2019.
//  This file contains the definitions of the member functions for the Model class

#include "Model.hpp"
#include <fstream>
#include <iomanip>
#include <string>
#include <algorithm>

//Constructors and destructor
Model::Model(const Model& aModel)
{
    manyMaterials = aModel.manyMaterials;
    manyVectors = aModel.manyVectors;
    manyCells = aModel.manyCells;
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

    Output << "\nTotal number of cells = " << aModel.manyCells.size() << std::endl;

    Output << "Total number of vectors = " << aModel.manyVectors.size() << std::endl;

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
        manyCells = aModel.manyCells;
        cellOrder = aModel.cellOrder;

        return(*this);
    }
}





//Set functions
void Model::Set_Materials(const std::vector<Material>& someMaterials) { manyMaterials = someMaterials; }

void Model::Set_Vectors(const std::vector<Vectors>& someVectors) { manyVectors = someVectors; }

void Model::Set_Cells(const std::vector<Cell*>& someCells) { manyCells = someCells; }

void Model::Set_Cell_Order(const std::string& someCellOrder) { cellOrder = someCellOrder; }





//Get functions
std::vector<Material> Model::Get_Materials(void) { return manyMaterials; }

std::vector<Vectors> Model::Get_Vectors(void) { return manyVectors; }

std::vector<Cell*> Model::Get_Cells(void) { return manyCells; }

std::string Model::Get_Cell_Order(void) { return cellOrder; }





//Model specific functions
void Model::Load_Model(const std::string& FilePath)
{
    std::ifstream myFile(FilePath);

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
                                unsigned int MaterialID = std::stoi(Placeholder, nullptr, 10);

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
                                double Density = std::stod(Placeholder, nullptr);

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
                                unsigned int VectorsID = std::stoi(Placeholder, nullptr, 10);

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
                                temp.SetX_Vector(std::stod(Placeholder, nullptr));
                                break;

                            case 3: //Read in Y value
                                temp.SetY_Vector(std::stod(Placeholder, nullptr));
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

                temp.SetZ_Vector(std::stod(Placeholder, nullptr)); //Last value is not proceeded by a space and so will remain in 'Placeholder' after for loop

                manyVectors.push_back(temp); //All variables of temp have been assigned and so can be added to Vectors list
            }

            else if (currentLine[0] == 'c') //Read in a shape
            {
                unsigned int tempCellOrder = 0;
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

                                    std::cout << manyCells[tempCellOrder]->Get_Material().GetID() << " ";

                                    for (unsigned int i = 0; i < manyCells[tempCellOrder]->Get_Vertices_Order().size(); i++)
                                        std::cout << manyCells[tempCellOrder]->Get_Vertices_Order()[i] << " ";

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
                    std::vector<Vectors> tempVertices; //The vertices of tetrahedron
                    std::vector<int> tempVerticesOrder; //The Vectors being used by the tetrahedron from the models perspective
                    Material tempMaterial; //The material of tetrahedron

                    for (unsigned int currentPosition = 0, spaceCount = 0; currentPosition < currentLine.size(); currentPosition++) //Iterate across the line
                    {
                        if (currentLine[currentPosition] == ' ') //If a space is reached then whatever is in 'Placeholder' must be read in
                        {
                            switch (spaceCount) {
                                case 3: { //Read in material ID
                                    unsigned int MaterialID = std::stoi(Placeholder, nullptr, 10);

                                    if (MaterialID < 0 || MaterialID > ( manyMaterials.size() - 1)) //Check if material ID actually exists
                                    {
                                        std::cout << "Error due to invalid material ID\n" << currentLine << "\n" << std::endl;
                                        exit(1);
                                    }

                                    tempMaterial = manyMaterials[MaterialID]; //If valid, use material ID
                                    break;
                                }

                                case 4: { //Read in V0
									unsigned int VectorsID = std::stoi(Placeholder, nullptr, 10);

                                    if (VectorsID < 0 || VectorsID > (manyVectors.size() - 1)) //Check if Vectors ID actually exists
                                    {
                                        std::cout << "Error due to invalid Vectors ID\n" << currentLine << "\n" << std::endl;
                                        exit(1);
                                    }

                                    tempVertices.push_back(manyVectors[VectorsID]); //Set Vectors
                                    tempVerticesOrder.push_back(VectorsID); //Store Vectors ID for when saving model
                                    break;
                                }

                                case 5: { //Read in V1
									unsigned int VectorsID = std::stoi(Placeholder, nullptr, 10);

                                    if (VectorsID < 0 || VectorsID > (manyVectors.size() - 1)) //Check if Vectors ID actually exists
                                    {
                                        std::cout << "Error due to invalid Vectors ID\n" << currentLine << "\n" << std::endl;
                                        exit(1);
                                    }

                                    tempVertices.push_back(manyVectors[VectorsID]); //Set Vectors
                                    tempVerticesOrder.push_back(VectorsID); //Store Vectors ID for when saving model
                                    break;
                                }

                                case 6: { //Read in V2
									unsigned int VectorsID = std::stoi(Placeholder, nullptr, 10);

                                    if (VectorsID < 0 || VectorsID > (manyVectors.size() - 1)) //Check if Vectors ID actually exists
                                    {
                                        std::cout << "Error due to invalid Vectors ID\n" << currentLine << "\n" << std::endl;
                                        exit(1);
                                    }

                                    tempVertices.push_back(manyVectors[VectorsID]); //Set Vectors
                                    tempVerticesOrder.push_back(VectorsID); //Store Vectors ID for when saving model
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

                    unsigned int VectorsID = std::stoi(Placeholder, nullptr, 10); //Read in V3

                    if (VectorsID < 0 || VectorsID > (manyVectors.size() - 1)) //Check if Vectors ID actually exists
                    {
                        std::cout << "Error due to invalid Vectors ID\n" << currentLine << "\n" << std::endl;
                        exit(1);
                    }

                    tempVertices.push_back(manyVectors[VectorsID]); //Set Vectors

                    tempVerticesOrder.push_back(VectorsID); //Store Vectors ID for when saving model

                    Cell* tempCell_Tetra = new Tetrahedron(tempVertices, tempVerticesOrder, tempMaterial); //All values have been read in so create the cell as tetrahedron

                    manyCells.push_back(tempCell_Tetra); //Add it to the cells list
                }

                if (currentCellType == 'p') //Read in pyramid
                {
                    std::vector<Vectors> tempVertices; //The vertices of pyramid
                    std::vector<int> tempVerticesOrder; //The Vectors being used by the pyramid from the models perspective
                    Material tempMaterial; //The material of pyramid

                    for (unsigned int currentPosition = 0, spaceCount = 0; currentPosition < currentLine.size(); currentPosition++) //Iterate across the line
                    {
                        if (currentLine[currentPosition] == ' ') //If a space is reached then whatever is in 'Placeholder' must be read in
                        {
                            switch (spaceCount) {
                                case 3: { //Read in material ID
									unsigned int MaterialID = std::stoi(Placeholder, nullptr, 10);

                                    if (MaterialID < 0 || MaterialID > ( manyMaterials.size() - 1)) //Check if material ID actually exists
                                    {
                                        std::cout << "Error due to invalid material ID\n" << currentLine << "\n" << std::endl;
                                        exit(1);
                                    }

                                    tempMaterial = manyMaterials[MaterialID];
                                    break;
                                }

                                case 4:  { //Read in V0
									unsigned int VectorsID = std::stoi(Placeholder, nullptr, 10);

                                    if (VectorsID < 0 || VectorsID > (manyVectors.size() - 1)) //Check if Vectors ID actually exists
                                    {
                                        std::cout << "Error due to invalid Vectors ID\n" << currentLine << "\n" << std::endl;
                                        exit(1);
                                    }

                                    tempVertices.push_back(manyVectors[VectorsID]);
                                    tempVerticesOrder.push_back(VectorsID);
                                    break;
                                }

                                case 5: { //Read in V1
									unsigned int VectorsID = std::stoi(Placeholder, nullptr, 10);

                                    if (VectorsID < 0 || VectorsID > (manyVectors.size() - 1)) //Check if Vectors ID actually exists
                                    {
                                        std::cout << "Error due to invalid Vectors ID\n" << currentLine << "\n" << std::endl;
                                        exit(1);
                                    }

                                    tempVertices.push_back(manyVectors[VectorsID]);
                                    tempVerticesOrder.push_back(VectorsID);
                                    break;
                                }

                                case 6: { //Read in V2
									unsigned int VectorsID = std::stoi(Placeholder, nullptr, 10);

                                    if (VectorsID < 0 || VectorsID > (manyVectors.size() - 1)) //Check if Vectors ID actually exists
                                    {
                                        std::cout << "Error due to invalid Vectors ID\n" << currentLine << "\n" << std::endl;
                                        exit(1);
                                    }

                                    tempVertices.push_back(manyVectors[VectorsID]);
                                    tempVerticesOrder.push_back(VectorsID);
                                    break;
                                }

                                case 7: { //Read in V3
									unsigned int VectorsID = std::stoi(Placeholder, nullptr, 10);

                                    if (VectorsID < 0 || VectorsID > (manyVectors.size() - 1)) //Check if Vectors ID actually exists
                                    {
                                        std::cout << "Error due to invalid Vectors ID\n" << currentLine << "\n" << std::endl;
                                        exit(1);
                                    }

                                    tempVertices.push_back(manyVectors[VectorsID]);
                                    tempVerticesOrder.push_back(VectorsID);
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

					unsigned int VectorsID = std::stoi(Placeholder, nullptr, 10); //Read in V4

                    if (VectorsID < 0 || VectorsID > (manyVectors.size() - 1)) //Check if Vectors ID actually exists
                    {
                        std::cout << "Error due to invalid Vectors ID\n" << currentLine << "\n" << std::endl;
                        exit(1);
                    }

                    tempVertices.push_back(manyVectors[VectorsID]); //Set Vectors

                    tempVerticesOrder.push_back(VectorsID); //Store Vectors ID for when saving model

                    Cell* tempCell_Pyra = new Pyramid(tempVertices, tempVerticesOrder, tempMaterial); //All values have been read in so create the cell as pyramid

                    manyCells.push_back(tempCell_Pyra); //Add it to the cells list
                }

                if (currentCellType == 'h') //Read in hexahedron
                {
                    std::vector<Vectors> tempVertices; //The vertices of hexahedron
                    std::vector<int> tempVerticesOrder; //The Vectors being used by the hexahedron from the models perspective
                    Material tempMaterial; //The material of hexahedron

                    for (unsigned int currentPosition = 0, spaceCount = 0; currentPosition < currentLine.size(); currentPosition++) //Iterate across the line
                    {
                        if (currentLine[currentPosition] == ' ') //If a space is reached then whatever is in 'Placeholder' must be read in
                        {
                            switch (spaceCount) {
                                case 3: { //Read in material ID
									unsigned int MaterialID = std::stoi(Placeholder, nullptr, 10);

                                    if (MaterialID < 0 || MaterialID > ( manyMaterials.size() - 1)) //Check if material ID actually exists
                                    {
                                        std::cout << "Error due to invalid material ID\n" << currentLine << "\n" << std::endl;
                                        exit(1);
                                    }

                                    tempMaterial = manyMaterials[MaterialID]; //If valid, store material ID
                                    break;
                                }

                                case 4: { //Read in V0
									unsigned int VectorsID = std::stoi(Placeholder, nullptr, 10);

                                    if (VectorsID < 0 || VectorsID > (manyVectors.size() - 1)) //Check if Vectors ID actually exists
                                    {
                                        std::cout << "Error due to invalid Vectors ID\n" << currentLine << "\n" << std::endl;
                                        exit(1);
                                    }

                                    tempVertices.push_back(manyVectors[VectorsID]);
                                    tempVerticesOrder.push_back(VectorsID);
                                    break;
                                }

                                case 5: { //Read in V1
									unsigned int VectorsID = std::stoi(Placeholder, nullptr, 10);

                                    if (VectorsID < 0 || VectorsID > (manyVectors.size() - 1)) //Check if Vectors ID actually exists
                                    {
                                        std::cout << "Error due to invalid Vectors ID\n" << currentLine << "\n" << std::endl;
                                        exit(1);
                                    }

                                    tempVertices.push_back(manyVectors[VectorsID]); //Set Vectors
                                    tempVerticesOrder.push_back(VectorsID); //Store Vectors ID for when saving model
                                    break;
                                }

                                case 6: { //Read in V2
									unsigned int VectorsID = std::stoi(Placeholder, nullptr, 10);

                                    if (VectorsID < 0 || VectorsID > (manyVectors.size() - 1)) //Check if Vectors ID actually exists
                                    {
                                        std::cout << "Error due to invalid Vectors ID\n" << currentLine << "\n" << std::endl;
                                        exit(1);
                                    }

                                    tempVertices.push_back(manyVectors[VectorsID]); //Set Vectors
                                    tempVerticesOrder.push_back(VectorsID); //Store Vectors ID for when saving model
                                    break;
                                }

                                case 7: { //Read in V3
									unsigned int VectorsID = std::stoi(Placeholder, nullptr, 10);

                                    if (VectorsID < 0 || VectorsID > (manyVectors.size() - 1)) //Check if Vectors ID actually exists
                                    {
                                        std::cout << "Error due to invalid Vectors ID\n" << currentLine << "\n" << std::endl;
                                        exit(1);
                                    }

                                    tempVertices.push_back(manyVectors[VectorsID]); //Set Vectors
                                    tempVerticesOrder.push_back(VectorsID); //Store Vectors ID for when saving model
                                    break;
                                }

                                case 8: { //Read in V4
									unsigned int VectorsID = std::stoi(Placeholder, nullptr, 10);

                                    if (VectorsID < 0 || VectorsID > (manyVectors.size() - 1)) //Check if Vectors ID actually exists
                                    {
                                        std::cout << "Error due to invalid Vectors ID\n" << currentLine << "\n" << std::endl;
                                        exit(1);
                                    }

                                    tempVertices.push_back(manyVectors[VectorsID]); //Set Vectors
                                    tempVerticesOrder.push_back(VectorsID); //Store Vectors ID for when saving model
                                    break;
                                }

                                case 9: { //Read in V5
									unsigned int VectorsID = std::stoi(Placeholder, nullptr, 10);

                                    if (VectorsID < 0 || VectorsID > (manyVectors.size() - 1)) //Check if Vectors ID actually exists
                                    {
                                        std::cout << "Error due to invalid Vectors ID\n" << currentLine << "\n" << std::endl;
                                        exit(1);
                                    }

                                    tempVertices.push_back(manyVectors[VectorsID]); //Set Vectors
                                    tempVerticesOrder.push_back(VectorsID); //Store Vectors ID for when saving model
                                    break;
                                }

                                case 10: { //Read in V6
									unsigned int VectorsID = std::stoi(Placeholder, nullptr, 10);

                                    if (VectorsID < 0 || VectorsID > (manyVectors.size() - 1)) //Check if Vectors ID actually exists
                                    {
                                        std::cout << "Error due to invalid Vectors ID\n" << currentLine << "\n" << std::endl;
                                        exit(1);
                                    }

                                    tempVertices.push_back(manyVectors[VectorsID]); //Set Vectors
                                    tempVerticesOrder.push_back(VectorsID); //Store Vectors ID for when saving model
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

					unsigned int VectorsID = std::stoi(Placeholder, nullptr, 10); //Read in V7

                    if (VectorsID < 0 || VectorsID > (manyVectors.size() - 1)) //Check if Vectors ID actually exists
                    {
                        std::cout << "Error due to invalid Vectors ID\n" << currentLine << "\n" << std::endl;
                        exit(1);
                    }

                    tempVertices.push_back(manyVectors[VectorsID]); //Set Vectors

                    tempVerticesOrder.push_back(VectorsID); //Store Vectors ID for when saving model

                    Cell* tempCell_Hexa = new Hexahedron(tempVertices, tempVerticesOrder, tempMaterial); //All values have been read in so create the cell as hexahedron

                    manyCells.push_back(tempCell_Hexa); //Add it to the cells list
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
            myFile << "v " << i << " " <<  manyVectors[i].GetXVector() << " " << manyVectors[i].GetYVector() << " " << manyVectors[i].GetZVector() << std::endl;
        }

        myFile << "\n# Cells (c, Cell ID, Cell Type, Material ID, Vectors ID, Vectors ID, Vectors ID, Vectors ID...)" << std::endl;

        for (unsigned int i = 0; i < cellOrder.size(); i++)
        {
            myFile << "c " << i << " " << cellOrder[i] << " ";

            myFile << manyCells[i]->Get_Material().GetID() << " ";

            for (unsigned int j = 0; j < manyCells[i]->Get_Vertices_Order().size(); j++)
                myFile << manyCells[i]->Get_Vertices_Order()[j] << " ";

            myFile << std::endl;
        }

        myFile.close(); //Close file; free up space; and stop reading
    }

    else //If file did not open correctly then returns false
    {
        std::cout << "Unable to open file for writing: " << FilePath << "\n" << std::endl;
        exit(1);
    }
}

double Model::Get_Volume(void)
{
    double totalVolume = 0;

    for (unsigned int i = 0; i < manyCells.size(); i++)
        totalVolume += manyCells[i]->Get_Volume();

    return totalVolume;
}

double Model::Get_Weight(void)
{
    double totalWeight = 0;

    for (unsigned int i = 0; i < manyCells.size(); i++)
        totalWeight += manyCells[i]->Get_Weight();

    return totalWeight;
}

Vectors Model::Get_Centre_Of_Gravity(void)
{
    std::vector<Vectors> CentresOfGravities;
    std::vector<double> CentresOfGravitiesWeights;

    //The next for loop stores all centres of gravities of all object and its weight
    //at the same point in two arrays

    for (unsigned int i = 0; i < manyCells.size(); i++)
    {
        CentresOfGravities.push_back(manyCells[i]->Get_Centre_Of_Gravity());
        CentresOfGravitiesWeights.push_back(manyCells[i]->Get_Weight());
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

    return (MinMax[0] + MinMax[1]) / 2.0; //Geometric centre = midpoint of min and max values
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
    for (unsigned int i = 0; i < manyCells.size(); i++)
    {
        manyCells[i]->Rotate(Rotation_In_Degrees, Axis_Of_Rotation, Centre_Of_Rotation);

        std::vector<int> CurrentVectorsOrder = manyCells[i]->Get_Vertices_Order();
        std::vector<Vectors> CurrentVertices = manyCells[i]->Get_Vertices();

        for (unsigned int j = 0; j < CurrentVertices.size(); j++)
            manyVectors[CurrentVectorsOrder[j]] = CurrentVertices[j];
    }
}




//Private Member Functions
std::vector<int> Model::Get_Vectors_Being_Used(void)
{
    //The next three for loops determines which vectors are being used by cycling through each type of cell and
    //the vector IDs for each cell
    std::vector<int> VectorsBeingUsed;

    for (unsigned int i = 0; i < manyCells.size(); i++) //Cycle through cells
    {
        for (unsigned int j = 0; j < manyCells[i]->Get_Vertices().size(); j++) //Cycle through the Vectors being used for that particular cell
        {
            int currentVectorsID = manyCells[i]->Get_Vertices_Order()[j];

            //If currentVectorsID has already been recorded in VectorsBeingUsed then continue to next iteration
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

	std::vector<int> VectorsBeingUsed = Get_Vectors_Being_Used();
	Vectors Minimum = manyVectors[VectorsBeingUsed[0]];
	Vectors Maximum = manyVectors[VectorsBeingUsed[0]];

    //This for loop cycles through all Vectors (that are being used) and finds the min and max values of
    //X, Y, and Z and assign them to the correct Vectors

    for (unsigned int i = 0; i < VectorsBeingUsed.size(); i++)
    {
        Vectors CurrentVectors = manyVectors[VectorsBeingUsed[i]];

        if (CurrentVectors.GetXVector() < Minimum.GetXVector())
			Minimum.SetX_Vector(CurrentVectors.GetXVector());

        else if (CurrentVectors.GetXVector() > Maximum.GetXVector())
			Maximum.SetX_Vector(CurrentVectors.GetXVector());

        if (CurrentVectors.GetYVector() < Minimum.GetYVector())
			Minimum.SetY_Vector(CurrentVectors.GetYVector());

        else if (CurrentVectors.GetYVector() > Maximum.GetYVector())
			Maximum.SetY_Vector(CurrentVectors.GetYVector());

        if (CurrentVectors.GetZVector() < Minimum.GetZVector())
			Minimum.SetZ_Vector(CurrentVectors.GetZVector());

        else if (CurrentVectors.GetZVector() > Maximum.GetZVector())
			Maximum.SetZ_Vector(CurrentVectors.GetZVector());
    }

	std::vector<Vectors> MinMax;
	MinMax.push_back(Minimum);
	MinMax.push_back(Maximum);

    return MinMax;
}
