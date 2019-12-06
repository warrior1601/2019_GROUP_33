#include <iostream>
#include "../Include/Material.h"
//
//  Material.cpp
//  Computing Project
//
//  Created by Chayanis Kulanumphol on 27/11/2019.
//  This file contains the definitions of functions for the Class
//  Material.

using namespace std;


//-------------Constructors------------//

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

//--------------Destructor-------------//
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

string Material::GetColour()
{
    return (Colour);
}

string Material::GetName()
{
    return (Name);
}

//-----------Friend Functions----------//

std::ostream& operator<< (std::ostream&,const Material& aMaterial)
{
    std::cout << "ID = "<<aMaterial.ID;
    std::cout << " Density = "<<aMaterial.Density;
    std::cout << " Colour = "<<aMaterial.Colour;
    std::cout << " Name = "<<aMaterial.Name<<std::endl;

    return std::cout;
}

