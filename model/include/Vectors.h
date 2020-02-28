//
//  Vectors.h
//  Computing Project
//
//  Created by Jedidiah Paterson on 27/11/2019.
//  Copyright � 2019 Jedidiah Paterson. All rights reserved.
//
//  This header file contains the object Vectors. The Vectors class have
//  Members of X_Coord,Y_Coord, and Z_Coord that are the 3-dimensional
//  Coordinates of each point for a parent class for this project that
//  Class is named Cell
//

#ifndef VECTORS_H_INCLUDED
#define VECTORS_H_INCLUDED

#include <iostream>

class Vectors
{

private:
    /*
     * Members of the class Vectors
     * This Data is private and can only
     * Be accessed via friend or class functions
     */

    double X_Coord;
    double Y_Coord;
    double Z_Coord;

public:
    /*
     * These are public function the definition of each function
     * Is available in the source file Vectors.cpp
     */

    //-------------Constructors------------//

    Vectors(); // Blank Constructor
    Vectors(double aX_Coord); //Constructor with only one variable passed to the function
    Vectors(double aX_Coord, double aY_Coord); // Constructor with two variables passed to the function
    Vectors(double aX_Coord, double aY_Coord, double aZ_Coord);// Constructor with all possible variable passed to the function

    //--------------Destructor-------------//

    ~Vectors(); //destructor

    //-------------Set Functions-----------//

    /*
     * These function allow the user to set values of the
     * Individual members of the class Vectors or set all
     * Three members at once
     */

    void SetX_Vector(double aX_Coord);
    void SetY_Vector(double aY_Coord);
    void SetZ_Vector(double aZ_Coord);
    void SetVector(double aX_Coord, double aY_Coord, double aZ_Coord);

    //-------------Get Functions-----------//

    /*
     * The Get Functions all for the return of value
     * Stored in the Vector Member to be used
     */

    double GetXVector();
    double GetYVector();
    double GetZVector();

    //-----Operator Overload Functions-----//

    /*
     * Operator Overload function enable the
     * Addition subtraction and set equal to
     * Functions const references values are
     * Passed into function to unsure that the
     * original value is not changed
     */

    Vectors operator=(const Vectors& Copy);
    Vectors operator+(const Vectors& Add);
    Vectors operator-(const Vectors& Subtract);
    Vectors operator/(const double& Divide);
    Vectors operator*(const double& Multiply);

    /*
     * To find the Vector (Cross) product the following functions are applied
     * Cx = (Ay *Bz) - (Az *By)
     * Cy = (Az *Bx) - (Ax *Bz)
     * Cz = (Ax *By) - (Ay *Bx)
     * Vectors (Cx, Cy, Cz) is returned
     * For more information on scalar products visit
     * https://www.mathsisfun.com/algebra/vectors-cross-product.html
     */

    Vectors operator*(const Vectors& Multiply);

    //-------Special Member Functions------//

    /*
     * To find the scalar(Dot) product the following function is applied
     * Y = (Ax * Bx) + (Ay * By) + (Az + Bz)
     * Y is returned as a scalar product (single double value) not a Vectors
     * For more information on scalar products visit
     * https://www.mathsisfun.com/algebra/vectors-dot-product.html
     */

    double Scalar_Product(const Vectors& aVectors);
    
    //Square root of the summation of the square of X, Y and Z
    double Get_Magnitude(void);
    
    //Magnitude of the difference between it and aVectors
    double Get_Distance_To(const Vectors& aVectors);

     //-----------Friend Functions----------//

    friend std::ostream& operator<< (std::ostream& Output, const Vectors& aVectors);
    
    friend class Matrix3x3;
};

#endif // VECTORS_H_INCLUDED
