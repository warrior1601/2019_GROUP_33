//
//  Cell.cpp
//  Computing Project
//

#include "Cell.hpp"

//Cell specific functions
float Cell::Get_Volume() { return 0; }

float Cell::Get_Weight() { return 0; }

Vectors Cell::Get_Centre_Of_Gravity() { Vectors temp; return temp; }





//------------------------------------------------------------------------TETRAHEDRON MEMBER FUNCTIONS------------------------------------------------------------------------//

//Constructors and destructors
Tetrahedron::Tetrahedron(const Vectors& aV0, const Vectors& aV1, const Vectors& aV2, const Vectors& aV3, const Material& aMaterial) { V0 = aV0; V1 = aV1; V2 = aV2; V3 = aV3; theMaterial = aMaterial; }

Tetrahedron::Tetrahedron() {}

Tetrahedron::~Tetrahedron() {}





//Custom std::cout function
std::ostream& operator<< (std::ostream&, Tetrahedron& aTetrahedron)
{
    std::cout << "V0 = ";
    aTetrahedron.Get_V0().SeeVector();
    std::cout << "V1 = ";
    aTetrahedron.Get_V1().SeeVector();
    std::cout << "V2 = ";
    aTetrahedron.Get_V2().SeeVector();
    std::cout << "V3 = ";
    aTetrahedron.Get_V3().SeeVector();

    //std::cout << "Material " << aTetrahedron.Get_Material() << std::endl;

    return std::cout;
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
        theMaterial = aTetrahedron.theMaterial;

        return(*this);
    }
}





//Set functions
void Tetrahedron::Set_V0(const Vectors& aVectors) { V0 = aVectors; }

void Tetrahedron::Set_V1(const Vectors& aVectors) { V1 = aVectors; }

void Tetrahedron::Set_V2(const Vectors& aVectors) { V2 = aVectors; }

void Tetrahedron::Set_V3(const Vectors& aVectors) { V3 = aVectors; }

void Tetrahedron::Set_Material(const Material& aMaterial) { theMaterial = aMaterial; }





//Get functions
Vectors Tetrahedron::Get_V0() { return V0; }

Vectors Tetrahedron::Get_V1() { return V1; }

Vectors Tetrahedron::Get_V2() { return V2; }

Vectors Tetrahedron::Get_V3() { return V3; }

Material Tetrahedron::Get_Material() { return theMaterial; }





//Tetrahedron specific functions
float Tetrahedron::Get_Volume()
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
    float Volume = abs( a.Scalar_Product( b.Vector_Product(c) ) / 6.0 );

    return Volume;
}

float Tetrahedron::Get_Weight()
{
    float Weight = Get_Volume() * (float)theMaterial.getDensity();

    return Weight;
}

Vectors Tetrahedron::Get_Centre_Of_Gravity()
{
    //Top down view of Vectors numbering assumption
    //
    //    V2         V1
    //
    //         V3
    //
    //         V0

    //Centroid = centre of gravity assuming uniform density across object
    //It is calculated by finding the average of each co-ordinate

    Vectors Centroid;

//    Centroid.Set_X( ( V0.Get_X() + V1.Get_X() + V2.Get_X() + V3.Get_X() ) / 4.0 );
//    Centroid.Set_Y( ( V0.Get_Y() + V1.Get_Y() + V2.Get_Y() + V3.Get_Y() ) / 4.0 );
//    Centroid.Set_Z( ( V0.Get_Z() + V1.Get_Z() + V2.Get_Z() + V3.Get_Z() ) / 4.0 );

    return Centroid;
}





//------------------------------------------------------------------------PYRAMID MEMBER FUNCTIONS------------------------------------------------------------------------//

//Constructors and destructors
Pyramid::Pyramid(const Vectors& aV0, const Vectors& aV1, const Vectors& aV2, const Vectors& aV3, const Vectors& aV4, const Material& aMaterial) { V0 = aV0; V1 = aV1; V2 = aV2; V3 = aV3; V4 = aV4; theMaterial = aMaterial; }

Pyramid::Pyramid() { }

Pyramid::~Pyramid() { }





//Custom std::cout function
std::ostream& operator<< (std::ostream&, Pyramid& aPyramid)
{
    std::cout << "V0 = ";
    aPyramid.Get_V0().SeeVector();
    std::cout << "V1 = ";
    aPyramid.Get_V1().SeeVector();
    std::cout << "V2 = ";
    aPyramid.Get_V2().SeeVector();
    std::cout << "V3 = ";
    aPyramid.Get_V3().SeeVector();
    std::cout << "V4 = ";
    aPyramid.Get_V4().SeeVector();

    //std::cout << "Material " << aPyramid.Get_Material() << std::endl;

    return std::cout;
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

void Pyramid::Set_Material(const Material& aMaterial) { theMaterial = aMaterial; }





//Get functions
Vectors Pyramid::Get_V0() { return V0; }

Vectors Pyramid::Get_V1() { return V1; }

Vectors Pyramid::Get_V2() { return V2; }

Vectors Pyramid::Get_V3() { return V3; }

Vectors Pyramid::Get_V4() { return V4; }

Material Pyramid::Get_Material() { return theMaterial; }





//Pyramid specific functions
float Pyramid::Get_Volume()
{
    //Top down view of Vectors numbering assumption
    //
    //    V3         V2
    //
    //         V4
    //
    //    V0         V1

    //Split the pyramid along V0 - V4 - V2 "line" to create two tetrahedrons
    Tetrahedron a(V0, V2, V3, V4, theMaterial);
    Tetrahedron b(V0, V1, V2, V4, theMaterial);

    return a.Get_Volume() + b.Get_Volume();
}

float Pyramid::Get_Weight()
{
    float Weight = Get_Volume() * (float)theMaterial.getDensity();

    return Weight;
}

Vectors Pyramid::Get_Centre_Of_Gravity()
{
    //Top down view of Vectors numbering assumption
    //
    //    V3         V2
    //
    //         V4
    //
    //    V0         V1

    //Split the pyramid along V0 - V4 - V2 "line" to create two tetrahedrons and find centroid of each
    //Then centroid of pyramid will be the average/midpoint of the tetrahedron centroids as they have equal volume and therefore equal weight
    Tetrahedron a(V0, V2, V3, V4, theMaterial);
    Tetrahedron b(V0, V1, V2, V4, theMaterial);

    Vectors aCentroid = a.Get_Centre_Of_Gravity();
    Vectors bCentroid = b.Get_Centre_Of_Gravity();

    //Vectors Centroid = (aCentroid + bCentroid) / 2.0;

    Vectors Centroid;

    return Centroid;
}





//------------------------------------------------------------------------HEXAHEDRON MEMBER FUNCTIONS------------------------------------------------------------------------//

//Constructors and destructors
Hexahedron::Hexahedron(const Vectors& aV0, const Vectors& aV1, const Vectors& aV2, const Vectors& aV3, const Vectors& aV4, const Vectors& aV5, const Vectors& aV6, const Vectors& aV7, const Material& aMaterial)
{ V0 = aV0; V1 = aV1; V2 = aV2; V3 = aV3; V4 = aV4; V5 = aV5; V6 = aV6; V7 = aV7; theMaterial = aMaterial; }

Hexahedron::Hexahedron() {}

Hexahedron::~Hexahedron() {}





//Custom std::cout function
std::ostream& operator<< (std::ostream&, Hexahedron& aHexahedron)
{
    std::cout << "V0 = " << aHexahedron.Get_V0().SeeVector() << "V1 = " << aHexahedron.Get_V1().SeeVector() << "V2 = " << aHexahedron.Get_V2().SeeVector() << "V3 = " << aHexahedron.Get_V3().SeeVector() << "V4 = " << aHexahedron.Get_V4().SeeVector() << "V5 = " << aHexahedron.Get_V5().SeeVector() << "V6 = " << aHexahedron.Get_V6().SeeVector() << "V7 = " << aHexahedron.Get_V7().SeeVector();

    //std::cout << "Material " << aHexahedron.Get_Material() << std::endl;

    return std::cout;
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

void Hexahedron::Set_Material(const Material& aMaterial) { theMaterial = aMaterial; }





//Get functions
Vectors Hexahedron::Get_V0() { return V0; }

Vectors Hexahedron::Get_V1() { return V1; }

Vectors Hexahedron::Get_V2() { return V2; }

Vectors Hexahedron::Get_V3() { return V3; }

Vectors Hexahedron::Get_V4() { return V4; }

Vectors Hexahedron::Get_V5() { return V5; }

Vectors Hexahedron::Get_V6() { return V6; }

Vectors Hexahedron::Get_V7() { return V7; }

Material Hexahedron::Get_Material() { return theMaterial; }





//Hexahedron specific functions
float Hexahedron::Get_Volume()
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
    Pyramid a(V0, V1, V2, V3, V6, theMaterial);
    Pyramid b(V0, V1, V5, V4, V6, theMaterial);
    Pyramid c(V0, V3, V7, V4, V6, theMaterial);

    return a.Get_Volume() + b.Get_Volume() + c.Get_Volume();
}

float Hexahedron::Get_Weight()
{
    float Weight = Get_Volume() * (float)theMaterial.getDensity();

    return Weight;
}

Vectors Hexahedron::Get_Centre_Of_Gravity()
{
    //Top down view of Vectors numbering assumption
    //
    //    V3/V7         V2/V6
    //
    //
    //
    //    V0/V4         V1/V5

    //Split the hexahedron in to three pyramids and find centroid of each
    //See http://mathcentral.uregina.ca/QQ/database/QQ.09.06/siva1.html for more info
    //Then centroid of hexahedron will be the average/midpoint of the pyramid centroids as they have equal volume and therefore equal weight
    Pyramid a(V0, V1, V2, V3, V6, theMaterial);
    Pyramid b(V0, V1, V5, V4, V6, theMaterial);
    Pyramid c(V0, V3, V7, V4, V6, theMaterial);

    //Vectors Centroid = ( a.Get_Centre_Of_Gravity() + b.Get_Centre_Of_Gravity() + c.Get_Centre_Of_Gravity() ) / 3.0;

    Vectors Centroid;

    return Centroid;
}
