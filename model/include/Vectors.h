//  Vectors.h
//  Computing Project
//  Created by Jedidiah Paterson on 27/11/2019.

/** @file
 *  This header file contains the class Vectors. The Vectors class has the
 *  members X_Coord, Y_Coord and Z_Coord and represents a point in 3D space. It is
 *  a required member variable of the Cell and Model classes.
 *  @author Jedidiah Paterson
 */

#ifndef VECTORS_H_INCLUDED
#define VECTORS_H_INCLUDED

#include <iostream>

/** @class Vectors Vectors.h "Vectors.h"
 *  @brief The Vectors class represents a point in 3D space with private members
 *  of three floating point numbers - X_Coord, Y_Coord, and Z_Coord.
 *  @details The class has numerous operator overloads, including a vector/cross product
 *  overload as the operator*; ability to calculate the scalar product of two vectors; ability to calculate
 *  the magitude of a vectors; and ability to get the distance between two vectors.
 */

class Vectors
{
public:
//-------------Constructors and Destructor------------//
    /** @brief Blank constructor that assigns all co-ordinates to 0
     */
    Vectors();

    /** @brief This will assign the X co-ordinate and assigning the others to their blank constructor equivalent
     *  @param aX_Coord This is the X co-ordinate of the vectors
     */
    Vectors(double aX_Coord);

    /** @brief This will assign the X and Y co-ordinates and assigning the other to their blank constructor equivalent
     *  @param aX_Coord This is the X co-ordinate of the vectors
     *  @param aY_Coord This is the Y co-ordinate of the vectors
     */
    Vectors(double aX_Coord, double aY_Coord);

    /** @brief Full constructor
     *  @param aX_Coord This is the X co-ordinate of the vectors
     *  @param aY_Coord This is the Y co-ordinate of the vectors
     *  @param aZ_Coord This is the Z co-ordinate of the vectors
     */
    Vectors(double aX_Coord, double aY_Coord, double aZ_Coord);

    /** @brief Blank destructor (empty)
     */
    ~Vectors();



//-------------Set Functions-----------//
    /** @brief Sets the X co-ordinate of the vectors
     */
    void SetX_Vector(double aX_Coord);

    /** @brief Sets the Y co-ordinate of the vectors
     */
    void SetY_Vector(double aY_Coord);

    /** @brief Sets the Z co-ordinate of the vectors
     */
    void SetZ_Vector(double aZ_Coord);

    /**@brief Sets all member variables of the vectors
     */
    void SetVector(double aX_Coord, double aY_Coord, double aZ_Coord);



//-------------Get Functions-----------//
    /** @brief Returns the X co-ordinate of the vectors
     */
    double GetXVector();

    /** @brief Returns the Y co-ordinate of the vectors
     */
    double GetYVector();

    /** @brief Returns the Z co-ordinate of the vectors
     */
    double GetZVector();



//-----Operator Overload Functions-----//
    /** @brief Overwrites the member variables of the vectors calling the function
     *  with the values of Copy member variables
     */
    Vectors operator=(const Vectors& Copy);

    /** @brief Returns the addition of Add with the vectors calling the function by adding
     *  X co-ordinate to X co-ordinate, Y co-ordinate to Y co-ordinate and Z co-ordinate to Z co-ordinate.
     */
    Vectors operator+(const Vectors& Add);

    /** @brief Returns the subtraction of Subtract to the vectors calling the function by
     *  subtracting X co-ordinate of Subtract from X co-ordinate vectors calling the function;
     *  Y co-ordinate from Y co-ordinate and Z co-ordinate from Z co-ordinate.
     */
    Vectors operator-(const Vectors& Subtract);

    /** @brief Returns the scalar division of the vectors by Divide. It will output a
     *  warning to the console if divide by 0 is attempted and will not execute division
     */
    Vectors operator/(const double& Divide);

    /** @brief Returns the scalar multiplication of the vectors with Multiply
     */
    Vectors operator*(const double& Multiply);

    /** @brief Returns the vector/cross product of the vector calling the function, A(x,y,z), with Multiply, B(x,y,z),
     *  to give the result C(x,y,z). The formula used is: \n
     *  C(x) = A(y)*B(z) -  A(z)*B(y) \n
     *  C(y) = A(z)*B(x) - A(x)*B(z) \n
     *  C(z) = A(x)*B(y) - A(y)*B(x) \n
     */
    Vectors operator*(const Vectors& Multiply);



//-------Special Member Functions------//
    /** @brief Returns scalar/dot product of the vector calling the function, A(x,y,z), with Multiply, B(x,y,z),
     *  to give the result Result (a scalar). The formula used is: \n
     * Result = A(x)*B(x) + A(y)*B(y) + A(z)*B(z)
     */
    double Scalar_Product(const Vectors& aVectors);

    /** @brief Returns the magnitude of the vectors calling the function by
     * finding the square root of the summation of the square of X, Y, and Z co-ordinates
     */
    double Get_Magnitude(void);

    /** @brief Returns the distance between aVectors and the vectors calling the function
     *  by creating a difference vectors whose member variables is the difference the member
     *  variables of aVectors and the vectors calling the function. Then the magnitude of the
     *  difference vector is returned to give the distance.
     */
    double Get_Distance_To(const Vectors& aVectors);



//-----------Friend Functions----------//
    /** @brief Displays the values of all member variables of the vectors
     */
    friend std::ostream& operator<< (std::ostream& Output, const Vectors& aVectors);

    /** @brief This is to allow Matrix3x3 to access vectors member variables directly
     */
    friend class Matrix3x3;

private:
  double X_Coord;         ///< The X co-ordinate
  double Y_Coord;         ///< The Y co-ordinate
  double Z_Coord;         ///< The Z co-ordinate
};

#endif // VECTORS_H_INCLUDED
