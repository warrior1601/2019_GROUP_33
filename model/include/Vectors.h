//  Vectors.h
//  Computing Project
//
//  Created by Jedidiah Paterson on 27/11/2019.
//  Copyright @ 2019 Jedidiah Paterson. All rights reserved.
    /** @file
      * This header file contains the object Vectors. The Vectors class have
      * members of X_Coord, Y_Coord, and Z_Coord which are the 3-dimensional
      * coordinates of each point, found in its parent class named Cell
      */
#ifndef VECTORS_H_INCLUDED
#define VECTORS_H_INCLUDED

#include <iostream>

    /** @class Vectors Vectors.h "Vectors.h"
     *  @brief A Vector represnts a point in space
     *  that has an X, Y, and Z coordinate in the 3D
     *  Cartesian coordinate system.
     *  Members of the class Vectors
     *  are private and can only
     *  be accessed via friend or class functions
     */

class Vectors
{

private:

    double X_Coord;         ///< The X coordinate
    double Y_Coord;         ///< The Y coordinate
    double Z_Coord;         ///< The Z coordinate

public:
//-------------Constructors------------//
    /**
     * @brief Blank Constructor
     */
    Vectors();

    /**
     * @brief Constructor with only one variable passed to the function
     * @param aX_Coord
     */
    Vectors(double aX_Coord);

    /**
     * @brief Constructor with two variables passed to the function
     * @param aX_Coord
     * @param aY_Coord
     */
    Vectors(double aX_Coord, double aY_Coord);

    /**
     * @brief Constructor with all possible variables passed to the function
     * @param aX_Coord
     * @param aY_Coord
     * @param aZ_Coord
     */
    Vectors(double aX_Coord, double aY_Coord, double aZ_Coord);

//--------------Destructor-------------//
    ~Vectors(); //destructor

//-------------Set Functions-----------//
    /**
     * @brief Set the X coodinate of the Vector
     * @param aX_Coord
     */
    void SetX_Vector(double aX_Coord);

    /**
     * @brief Set the Y coodinate of the Vector
     * @param aY_Coord
     */
    void SetY_Vector(double aY_Coord);

    /**
     * @brief Set the Z coodinate of the Vector
     * @param aZ_Coord
     */
    void SetZ_Vector(double aZ_Coord);

    /**
     * @brief Set the entire Vector
     * @param aX_Coord
     * @param aY_Coord
     * @param aZ_Coord
     */
    void SetVector(double aX_Coord, double aY_Coord, double aZ_Coord);

//-------------Get Functions-----------//
    /**
     * @returns The X coordinate
     */
    double GetXVector();

    /**
     * @returns The Y coordinate
     */
    double GetYVector();

    /**
     * @return The Z coordinate
     */
    double GetZVector();

//-----Operator Overload Functions-----//
    /**
     * @brief This enable one vector to be copied to another vector
     * @param Copy is the second Vectors
     */
    Vectors operator=(const Vectors& Copy);

    /**
     * @brief Allows the addition of TWO vectors
     * @param Add this is the second Vectors
     * @returns A vector that is the addition value of the two vectors being added
     */
    Vectors operator+(const Vectors& Add);

    /**
     * @brief Allows for the subtraction of TWO vectors
     * @param Subtract this is the second Vectors
     * @returns A vector that is the subtracted value of one vector on another
     */
    Vectors operator-(const Vectors& Subtract);

    /**
     * @brief Allows for the division of ONE vector by a number
     * @param Divide this a number other than 0
     * @returns A vector that has been devided by a number
     */
    Vectors operator/(const double& Divide);

    /**
     * @brief Mulitplies a vector by a number
     * @param Multiply This can be any number
     * @returns A vector that have been multplied by a number
     */
    Vectors operator*(const double& Multiply);

    /**
      * @brief To find the Vector (Cross) product the following functions are applied
      * Cx = (Ay *Bz) - (Az *By)
      * Cy = (Az *Bx) - (Ax *Bz)
      * Cz = (Ax *By) - (Ay *Bx)
      * Vectors (Cx, Cy, Cz) is returned
      * For more information on scalar products visit
      * (https://www.mathsisfun.com/algebra/vectors-cross-product.html)
      * @param Multiply This is a Vector consisiting of a valid X, Y, and Z coordinate
      * @returns a vector that has been multiplied by another vector
      */
    Vectors operator*(const Vectors& Multiply);

//-------Special Member Functions------//

    /**
      * @brief To find the scalar(Dot) product the following function is applied
      * Y = (Ax * Bx) + (Ay * By) + (Az + Bz)
      * Y is returned as a scalar product (single double value) not a Vectors
      * For more information on scalar products visit
      * (https://www.mathsisfun.com/algebra/vectors-dot-product.html)
      * @param aVectors
      * @returns The scalar product of TWO vectors
      */
    double Scalar_Product(const Vectors& aVectors);

    /**
      * @returns The Square root of the summation of the square of X, Y, and Z coordanites
      */
    double Get_Magnitude(void);
    
    /**
     * @brief Magnitude of the difference between it and aVectors
     * @param aVectors
     * @returns Distance between two Vectors
     */
    double Get_Distance_To(const Vectors& aVectors);

//-----------Friend Functions----------//

    /**
     * @brief Dispays the contents of the Vector in the terminal block
     * @param Output this is typically "std::cout"
     * @param aVectors the desired Vector is selected here
     */
    friend std::ostream& operator<< (std::ostream& Output, const Vectors& aVectors);
    
    friend class Matrix3x3;
};

#endif // VECTORS_H_INCLUDED
