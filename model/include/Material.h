//  Material.h
//  Computing Project
//  Created by Chayanis Kulanumphol on 27/11/2019.

/** @file
 *  This header file contains the class Material. The Material class has the
 *  members ID, Density, Colour, and Name and represnts the material of a particular
 *  cell. It is a required member variable of the Cell and Model classes.
 *  @author Chayanis Kulanumphol
 */

#ifndef MATERIAL_H_INCLUDED
#define MATERIAL_H_INCLUDED

#include <string>
#include <iostream>

/** @class Material Material.h "Material.h"
 *  @brief The material of a cell with private members of ID, Density, Colour, and Name.
 *  @details This class is merely a container for material details and has no specialised functions.
 *  The Material class private members are an integer ID that will be used to
 *  identify the material amongst many material objects (when used by the model class,
 *  this value will be NOT be negative); a floating-point density variable; a string
 *  of 3 hexadecimal numbers, representing red, green and blue (when used by the model
 *  class this string will contain 3 two-digit hexadecimal numbers), that range from
 *  0-FF to hold the colour of the material; and a string to hold the name of the material.
 *  @warning No error checking on member variables, e.g. negative densities
 */

class Material
{
public:
//-------------Constructors and Destructors------------//
    /** @brief Blank constructor that assigns ID to 0; Density to 0; Colour to "N/A"; and Name to "N/A".
     */
    Material();

    /** @brief This will assign the identification number of the material and all
     *  other unassigned values to their blank constructor equivalent
     *  @param ID is the identification number for the material
     */
    Material(int ID);

    /** @brief This will assign the identification number and density of the material and all
     *  other unassigned values to their blank constructor equivalent
     *  @param ID is the identification number for the material
     *  @param Density is the density of the Material
     */
    Material(int ID, double Density);

    /** @brief This will assign the identification number, density and colour
     *  of the material and all other unassigned values to their blank constructor equivalent
     *  @param ID is the identification number for the material
     *  @param Density is the density of the Material
     *  @param Colour is the colour of the material
     */
    Material(int ID, double Density, const std::string &Colour);

    /** @brief Full constructor
     *  @param ID is the identification number for the material
     *  @param Density is the density of the Material
     *  @param Colour is the colour of the material
     *  @param Name is the name of the material
     */
    Material(int ID, double Density, const std::string &Colour, const std::string &Name);

    /** @brief Blank destructor (empty)
     */
    ~Material();



//-------------Set Functions-----------//
    /** @brief Sets the identification number of the material
     */
    void SetID(int ID);

    /** @brief Sets the density of the material
     */
    void SetDensity(double Density);

    /** @brief Sets the colour of the material
     */
    void SetColour(const std::string &Colour);

    /** @brief Sets the name of the material
     */
    void SetName(const std::string &Name);

    /** @brief Sets all member variables of the material
     */
    void SetMaterial(int ID, double Density, const std::string &Colour,const std::string &Name);



//-------------Get Functions-----------//
    /** @brief Returns the identification number of the material
     */
    int GetID();

    /** @brief Returns the density of the material
     */
    double GetDensity();

    /** @brief Returns colour of the materials
     */
    std::string GetColour();

    /** @brief Returns The Name of the Material
     */
    std::string GetName();

//-----Operator Overload Functions-----//
    /**
     * @brief Returns true if their is equality
     */
    bool operator==(const Material& IsEqual);


//-----------Friend Functions----------//
    /** @brief Displays the values of all member variables of the material
     */
    friend std::ostream& operator<< (std::ostream& Output, const Material& Material);

private:
  int ID;                 ///< Identification number for the material, when used by the model class this value will be NOT be negative
  double Density;         ///< Density of the material
  std::string Colour;     ///< Colour of the material, when used by the model class this string will contain 3 two digit hexadecimal numbers
  std::string Name;       ///< Name of the material
};

#endif // MATERIAL_H_INCLUDED
