//
//  Model.hpp
//  Computing Project
//
//  Created by Junaid Afzal on 16/11/2019.
//  Copyright © 2019 Junaid Afzal. All rights reserved.
//
//  This header file contains the object Model which has the
//  ability to load from and save to a file which contains all
//  the info needed to create the model.
//

#ifndef Model_hpp
#define Model_hpp

#include "../Include/Material.h"
#include "../Include/Vectors.h"
#include "../Include/Cell.hpp"

class Model {
public:
    //Constructors and destructors
    Model(const Model& aModel);
    Model(void);
    ~Model(void);

    //Custom std::cout function
    friend std::ostream& operator<< (std::ostream& Output, const Model& aModel);

    //Custom operator function
    Model& operator = (const Model& aModel);

    //Set and get functions
    void Load_Model(const std::string& FilePath);
    void Save_Model(const std::string& FilePath);

    void Set_Materials(const std::vector<Material>& someMaterials);
    void Set_Vectors(const std::vector<Vectors>& someVectors);
    void Set_Tetrahedrons(const std::vector<Tetrahedron>& someTetrahedrons);
    void Set_Pyramids(const std::vector<Pyramid>& somePyramids);
    void Set_Hexahedrons(const std::vector<Hexahedron>& someHexahedrons);
    void Set_Cell_Order(const std::string& someCellOrder);

    std::vector<Material> Get_Materials(void);
    std::vector<Vectors> Get_Vectors(void);
    std::vector<Tetrahedron> Get_Tetrahedrons(void);
    std::vector<Pyramid> Get_Pyramids(void);
    std::vector<Hexahedron> Get_Hexahedrons(void);
    std::string Get_Cell_Order(void);

    //Model specific functions

    //Summation of all the volumes of all the shapes in model
	double Get_Volume(void);

    //Summation of all the weights of all the shapes in model
	double Get_Weight(void);

    //First find all COGs and their corresponding weight. Then take two COGs and treat is as a
    //fulcrum problem and try to balance the weights. The position of the fulcrum will be the new
    //COG and its weight is the combination of the two weights. This process is repeated until only
    //one COG is left.
    Vectors Get_Centre_Of_Gravity(void);

    //Get_Min_Max() is called and the midpoint between the min and max values is the geometric centre
    Vectors Get_Geometric_Centre(void);

    //Get_Min_Max() is called and the difference between the min and max values is the overall dimension
    Vectors Get_Overall_Dimensions(void);

    //Goes through every shape and rotates it about the centre of rotation and also updates the manyVectors
    //list with the new Vectors
    void Rotate(double Rotation_In_Degrees, char Axis_Of_Rotation, Vectors Centre_Of_Rotation);

private:
    std::vector<Material> manyMaterials;                //Material position = Material ID
    std::vector<Vectors> manyVectors;                   //Vectors position = Vectors ID
    std::vector<Tetrahedron> manyTetrahedrons;
    std::vector<Pyramid> manyPyramids;
    std::vector<Hexahedron> manyHexahedrons;
    std::string cellOrder;                              //This represents the order in which the cells were created from the load file

    //Required funtions for Get_Geometric_Centre() and Get_Overall_Dimensions() that returns the most positive and most negative Vectors
    std::vector<int> Get_Vectors_Being_Used(void);
    std::vector<Vectors> Get_Min_Max(void);
};

#endif // Model_hpp
