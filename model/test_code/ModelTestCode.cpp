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

#include "Material.h"
#include "Vectors.h"
#include "Matrix.hpp"
#include "Cell.hpp"
#include "Model.hpp"
#include "Testing_File_Functions.h"
#include <iomanip>
#include <fstream>
#include <string>

int main()
{
    std::cout << std::fixed;
    std::cout << std::setprecision(14);

    unsigned int Testing_For_Error = 0;
    unsigned int Error = 0;
    unsigned int Private_Function_Error_Tracker = 0;

    std::cout << "------------------------------Model.hpp Test Code------------------------------" << std::endl;

    // Blank constructor test
    Model Empty_Model;

    // The model has several members all of these are either vector arrays or strings
    // We need to ensure taht they are created and are empty
    // This will also test the get functions for the model members

    Error = Testing(Empty_Model);

    // If passed Blank constuctor and get functions for private members work properly

    // Now we test the Set Materials/Vectors/Cells/Cell_Order functions
    // We will create these components and push them a vector list and them set them to the model

    Material Diamond(0, 3514.0, "B9F2FF", "Diamond" );
    Material Gold(1, 19300.0, "D4AF37", "Gold" );

    std::vector<Material> List_of_Material;
    List_of_Material.push_back(Diamond);
    List_of_Material.push_back(Gold);

    Empty_Model.Set_Materials(List_of_Material);

    std::vector<Vectors> List_of_Vectors;
    Vectors V0_Hex(-1.5,-2.5,-1.5);
    Vectors V1_Hex( 1.5,-2.5,-1.5);
    Vectors V2_Hex( 1.5, 2.5,-1.5);
    Vectors V3_Hex(-1.5, 2.5,-1.5);
    Vectors V4_Hex(-2.5,-2.5, 2.5);
    Vectors V5_Hex( 2.5,-2.5, 2.5);
    Vectors V6_Hex( 2.5, 2.5, 2.5);
    Vectors V7_Hex(-2.5, 2.5, 2.5);
    // Volume: 80.0 Weight: 281120.0

    Vectors V0_Tetra( 0.0,  0.0,  0.0);
    Vectors V1_Tetra( 5.0,  0.0,  1.0);
    Vectors V2_Tetra( 2.5,  3.2, -1.25);
    Vectors V3_Tetra(-1.9, -0.5, -2.23);
    // Volume: 5.6625 Weight: 109286.25
    // Totals: 85.6625 , 390406.25

    List_of_Vectors.push_back(V0_Hex);
    List_of_Vectors.push_back(V1_Hex);
    List_of_Vectors.push_back(V2_Hex);
    List_of_Vectors.push_back(V3_Hex);
    List_of_Vectors.push_back(V4_Hex);
    List_of_Vectors.push_back(V5_Hex);
    List_of_Vectors.push_back(V6_Hex);
    List_of_Vectors.push_back(V7_Hex);

    List_of_Vectors.push_back(V0_Tetra);
    List_of_Vectors.push_back(V1_Tetra);
    List_of_Vectors.push_back(V2_Tetra);
    List_of_Vectors.push_back(V3_Tetra);

    Empty_Model.Set_Vectors(List_of_Vectors);

    // now we need to create cells from the vectors and Materials then add them to the model
    std::vector<Vectors> HexaVertices;
    HexaVertices.push_back(V0_Hex);
    HexaVertices.push_back(V1_Hex);
    HexaVertices.push_back(V2_Hex);
    HexaVertices.push_back(V3_Hex);
    HexaVertices.push_back(V4_Hex);
    HexaVertices.push_back(V5_Hex);
    HexaVertices.push_back(V6_Hex);
    HexaVertices.push_back(V7_Hex);
    std::vector<Vectors> TetraVertices;
    TetraVertices.push_back(V0_Tetra);
    TetraVertices.push_back(V1_Tetra);
    TetraVertices.push_back(V2_Tetra);
    TetraVertices.push_back(V3_Tetra);
    std::vector<int> aRelevantVectorsOrder;
    aRelevantVectorsOrder.push_back(0);
    aRelevantVectorsOrder.push_back(1);
    aRelevantVectorsOrder.push_back(2);
    aRelevantVectorsOrder.push_back(3);
    aRelevantVectorsOrder.push_back(4);
    aRelevantVectorsOrder.push_back(5);
    aRelevantVectorsOrder.push_back(6);
    aRelevantVectorsOrder.push_back(7);
    std::vector<int> aRelevantVectorsOrder2;
    aRelevantVectorsOrder2.push_back(8);
    aRelevantVectorsOrder2.push_back(9);
    aRelevantVectorsOrder2.push_back(10);
    aRelevantVectorsOrder2.push_back(11);
    
    Cell* aHexahedron = new Hexahedron (HexaVertices, aRelevantVectorsOrder, Diamond);
    Cell* aTetra = new Tetrahedron (TetraVertices, aRelevantVectorsOrder2, Gold);

    std::vector<Cell*> List_of_Cells;
    List_of_Cells.push_back(aHexahedron);
    List_of_Cells.push_back(aTetra);

    Empty_Model.Set_Cells(List_of_Cells);

    std::string cellOrder;
    cellOrder.push_back('h');
    cellOrder.push_back('t');

    Empty_Model.Set_Cell_Order(cellOrder);

    //Now we test our hopefully our "Not so" Empty_Model

    Testing_For_Error = Test(Empty_Model, List_of_Material, List_of_Vectors, List_of_Cells, cellOrder);

    if (Testing_For_Error == 0)
        std::cout << "Set Functions Work Properly" << std::endl;
    else
    {
        std::cout << "Set Functions Do Not Work Properly" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }

    Testing_For_Error = Testing(Empty_Model.Get_Volume(), 85.6625 );

    if (Testing_For_Error == 0)
        std::cout << "Get Volume Function Works Properly" << std::endl;
    else
    {
        std::cout << "Get Volume Function Does Not Work Properly" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }

    Testing_For_Error = Testing(Empty_Model.Get_Weight(), 390406.25 );

    if (Testing_For_Error == 0)
        std::cout << "Get Weight Function Works Properly" << std::endl;
    else
    {
        std::cout << "Get Weight Function Does Not Work Properly" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }
    Vectors CoG(0.39190138477547, 0.18895245337389, 0.30649063208730);
    Testing_For_Error = Testing(Empty_Model.Get_Centre_Of_Gravity(), CoG);

    if (Testing_For_Error == 0)
    {
        std::cout << "Get Centre Of Gravity Function Works Properly" << std::endl;
        Private_Function_Error_Tracker++;
    }
        else
    {
        std::cout << "Get Centre Of Gravity Function Does Not Work Properly" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }

    Vectors GeoCentre(1.25, 0.35, 0.135);
    Testing_For_Error = Testing(Empty_Model.Get_Geometric_Centre(), GeoCentre );

    if (Testing_For_Error == 0)
    {
        std::cout << "Get Geometric Centre Function Works Properly" << std::endl;
        Private_Function_Error_Tracker++;
    }
    else
    {
        std::cout << "Get Geometric Centre Function Does Not Work Properly" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }

    Vectors OverallDimensions(7.5, 5.7, 4.73);
    Testing_For_Error = Testing(Empty_Model.Get_Overall_Dimensions(), OverallDimensions );

    if (Testing_For_Error == 0)
    {
        std::cout << "Get Overall Dimesions Function Works Properly" << std::endl;
        Private_Function_Error_Tracker++;
    }
    else
    {
        std::cout << "Get Overall Dimesions Function Does Not Work Properly" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }

    if (Private_Function_Error_Tracker != 3)
        std::cout << "There is an Error in the Private Member Functions of Get_Vectors_Being_Used or Get_Min_Max" << std::endl;
    else
        std::cout << "Private Member Functions Work Properly" << std::endl;

    // Now we test the copy constructor

    Model Copy(Empty_Model);
    Testing_For_Error = Testing(Empty_Model, Copy);

    if (Testing_For_Error == 0)
    {
        std::cout << "Copy Constuctor Works Properly" << std::endl;
    }
    else
    {
        std::cout << "Copy Constuctor Does Not Work Properly" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }

    // Now we test the save/load function

    Empty_Model.Save_Model("Model_Example.txt");
    Model Loading_Example;
    Loading_Example.Load_Model("Model_Example.txt");

    Testing_For_Error = Testing(Empty_Model, Loading_Example);

    if (Testing_For_Error == 0)
    {
        std::cout << "Saving and Loading Functions Work Properly" << std::endl;
    }
    else
    {
        std::cout << "Saving and Loading Functions Do Not Work Properly" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }

    // Now we test the operator= function
    // To do this we are going to use the blank constuctor to create a model
    // Which will be Empty and we will set our Empty_Model equal to the new blank Model

    Model Blank;
    Empty_Model = Blank;

    Testing_For_Error = Testing(Empty_Model, Blank);

    if (Testing_For_Error == 0)
    {
        std::cout << "Set Equal to Operator Overload Function Works Properly" << std::endl;
    }
    else
    {
        std::cout << "Set Equal to Operator Overload Function Does Not Work Properly" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }

    // The next function to test is the Rotate the number of possible rotations
    // around the x, y, and Z axis from 0-360 degrees is near infinate. We will
    // only test 3 rotations about the x, y, and z axis at 90 degrees for each
    // rotation.

    Vectors Centre_Of_Rotation(0.0, 0.0, 0.0);
    Loading_Example.Rotate(90.0 ,'x', Centre_Of_Rotation);
    // Now compared to a model that is manually rotated

    Model X_Rotated;
    X_Rotated.Set_Materials(List_of_Material);
    std::vector<Vectors> X_Rotated_Vectors;

    Vectors V0_Hex_X_Rotated(-1.5,  1.5, -2.5);
    Vectors V1_Hex_X_Rotated( 1.5,  1.5, -2.5);
    Vectors V2_Hex_X_Rotated( 1.5,  1.5,  2.5);
    Vectors V3_Hex_X_Rotated(-1.5,  1.5,  2.5);
    Vectors V4_Hex_X_Rotated(-2.5, -2.5, -2.5);
    Vectors V5_Hex_X_Rotated( 2.5, -2.5, -2.5);
    Vectors V6_Hex_X_Rotated( 2.5, -2.5,  2.5);
    Vectors V7_Hex_X_Rotated(-2.5, -2.5,  2.5);

    Vectors V0_Tetra_X_Rotated( 0.0,  0.0,  0.0);
    Vectors V1_Tetra_X_Rotated( 5.0, -1.0,  0.0);
    Vectors V2_Tetra_X_Rotated( 2.5, 1.25,  3.2);
    Vectors V3_Tetra_X_Rotated(-1.9, 2.23, -0.5);

    X_Rotated_Vectors.push_back(V0_Hex_X_Rotated);
    X_Rotated_Vectors.push_back(V1_Hex_X_Rotated);
    X_Rotated_Vectors.push_back(V2_Hex_X_Rotated);
    X_Rotated_Vectors.push_back(V3_Hex_X_Rotated);
    X_Rotated_Vectors.push_back(V4_Hex_X_Rotated);
    X_Rotated_Vectors.push_back(V5_Hex_X_Rotated);
    X_Rotated_Vectors.push_back(V6_Hex_X_Rotated);
    X_Rotated_Vectors.push_back(V7_Hex_X_Rotated);

    X_Rotated_Vectors.push_back(V0_Tetra_X_Rotated);
    X_Rotated_Vectors.push_back(V1_Tetra_X_Rotated);
    X_Rotated_Vectors.push_back(V2_Tetra_X_Rotated);
    X_Rotated_Vectors.push_back(V3_Tetra_X_Rotated);

    X_Rotated.Set_Vectors(X_Rotated_Vectors);

    std::vector<Vectors> HexaVertices_X_Rotated;
    HexaVertices_X_Rotated.push_back(V0_Hex_X_Rotated);
    HexaVertices_X_Rotated.push_back(V1_Hex_X_Rotated);
    HexaVertices_X_Rotated.push_back(V2_Hex_X_Rotated);
    HexaVertices_X_Rotated.push_back(V3_Hex_X_Rotated);
    HexaVertices_X_Rotated.push_back(V4_Hex_X_Rotated);
    HexaVertices_X_Rotated.push_back(V5_Hex_X_Rotated);
    HexaVertices_X_Rotated.push_back(V6_Hex_X_Rotated);
    HexaVertices_X_Rotated.push_back(V7_Hex_X_Rotated);
    std::vector<Vectors> TetraVertices_X_Rotated;
    TetraVertices_X_Rotated.push_back(V0_Tetra_X_Rotated);
    TetraVertices_X_Rotated.push_back(V1_Tetra_X_Rotated);
    TetraVertices_X_Rotated.push_back(V2_Tetra_X_Rotated);
    TetraVertices_X_Rotated.push_back(V3_Tetra_X_Rotated);

    Cell* aHexahedron_X_Rotated = new Hexahedron (HexaVertices_X_Rotated, aRelevantVectorsOrder, Diamond);
    Cell* aTetra_X_Rotated = new Tetrahedron (TetraVertices_X_Rotated, aRelevantVectorsOrder2, Gold);

    std::vector<Cell*> List_of_Cells_X_Rotated;
    List_of_Cells_X_Rotated.push_back(aHexahedron_X_Rotated);
    List_of_Cells_X_Rotated.push_back(aTetra_X_Rotated);

    X_Rotated.Set_Cells(List_of_Cells_X_Rotated);

    std::string cellOrder_X_Rotated;
    cellOrder_X_Rotated.push_back('h');
    cellOrder_X_Rotated.push_back('t');

    X_Rotated.Set_Cell_Order(cellOrder_X_Rotated);


    Testing_For_Error = Testing(Loading_Example, X_Rotated);

    if (Testing_For_Error == 0)
    {
        std::cout << "X Rotation Works Properly" << std::endl;
    }
    else
    {
        std::cout << "X Rotation Does Not Work Properly" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }

    Loading_Example.Rotate(90.0 ,'y',Centre_Of_Rotation);
    // Now compared to a model that is manually rotated
    Model Y_Rotated;
    Y_Rotated.Set_Materials(List_of_Material);
    std::vector<Vectors> Y_Rotated_Vectors;

    Vectors V0_Hex_Y_Rotated(-2.5,  1.5,  1.5);
    Vectors V1_Hex_Y_Rotated(-2.5,  1.5, -1.5);
    Vectors V2_Hex_Y_Rotated( 2.5,  1.5, -1.5);
    Vectors V3_Hex_Y_Rotated( 2.5,  1.5,  1.5);
    Vectors V4_Hex_Y_Rotated(-2.5, -2.5,  2.5);
    Vectors V5_Hex_Y_Rotated(-2.5, -2.5, -2.5);
    Vectors V6_Hex_Y_Rotated( 2.5, -2.5, -2.5);
    Vectors V7_Hex_Y_Rotated( 2.5, -2.5,  2.5);

    Vectors V0_Tetra_Y_Rotated( 0.0,  0.0,  0.0);
    Vectors V1_Tetra_Y_Rotated( 0.0, -1.0, -5.0);
    Vectors V2_Tetra_Y_Rotated( 3.2, 1.25, -2.5);
    Vectors V3_Tetra_Y_Rotated(-0.5, 2.23,  1.9);

    Y_Rotated_Vectors.push_back(V0_Hex_Y_Rotated);
    Y_Rotated_Vectors.push_back(V1_Hex_Y_Rotated);
    Y_Rotated_Vectors.push_back(V2_Hex_Y_Rotated);
    Y_Rotated_Vectors.push_back(V3_Hex_Y_Rotated);
    Y_Rotated_Vectors.push_back(V4_Hex_Y_Rotated);
    Y_Rotated_Vectors.push_back(V5_Hex_Y_Rotated);
    Y_Rotated_Vectors.push_back(V6_Hex_Y_Rotated);
    Y_Rotated_Vectors.push_back(V7_Hex_Y_Rotated);

    Y_Rotated_Vectors.push_back(V0_Tetra_Y_Rotated);
    Y_Rotated_Vectors.push_back(V1_Tetra_Y_Rotated);
    Y_Rotated_Vectors.push_back(V2_Tetra_Y_Rotated);
    Y_Rotated_Vectors.push_back(V3_Tetra_Y_Rotated);

    Y_Rotated.Set_Vectors(Y_Rotated_Vectors);

    std::vector<Vectors> HexaVertices_Y_Rotated;
    HexaVertices_Y_Rotated.push_back(V0_Hex_Y_Rotated);
    HexaVertices_Y_Rotated.push_back(V1_Hex_Y_Rotated);
    HexaVertices_Y_Rotated.push_back(V2_Hex_Y_Rotated);
    HexaVertices_Y_Rotated.push_back(V3_Hex_Y_Rotated);
    HexaVertices_Y_Rotated.push_back(V4_Hex_Y_Rotated);
    HexaVertices_Y_Rotated.push_back(V5_Hex_Y_Rotated);
    HexaVertices_Y_Rotated.push_back(V6_Hex_Y_Rotated);
    HexaVertices_Y_Rotated.push_back(V7_Hex_Y_Rotated);
    std::vector<Vectors> TetraVertices_Y_Rotated;
    TetraVertices_Y_Rotated.push_back(V0_Tetra_Y_Rotated);
    TetraVertices_Y_Rotated.push_back(V1_Tetra_Y_Rotated);
    TetraVertices_Y_Rotated.push_back(V2_Tetra_Y_Rotated);
    TetraVertices_Y_Rotated.push_back(V3_Tetra_Y_Rotated);

    Cell* aHexahedron_Y_Rotated = new Hexahedron (HexaVertices_Y_Rotated, aRelevantVectorsOrder, Diamond);
    Cell* aTetra_Y_Rotated = new Tetrahedron (TetraVertices_Y_Rotated, aRelevantVectorsOrder2, Gold);

    std::vector<Cell*> List_of_Cells_Y_Rotated;
    List_of_Cells_Y_Rotated.push_back(aHexahedron_Y_Rotated);
    List_of_Cells_Y_Rotated.push_back(aTetra_Y_Rotated);

    Y_Rotated.Set_Cells(List_of_Cells_Y_Rotated);

    std::string cellOrder_Y_Rotated;
    cellOrder_Y_Rotated.push_back('h');
    cellOrder_Y_Rotated.push_back('t');

    Y_Rotated.Set_Cell_Order(cellOrder_Y_Rotated);

    Testing_For_Error = Testing(Loading_Example, Y_Rotated);

    if (Testing_For_Error == 0)
    {
        std::cout << "Y Rotation Works Properly" << std::endl;
    }
    else
    {
        std::cout << "Y Rotation Does Not Work Properly" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }


    Loading_Example.Rotate(90.0 ,'z',Centre_Of_Rotation);
    // Now compared to a model that is manually rotated
    Model Z_Rotated;
    Z_Rotated.Set_Materials(List_of_Material);
    std::vector<Vectors> Z_Rotated_Vectors;

    Vectors V0_Hex_Z_Rotated(-1.5, -2.5,  1.5);
    Vectors V1_Hex_Z_Rotated(-1.5, -2.5, -1.5);
    Vectors V2_Hex_Z_Rotated(-1.5,  2.5, -1.5);
    Vectors V3_Hex_Z_Rotated(-1.5,  2.5,  1.5);
    Vectors V4_Hex_Z_Rotated( 2.5, -2.5,  2.5);
    Vectors V5_Hex_Z_Rotated( 2.5, -2.5, -2.5);
    Vectors V6_Hex_Z_Rotated( 2.5,  2.5, -2.5);
    Vectors V7_Hex_Z_Rotated( 2.5,  2.5,  2.5);

    Vectors V0_Tetra_Z_Rotated(  0.0,  0.0,  0.0);
    Vectors V1_Tetra_Z_Rotated(  1.0,  0.0, -5.0);
    Vectors V2_Tetra_Z_Rotated(-1.25,  3.2, -2.5);
    Vectors V3_Tetra_Z_Rotated(-2.23, -0.5,  1.9);

    Z_Rotated_Vectors.push_back(V0_Hex_Z_Rotated);
    Z_Rotated_Vectors.push_back(V1_Hex_Z_Rotated);
    Z_Rotated_Vectors.push_back(V2_Hex_Z_Rotated);
    Z_Rotated_Vectors.push_back(V3_Hex_Z_Rotated);
    Z_Rotated_Vectors.push_back(V4_Hex_Z_Rotated);
    Z_Rotated_Vectors.push_back(V5_Hex_Z_Rotated);
    Z_Rotated_Vectors.push_back(V6_Hex_Z_Rotated);
    Z_Rotated_Vectors.push_back(V7_Hex_Z_Rotated);

    Z_Rotated_Vectors.push_back(V0_Tetra_Z_Rotated);
    Z_Rotated_Vectors.push_back(V1_Tetra_Z_Rotated);
    Z_Rotated_Vectors.push_back(V2_Tetra_Z_Rotated);
    Z_Rotated_Vectors.push_back(V3_Tetra_Z_Rotated);

    Z_Rotated.Set_Vectors(Z_Rotated_Vectors);

    std::vector<Vectors> HexaVertices_Z_Rotated;
    HexaVertices_Z_Rotated.push_back(V0_Hex_Z_Rotated);
    HexaVertices_Z_Rotated.push_back(V1_Hex_Z_Rotated);
    HexaVertices_Z_Rotated.push_back(V2_Hex_Z_Rotated);
    HexaVertices_Z_Rotated.push_back(V3_Hex_Z_Rotated);
    HexaVertices_Z_Rotated.push_back(V4_Hex_Z_Rotated);
    HexaVertices_Z_Rotated.push_back(V5_Hex_Z_Rotated);
    HexaVertices_Z_Rotated.push_back(V6_Hex_Z_Rotated);
    HexaVertices_Z_Rotated.push_back(V7_Hex_Z_Rotated);
    std::vector<Vectors> TetraVertices_Z_Rotated;
    TetraVertices_Z_Rotated.push_back(V0_Tetra_Z_Rotated);
    TetraVertices_Z_Rotated.push_back(V1_Tetra_Z_Rotated);
    TetraVertices_Z_Rotated.push_back(V2_Tetra_Z_Rotated);
    TetraVertices_Z_Rotated.push_back(V3_Tetra_Z_Rotated);

    Cell* aHexahedron_Z_Rotated = new Hexahedron (HexaVertices_Z_Rotated, aRelevantVectorsOrder, Diamond);
    Cell* aTetra_Z_Rotated = new Tetrahedron (TetraVertices_Z_Rotated, aRelevantVectorsOrder2, Gold);

    std::vector<Cell*> List_of_Cells_Z_Rotated;
    List_of_Cells_Z_Rotated.push_back(aHexahedron_Z_Rotated);
    List_of_Cells_Z_Rotated.push_back(aTetra_Z_Rotated);

    Z_Rotated.Set_Cells(List_of_Cells_Z_Rotated);

    std::string cellOrder_Z_Rotated;
    cellOrder_Z_Rotated.push_back('h');
    cellOrder_Z_Rotated.push_back('t');

    Z_Rotated.Set_Cell_Order(cellOrder_Z_Rotated);

    Testing_For_Error = Testing(Loading_Example, Z_Rotated);

    if (Testing_For_Error == 0)
    {
        std::cout << "Z Rotation Works Properly" << std::endl;
    }
    else
    {
        std::cout << "Z Rotation Does Not Work Properly" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
    }

    std::cout << "************************" << std::endl;
    if(Error == 0 )
        std::cout << "End of Test: Successful" << std::endl;
    else
        std::cout << "End of Test: Failure" << std::endl;
    std::cout << "************************" << std::endl;

    return (Error == 0) ? 0 : 1;
}
