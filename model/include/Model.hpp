//  Model.hpp
//  Computing Project
//
//  Created by Junaid Afzal on 16/11/2019.
//  Copyright © 2019 Junaid Afzal. All rights reserved.


/** @file
 * This header file contains the object Model which has the
 * ability to load from and save to a file which contains all
 * the info needed to create the model.
 */

#ifndef Model_hpp
#define Model_hpp

#include "Material.h"
#include "Vectors.h"
#include "Cell.hpp"


/** @class Model Model.hpp "Model.hpp"
 * @brief The Model class contains a list of
 * Cell, Vectors, and Material that make up
 * the Model. In order to call the Model constructor
 * you need to include the Cell, Vectors, and Material
 * header files.
 */
class Model {
public:
    /**
     * @brief Creates a model
     * @param aModel
     */
    Model(const Model& aModel);
    Model(void);
    ~Model(void);

    /**
     * @brief Custom cout function
     * @param Output
     * @param aModel
     * @returns
     */
    friend std::ostream& operator<< (std::ostream& Output, const Model& aModel);

    /**
     * @brief Allows for a model to be compied
     * @param aModel
     * @returns
     */
    Model& operator = (const Model& aModel);

    /**
     * @brief Will load a model
     * @param FilePath is the loaction of the file in the directory system
     */
    void Load_Model(const std::string& FilePath);

    /**
     * @brief Will Save the file to the FilePath
     * @param FilePath is the loaction that the save will be placed in the directory system
     */
    void Save_Model(const std::string& FilePath);

    /**
     * @brief Sets the Materials in the list of Materials
     * @param someMaterials
     */
    void Set_Materials(const std::vector<Material>& someMaterials);

    /**
     * @brief Set_Vectors
     * @param someVectors
     */
    void Set_Vectors(const std::vector<Vectors>& someVectors);
    /**
     * @brief Set_Cells
     * @param someCells
     */
    void Set_Cells(const std::vector<Cell*>& someCells);
    /**
     * @brief Set_Cell_Order
     * @param someCellOrder
     */
    void Set_Cell_Order(const std::string& someCellOrder);

    /**
     * @brief Get_Materials
     * @return
     */
    std::vector<Material> Get_Materials(void);

    /**
     * @brief Get_Vectors
     * @return
     */
    std::vector<Vectors> Get_Vectors(void);

    /**
     * @brief Get_Cells
     * @return
     */
    std::vector<Cell*> Get_Cells(void);

    /**
     * @brief Get_Cell_Order
     * @return
     */
    std::string Get_Cell_Order(void);

    //Model specific functions

    /**
     * @brief Summation of all the volumes of all the Cell (s) in model
     * @returns The total volume of the Model
     */
    double Get_Volume(void);

    /**
     * @brief Summation of all the weights of all the Cell (s) in model
     * @returns The total weight of the Model
     */
    double Get_Weight(void);

    /**
     * @brief Get_Centre_Of_Gravity
     * First find all COGs and their corresponding weight. Then take two COGs and treat is as a
     * fulcrum problem and try to balance the weights. The position of the fulcrum will be the new
     * COG and its weight is the combination of the two weights. This process is repeated until only
     * one COG is left.
     * @returns Center or Gravity
     */
    Vectors Get_Centre_Of_Gravity(void);

    /**
     * @brief Get_Min_Max() is called and the midpoint between the min and max values is the geometric centre
     * @returns The Geometric Centre
     */
    Vectors Get_Geometric_Centre(void);

    /**
     * @brief
     *       NOT SURE IF THIS COMMENT IS CORRET     Get_Min_Max() is called and the difference between the min and max values is the overall dimension
     * @returns
     */
    Vectors Get_Overall_Dimensions(void);

    /**
     * @brief Goes through every shape and rotates it about the centre of rotation and also updates the manyVectors list with the new Vectors
     * @param Rotation_In_Degrees is how are you want to rotate the object 1-359 degrees NOTE 0 and 360 degrees will do nothing to the shape
     * @param Axis_Of_Rotation is which axis you want to rotate to X, Y, or Z
     * @param Centre_Of_Rotation is the point you want to rotate from in using the class Vectors (X,Y, Z)
     */
    void Rotate(double Rotation_In_Degrees, char Axis_Of_Rotation, Vectors Centre_Of_Rotation);



private:
    std::vector<Material> manyMaterials;                ///<Material position = Material ID
    std::vector<Vectors> manyVectors;                   ///<Vectors position = Vectors ID
    std::vector<Cell*> manyCells;                       ///<All the shapes
    std::string cellOrder;                              ///<This represents the order in which the cells were created from the load file

    std::vector<int> Get_Vectors_Being_Used(void);      ///<Required funtion for Get_Geometric_Centre() and Get_Overall_Dimensions() that returns the most positive and most negative Vectors
    std::vector<Vectors> Get_Min_Max(void);             ///<Required funtionsfor Get_Geometric_Centre() and Get_Overall_Dimensions() that returns the most positive and most negative Vectors
};

#endif // Model_hpp
