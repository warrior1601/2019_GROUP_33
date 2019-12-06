#ifndef MATERIAL_H_INCLUDED
#define MATERIAL_H_INCLUDED
//
//  Material.h
//  Computing Project
//
//  Created by Chayanis Kulanumphol on 27/11/2019.
//  This header file contains the object Material. The Material class has
//  Members of ID, Density, Colour, and Name these are required to for further
//  Functions that are members of the Cell Class such as Volume and Weight function
//  The Material Class will be a Sub-Class of a Cell for this project


#include <string>
#include <iostream>

using namespace std;

class Material
{
private:
    /*
     * Members of the class Material
     * This Data is private and can only
     * Be accessed via friend or class functions
     */

    int ID;
    double Density;
    std::string Colour;
    std::string Name;

public:
    /*
     * These are public function the definition of each function
     * Is available in the source file Material.cpp
     */

//-------------Constructors------------//
    Material(); //Blank Constructor
    Material(int ID); //Constructor receiving only an ID number
    Material(int ID, double Density); //Constructor receiving ID and Density only
    Material(int ID, double Density, const std::string &Colour); //Constructor receiving ID, Density, Colour only
    Material(int ID, double Density, const std::string &Colour, const std::string &Name); //Constructor receiving all members for Material

//--------------Destructor-------------//
    ~Material();

//-------------Set Functions-----------//

    /*
     * These function allow the user to set values of the
     * Individual members of the class Material or set all
     * Four members at once
     */

    void SetID(int ID);
    void SetDensity(double Density);
    void SetColour(const std::string &Colour);
    void SetName(const std::string &Name);
    void SetMaterial(int ID, double Density, const std::string &Colour,const std::string &Name);

//-------------Get Functions-----------//

    /*
     * The Get Functions all for the return of value
     * Stored in the Material Member to be used
     */

    int GetID();
    double GetDensity();
    std::string GetColour();
    std::string GetName();


//-----------Friend Functions----------//
    friend std::ostream& operator<< (std::ostream&, const Material& Material);
};

#endif // MATERIAL_H_INCLUDED
