#include <iostream>
#include "Material.h"

//Default Value
Material::Material()
{

}


Material::Material( float Density, const std::string &Name, const std::string &Colour, int ID)
{
    this->Density = Density;
    this->Colour = Colour;
    this->Name = Name;
    this->ID = ID;
}
//Destructor
Material::~Material()
{

}
//Create Material by Setup Function
void Material::SetMaterial( float Density, const std::string &Name, const std::string &Colour, int ID)
{
    this->Density = Density;
    this->Colour = Colour;
    this->Name = Name;
    this->ID = ID;
}

float Material::GetDensity()
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
int Material::GetID()
{
    return (ID);
}

void Material::SetDensity(float Density)
{
    this->Density = Density;
}
void Material::SetName(const std::string &Name)
{
    this->Name = Name;
}
void Material::SetColour(const std::string &Colour)
{
    this->Colour = Colour;
}
void Material::SetID(int ID)
{
    this->ID = ID;
}

std::ostream& operator<< (std::ostream&,const Material& aMaterial)
{
    std::cout << "ID = "<<aMaterial.ID;
    std::cout << " Density = "<<aMaterial.Density;
    std::cout << " Colour = "<<aMaterial.Colour;
    std::cout << " Name = "<<aMaterial.Name<<std::endl;

    return std::cout;
}

