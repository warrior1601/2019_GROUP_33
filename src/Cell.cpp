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

//Default values of an uninitialised Cell object functions
float Cell::Get_Volume(void)
{
    std::cout << "No implementation of calculating volume for this object" << std::endl;
    return 0;
    
}

float Cell::Get_Weight(void)
{
    std::cout << "No implementation of weight volume for this object" << std::endl;
    return 0;
}

Vectors Cell::Get_Centre_Of_Gravity()
{
    std::cout << "No implementation of calculating centre of gravity for this object" << std::endl;
    Vectors temp;
    return temp;
    
}

void Cell::Rotate(float Rotation_In_Degrees, char Axis_Of_Rotation)
{
    std::cout << "No implementation for rotating this object" << std::endl;
}










//------------------------------------------------------------------------TETRAHEDRON MEMBER FUNCTIONS------------------------------------------------------------------------//

//Constructors and destructors
Tetrahedron::Tetrahedron(const Vectors& aV0, const Vectors& aV1, const Vectors& aV2, const Vectors& aV3, const std::vector<int>& aVectorsOrder, const Material& aMaterial) { V0 = aV0; V1 = aV1; V2 = aV2; V3 = aV3; VectorsOrder = aVectorsOrder; theMaterial = aMaterial; }

Tetrahedron::Tetrahedron(const Tetrahedron& aTetrahedron)
{
    V0 = aTetrahedron.V0;
    V1 = aTetrahedron.V1;
    V2 = aTetrahedron.V2;
    V3 = aTetrahedron.V3;
    VectorsOrder = aTetrahedron.VectorsOrder;
    theMaterial = aTetrahedron.theMaterial;
}

Tetrahedron::Tetrahedron(void) {}

Tetrahedron::~Tetrahedron(void) {}





//Custom std::cout function
std::ostream& operator<< (std::ostream& Output, const Tetrahedron& aTetrahedron)
{
    Output << "V0 = " << aTetrahedron.V0 << "V1 = " << aTetrahedron.V1 << "V2 = " << aTetrahedron.V2 << "V3 = " << aTetrahedron.V3 << "Material " << aTetrahedron.theMaterial << std::endl;
    
    return Output;
}





//Custom operator function
Tetrahedron& Tetrahedron::operator = (const Tetrahedron& aTetrahedron)
{
    if(&aTetrahedron == this)
        return(*this);
    
    else
    {
        V0 = aTetrahedron.V0;
        V1 = aTetrahedron.V1;
        V2 = aTetrahedron.V2;
        V3 = aTetrahedron.V3;
        VectorsOrder = aTetrahedron.VectorsOrder;
        theMaterial = aTetrahedron.theMaterial;
        
        return(*this);
    }
}





//Set functions
void Tetrahedron::Set_V0(const Vectors& aVectors) { V0 = aVectors; }

void Tetrahedron::Set_V1(const Vectors& aVectors) { V1 = aVectors; }

void Tetrahedron::Set_V2(const Vectors& aVectors) { V2 = aVectors; }

void Tetrahedron::Set_V3(const Vectors& aVectors) { V3 = aVectors; }

void Tetrahedron::Set_Vectors_Order(const std::vector<int>& aVectorsOrder) { VectorsOrder = aVectorsOrder; }

void Tetrahedron::Set_Material(const Material& aMaterial) { theMaterial = aMaterial; }





//Get functions
Vectors Tetrahedron::Get_V0(void) { return V0; }

Vectors Tetrahedron::Get_V1(void) { return V1; }

Vectors Tetrahedron::Get_V2(void) { return V2; }

Vectors Tetrahedron::Get_V3(void) { return V3; }

std::vector<int> Tetrahedron::Get_Vectors_Order(void) { return VectorsOrder; }

Material Tetrahedron::Get_Material(void) { return theMaterial; }





//Tetrahedron specific functions
float Tetrahedron::Get_Volume(void)
{
    //Top down view of Vectors numbering assumption
    //
    //    V2         V1
    //
    //         V3
    //
    //         V0
    
    Vectors a = V0 - V3;
    Vectors b = V1 - V3;
    Vectors c = V2 - V3;
    
    //Volume is calculated using the triple scalar product formula
    
    return abs( a.Scalar_Product( b * c ) / 6.0 );
}

float Tetrahedron::Get_Weight(void)
{
    return Get_Volume() * (float)theMaterial.GetDensity();
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
    
    Vectors Centroid;
    
    Centroid.SetX_Vector( ( V0.GetXVector() + V1.GetXVector() + V2.GetXVector() + V3.GetXVector() ) / 4.0 );
    Centroid.SetY_Vector( ( V0.GetYVector() + V1.GetYVector() + V2.GetYVector() + V3.GetYVector() ) / 4.0 );
    Centroid.SetZ_Vector( ( V0.GetZVector() + V1.GetZVector() + V2.GetZVector() + V3.GetZVector() ) / 4.0 );
    
    return Centroid;
}
    

void Tetrahedron::Rotate(float Rotation_In_Degrees, char Axis_Of_Rotation, Vectors Centre_Of_Rotation)
{
    //Rotates tetrahedron an amount of degrees about it's centre along the X, Y or Z axis
    
    //Create a rotation matrix based on degrees and axis of rotation
    Matrix3x3 RotationMatrix;
    RotationMatrix.Initialise_As_Rotation_Matrix(Rotation_In_Degrees, Axis_Of_Rotation);
        
    V0 = (RotationMatrix * (V0 - Centre_Of_Rotation)) + Centre_Of_Rotation;
    V1 = (RotationMatrix * (V1 - Centre_Of_Rotation)) + Centre_Of_Rotation;
    V2 = (RotationMatrix * (V2 - Centre_Of_Rotation)) + Centre_Of_Rotation;
    V3 = (RotationMatrix * (V3 - Centre_Of_Rotation)) + Centre_Of_Rotation;
    
    //Subtract centre of hexahedron from all Vectors to move centre of hexahedron to the origin
    //                           ^^^^^^^^^^^^
    //Apply rotation matrix to all vertcies
    //      ^^^^^^^^^^^^
    //Add centre of hexahedron to all Vectors to move centre of hexahedron back to where it was
    //                                                    ^^^^^^^^^^^^
}










//------------------------------------------------------------------------PYRAMID MEMBER FUNCTIONS------------------------------------------------------------------------//

//Constructors and destructors
Pyramid::Pyramid(const Vectors& aV0, const Vectors& aV1, const Vectors& aV2, const Vectors& aV3, const Vectors& aV4, const std::vector<int>& aVectorsOrder, const Material& aMaterial) { V0 = aV0; V1 = aV1; V2 = aV2; V3 = aV3; V4 = aV4; VectorsOrder = aVectorsOrder; theMaterial = aMaterial; }
    
Pyramid::Pyramid(const Pyramid& aPyramid)
{
    V0 = aPyramid.V0;
    V1 = aPyramid.V1;
    V2 = aPyramid.V2;
    V3 = aPyramid.V3;
    V4 = aPyramid.V4;
    VectorsOrder = aPyramid.VectorsOrder;
    theMaterial = aPyramid.theMaterial;
}


Pyramid::Pyramid(void) { }

Pyramid::~Pyramid(void) { }





//Custom std::cout function
std::ostream& operator<< (std::ostream& Output, const Pyramid& aPyramid)
{
    Output << "V0 = " << aPyramid.V0 << "V1 = " << aPyramid.V1 << "V2 = " << aPyramid.V2 << "V3 = " << aPyramid.V3 << "V4 = " << aPyramid.V4 << "Material " << aPyramid.theMaterial << std::endl;
    
    return Output;
}





//Custom operator function
Pyramid& Pyramid::operator = (const Pyramid& aPyramid)
{
    if(&aPyramid == this)
        return(*this);
    
    else
    {
        V0 = aPyramid.V0;
        V1 = aPyramid.V1;
        V2 = aPyramid.V2;
        V3 = aPyramid.V3;
        V4 = aPyramid.V4;
        VectorsOrder = aPyramid.VectorsOrder;
        theMaterial = aPyramid.theMaterial;
        
        return(*this);
    }
}





//Set functions
void Pyramid::Set_V0(const Vectors& aVectors) { V0 = aVectors; }

void Pyramid::Set_V1(const Vectors& aVectors) { V1 = aVectors; }

void Pyramid::Set_V2(const Vectors& aVectors) { V2 = aVectors; }

void Pyramid::Set_V3(const Vectors& aVectors) { V3 = aVectors; }

void Pyramid::Set_V4(const Vectors& aVectors) { V4 = aVectors; }

void Pyramid::Set_Vectors_Order(const std::vector<int>& aVectorsOrder) { VectorsOrder = aVectorsOrder; }

void Pyramid::Set_Material(const Material& aMaterial) { theMaterial = aMaterial; }





//Get functions
Vectors Pyramid::Get_V0(void) { return V0; }

Vectors Pyramid::Get_V1(void) { return V1; }

Vectors Pyramid::Get_V2(void) { return V2; }

Vectors Pyramid::Get_V3(void) { return V3; }

Vectors Pyramid::Get_V4(void) { return V4; }

std::vector<int> Pyramid::Get_Vectors_Order(void) { return VectorsOrder; }

Material Pyramid::Get_Material(void) { return theMaterial; }





//Pyramid specific functions
float Pyramid::Get_Volume(void)
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
    Tetrahedron a(V0, V2, V3, V4, VectorsOrder, theMaterial);
    Tetrahedron b(V0, V1, V2, V4, VectorsOrder, theMaterial);
    
    return a.Get_Volume() + b.Get_Volume();
}

float Pyramid::Get_Weight(void)
{
    return Get_Volume() * (float)theMaterial.GetDensity();
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
    Tetrahedron a(V0, V2, V3, V4, VectorsOrder, theMaterial);
    Tetrahedron b(V0, V1, V2, V4, VectorsOrder, theMaterial);
    
    Vectors aCentroid = a.Get_Centre_Of_Gravity();
    Vectors bCentroid = b.Get_Centre_Of_Gravity();
    
    Vectors Centroid = (aCentroid + bCentroid) / 2.0;
    
    return Centroid;
}
    
void Pyramid::Rotate(float Rotation_In_Degrees, char Axis_Of_Rotation, Vectors Centre_Of_Rotation)
{
    //Rotates pyramid an amount of degrees about it's centre along the X, Y or Z axis
    
    //Create a rotation matrix based on degrees and axis of rotation
    Matrix3x3 RotationMatrix;
    RotationMatrix.Initialise_As_Rotation_Matrix(Rotation_In_Degrees, Axis_Of_Rotation);
            
    V0 = (RotationMatrix * (V0 - Centre_Of_Rotation)) + Centre_Of_Rotation;
    V1 = (RotationMatrix * (V1 - Centre_Of_Rotation)) + Centre_Of_Rotation;
    V2 = (RotationMatrix * (V2 - Centre_Of_Rotation)) + Centre_Of_Rotation;
    V3 = (RotationMatrix * (V3 - Centre_Of_Rotation)) + Centre_Of_Rotation;
    V4 = (RotationMatrix * (V4 - Centre_Of_Rotation)) + Centre_Of_Rotation;
    
    //Subtract centre of hexahedron from all Vectors to move centre of hexahedron to the origin
    //                           ^^^^^^^^^^^^
    //Apply rotation matrix to all vertcies
    //      ^^^^^^^^^^^^
    //Add centre of hexahedron to all Vectors to move centre of hexahedron back to where it was
    //                                                    ^^^^^^^^^^^^
}










//------------------------------------------------------------------------HEXAHEDRON MEMBER FUNCTIONS------------------------------------------------------------------------//

//Constructors and destructors
Hexahedron::Hexahedron(const Vectors& aV0, const Vectors& aV1, const Vectors& aV2, const Vectors& aV3, const Vectors& aV4, const Vectors& aV5, const Vectors& aV6, const Vectors& aV7, const std::vector<int>& aVectorsOrder, const Material& aMaterial)
{ V0 = aV0; V1 = aV1; V2 = aV2; V3 = aV3; V4 = aV4; V5 = aV5; V6 = aV6; V7 = aV7; VectorsOrder = aVectorsOrder; theMaterial = aMaterial; }
    
Hexahedron::Hexahedron(const Hexahedron& aHexahedron)
{
    V0 = aHexahedron.V0;
    V1 = aHexahedron.V1;
    V2 = aHexahedron.V2;
    V3 = aHexahedron.V3;
    V4 = aHexahedron.V4;
    V5 = aHexahedron.V5;
    V6 = aHexahedron.V6;
    V7 = aHexahedron.V7;
    VectorsOrder = aHexahedron.VectorsOrder;
    theMaterial = aHexahedron.theMaterial;
}

Hexahedron::Hexahedron(void) {}

Hexahedron::~Hexahedron(void) {}





//Custom std::cout function
std::ostream& operator<< (std::ostream& Output, const Hexahedron& aHexahedron)
{
    Output << "V0 = " << aHexahedron.V0 << "V1 = " << aHexahedron.V1 << "V2 = " << aHexahedron.V2 << "V3 = " << aHexahedron.V3 << "V4 = " << aHexahedron.V4 << "V5 = " << aHexahedron.V5 << "V6 = " << aHexahedron.V6 << "V7 = " << aHexahedron.V7 << "Material " << aHexahedron.theMaterial << std::endl;
    
    return Output;
}





//Custom operator function
Hexahedron& Hexahedron::operator= (const Hexahedron& aHexahedron)
{
    if(&aHexahedron == this)
        return(*this);
    
    else
    {
        V0 = aHexahedron.V0;
        V1 = aHexahedron.V1;
        V2 = aHexahedron.V2;
        V3 = aHexahedron.V3;
        V4 = aHexahedron.V4;
        V5 = aHexahedron.V5;
        V6 = aHexahedron.V6;
        V7 = aHexahedron.V7;
        VectorsOrder = aHexahedron.VectorsOrder;
        theMaterial = aHexahedron.theMaterial;
        
        return(*this);
    }
}





//Set functions
void Hexahedron::Set_V0(const Vectors& aVectors) { V0 = aVectors; }

void Hexahedron::Set_V1(const Vectors& aVectors) { V1 = aVectors; }

void Hexahedron::Set_V2(const Vectors& aVectors) { V2 = aVectors; }

void Hexahedron::Set_V3(const Vectors& aVectors) { V3 = aVectors; }

void Hexahedron::Set_V4(const Vectors& aVectors) { V4 = aVectors; }

void Hexahedron::Set_V5(const Vectors& aVectors) { V5 = aVectors; }

void Hexahedron::Set_V6(const Vectors& aVectors) { V6 = aVectors; }

void Hexahedron::Set_V7(const Vectors& aVectors) { V7 = aVectors; }

void Hexahedron::Set_Vectors_Order(const std::vector<int>& aVectorsOrder) { VectorsOrder = aVectorsOrder; }

void Hexahedron::Set_Material(const Material& aMaterial) { theMaterial = aMaterial; }





//Get functions
Vectors Hexahedron::Get_V0(void) { return V0; }

Vectors Hexahedron::Get_V1(void) { return V1; }

Vectors Hexahedron::Get_V2(void) { return V2; }

Vectors Hexahedron::Get_V3(void) { return V3; }

Vectors Hexahedron::Get_V4(void) { return V4; }

Vectors Hexahedron::Get_V5(void) { return V5; }

Vectors Hexahedron::Get_V6(void) { return V6; }

Vectors Hexahedron::Get_V7(void) { return V7; }

std::vector<int> Hexahedron::Get_Vectors_Order(void) { return VectorsOrder; }

Material Hexahedron::Get_Material(void) { return theMaterial; }





//Hexahedron specific functions
float Hexahedron::Get_Volume(void)
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
    Pyramid a(V0, V1, V2, V3, V6, VectorsOrder, theMaterial);
    Pyramid b(V0, V1, V5, V4, V6, VectorsOrder, theMaterial);
    Pyramid c(V0, V3, V7, V4, V6, VectorsOrder, theMaterial);
    
    return a.Get_Volume() + b.Get_Volume() + c.Get_Volume();
}

float Hexahedron::Get_Weight(void)
{
    return Get_Volume() * (float)theMaterial.GetDensity();
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
    Pyramid a(V0, V1, V2, V3, V6, VectorsOrder, theMaterial);
    Pyramid b(V0, V1, V5, V4, V6, VectorsOrder, theMaterial);
    Pyramid c(V0, V3, V7, V4, V6, VectorsOrder, theMaterial);
    
    Vectors Centroid = ( a.Get_Centre_Of_Gravity() + b.Get_Centre_Of_Gravity() + c.Get_Centre_Of_Gravity() ) / 3.0;
    
    return Centroid;
}
    
void Hexahedron::Rotate(float Rotation_In_Degrees, char Axis_Of_Rotation, Vectors Centre_Of_Rotation)
{
    //Rotates hexahedron an amount of degrees about it's centre along the X, Y or Z axis
    
    //Create a rotation matrix based on degrees and axis of rotation
    Matrix3x3 RotationMatrix;
    RotationMatrix.Initialise_As_Rotation_Matrix(Rotation_In_Degrees, Axis_Of_Rotation);
                                 
    V0 = (RotationMatrix * (V0 - Centre_Of_Rotation)) + Centre_Of_Rotation;
    V1 = (RotationMatrix * (V1 - Centre_Of_Rotation)) + Centre_Of_Rotation;
    V2 = (RotationMatrix * (V2 - Centre_Of_Rotation)) + Centre_Of_Rotation;
    V3 = (RotationMatrix * (V3 - Centre_Of_Rotation)) + Centre_Of_Rotation;
    V4 = (RotationMatrix * (V4 - Centre_Of_Rotation)) + Centre_Of_Rotation;
    V5 = (RotationMatrix * (V5 - Centre_Of_Rotation)) + Centre_Of_Rotation;
    V6 = (RotationMatrix * (V6 - Centre_Of_Rotation)) + Centre_Of_Rotation;
    V7 = (RotationMatrix * (V7 - Centre_Of_Rotation)) + Centre_Of_Rotation;
    
    //Subtract centre of hexahedron from all Vectors to move centre of hexahedron to the origin
    //                           ^^^^^^^^^^^^
    //Apply rotation matrix to all vertcies
    //      ^^^^^^^^^^^^
    //Add centre of hexahedron to all Vectors to move centre of hexahedron back to where it was
    //                                                    ^^^^^^^^^^^^
}
