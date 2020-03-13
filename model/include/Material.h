//  Material.h
//  Computing Project
//
//  Created by Chayanis Kulanumphol on 27/11/2019.

    /** @file
     * This header file contains the object Material. The Material class has
     * members of ID, Density, Colour, and Name these are required to for further
     * functions that are members of the Cell Class such as Volume and Weight function
     * the Material Class will be a Sub-Class of a Cell for this project
     */

#ifndef MATERIAL_H_INCLUDED
#define MATERIAL_H_INCLUDED

#include <string>
#include <iostream>

/** @class Material Material.h "inc/Material.h"
 *  @brief Members of the class Material
 *  are private and can only be accessed
 *  via friend or class functions
 */
class Material
{
private:

    int ID;                 ///< The assigned identification number for the material
    double Density;         ///< The density in kilograms per meter cubed
    std::string Colour;     ///< The color of the object which is represented by 6 digit hex number Two digits are for the RGB colours and range from 0 - 255
    std::string Name;       ///< The name of the Material

public:
//-------------Constructors------------//
    /**
     *  Blank Constructor
     */
    Material();

    /** @param ID is the Materials identification number
     */
    Material(int ID);

    /** @param ID is the Materials identification number
     *  @param Density is the density of the object in kgm^3
     */
    Material(int ID, double Density);

    /** @param ID is the Materials identification number
     *  @param Density is the density of the object in kgm^3
     *  @param Colour is a string that is 6 digits long.
     */
    Material(int ID, double Density, const std::string &Colour);

    /** @param ID is the Materials identification number
     *  @param Density is the density of the object in kg/m^3
     *  @param Colour is a string that is 6 digits long.
     *  @param Name is a string that names the Material
     */
    Material(int ID, double Density, const std::string &Colour, const std::string &Name); //Constructor receiving all members for Material

//--------------Destructor-------------//
    ~Material();

//-------------Set Functions-----------//

    /**
     * @param Sets the ID number given a integer
     */
    void SetID(int ID);

    /**
     * @param Set the Density of the object gievn a double
     */
    void SetDensity(double Density);

    /**
     * @param Sets the Colour given a 6 digit string ranging from 00000 - FFFFFF
     */
    void SetColour(const std::string &Colour);

    /**
     * @param Sets the Name of the Material given a string
     */
    void SetName(const std::string &Name);

    /**
     * @param Sets the ID number given a integer
     * @param Set the Density of the object gievn a double
     * @param Sets the Colour given a 6 digit string ranging from 00000 - FFFFFF
     * @param Sets the Name of the Material given a string
     */
    void SetMaterial(int ID, double Density, const std::string &Colour,const std::string &Name);

//-------------Get Functions-----------//

    /**
     * @returns The Materials ID number
     */
    int GetID();

    /**
     * @returns The Materials Density
     */
    double GetDensity();

    /**
     * @returns The Materials colour as a 6 digit hexadecemal number
     */
    std::string GetColour();

    /**
     * @returns The Name of the Material
     */
    std::string GetName();


//-----------Friend Functions----------//

    /**
     * @brief Dispays the contents of the Material in the terminal block
     * @param ostream
     * @param Material
     */
    friend std::ostream& operator<< (std::ostream& Output, const Material& Material);
};

#endif // MATERIAL_H_INCLUDED
