//  Cell.hpp
//  Computing Project
//  Created by Junaid Afzal on 10/11/2019.

/** @file This header file contains the parent class Cell and the sub-classes
 *  Tetrahedron, Pyramid and Hexahedron. The cell represents an abstraction of all
 *  shapes and has the private member variables of Vertices containing all the vertices
 *  of the cell; aVerticesOrder which is a variable used only by the model class; and
 *  theMaterial containing the material the cell is made up of.
 *  @author Junaid Afzal
 */

#ifndef Cell_hpp
#define Cell_hpp

#include "Material.h"
#include "Vectors.h"
#include <vector>

/** @class Cell Cell.hpp "Cell.hpp"
 *  @brief The Cell class is a parent class that represnts an abstraction of all shapes
 *  @details The main cell member function is Rotate, which rotates the cell
 *  @warning No error checking for negative densities
 */

class Cell {
public:
    //Constructor and destructor
    /** @brief Blank constructor (empty)
     */
    Cell(void);
    /** @brief Blank destructor (empty)
     */
    ~Cell(void);

    //Custom std::cout function
    /** @brief Displays the vertices, in order, and the material of cell by
     *  using vectors and materials display functions
     */
    friend std::ostream& operator<< (std::ostream& Output, const Cell& aCell);

    //Custom operator function
    /** @brief Overwrites the member variables of the cell calling the function
     *  with the values of aCell member variables
     */
    Cell& operator= (const Cell& aCell);
    /** @brief Checks to see if two cells are equal returns true if they are
     */
    bool operator==(Cell& aCell);

    //Set functions
    /** @brief Sets the Vertices of cell
     */
    void Set_Vertices(const std::vector<Vectors>& aVertices);
    /** @brief Sets the VerticesOrder of cell
     */
    void Set_Vertices_Order(const std::vector<int>& aVerticesOrder);
    /** @brief Sets the theMaterial of cell
     */
    void Set_Material(const Material& aMaterial);

    //Get function
    /** @brief Returns the Vertices of cell
     */
    std::vector<Vectors> Get_Vertices(void);
    /** @brief Returns the VerticesOrder of cell
     */
    std::vector<int> Get_Vertices_Order(void);
    /** @brief Returns the theMaterial of cell
     */
    Material Get_Material(void);

    //Cell specific functions
    /** @brief Returns -1. Note that this should never be
     *  called should be re-defined for every sub-class. If it is called an error
     *  message will be displayed on the console.
     */
    virtual double Get_Volume(void);
    /** @brief Returns -1. Note that this should never be
     *  called should be re-defined for every sub-class. If it is called an error
     *  message will be displayed on the console.
     */
    virtual double Get_Weight(void);
    /** @brief Returns a vectors with the co-ordinates (-1,-1,-1). Note that this should never be
     *  called should be re-defined for every sub-class. If it is called an error
     *  message will be displayed on the console.
     */
    virtual Vectors Get_Centre_Of_Gravity(void);
    /** @brief Translates all vertices of cell such that it appear that the cell has been rotated by Rotation_In_Degrees
     *  amount of degrees around the Axis_Of_Rotation about the point Centre_Of_Rotation.
     *  @details \n This is achieved by first translating the cell such that its position to the origin after translation is the same as its position to the
     *  Centre_Of_Rotation before the translation. Then the rotation matrix of Matrix3x3 is applied to all vertices
     *  in the cell using the Rotation_In_Degrees (0 to 360) and Axis_Of_Rotation (x, y or z as char - if any other
     *  letter is used an error message will be displayed on the console) as the parameters. Then the translation is undone
     *  so that cell is back in the same position but rotated. \n\n This is done as the translation matrix rotates and object
     *  around the origin, therefore if rotation of a cell about its own centre is required then pass the centre of gravity
     *  of the cell as the Centre_Of_Rotation.
     *  @param Rotation_In_Degrees This is an angle where positive will cause clockwise rotation and negative anti-clockwise rotation
     *  @param Axis_Of_Rotation This can be either x, y or z - lowercase only - otherwise an error message will be displayed on console
     *  @param Centre_Of_Rotation This will be the point in space the cell is rotating around
     */
    void Rotate(double Rotation_In_Degrees, char Axis_Of_Rotation, Vectors Centre_Of_Rotation);

private:
    std::vector<Vectors> Vertices;          ///< @brief This is a list of vectors (points/vertices/corners) that make up the cell
    std::vector<int> VerticesOrder;         ///< @brief This is a variable required by the model in order for the model to keep track of which vectors from its own vectors list are being used in this particular cell - thus this will contain all the vectors IDs. @details For example if VectorsOrder[1] = 5 then Vectors V1 get its value from the 5th element in models vectors list as position in models vectors list = vectors ID. VectorsOrder exists to allow the model class to keep track of which IDs the Vectors get their values from.
    Material theMaterial;                   ///< @brief This is the material the cell is made up of
};

/** @class Tetrahedron Cell.hpp "Cell.hpp"
 *  @brief A sub-class of cell with all its private members being inherited from the cell class
 *  @details This class can calculate its volume, weight and centre of Gravity
 *  as well as all the abilities of cell
 *  \image html tetrahedron.png "Tetrahedron Vertices Number Ordering" width=500cm
 *  @warning No error checking for negative densities
 */
class Tetrahedron:public Cell {
public:
    //Constructors and destructor
    /** @brief Full constructor
     *  @param aVertices This is a list of vertices that the tetrahedron is made up of.
     *  See detailed description for info on how to order vertices
     *  @param aVerticesOrder This is a parameter used by the model class, if model class
     *  is not being used then an empty variable can be used with no effect on functionality of tetrahedron,
     *  it represents vectors IDs of aVertices.
     *  @param aMaterial This is the material the tetrahedron is made up of
     *  @warning No error checking for whether aVertices or aVerticesOrder is a valid size
     */
    Tetrahedron(const std::vector<Vectors>& aVertices, const std::vector<int>& aVerticesOrder, const Material& aMaterial);
    /** @brief Blank constructor which adjust the size of Vertices to 4 but leaves each index empty; uses std::vector constructor
     *  for VerticesOrder to initialise; and material constructor to initialise theMaterial.
     */
    Tetrahedron(void);
    /** @brief Standard empty destructor
     */
    ~Tetrahedron(void);

    //Tetrahedron specific functions
    /** @brief Returns volume of tetrahedron using the triple scalar product formula
     */
    virtual double Get_Volume(void);
    /** @brief Returns the weight of tetrahedron by multiplying volume of pyrmaid by density of theMaterial
     *  @warning No error checking for negative densities
     */
    virtual double Get_Weight(void);
    /** @brief Returns the centre of gravity by using centroid of tetrahedron formula which, assuming uniform density, is
     * the average of each co-ordinate - i.e. average of all x components of vertices, average of all y components of vertices etc
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

/** @class Pyramid Cell.hpp "Cell.hpp"
 *  @brief A sub-class of cell with all its private members being inherited from the cell class
 *  @details This class can calculate its volume, weight and centre of Gravity
 *  as well as all the abilities of cell
 *  \image html pyramid.png "Pyramid Vertices Number Ordering" width=500cm
 *  @warning No error checking for negative densities
 */
class Pyramid:public Cell {
public:
    //Constructors and destructor
    /** @brief Full constructor
     *  @param aVertices This is a list of vertices that the pyramid is made up of.
     *  See detailed description for info on how to order vertices
     *  @param aVerticesOrder This is a parameter used by the model class, if model class
     *  is not being used then an empty variable can be used with no effect on functionality of pyramid,
     *  it represents vectors IDs of aVertices.
     *  @param aMaterial This is the material the pyramid is made up of
     *  @warning No error checking for whether aVertices or aVerticesOrder is a valid size
     */
    Pyramid(const std::vector<Vectors>& aVertices, const std::vector<int>& aVerticesOrder, const Material& aMaterial);
    /** @brief Blank constructor which adjust the size of Vertices to 5 but leaves each index empty; uses std::vector constructor
     *  for VerticesOrder to initialise; and material constructor to initialise theMaterial.
     */
    Pyramid(void);
    /** @brief Standard empty destructor
     */
    ~Pyramid(void);
    /** @brief Returns the volume of the pyramid by splitting it in half diagonally along V0 - V2 "line"
     *  to create two tetrahedrons and summing the volumes of all of them.
     */
    virtual double Get_Volume(void);
    /** @brief Returns the weight of pyramid by multiplying volume of pyramid by density of theMaterial
     *  @warning No error checking for negative densities
     */
    virtual double Get_Weight(void);
     /** @brief Returns the centre of gravity of pyramid by splitting it in half diagonally along V0 - V2 "line"
      *  to create two tetrahedrons and finding centre of gravity of each.
      *  @details Since the two tetrahedrons have equal  volume and density, they will have equal weight and therefore the
      * centre of gravity of pyramid will be the average/midpoint of the two tetrahedrons centres of gravities. See http://mathcentral.uregina.ca/QQ/database/QQ.09.06/siva1.html for more info
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

/** @class Hexahedron Cell.hpp "Cell.hpp"
 *  @brief A sub-class of cell with all its private members being inherited from the cell class
 *  @details This class can calculate its volume, weight and centre of Gravity
 *  as well as all the abilities of cell
 *  \image html hexahedron.png "Hexahedron Vertices Number Ordering" width=500cm
 *  @warning No error checking for negative densities
 */
class Hexahedron:public Cell {
public:
    //Constructors and destructor
    /** @brief Full constructor
     *  @param aVertices This is a list of vertices that the hexahedron is made up of.
     *  See detailed description for info on how to order vertices
     *  @param aVerticesOrder This is a parameter used by the model class, if model class
     *  is not being used then an empty variable can be used with no effect on functionality of hexahedron,
     *  it represents vectors IDs of aVertices.
     *  @param aMaterial This is the material the hexahedron is made up of
     *  @warning No error checking for whether aVertices or aVerticesOrder is a valid size
     */
    Hexahedron(const std::vector<Vectors>& aVertices, const std::vector<int>& aVerticesOrder, const Material& aMaterial);
    /** @brief Blank constructor which adjust the size of Vertices to 8 but leaves each index empty; uses std::vector constructor
     *  for VerticesOrder to initialise; and material constructor to initialise theMaterial.
     */
    Hexahedron(void);
    /** @brief Standard empty destructor
     */
    ~Hexahedron(void);
    /** @brief Returns the volume of hexahedron by splitting it in to three pyramids and
     *  summing the volumes of all of them.
     *  @details See http://mathcentral.uregina.ca/QQ/database/QQ.09.06/siva1.html for more info
     */
    virtual double Get_Volume(void);
    /** @brief Returns the weight of hexahedron by multiplying volume of hexahedron by density of theMaterial
     *  @warning No error checking for negative densities
     */
    virtual double Get_Weight(void);
    /** @brief Returns the centre of gravity of hexahedron by splitting it in to three pyramids and find centre of gravity of each.
     *  @details Since the three pyramids have equal volume and density, they
     *  will have equal weight and therefore the centre of gravity of hexahedron will be the average/midpoint
     *  of the three pyramid centres of gravities. See http://mathcentral.uregina.ca/QQ/database/QQ.09.06/siva1.html for more info
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
