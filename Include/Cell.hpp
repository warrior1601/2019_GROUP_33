//
//  Cell.hpp
//  Computing Project
//
//  Created by Junaid Afzal on 10/11/2019.
//  Copyright © 2019 Junaid Afzal. All rights reserved.
//
//  This header file contains the object Cell and the sub-objects
//  Tetrahedron, Pyramid and Hexahedron. Cell is the general form
//  of a shape, while the sub-objects conatin the specific member
//  functions.
//
//  Each sub-object contains the appropriate number of vertices, Vectors order
//  and material. Note that VectorsOrder represents the Vectors IDs that the sub-objects
//  contains, with the position of the Vectors ID in the array representing its Vectors.
//  E.g. if VectorsOrder[1] = 5 then Vectors V1 get its value from the Vectors with ID = 5.
//
//  VectorsOrder exists to allow the object Model to keep track of which IDs the Vectors
//  get their values from.
//

#ifndef Cell_hpp
#define Cell_hpp

#include "Material.h"
#include "Vectors.h"
#include <vector>

class Cell {
public:
    //Cell specific functions
    virtual float Get_Volume(void);
    virtual float Get_Weight(void);
    virtual Vectors Get_Centre_Of_Gravity(void);
    virtual void Rotate(float Rotation_In_Degrees, char Axis_Of_Rotation);
    
private:
    
};





class Tetrahedron:public Cell {
public:
    //Constructors and destructors
    Tetrahedron(const Vectors& aV0, const Vectors& aV1, const Vectors& aV2, const Vectors& aV3, const std::vector<int>& aVectorsOrder, const Material& aMaterial);
    Tetrahedron(const Tetrahedron& aTetrahedron);
    Tetrahedron(void);
    ~Tetrahedron(void);
    
    //Custom std::cout function
    friend std::ostream& operator<< (std::ostream& Output, const Tetrahedron& aTetrahedron);
    
    //Custom operator function
    Tetrahedron& operator = (const Tetrahedron& aTetrahedron);
    
    //Set functions
    void Set_V0(const Vectors& aVectors);
    void Set_V1(const Vectors& aVectors);
    void Set_V2(const Vectors& aVectors);
    void Set_V3(const Vectors& aVectors);
    void Set_Vectors_Order(const std::vector<int>& aVectorsOrder);
    void Set_Material(const Material& aMaterial);
    
    //Get functions
    Vectors Get_V0(void);
    Vectors Get_V1(void);
    Vectors Get_V2(void);
    Vectors Get_V3(void);
    std::vector<int> Get_Vectors_Order(void);
    Material Get_Material(void);
    
    //Tetrahedron specific functions
    
    //Volume is calculated using the triple scalar product formula
    virtual float Get_Volume(void);
    
    //Weight = Volume * Density
    virtual float Get_Weight(void);
    
    //Centroid = centre of gravity, assuming uniform density across object, and is calculated by finding the average of each co-ordinate
    virtual Vectors Get_Centre_Of_Gravity(void);
    
    //Rotates tetrahedron clockwise an amount of degrees about it's centre of rotation along the X, Y or Z axis. Method is as follows -
    //Create a rotation matrix based on degrees and axis of rotation and then subtracts centre of
    //tetrahedron from all vertices to move centre of tetrahedron to the origin. Then apply rotation matrix
    //to all vertcies. Then add centre of tetrahedron to all vertices to move centre of tetrahedron back to where it was
    void Rotate(float Rotation_In_Degrees, char Axis_Of_Rotation, Vectors Centre_Of_Rotation);
    
private:
    Vectors V0, V1, V2, V3;
    std::vector<int> VectorsOrder;
    Material theMaterial;
    
    //Top down view of Vectors numbering assumption
    //
    //    V2         V1
    //
    //         V3
    //
    //         V0

};





class Pyramid:public Cell {
public:
    //Constructors and destructors
    Pyramid(const Vectors& aV0, const Vectors& aV1, const Vectors& aV2, const Vectors& aV3, const Vectors& aV4, const std::vector<int>& aVectorsOrder, const Material& aMaterial);
    Pyramid(const Pyramid& aPyramid);
    Pyramid(void);
    ~Pyramid(void);
    
    //Custom std::cout function
    friend std::ostream& operator<< (std::ostream& Output, const Pyramid& aPyramid);
    
    //Custom operator function
    Pyramid& operator = (const Pyramid& aPyramid);
    
    //Set functions
    void Set_V0(const Vectors& aVectors);
    void Set_V1(const Vectors& aVectors);
    void Set_V2(const Vectors& aVectors);
    void Set_V3(const Vectors& aVectors);
    void Set_V4(const Vectors& aVectors);
    void Set_Vectors_Order(const std::vector<int>& aVectorsOrder);
    void Set_Material(const Material& aMaterial);
    
    //Get functions
    Vectors Get_V0(void);
    Vectors Get_V1(void);
    Vectors Get_V2(void);
    Vectors Get_V3(void);
    Vectors Get_V4(void);
    std::vector<int> Get_Vectors_Order(void);
    Material Get_Material(void);
    
    //Pyramid specific functions
    
    //Split the pyramid along V0 - V4 - V2 "line" to create two tetrahedrons and calculate the volume of two tetrahedrons and add them together
    virtual float Get_Volume(void);
    
    //Weight = Volume * Density
    virtual float Get_Weight(void);
    
    //Split the pyramid along V0 - V4 - V2 "line" to create two tetrahedrons and calculate centre of gravity of each one
    //The two tetrahedrons will have the same volume, thus the same weight and thus the centre of gravity of the pyramid will
    //be the midpoint between the two centres of gravities of the two tetrahedrons
    virtual Vectors Get_Centre_Of_Gravity(void);
    
    //Rotates pyramid clockwise an amount of degrees about it's centre of rotation along the X, Y or Z axis. Method is as follows -
    //Create a rotation matrix based on degrees and axis of rotation and then subtracts centre of
    //pyramid from all vertices to move centre of pyramid to the origin. Then apply rotation matrix
    //to all vertcies. Then add centre of pyramid to all vertices to move centre of pyramid back to where it was
    void Rotate(float Rotation_In_Degrees, char Axis_Of_Rotation, Vectors Centre_Of_Rotation);
    
private:
    Vectors V0, V1, V2, V3, V4;
    std::vector<int> VectorsOrder;
    Material theMaterial;
    
    //Top down view of Vectors numbering assumption
    //
    //    V3         V2
    //
    //         V4
    //
    //    V0         V1
    
};





class Hexahedron:public Cell {
public:
    //Constructors and destructors
    Hexahedron(const Vectors& aV0, const Vectors& aV1, const Vectors& aV2, const Vectors& aV3, const Vectors& aV4, const Vectors& aV5, const Vectors& aV6, const Vectors& aV7, const std::vector<int>& aVectorsOrder, const Material& aMaterial);
    Hexahedron(const Hexahedron& aHexahedron);
    Hexahedron(void);
    ~Hexahedron(void);
    
    //Custom std::cout function
    friend std::ostream& operator<< (std::ostream& Output, const Hexahedron& aHexahedron);
    
    //Custom operator function
    Hexahedron& operator = (const Hexahedron& aHexahedron);
    
    //Set functions
    void Set_V0(const Vectors& aVectors);
    void Set_V1(const Vectors& aVectors);
    void Set_V2(const Vectors& aVectors);
    void Set_V3(const Vectors& aVectors);
    void Set_V4(const Vectors& aVectors);
    void Set_V5(const Vectors& aVectors);
    void Set_V6(const Vectors& aVectors);
    void Set_V7(const Vectors& aVectors);
    void Set_Vectors_Order(const std::vector<int>& aVectorsOrder);
    void Set_Material(const Material& aMaterial);
    
    //Get functions
    Vectors Get_V0(void);
    Vectors Get_V1(void);
    Vectors Get_V2(void);
    Vectors Get_V3(void);
    Vectors Get_V4(void);
    Vectors Get_V5(void);
    Vectors Get_V6(void);
    Vectors Get_V7(void);
    std::vector<int> Get_Vectors_Order(void);
    Material Get_Material(void);
    
    //Hexahedron specific functions
    
    //Split the hexahedron in to three pyramids and find volume of each
    //See http://mathcentral.uregina.ca/QQ/database/QQ.09.06/siva1.html for more info
    virtual float Get_Volume(void);
    
    //Weight = Volume * Density
    virtual float Get_Weight(void);
    
    //Split the hexahedron in to three pyramids and find centre of gravity of each
    //See http://mathcentral.uregina.ca/QQ/database/QQ.09.06/siva1.html for more info
    //Then centroid of hexahedron will be the average/midpoint of the pyramid centroids as they have equal volume and therefore equal weight
    virtual Vectors Get_Centre_Of_Gravity(void);
    
    //Rotates hexahedron clockwise an amount of degrees about it's centre of rotation along the X, Y or Z axis. Method is as follows -
    //Create a rotation matrix based on degrees and axis of rotation and then subtracts centre of
    //hexahedron from all vertices to move centre of hexahedron to the origin. Then apply rotation matrix
    //to all vertcies. Then add centre of hexahedron to all vertices to move centre of hexahedron back to where it was
    void Rotate(float Rotation_In_Degrees, char Axis_Of_Rotation, Vectors Centre_Of_Rotation);
    
private:
    Vectors V0, V1, V2, V3, V4, V5, V6, V7;
    std::vector<int> VectorsOrder;
    Material theMaterial;
    
    //Top down view of Vectors numbering assumption
    //
    //    V3/V7         V2/V6
    //
    //
    //
    //    V0/V4         V1/V5
};

#endif // Cell_hpp
