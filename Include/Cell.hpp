//
//  Cell.hpp
//  Computing Project
//
//  Created by Junaid Afzal on 16/11/2019.
//  Copyright © 2019 Junaid Afzal. All rights reserved.
//
//  This header file contains the object Cell and the sub-objects
//  Tetrahedron, Pyramid and Hexahedron. Cell is the general form
//  of a shape, while the sub-objects conatin the specific member
//  functions.
//

#ifndef Cell_hpp
#define Cell_hpp

#include "Materail.h"
#include "Vectors.h"
#include <vector>

class Cell {
public:
    //Cell specific functions
    virtual float Get_Volume(void);
    virtual float Get_Weight(void);
    virtual Vectors Get_Centre_Of_Gravity(void);
    
private:
    
};





class Tetrahedron:public Cell {
public:
    //Constructors and destructors
    Tetrahedron(const Vectors& aV0, const Vectors& aV1, const Vectors& aV2, const Vectors& aV3, const Material& aMaterial);
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
    void Set_Material(const Material& aMaterial);
    
    //Get functions
    Vectors Get_V0(void);
    Vectors Get_V1(void);
    Vectors Get_V2(void);
    Vectors Get_V3(void);
    Material Get_Material(void);
    
    //Tetrahedron specific functions
    virtual float Get_Volume(void);
    virtual float Get_Weight(void);
    virtual Vectors Get_Centre_Of_Gravity(void);
    
private:
    Vectors V0, V1, V2, V3;
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
    Pyramid(const Vectors& aV0, const Vectors& aV1, const Vectors& aV2, const Vectors& aV3, const Vectors& aV4, const Material& aMaterial);
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
    void Set_Material(const Material& aMaterial);
    
    //Get functions
    Vectors Get_V0(void);
    Vectors Get_V1(void);
    Vectors Get_V2(void);
    Vectors Get_V3(void);
    Vectors Get_V4(void);
    Material Get_Material(void);
    
    //Pyramid specific functions
    virtual float Get_Volume(void);
    virtual float Get_Weight(void);
    virtual Vectors Get_Centre_Of_Gravity(void);
    
private:
    Vectors V0, V1, V2, V3, V4;
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
    Hexahedron(const Vectors& aV0, const Vectors& aV1, const Vectors& aV2, const Vectors& aV3, const Vectors& aV4, const Vectors& aV5, const Vectors& aV6, const Vectors& aV7, const Material& aMaterial);
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
    Material Get_Material(void);
    
    //Hexahedron specific functions
    virtual float Get_Volume(void);
    virtual float Get_Weight(void);
    virtual Vectors Get_Centre_Of_Gravity(void);
    
private:
    Vectors V0, V1, V2, V3, V4, V5, V6, V7;
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
