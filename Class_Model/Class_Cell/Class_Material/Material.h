#pragma once

#include <string>


class Material {
private:
    int density;
    std::string colour;
    std::string name;
public:
    int getDensity() const;

    void setDensity(int density);

    const std::string &getName() const;

    void setName(const std::string &name);

    const std::string &getColour() const;

    void setColour(const std::string &colour);

    friend std::ostream &operator<<(std::ostream &os, const Material &mat); // Owen

    friend std::istream &operator>>(std::istream &in, Material &out); // Dom - done

    std::string describe() const; // done
};

