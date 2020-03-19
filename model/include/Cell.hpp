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
/**
 * @class Cell cell.hpp "inc/cell.hpp"
 * @brief The Cell class is the parent class for all shapes
 * that can be created with this library
 */
class Cell {
public:
    Cell();
    ~Cell();
    
    /**
     * @brief Displays the content of the Cell
     */
    friend std::ostream& operator<< (std::ostream& Output, const Cell& aCell);
    
    /**
     * @brief Allows one Cell to be set equal to another Cell
     */
    Cell& operator = (const Cell& aCell);
    
    /**
     * @brief Sets the Vertices of a Cell from a list of Vectors
     */
    void Set_Vertices(const std::vector<Vectors>& aVertices);

    /**
     * @brief Sets the order of the vertices to the correct order
     */
    void Set_Vertices_Order(const std::vector<int>& aVerticesOrder);
    /**
     * @brief Sets the material of the cell
     */
    void Set_Material(const Material& aMaterial);
    
    /**
     * @brief Gets all Vectors of the cell
     * @returns a list of Vectors with the X, Y, and Z coordanites of the cells
     */
    std::vector<Vectors> Get_Vertices(void);

    /**
     * @brief Gets the order of the Vectors
     * @returns The correct order of the Vectors to creat the cell
     */
    std::vector<int> Get_Vertices_Order(void);

    /**
     * @brief Get the Material of the cell
     * @returns the Material of the cell
     */
    Material Get_Material(void);

    /**
     * @brief Calculates the volume of the cell
     */
    virtual double Get_Volume(void);

    /**
     * @brief Calculates the weight of the cells
     */
    virtual double Get_Weight(void);

    /**
     * @brief Calculates the center of gravity for the cell
     */
    virtual Vectors Get_Centre_Of_Gravity(void);
    
    /**
     * @brief Rotates Cell clockwise an amount of degrees about it's centre of rotation along the X, Y or Z axis. Method is as follows -
     * Create a rotation matrix based on degrees and axis of rotation and then subtracts centre of
     * tetrahedron from all Vectors to move centre of tetrahedron to the origin. Then apply rotation matrix
     * to all vertcies. Then add centre of Cell to all Vectors to move centre of Cell back to where it was
     * @param Rotation_In_Degrees (0-360)
     * @param Axis_Of_Rotation (X,Y, or Z)
     * @param Centre_Of_Rotation (Vectors)
     */
    void Rotate(double Rotation_In_Degrees, char Axis_Of_Rotation, Vectors Centre_Of_Rotation);
    
private:
    std::vector<Vectors> Vertices;          ///< List of Vectors in the Cell
    std::vector<int> VerticesOrder;         ///< Order if the Vectors in the Cell
    Material theMaterial;                   ///< THe Material information of the cell
};




/**
 * @class Tetrahedron cell.hpp "inc/cell.hpp"
 * @brief The Tetrahedron class is a subclass of the cell class
 * that has 4 Vectors.
 * \image html tetrahedron.png " Tetrahedron Vector numbering" width 20cm
 */
class Tetrahedron:public Cell {
public:

    /**
     * @brief Constructor with is variables
     * @param aVertices is a List of Vectors
     * @param aVerticesOrder is a List of the order of Vectors
     * @param aMaterial is The Material
     */
    Tetrahedron(const std::vector<Vectors>& aVertices, const std::vector<int>& aVerticesOrder, const Material& aMaterial);

    /**
     * @brief Blank Constructor
     */
    Tetrahedron(void);
    ~Tetrahedron(void);

    /**
     * @brief Get_Volume
     * Volume is calculated using the triple scalar product formula
     */
    virtual double Get_Volume(void);
    
    /**
     * @brief Get_Weight
     * Weight = Volume * Density
     */
    virtual double Get_Weight(void);
    
    /**
     * @brief Get_Centre_Of_Gravity
     * Centroid = centre of gravity, assuming uniform density across object, and is calculated by finding the average of each co-ordinate
     * @return
     */
    virtual Vectors Get_Centre_Of_Gravity(void);

    //Top down view of Vectors numbering assumption
    //
    //    V2         V1
    //
    //         V3
    //
    //         V0
};




/**
 * @class Pyramid cell.hpp "inc/cell.hpp"
 * @brief The Pyramid class is a subclass of the cell class
 * that has 5 Vectors.
 * \image html pyramid.png " Pyramid Vector numbering" width 20cm
 */
class Pyramid:public Cell {
public:

    /**
     * @brief Constructor with is variables
     * @param aVertices is a List of Vectors
     * @param aVerticesOrder is a List of the order of Vectors
     * @param aMaterial is The Material
     */
    Pyramid(const std::vector<Vectors>& aVertices, const std::vector<int>& aVerticesOrder, const Material& aMaterial);
    Pyramid(void);
    ~Pyramid(void);

    /**
     * @brief Split the pyramid along V0 - V4 - V2 "line" to create two tetrahedrons
     * and calculate the volume of two tetrahedrons and add them together
     * @returns The volume of the cell
     */
    virtual double Get_Volume(void);
    
    /**
     * @brief Weight = Volume * Density
     * @returns The weight of the cell
     */
    virtual double Get_Weight(void);
    
    /**
     * @brief Split the pyramid along V0 - V4 - V2 "line" to create two tetrahedrons and calculate centre of gravity of each one
     * The two tetrahedrons will have the same volume, thus the same weight and thus the centre of gravity of the pyramid will
     * be the midpoint between the two centres of gravities of the two tetrahedrons
     * @returns Centre Of Gravity
     */
    virtual Vectors Get_Centre_Of_Gravity(void);

    //Top down view of Vectors numbering assumption
    //
    //    V3         V2
    //
    //         V4
    //
    //    V0         V1
};




/**
 * @class Hexahedron cell.hpp "inc/cell.hpp"
 * @brief The Hexahedron class is a subclass of the cell class
 * that has 8 Vectors.
 * \image html hexahedron.png " Hexahedron Vector numbering" width 20cm
 */
class Hexahedron:public Cell {
public:
    /**
     * @brief Constructor with is variables
     * @param aVertices is a List of Vectors
     * @param aVerticesOrder is a List of the order of Vectors
     * @param aMaterial is The Material
     */
    Hexahedron(const std::vector<Vectors>& aVertices, const std::vector<int>& aVerticesOrder, const Material& aMaterial);
    Hexahedron(void);
    ~Hexahedron(void);

    /**
     * @brief Split the hexahedron in to three pyramids and find volume of each
     * See (http://mathcentral.uregina.ca/QQ/database/QQ.09.06/siva1.html) for more info
     * @returns the volume
     */
    virtual double Get_Volume(void);
    
    /**
     * @brief Weight = Volume * Density
     * @returns the weight of the object
     */
    virtual double Get_Weight(void);
       
    /**
     * @brief Split the hexahedron in to three pyramids and find centre of gravity of each
     * See (http://mathcentral.uregina.ca/QQ/database/QQ.09.06/siva1.html) for more info
     * Then centroid of hexahedron will be the average/midpoint of the pyramid centroids
     * as they have equal volume and therefore equal weight
     * @returns the Centre of Gravity
     */
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
