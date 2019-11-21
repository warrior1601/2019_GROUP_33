#include <iostream>
#include "Materail.h"

//Default Value
Material::Material()
{

}


Material::Material( float density, const std::string &name, const std::string &colour, int id)
{
    this->density = density;
    this->colour = colour;
    this->name = name;
    this->id = id;
}
//Destructor
Material::~Material()
{

}
//Create Material by Setup Function
void Material::setMaterial( float density,const std::string &name, const std::string &colour, int id)
{
    this->density = density;
    this->colour = colour;
    this->name = name;
    this->id = id;
}
// Return Value
float Material::getdensity()
{
    cout<<density<<endl;
    return (density);
}


string Material::getcolour()
{
    cout<<colour<<endl;
    return (colour);
}
string Material::getname()
{
    cout<<name<<endl;
    return (name);
}
int Material::getid()
{
    cout<<id<<endl;
    return (id);
}
