//  Cell.hpp
//  Computing Project
//
//  Created by Junaid Afzal on 10/11/2019.
//  Copyright © 2019 Junaid Afzal. All rights reserved.
//
  /** @file
   *  This header file contains the object Cell and the sub-objects
   *  Tetrahedron, Pyramid and Hexahedron. Cell is the general form
   *  of a shape, while the sub-objects conatin the specific member
   *  functions.
   *
   *  Each sub-object contains the appropriate number of Vectors, Vectors order
   *  and material. Note that VectorsOrder represents the Vectors IDs that the sub-objects
   *  contains, with the position of the Vectors ID in the array representing its Vectors.
   *  E.g. if VectorsOrder[1] = 5 then Vectors V1 get its value from the Vectors with ID = 5.
   *  VectorsOrder exists to allow the object Model to keep track of which IDs the Vectors
   *  get their values from.
   */

#ifndef Cell_hpp
#define Cell_hpp

#include "Material.h"
#include "Vectors.h"
#include <vector>

class Cell {
public:
    Cell();
    ~Cell();
    
    /**
     * @brief Displays the content of the Cell
     * @param ostream
     * @param aCell
     */
    friend std::ostream& operator<< (std::ostream& Output, const Cell& aCell);
    
    /**
     * @brief Allows one Cell to be set equal to another Cell
     * @param aCell
     */
    Cell& operator = (const Cell& aCell);
    
    /**
     * @brief Sets the Vertices of a Cell from a list of Vectors
     * @param std::vector<Vectors> aVetices
     */
    void Set_Vertices(const std::vector<Vectors>& aVertices);

    /**
     * @brief THINK ABOUT THIS
     *
     *
     *
     * @param aVerticesOrder
     */
    void Set_Vertices_Order(const std::vector<int>& aVerticesOrder);
    /**
     * @brief Set_Material
     * @param aMaterial
     */
    void Set_Material(const Material& aMaterial);
    
    /**
     * @brief Get_Vertices
     * @return
     */
    std::vector<Vectors> Get_Vertices(void);

    /**
     * @brief Get_Vertices_Order
     * @return
     */
    std::vector<int> Get_Vertices_Order(void);

    /**
     * @brief Get_Material
     * @return
     */
    Material Get_Material(void);

    /**
     * @brief Get_Volume
     * @return
     */
    virtual double Get_Volume(void);

    /**
     * @brief Get_Weight
     * @return
     */
    virtual double Get_Weight(void);

    /**
     * @brief Get_Centre_Of_Gravity
     * @return
     */
    virtual Vectors Get_Centre_Of_Gravity(void);
    
    //Rotates Cell clockwise an amount of degrees about it's centre of rotation along the X, Y or Z axis. Method is as follows -
    //Create a rotation matrix based on degrees and axis of rotation and then subtracts centre of
    //tetrahedron from all Vectors to move centre of tetrahedron to the origin. Then apply rotation matrix
    //to all vertcies. Then add centre of Cell to all Vectors to move centre of Cell back to where it was
    void Rotate(double Rotation_In_Degrees, char Axis_Of_Rotation, Vectors Centre_Of_Rotation);
    
private:
    std::vector<Vectors> Vertices;
    std::vector<int> VerticesOrder;
    Material theMaterial;
};





class Tetrahedron:public Cell {
public:
    //Constructors and destructor
    Tetrahedron(const std::vector<Vectors>& aVertices, const std::vector<int>& aVerticesOrder, const Material& aMaterial);
    Tetrahedron(void);
    ~Tetrahedron(void);

    //Volume is calculated using the triple scalar product formula
    virtual double Get_Volume(void);
    
    //Weight = Volume * Density
    virtual double Get_Weight(void);
    
    //Centroid = centre of gravity, assuming uniform density across object, and is calculated by finding the average of each co-ordinate
    virtual Vectors Get_Centre_Of_Gravity(void);
    
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
    //Constructors and destructor
    Pyramid(const std::vector<Vectors>& aVertices, const std::vector<int>& aVerticesOrder, const Material& aMaterial);
    Pyramid(void);
    ~Pyramid(void);

    //Split the pyramid along V0 - V4 - V2 "line" to create two tetrahedrons and calculate the volume of two tetrahedrons and add them together
    virtual double Get_Volume(void);
    
    //Weight = Volume * Density
    virtual double Get_Weight(void);
    
    //Split the pyramid along V0 - V4 - V2 "line" to create two tetrahedrons and calculate centre of gravity of each one
    //The two tetrahedrons will have the same volume, thus the same weight and thus the centre of gravity of the pyramid will
    //be the midpoint between the two centres of gravities of the two tetrahedrons
    virtual Vectors Get_Centre_Of_Gravity(void);

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
    //Constructors and destructor
    Hexahedron(const std::vector<Vectors>& aVertices, const std::vector<int>& aVerticesOrder, const Material& aMaterial);
    Hexahedron(void);
    ~Hexahedron(void);

    //Split the hexahedron in to three pyramids and find volume of each
    //See http://mathcentral.uregina.ca/QQ/database/QQ.09.06/siva1.html for more info
    virtual double Get_Volume(void);
    
    //Weight = Volume * Density
    virtual double Get_Weight(void);
    
    //Split the hexahedron in to three pyramids and find centre of gravity of each
    //See http://mathcentral.uregina.ca/QQ/database/QQ.09.06/siva1.html for more info
    //Then centroid of hexahedron will be the average/midpoint of the pyramid centroids as they have equal volume and therefore equal weight
    virtual Vectors Get_Centre_Of_Gravity(void);

    //Top down view of Vectors numbering assumption
    //
    //    V3/V7         V2/V6
    //
    //
    //
    //    V0/V4         V1/V5
};

#endif // Cell_hpp
