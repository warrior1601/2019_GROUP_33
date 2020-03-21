//  Matrix.hpp
//  Computing Project
//  Created by Junaid Afzal on 24/11/2019.

/**
 *  @file This header file contains the class Matrix3x3. The Matrix3x3 class has a
 *  single floating-point 2D array and represents a 3x3 matrix. It is a required
 *  variable for the rotation members functions of Cell and Model classes.
 *  @author Junaid Afzal
 */

#ifndef Matrix_hpp
#define Matrix_hpp

#include "Vectors.h"
#include <vector>

/** @class Matrix3x3 Matrix3x3.hpp "Matrix3x3.hpp"
 *  @brief The Matrix3x3 class represents a 3x3 matrix with private members of a
 *  single floating-point 2D array.
 *  @details This class has numerous operator overloads for both scalars and other
 *  matrix3x3 objects; abilities to initialise the matrix3x3 as a rotation matrix for cells;
 *  ability to transpose the matrix3x3; ability to determine the determinant; and ability to
 *  get the inverse of a matrix3x3.
 *  \image html Matrix.png "Matrix numbering" width=500cm
 */

class Matrix3x3 {
public:
    //Constructors and Destructor
    /** @brief Full constructor that adds the appropriate number of columns and rows and assigns the values
     *  as described in the detailed description
     */
    Matrix3x3(const double& One, const double& Two, const double& Three,
              const double& Four, const double& Five, const double& Six,
              const double& Seven, const double& Eight, const double& Nine);

    /** @brief Copy constructor
    */
    Matrix3x3(const Matrix3x3& aMatrix3x3);

    /** @brief Blank constructor that adds the appropriate number of columns and rows and assigns the values to 0
    */
    Matrix3x3(void);
    
    /** @brief Blank destructor (empty)
     */
    ~Matrix3x3(void);



    //Custom std::cout function
    /** @brief Displays all matrix3x3 private members in the standard 3x3 matrix layout
     */
    friend std::ostream& operator<< (std::ostream& Output, const Matrix3x3& aMatrix3x3);



    //Custom operator functions
    /** @brief Overwrites the member variables of the matrix3x3 calling the function
     *  with the values of aMatrix3x3 member variables
     */
    Matrix3x3& operator= (const Matrix3x3& aMatrix3x3);

    /** @brief Returns the addition of two matrix3x3
     */
    Matrix3x3 operator+ (const Matrix3x3& aMatrix3x3);

    /** @brief Returns the subtraction of aMatrix3x3 to the matrix3x3 calling the function
     */
    Matrix3x3 operator- (const Matrix3x3& aMatrix3x3);

    /** @brief Returns the multiplication of two matrix3x3
     */
    Matrix3x3 operator* (const Matrix3x3& aMatrix3x3);

    /** @brief Returns the multiplication of a matrix3x3 with a vectors, which is treated
     *  as a 3x1 matrix
     */
    Vectors operator* (const Vectors& aVectors);

    /** @brief Returns the addition of a scalar to matrix3x3
     */
    Matrix3x3 operator+ (const double& aNumber);

    /** @brief Returns the subtraction of a scalar from matrix3x3
     */
    Matrix3x3 operator- (const double& aNumber);

    /** @brief Returns the multiplication of a scalar to matrix3x3
     */
    Matrix3x3 operator* (const double& aNumber);

    /** @brief Returns the division of matrix3x3 by a scalar. It will output a
     *  warning to the console if divide by 0 is attempted and will not execute division
     */
    Matrix3x3 operator/ (const double& aNumber);

    /** @brief Returns the addition of two matrix3x3 but the matrix3x3
     *  calling the function is overwritten with the result
     */
    Matrix3x3& operator+= (const Matrix3x3& aMatrix3x3);

    /** @brief Returns the subtraction of aMatrix3x3 to the matrix3x3 calling
     *  the function and is overwritten with the result
     */
    Matrix3x3& operator-= (const Matrix3x3& aMatrix3x3);

    /** @brief Returns the multiplication of two matrix3x3 but the matrix3x3
     *  calling the function is overwritten with the result
     */
    Matrix3x3& operator*= (const Matrix3x3& aMatrix3x3);

    /** @brief Returns the addition of a scalar to matrix3x3 but the matrix3x3
     *  calling the function is overwritten with the result
     */
    Matrix3x3 operator+= (const double& aNumber);

    /** @brief Returns the subtraction of a scalar from matrix3x3 but the matrix3x3
     *  calling the function is overwritten with the result
     */
    Matrix3x3 operator-= (const double& aNumber);

    /** @brief Returns the multiplication of a scalar to matrix3x3 but the matrix3x3
     *  calling the function is overwritten with the result
     */
    Matrix3x3 operator*= (const double& aNumber);

    /** @brief Returns the division of matrix3x3 by a scalar but the matrix3x3
     *  calling the function is overwritten with the result. It will output a
     *  warning to the console if divide by 0 is attempted and will not execute division
     */
    Matrix3x3 operator/= (const double& aNumber);



    //Set functions
    /** @brief Sets all matrix3x3 data with an equivalent 2D array. All information
     *  outside the 3x3 range will be ignored
     */
    void Set_MatrixData(std::vector< std::vector<double> >& aMatrixData);

    /** @brief Sets data point 1. See detailed description for image
     */
    void Set_Matrix_Data_1(const double& aMatrixNumber);

    /** @brief Sets data point 2. See detailed description for image
     */
    void Set_Matrix_Data_2(const double& aMatrixNumber);

    /** @brief Sets data point 3. See detailed description for image
     */
    void Set_Matrix_Data_3(const double& aMatrixNumber);

    /** @brief Sets data point 4. See detailed description for image
     */
    void Set_Matrix_Data_4(const double& aMatrixNumber);

    /** @brief Sets data point 5. See detailed description for image
     */
    void Set_Matrix_Data_5(const double& aMatrixNumber);

    /** @brief Sets data point 6. See detailed description for image
     */
    void Set_Matrix_Data_6(const double& aMatrixNumber);

    /** @brief Sets data point 7. See detailed description for image
     */
    void Set_Matrix_Data_7(const double& aMatrixNumber);

    /** @brief Sets data point 8. See detailed description for image
     */
    void Set_Matrix_Data_8(const double& aMatrixNumber);

    /** @brief Sets data point 9. See detailed description for image
     */
    void Set_Matrix_Data_9(const double& aMatrixNumber);



    //Get functions
    /** @brief Returns all matrix3x3 data in an equivalent 2D array
     */
    std::vector< std::vector<double> > Get_MatrixData(void);

    /** @brief Returns data point 1. See detailed description for image
     */
    double Get_Matrix_Data_1(void);

    /** @brief Returns data point 2. See detailed description for image
     */
    double Get_Matrix_Data_2(void);

    /** @brief Returns data point 3. See detailed description for image
     */
    double Get_Matrix_Data_3(void);

    /** @brief Returns data point 4. See detailed description for image
     */
    double Get_Matrix_Data_4(void);

    /** @brief Returns data point 5. See detailed description for image
     */
    double Get_Matrix_Data_5(void);

    /** @brief Returns data point 6. See detailed description for image
     */
    double Get_Matrix_Data_6(void);

    /** @brief Returns data point 7. See detailed description for image
     */
    double Get_Matrix_Data_7(void);

    /** @brief Returns data point 8. See detailed description for image
     */
    double Get_Matrix_Data_8(void);

    /** @brief Returns data point 9. See detailed description for image
     */
    double Get_Matrix_Data_9(void);



    //Matrix3x3 specific functions
    /** @brief A rotation matrix translates a vectors such that it would appear to have
     *  rotated along Axis_Of_Rotation by an amount equal to Rotation_In_Degrees. Note that the
     *  centre of rotation is the origin and that positive Rotation_In_Degrees will result in
     *  clockwise rotation and a negative Rotation_In_Degrees counter-clockwise rotation.
     *  See https://en.wikipedia.org/wiki/Rotation_matrix for more info
     *  @param Rotation_In_Degrees This is how much rotation is required
     *  @param Axis_Of_Rotation This is which axis of rotation is required - acceptable parameters are
     *  x, y and z in char form. If any other char is used, an error message will be displayed on the console
     */
    void Initialise_As_Rotation_Matrix(double Rotation_In_Degrees, char Axis_Of_Rotation);

    /**
     * @brief Transposes matrix3x3 and overwrites the matrix3x3 calling the function with the result
     */
    void Transpose_Matrix(void);

    /** @brief Returns the determinant of matrix3x3 using Sarrus' Rule.
     *  See (https://en.wikipedia.org/wiki/Rule_of_Sarrus) for more info
     */
    double Get_Determinant(void);

    /** Finds the inverse of matrix3x3 and overwrites the matrix3x3 calling the function with the result.
     *  Note that if there is no inverse, then an error message will be displayed to the console.
     *  The method is as follows: replace each element in matrix3x3 by it's co-factor;
     *  trasnpose the matirx; and divide matrix data by its determinant.
     */
    void Inverse_Matrix(void);

private:
    std::vector< std::vector<double> > MatrixData; ///< A floating-point 2D array, representing a 3x3 matrix \image html Matrix.png "Matrix numbering" width=500cm
};

#endif // Matrix_hpp
