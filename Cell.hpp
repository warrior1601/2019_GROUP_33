//
//  Cell.hpp
//  Computing Project
//


/*
Material
- one line cou

- correct member functions
 */


#ifndef Cell_hpp
#define Cell_hpp

#include <iostream>
#include <vector>
#include <cstdlib>
#include "Material.h"
#include "Vectors.h"

class Cell {
public:
    //Cell specific functions
    virtual float Get_Volume();
    virtual float Get_Weight();
    virtual Vectors Get_Centre_Of_Gravity();

private:

};

std::vector<Tetrahedron> manyTetrahedrons;



class Tetrahedron:public Cell {
public:
    //Constructors and destructors
    Tetrahedron(const Vectors& aV0, const Vectors& aV1, const Vectors& aV2, const Vectors& aV3, const Material& aMaterial);
    Tetrahedron();
    ~Tetrahedron();

    //Custom std::cout function
    friend std::ostream& operator<< (std::ostream&, Tetrahedron& aTetrahedron);

    //Custom operator function
    Tetrahedron& operator = (const Tetrahedron& aTetrahedron);

    //Set functions
    void Set_V0(const Vectors& aVectors);
    void Set_V1(const Vectors& aVectors);
    void Set_V2(const Vectors& aVectors);
    void Set_V3(const Vectors& aVectors);
    void Set_Material(const Material& aMaterial);

    //Get functions
    Vectors Get_V0();
    Vectors Get_V1();
    Vectors Get_V2();
    Vectors Get_V3();
    Material Get_Material();

    //Tetrahedron specific functions
    virtual float Get_Volume();
    virtual float Get_Weight();
    virtual Vectors Get_Centre_Of_Gravity();

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
    Pyramid();
    ~Pyramid();

    //Custom std::cout function
    friend std::ostream& operator<< (std::ostream&, Pyramid& aPyramid);

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
    Vectors Get_V0();
    Vectors Get_V1();
    Vectors Get_V2();
    Vectors Get_V3();
    Vectors Get_V4();
    Material Get_Material();

    //Pyramid specific functions
    virtual float Get_Volume();
    virtual float Get_Weight();
    virtual Vectors Get_Centre_Of_Gravity();

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
    Hexahedron();
    ~Hexahedron();

    //Custom std::cout function
    friend std::ostream& operator<< (std::ostream&, Hexahedron& aHexahedron);

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
    Vectors Get_V0();
    Vectors Get_V1();
    Vectors Get_V2();
    Vectors Get_V3();
    Vectors Get_V4();
    Vectors Get_V5();
    Vectors Get_V6();
    Vectors Get_V7();
    Material Get_Material();

    //Hexahedron specific functions
    virtual float Get_Volume();
    virtual float Get_Weight();
    virtual Vectors Get_Centre_Of_Gravity();

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

#endif /* Cell_hpp */
