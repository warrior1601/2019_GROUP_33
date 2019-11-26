#ifndef MATERIAL_H_INCLUDED
#define MATERIAL_H_INCLUDED

#include <string>
#include <iostream>

using namespace std;//for std::

class Material
{
private:

    //Variables
    int ID;
    float Density;
    std::string Colour;
    std::string Name;

public:
    //Construct
    Material();
    Material( float Density, const std::string &Name, const std::string &Colour, int ID);
    //Destruct
    ~Material();
    /*Setup Function*/
    void SetMaterial( float Density, const std::string &Name, const std::string &Colour, int ID);
    void SetDensity(float Density);
    void SetName(const std::string &Name);
    void SetColour(const std::string &Colour);
    void SetID(int ID);
    float GetDensity();//return density
    std::string GetColour();//return colour
    std::string GetName();//return name
    int GetID();//return id
    friend std::ostream& operator<< (std::ostream&, const Material& Material);
};

#endif // MATERIAL_H_INCLUDED
