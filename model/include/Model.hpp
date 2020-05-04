//  Model.hpp
//  Computing Project
//  Created by Junaid Afzal on 16/11/2019.

/** @file This header file contains the Model class which has the private member variables
 *  of manyMaterials, containing a list of all the materials; manyVectors, containing a
 *  list of all the vectors; manyCells, containing a list of all the cells; and cellOrder,
 *  containing a list of the order in which the different types cells were created
 *  @author Junaid Afzal
 */

#ifndef Model_hpp
#define Model_hpp

#include "Material.h"
#include "Vectors.h"
#include "Cell.hpp"


/** @class Model Model.hpp "Model.hpp"
 *  @brief An abstraction of a model
 *  @details The two intended ways of loading the model are through the copy constructor or
 *  the Load_Model function. With the latter the chosen file must be a .txt or .mod and written in the format:
 *  \n\n m 0 8960 b87373 copper
 *  \n Reading the line left to right, this declares a material with material ID of 0, density of 8960,
 *  colour of R=B8 G=73 B=73, and name of copper.
 *  \n\n v 10 25 20 25
 *  \n Reading the line left to right, this declares a vectors with a vector ID of 10, X co-ordinate of 25,
 *  Y co-ordinate of 20, and Z co-ordinate of 25
 *  \n\n c 2 h 2 28 9 10 11 12 13 14 15
 *  \n Reading the line left to right, this declares a cell with cell ID of 2, cell type of hexahedron
 *  (note that tetrahedron = t and pyramid = p), materialID of 2, and the next eight values are the VectorsID of
 *  that need to be retrieved from the manyVectors list.
 */

class Model {
public:
    //Constructors and Destructor
    /** @brief Copy constructor
     */
    Model(const Model& aModel);
    /** @brief Blank constructor (empty)
     */
    Model(void);
    /** @brief Blank destructor (empty)
     */
    ~Model(void);

    //Custom std::cout function
    /** @brief Displays all the materials, using material display function; all the vectors,
     *  using vectors display function; the cell type at every cell ID; total number of cells;
     *  and the total number of vectors in the model
     */
    friend std::ostream& operator<< (std::ostream& Output, const Model& aModel);

    //Custom operator functions
    /** @brief Overwrites the member variables of the model calling the function
     *  with the values of aModel member variables
     */
    Model& operator= (const Model& aModel);
    /** @brief Returns true if they are equal
     */
    bool operator== ( Model& aModel);

    //Set functions
    /** @brief Sets the material list of the model
     */
    void Set_Materials(const std::vector<Material>& someMaterials);
    /** @brief Sets the vectors list of the model
     */
    void Set_Vectors(const std::vector<Vectors>& someVectors);
    /** @brief Sets the cell list of the model
     */
    void Set_Cells(const std::vector<Cell*>& someCells);
    /** @brief Sets the cell order list of the model
     */
    void Set_Cell_Order(const std::string& someCellOrder);

    //Get functions
    /** @brief Returns the material list of the model
     */
    std::vector<Material> Get_Materials(void);
    /** @brief Returns the vectors list of the model
     */
    std::vector<Vectors> Get_Vectors(void);
    /** @brief Returns the cell list of the model
     */
    std::vector<Cell*> Get_Cells(void);
    /** @brief Returns the cell order list of the model
     */
    std::string Get_Cell_Order(void);

    //Model specific functions
    /** @brief Loads a model from a proprietary file format. See detailed description for more info on the file format used
     */
    void Load_Model(const std::string& FilePath);
    /** @brief Saves a model to a proprietary file format. See detailed description for more info on the file format used
     */
    void Save_Model(const std::string& FilePath);
    /** @brief Returns the volume of the model by summing all the volumes of all the Cell(s) in the model
     */
    double Get_Volume(void);
    /** @brief Returns the weight of the model by summing all the weights of all the Cell(s) in the model
     */
    double Get_Weight(void);
    /** @brief Returns a vectors containing the centre of gravity of model
     *  @details First it finds all centre of gravities of all cells and their corresponding weight. Then it takes two centre of gravities and
     *  treat is as a fulcrum problem where you try to find the point in space where you would place the fulcrum to
     *  'balance' the weights. The position of the fulcrum will be the new centre of gravity and its weight is the combination of
     *  the two weights. This process is repeated until only one centre of gravity is left.
     */
    Vectors Get_Centre_Of_Gravity(void);
    /** @brief Returns a vectors containing the geometric centre by finding the most negative x,y,z co-ordinates
     *  and the most positive x,y,z co-ordinates and finding the midpoint
     */
    Vectors Get_Geometric_Centre(void);
    /** @brief Returns a vectors containing the overall dimensions by finding the most negative x,y,z co-ordinates
     *  and the most postive x,y,z co-ordinates and finding the difference
     */
    Vectors Get_Overall_Dimensions(void);
    /** @brief Translates all vertices of all cells such that it appears that the model has been rotated by Rotation_In_Degrees
     *  amount of degrees around the Axis_Of_Rotation about the point Centre_Of_Rotation.
     *  @details This is achieved by executing the Rotate member function, of every cell, on every cell and updating the manyVectors list
     *  @param Rotation_In_Degrees This is an angle where positive will cause clockwise rotation and negative anti-clockwise rotation
     *  @param Axis_Of_Rotation This can be either x, y or z - lowercase only - otherwise an error message will be displayed on console
     *  @param Centre_Of_Rotation This will be the point in space the cell is rotating around
     */
    void Rotate(double Rotation_In_Degrees, char Axis_Of_Rotation, Vectors Centre_Of_Rotation);

private:
    std::vector<Material> manyMaterials;           ///< @brief The list of materials in model, where manyMaterials index position = Material ID
    std::vector<Vectors> manyVectors;              ///< @brief The list of vectors in model, where manyVectors index position = Vectors ID
    std::vector<Cell*> manyCells;                  ///< @brief The list of cells in model, where manyCells index postion = Cell ID
    std::string cellOrder;                         ///< @brief The list representing the order in which the different types cells were created from the load file so that the save file can be saved with minimal changes

    std::vector<int> Get_Vectors_Being_Used(void); ///< @brief Returns the vectors from manyVectors being used in cells and is a required function for Get_Geometric_Centre() and Get_Overall_Dimensions()
    std::vector<Vectors> Get_Min_Max(void);        ///< @brief Returns the most positive and most negative vectors and is required function for Get_Geometric_Centre() and Get_Overall_Dimensions()
};

#endif // Model_hpp
