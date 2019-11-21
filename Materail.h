#ifndef MATERAIL_H_INCLUDED
#define MATERAIL_H_INCLUDED

#include <string>
using namespace std;//for std::

class Material {
private:
  //Variables
  float density;
  std::string colour;
  std::string name;
  int id;
public:
  //Construct
  Material();

  Material ( float density, const std::string &name, const std::string &colour, int id);
  //Destruct
  ~Material();
  /*Setup Function*/
  void setMaterial( float density, const std::string &name, const std::string &colour, int id);
  float getdensity();//return density
  std::string getcolour();//return colour
  std::string getname();//return name
  int getid();//return id
  };

#endif // MATERAIL_H_INCLUDED
