#ifndef VECTORS_H_INCLUDED
#define VECTORS_H_INCLUDED

class Vectors
{

private:
    float *Coordinates;

public:
    Vectors(); //Constructor
    ~Vectors(); //destructor
    void SetVector(float *Coord);
    float GetXVector();
    float GetYVector();
    float GetZVector();
    /*void SeeVector(); // Make this a friend ostream function*/
    Vectors operator=(const Vectors& Copy);
    Vectors operator+(const Vectors& add);
    Vectors operator-(const Vectors& subtract);
    float Scalar_Product(const Vectors& aVectors);
    Vectors Vector_Product(const Vectors& aVectors);
    Vectors Vector_Divide_By_Number(float My_Number);
    friend std::ostream& operator<< (std::ostream&, Vectors& aVectors);

};

#endif // VECTORS_H_INCLUDED
