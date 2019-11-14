#include "Material.h"
#include <iostream>
#include <string>


std::string Material::describe() const {
    return name + " with colour " + colour + " with density " + std::to_string(density);
}

int Material::getDensity() const {
    return density;
}

void Material::setDensity(int density) {
    Material::density = density;
}

const std::string &Material::getName() const {
    return name;
}

void Material::setName(const std::string &name) {
    Material::name = name;
}

const std::string &Material::getColour() const {
    return colour;
}

void Material::setColour(const std::string &colour) {
    Material::colour = colour;
}


std::istream &operator>>(std::istream &in, Material &out)
{
    return in >> out.density >> out.colour >> out.name;
}


std::ostream &operator<<(std::ostream &os, const Material &mat)
{
    return os << mat.density << " " << mat.colour << " " << mat.name;
}

