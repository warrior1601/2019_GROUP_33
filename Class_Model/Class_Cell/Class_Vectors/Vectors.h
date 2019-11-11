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
        float GetVector(float *Coord);
        float SeeVector();
        Vectors operator+(const Vectors& add);
        Vectors operator-(const Vectors& subtract);
        float Scalar_Product(const Vectors& a);
        Vectors Vector_Product(const Vectors& a);
};

#endif // VECTORS_H_INCLUDED
