//
//  Cell.cpp
//  Computing Project
//
//  Created by Junaid Afzal on 10/11/2019.
//  Copyright © 2019 Junaid Afzal. All rights reserved.
//
//  This source file contains implementations the object Cell and
//  the sub-objects Tetrahedron, Pyramid and Hexahedron.
//

#include "Cell.hpp"
#include "Matrix.hpp"
#include <cmath>

#include "Vectors.h"

//------------------------------------------------------------------------CELL MEMBER FUNCTIONS------------------------------------------------------------------------//

//Destructor
Cell::Cell() { }

Cell::~Cell() { }





//Custom std::cout function
std::ostream& operator<< (std::ostream& Output, const Cell& aCell)
{
    for (unsigned int i = 0; i < aCell.Vertices.size(); i++)
    {
        Output << "V" << i << " " << aCell.Vertices[i];
    }

    Output << "Material " << aCell.theMaterial;

    return Output;
}





//Custom operator function
Cell& Cell::operator = (const Cell& aCell)
{
    if (&aCell == this)
        return *this;

    else
    {
        Vertices = aCell.Vertices;
        VerticesOrder = aCell.VerticesOrder;
        theMaterial = aCell.theMaterial;

        return *this;
    }
}





//Set functions
void Cell::Set_Vertices(const std::vector<Vectors>& aVertices) { Vertices = aVertices; }

void Cell::Set_Vertices_Order(const std::vector<int>& aVectorsOrder) { VerticesOrder = aVectorsOrder; }

void Cell::Set_Material(const Material& aMaterial) { theMaterial = aMaterial; }





//Get functions
std::vector<Vectors> Cell::Get_Vertices(void) { return Vertices; }

std::vector<int> Cell::Get_Vertices_Order(void) { return VerticesOrder; }

Material Cell::Get_Material(void) { return theMaterial;  }





//Cell specific functions
double Cell::Get_Volume(void)
{
    std::cout << "No implementation of calculating volume for this object" << std::endl;

    return -1;
}

double Cell::Get_Weight(void)
{
    std::cout << "No implementation of weight volume for this object" << std::endl;

    return -1;
}

Vectors Cell::Get_Centre_Of_Gravity()
{
    std::cout << "No implementation of calculating centre of gravity for this object" << std::endl;

    Vectors temp(-1, -1, -1);

    return temp;
}

void Cell::Rotate(double Rotation_In_Degrees, char Axis_Of_Rotation, Vectors Centre_Of_Rotation)
{
    //Rotates hexahedron an amount of degrees about it's centre along the X, Y or Z axis

    //Create a rotation matrix based on degrees and axis of rotation
    Matrix3x3 RotationMatrix;
    RotationMatrix.Initialise_As_Rotation_Matrix(Rotation_In_Degrees, Axis_Of_Rotation);

    for (unsigned int i = 0; i < Vertices.size(); i++)
        Vertices[i] = (RotationMatrix * (Vertices[i] - Centre_Of_Rotation)) + Centre_Of_Rotation;
    //Subtract centre of hexahedron from all Vectors to move centre of hexahedron to the origin
    //                                          ^^^^^^^^^^^^
    //Apply rotation matrix to all vertcies
    //                 ^^^^^^^^^^^^
    //Add centre of hexahedron to all Vectors to move centre of hexahedron back to where it was
    //                                                                          ^^^^^^^^^^^^                      
}










//------------------------------------------------------------------------TETRAHEDRON MEMBER FUNCTIONS------------------------------------------------------------------------//

//Constructors and destructor
Tetrahedron::Tetrahedron(const std::vector<Vectors>& aVertices, const std::vector<int>& aVerticesOrder, const Material& aMaterial)
{
    Set_Vertices(aVertices);
    Set_Vertices_Order(aVerticesOrder);
    Set_Material(aMaterial);
}

Tetrahedron::Tetrahedron(void)
{
    std::vector<Vectors> tempVertices;
   
    Vectors tempVectors;
    
    tempVertices.push_back(tempVectors);
    tempVertices.push_back(tempVectors);
    tempVertices.push_back(tempVectors);
    tempVertices.push_back(tempVectors);

    Set_Vertices(tempVertices);
}

Tetrahedron::~Tetrahedron(void) { }





//Tetrahedron specific functions
double Tetrahedron::Get_Volume(void)
{
    //Top down view of Vectors numbering assumption
    //
    //    V2         V1
    //
    //         V3
    //
    //         V0

    std::vector <Vectors> tempVertices = Get_Vertices();
    
    Vectors a = tempVertices[0] - tempVertices[3]; //V0 - V3;
    Vectors b = tempVertices[1] - tempVertices[3]; //V1 - V3;
    Vectors c = tempVertices[2] - tempVertices[3]; //V2 - V3;
    
    //Volume is calculated using the triple scalar product formula
    
    return abs( a.Scalar_Product( b * c ) / 6.0 );
}

double Tetrahedron::Get_Weight(void)
{
    return Get_Volume() * Get_Material().GetDensity();
}

Vectors Tetrahedron::Get_Centre_Of_Gravity(void)
{
    //Top down view of Vectors numbering assumption
    //
    //    V2         V1
    //
    //         V3
    //
    //         V0
    
    //Centroid = centre of gravity, assuming uniform density across object, and
    //is calculated by finding the average of each co-ordinate

    std::vector <Vectors> tempVertices = Get_Vertices();
    
    Vectors Centroid;
    
    Centroid.SetX_Vector( (tempVertices[0].GetXVector() + tempVertices[1].GetXVector() + tempVertices[2].GetXVector() + tempVertices[3].GetXVector() ) / 4.0 );
    Centroid.SetY_Vector( (tempVertices[0].GetYVector() + tempVertices[1].GetYVector() + tempVertices[2].GetYVector() + tempVertices[3].GetYVector() ) / 4.0 );
    Centroid.SetZ_Vector( (tempVertices[0].GetZVector() + tempVertices[1].GetZVector() + tempVertices[2].GetZVector() + tempVertices[3].GetZVector() ) / 4.0 );
    
    return Centroid;
}










//------------------------------------------------------------------------PYRAMID MEMBER FUNCTIONS------------------------------------------------------------------------//

//Constructors and destructor
Pyramid::Pyramid(const std::vector<Vectors>& aVertices, const std::vector<int>& aVerticesOrder, const Material& aMaterial)
{
    Set_Vertices(aVertices);
    Set_Vertices_Order(aVerticesOrder);
    Set_Material(aMaterial);
}

Pyramid::Pyramid(void) 
{
    std::vector<Vectors> tempVertices;
    
    Vectors tempVectors;
    
    tempVertices.push_back(tempVectors);
    tempVertices.push_back(tempVectors);
    tempVertices.push_back(tempVectors);
    tempVertices.push_back(tempVectors);
    tempVertices.push_back(tempVectors);

    Set_Vertices(tempVertices);
}

Pyramid::~Pyramid(void) { }





//Pyramid specific functions
double Pyramid::Get_Volume(void)
{
    //Top down view of Vectors numbering assumption
    //
    //    V3         V2
    //
    //         V4
    //
    //    V0         V1
    
    //Split the pyramid along V0 - V4 - V2 "line" to create two tetrahedrons and calculate
    //the volume of two tetrahedrons and add them together
    std::vector<Vectors> tempVertices = Get_Vertices();
    std::vector<Vectors> Tetra_a_Vertices; // = { tempVertices[0], tempVertices[2], tempVertices[3], tempVertices[4] };
    Tetra_a_Vertices.push_back(tempVertices[0]);
    Tetra_a_Vertices.push_back(tempVertices[2]);
    Tetra_a_Vertices.push_back(tempVertices[3]);
    Tetra_a_Vertices.push_back(tempVertices[4]);
    std::vector<Vectors> Tetra_b_Vertices; // = { tempVertices[0], tempVertices[1], tempVertices[2], tempVertices[4] };
    Tetra_b_Vertices.push_back(tempVertices[0]);
    Tetra_b_Vertices.push_back(tempVertices[1]);
    Tetra_b_Vertices.push_back(tempVertices[2]);
    Tetra_b_Vertices.push_back(tempVertices[4]);

    Tetrahedron a(Tetra_a_Vertices, Get_Vertices_Order(), Get_Material()); //V0, V2, V3, V4
    Tetrahedron b(Tetra_b_Vertices, Get_Vertices_Order(), Get_Material()); //V0, V1, V2, V4
    
    return a.Get_Volume() + b.Get_Volume();
}

double Pyramid::Get_Weight(void)
{
    return Get_Volume() * Get_Material().GetDensity();
}

Vectors Pyramid::Get_Centre_Of_Gravity(void)
{
    //Top down view of Vectors numbering assumption
    //
    //    V3         V2
    //
    //         V4
    //
    //    V0         V1
    
    //Split the pyramid along V0 - V4 - V2 "line" to create two tetrahedrons and calculate centre of gravity of each one
    //The two tetrahedrons will have the same volume, thus the same weight and thus the centre of gravity of the pyramid will
    //be the midpoint between the two centres of gravities of the two tetrahedrons
    std::vector<Vectors> tempVertices = Get_Vertices();
    std::vector<Vectors> Tetra_a_Vertices; // = { tempVertices[0], tempVertices[2], tempVertices[3], tempVertices[4] };
    Tetra_a_Vertices.push_back(tempVertices[0]);
    Tetra_a_Vertices.push_back(tempVertices[2]);
    Tetra_a_Vertices.push_back(tempVertices[3]);
    Tetra_a_Vertices.push_back(tempVertices[4]);
    std::vector<Vectors> Tetra_b_Vertices; // = { tempVertices[0], tempVertices[1], tempVertices[2], tempVertices[4] };
    Tetra_b_Vertices.push_back(tempVertices[0]);
    Tetra_b_Vertices.push_back(tempVertices[1]);
    Tetra_b_Vertices.push_back(tempVertices[2]);
    Tetra_b_Vertices.push_back(tempVertices[4]);

    Tetrahedron a(Tetra_a_Vertices, Get_Vertices_Order(), Get_Material()); //V0, V2, V3, V4
    Tetrahedron b(Tetra_b_Vertices, Get_Vertices_Order(), Get_Material()); //V0, V1, V2, V4
    
    Vectors aCentroid = a.Get_Centre_Of_Gravity();
    Vectors bCentroid = b.Get_Centre_Of_Gravity();
    
    Vectors Centroid = (aCentroid + bCentroid) / 2.0;
    
    return Centroid;
}










//------------------------------------------------------------------------HEXAHEDRON MEMBER FUNCTIONS------------------------------------------------------------------------//

//Constructors and destructor
Hexahedron::Hexahedron(const std::vector<Vectors>& aVertices, const std::vector<int>& aVerticesOrder, const Material& aMaterial)
{
    this->Set_Vertices(aVertices);
    this->Set_Vertices_Order(aVerticesOrder);
    this->Set_Material(aMaterial);
}

Hexahedron::Hexahedron(void)
{
    std::vector<Vectors> tempVertices;

    Vectors tempVectors;

    tempVertices.push_back(tempVectors);
    tempVertices.push_back(tempVectors);
    tempVertices.push_back(tempVectors);
    tempVertices.push_back(tempVectors);
    tempVertices.push_back(tempVectors);
    tempVertices.push_back(tempVectors);
    tempVertices.push_back(tempVectors);
    tempVertices.push_back(tempVectors);

    Set_Vertices(tempVertices);
}

Hexahedron::~Hexahedron(void) { }





//Hexahedron specific functions
double Hexahedron::Get_Volume(void)
{
    //Top down view of Vectors numbering assumption
    //
    //    V3/V7         V2/V6
    //
    //
    //
    //    V0/V4         V1/V5
    
    //Split the hexahedron in to three pyramids and find volume of each
    //See http://mathcentral.uregina.ca/QQ/database/QQ.09.06/siva1.html for more info
    std::vector<Vectors> tempVertices = Get_Vertices();
    std::vector<Vectors> Pyra_a_Vertices; // = { tempVertices[0], tempVertices[1], tempVertices[2], tempVertices[3], tempVertices[6] };
    Pyra_a_Vertices.push_back(tempVertices[0]);
    Pyra_a_Vertices.push_back(tempVertices[1]);
    Pyra_a_Vertices.push_back(tempVertices[2]);
    Pyra_a_Vertices.push_back(tempVertices[3]);
    Pyra_a_Vertices.push_back(tempVertices[6]);
    std::vector<Vectors> Pyra_b_Vertices; // = { tempVertices[0], tempVertices[1], tempVertices[5], tempVertices[4], tempVertices[6] };
    Pyra_b_Vertices.push_back(tempVertices[0]);
    Pyra_b_Vertices.push_back(tempVertices[1]);
    Pyra_b_Vertices.push_back(tempVertices[5]);
    Pyra_b_Vertices.push_back(tempVertices[4]);
    Pyra_b_Vertices.push_back(tempVertices[6]);
    std::vector<Vectors> Pyra_c_Vertices; // = { tempVertices[0], tempVertices[3], tempVertices[7], tempVertices[4], tempVertices[6] };
    Pyra_c_Vertices.push_back(tempVertices[0]);
    Pyra_c_Vertices.push_back(tempVertices[3]);
    Pyra_c_Vertices.push_back(tempVertices[7]);
    Pyra_c_Vertices.push_back(tempVertices[4]);
    Pyra_c_Vertices.push_back(tempVertices[6]);

    Pyramid a(Pyra_a_Vertices, Get_Vertices_Order(), Get_Material()); //V0, V1, V2, V3, V6
    Pyramid b(Pyra_b_Vertices, Get_Vertices_Order(), Get_Material()); //V0, V1, V5, V4, V6
    Pyramid c(Pyra_c_Vertices, Get_Vertices_Order(), Get_Material()); //V0, V3, V7, V4, V6

    return a.Get_Volume() + b.Get_Volume() + c.Get_Volume();
}

double Hexahedron::Get_Weight(void)
{
    return Get_Volume() * Get_Material().GetDensity();
}

Vectors Hexahedron::Get_Centre_Of_Gravity(void)
{
    //Top down view of Vectors numbering assumption
    //
    //    V3/V7         V2/V6
    //
    //
    //
    //    V0/V4         V1/V5
    
    //Split the hexahedron in to three pyramids and find centre of gravity of each
    //See http://mathcentral.uregina.ca/QQ/database/QQ.09.06/siva1.html for more info
    //Then centroid of hexahedron will be the average/midpoint of the pyramid centroids as they have equal volume and therefore equal weight
    std::vector<Vectors> tempVertices = Get_Vertices();
    std::vector<Vectors> Pyra_a_Vertices; // = { tempVertices[0], tempVertices[1], tempVertices[2], tempVertices[3], tempVertices[6] };
    Pyra_a_Vertices.push_back(tempVertices[0]);
    Pyra_a_Vertices.push_back(tempVertices[1]);
    Pyra_a_Vertices.push_back(tempVertices[2]);
    Pyra_a_Vertices.push_back(tempVertices[3]);
    Pyra_a_Vertices.push_back(tempVertices[6]);
    std::vector<Vectors> Pyra_b_Vertices; // = { tempVertices[0], tempVertices[1], tempVertices[5], tempVertices[4], tempVertices[6] };
    Pyra_b_Vertices.push_back(tempVertices[0]);
    Pyra_b_Vertices.push_back(tempVertices[1]);
    Pyra_b_Vertices.push_back(tempVertices[5]);
    Pyra_b_Vertices.push_back(tempVertices[4]);
    Pyra_b_Vertices.push_back(tempVertices[6]);
    std::vector<Vectors> Pyra_c_Vertices; // = { tempVertices[0], tempVertices[3], tempVertices[7], tempVertices[4], tempVertices[6] };
    Pyra_c_Vertices.push_back(tempVertices[0]);
    Pyra_c_Vertices.push_back(tempVertices[3]);
    Pyra_c_Vertices.push_back(tempVertices[7]);
    Pyra_c_Vertices.push_back(tempVertices[4]);
    Pyra_c_Vertices.push_back(tempVertices[6]);

    Pyramid a(Pyra_a_Vertices, Get_Vertices_Order(), Get_Material()); //V0, V1, V2, V3, V6
    Pyramid b(Pyra_b_Vertices, Get_Vertices_Order(), Get_Material()); //V0, V1, V5, V4, V6
    Pyramid c(Pyra_c_Vertices, Get_Vertices_Order(), Get_Material()); //V0, V3, V7, V4, V6
    
    Vectors Centroid = ( a.Get_Centre_Of_Gravity() + b.Get_Centre_Of_Gravity() + c.Get_Centre_Of_Gravity() ) / 3.0;
    
    return Centroid;
}
