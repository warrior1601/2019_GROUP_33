//  Material.cpp
//  Computing Project
//  Created by Chayanis Kulanumphol on 27/11/2019.
//  This file contains the definitions of the member functions for the Material class

#include <iostream>
#include "Material.h"
#include "double_equality_function.h"

//-------------Constructors and Destructor------------//
Material::Material()
{
    this->ID = 0;
    this->Density = 0;
    this->Colour = "N/A";
    this->Name = "N/A";
}

Material::Material(int ID)
{
    this->ID = ID;
    this->Density = 0;
    this->Colour = "N/A";
    this->Name = "N/A";
}

Material::Material(int ID, double Density)
{
    this->ID = ID;
    this->Density = Density;
    this->Colour = "N/A";
    this->Name = "N/A";
}

Material::Material(int ID, double Density, const std::string &Colour)
{
    this->ID = ID;
    this->Density = Density;
    this->Colour = Colour;
    this->Name = "N/A";
}

Material::Material(int ID, double Density, const std::string &Colour, const std::string &Name)
{
    this->ID = ID;
    this->Density = Density;
    this->Colour = Colour;
    this->Name = Name;
}

Material::~Material() {}

//-------------Set Functions-----------//
void Material::SetID(int ID)
{
    this->ID = ID;
}

void Material::SetDensity(double Density)
{
    this->Density = Density;
}

void Material::SetColour(const std::string &Colour)
{
    this->Colour = Colour;
}

void Material::SetName(const std::string &Name)
{
    this->Name = Name;
}

void Material::SetMaterial(int ID, double Density, const std::string &Colour, const std::string &Name)
{
    this->ID = ID;
    this->Density = Density;
    this->Colour = Colour;
    this->Name = Name;
}

//-------------Get Functions-----------//
int Material::GetID()
{
    return (ID);
}

double Material::GetDensity()
{
    return (Density);
}

std::string Material::GetColour()
{
    return (Colour);
}

std::string Material::GetName()
{
    return (Name);
}

//-----Operator Overload Functions-----//
bool Material::operator==(const Material& aMaterial)
{
    unsigned int Status = 0;

    if(this->ID != aMaterial.ID)
        Status++;
    if(Testing(Density, aMaterial.Density ) )
        Status++;
    if(this->Colour.compare(0, this->Colour.size(), aMaterial.Colour ) != 0)
        Status++;
    if(this->Name.compare(0, this->Name.size(), aMaterial.Name ) != 0)
        Status++;

    if (Status==0)
        return true;
    else
    {
       return false;
    }
}

//-----------Friend Functions----------//
std::ostream& operator<< (std::ostream& Output, const Material& aMaterial)
{
    Output << "ID = " << aMaterial.ID;
    Output << " Density = " << aMaterial.Density;
    Output << " Colour = " << aMaterial.Colour;
    Output << " Name = " << aMaterial.Name << std::endl;

    return Output;
}
