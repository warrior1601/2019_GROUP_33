
//  Matrix.hpp
//  Computing Project
//
//  Created by Junaid Afzal on 24/11/2019.
//  Copyright © 2019 Junaid Afzal. All rights reserved.

/** @file
    * This header file contains the object Matrix3x3 which is a
    * 3x3 matrix, with all the standard matrix functions. Operator
    * overloads for both matrix and double inputs and also vector
    * multiplication. Also includes the standard matrix operations
    * transpose, determinant, inverse of a matrix as well as the
    * the ability to initialise a matrix as a rotation matrix about
    * any axis and degrees.
    */

#ifndef Matrix_hpp
#define Matrix_hpp

#include "Vectors.h"
#include <vector>
/**
 * @class Matrix3x3 Matrix.hpp "Matrix.hpp"
 * @brief The Matrix3x3 class
 */
class Matrix3x3 {
public:

    /**
     * @brief Matrix3x3
     * @param One
     * @param Two
     * @param Three
     * @param Four
     * @param Five
     * @param Six
     * @param Seven
     * @param Eight
     * @param Nine
     */
    Matrix3x3(const double& One, const double& Two, const double& Three,
              const double& Four, const double& Five, const double& Six,
              const double& Seven, const double& Eight, const double& Nine);
    Matrix3x3(const Matrix3x3& aMatrix3x3);
    Matrix3x3(void);
    ~Matrix3x3(void);
    
    /**
     * @brief Custom std::cout function
     * @param Output
     * @param aMatrix3x3
     * @returns
     */
    friend std::ostream& operator<< (std::ostream& Output, const Matrix3x3& aMatrix3x3);
    
    /**
     * @brief Custom operator functions
     * @param aMatrix3x3
     * @returns
     */
    Matrix3x3& operator = (const Matrix3x3& aMatrix3x3);
    
    /**
     * @brief operator +
     * @param aMatrix3x3
     * @return
     */
    Matrix3x3 operator+ (const Matrix3x3& aMatrix3x3);
    /**
     * @brief operator -
     * @param aMatrix3x3
     * @return
     */
    Matrix3x3 operator- (const Matrix3x3& aMatrix3x3);
    /**
     * @brief operator *
     * @param aMatrix3x3
     * @return
     */
    Matrix3x3 operator* (const Matrix3x3& aMatrix3x3);
    /**
     * @brief operator *
     * @param aVectors
     * @return
     */
    Vectors operator* (const Vectors& aVectors);
    /**
     * @brief operator +
     * @param aNumber
     * @return
     */
    Matrix3x3 operator+ (const double& aNumber);
    /**
     * @brief operator -
     * @param aNumber
     * @return
     */
    Matrix3x3 operator- (const double& aNumber);
    /**
     * @brief operator *
     * @param aNumber
     * @return
     */
    Matrix3x3 operator* (const double& aNumber);
    /**
     * @brief operator /
     * @param aNumber
     * @return
     */
    Matrix3x3 operator/ (const double& aNumber);
    
    /**
     * @brief operator +=
     * @param aMatrix3x3
     * @return
     */
    Matrix3x3& operator+= (const Matrix3x3& aMatrix3x3);
    /**
     * @brief operator -=
     * @param aMatrix3x3
     * @return
     */
    Matrix3x3& operator-= (const Matrix3x3& aMatrix3x3);
    /**
     * @brief operator *=
     * @param aMatrix3x3
     * @return
     */
    Matrix3x3& operator*= (const Matrix3x3& aMatrix3x3);
    
    Matrix3x3 operator+= (const double& aNumber);
    /**
     * @brief operator -=
     * @param aNumber
     * @return
     */
    Matrix3x3 operator-= (const double& aNumber);
    /**
     * @brief operator *=
     * @param aNumber
     * @return
     */
    Matrix3x3 operator*= (const double& aNumber);
    /**
     * @brief operator /=
     * @param aNumber
     * @return
     */
    Matrix3x3 operator/= (const double& aNumber);
    
    /**
     * @brief Set_MatrixData
     * @param aMatrixData
     */
    void Set_MatrixData(std::vector< std::vector<double> >& aMatrixData);
    /**
     * @brief Set_Matrix_Data_1
     * @param aMatrixNumber
     */
    void Set_Matrix_Data_1(const double& aMatrixNumber);
    /**
     * @brief Set_Matrix_Data_2
     * @param aMatrixNumber
     */
    void Set_Matrix_Data_2(const double& aMatrixNumber);
    /**
     * @brief Set_Matrix_Data_3
     * @param aMatrixNumber
     */
    void Set_Matrix_Data_3(const double& aMatrixNumber);
    /**
     * @brief Set_Matrix_Data_4
     * @param aMatrixNumber
     */
    void Set_Matrix_Data_4(const double& aMatrixNumber);
    /**
     * @brief Set_Matrix_Data_5
     * @param aMatrixNumber
     */
    void Set_Matrix_Data_5(const double& aMatrixNumber);
    /**
     * @brief Set_Matrix_Data_6
     * @param aMatrixNumber
     */
    void Set_Matrix_Data_6(const double& aMatrixNumber);
    /**
     * @brief Set_Matrix_Data_7
     * @param aMatrixNumber
     */
    void Set_Matrix_Data_7(const double& aMatrixNumber);
    /**
     * @brief Set_Matrix_Data_8
     * @param aMatrixNumber
     */
    void Set_Matrix_Data_8(const double& aMatrixNumber);
    /**
     * @brief Set_Matrix_Data_9
     * @param aMatrixNumber
     */
    void Set_Matrix_Data_9(const double& aMatrixNumber);
    
    /**
     * @brief Get_MatrixData
     * @return
     */
    std::vector< std::vector<double> > Get_MatrixData(void);
    /**
     * @brief Get_Matrix_Data_1
     * @return
     */
    double Get_Matrix_Data_1(void);
    /**
     * @brief Get_Matrix_Data_2
     * @return
     */
    double Get_Matrix_Data_2(void);
    /**
     * @brief Get_Matrix_Data_3
     * @return
     */
    double Get_Matrix_Data_3(void);
    /**
     * @brief Get_Matrix_Data_4
     * @return
     */
    double Get_Matrix_Data_4(void);
    /**
     * @brief Get_Matrix_Data_5
     * @return
     */
    double Get_Matrix_Data_5(void);
    /**
     * @brief Get_Matrix_Data_6
     * @return
     */
    double Get_Matrix_Data_6(void);
    /**
     * @brief Get_Matrix_Data_7
     * @return
     */
    double Get_Matrix_Data_7(void);
    /**
     * @brief Get_Matrix_Data_8
     * @return
     */
    double Get_Matrix_Data_8(void);
    /**
     * @brief Get_Matrix_Data_9
     * @return
     */
    double Get_Matrix_Data_9(void);
    
    //Matrix3x3 specific functions
    /** @brief
     * For column vectors, each of these basic vector rotations appears counterclockwise
     * when the axis about which they occur points toward the observer, the coordinate system is
     * right-handed, and the angle θ is positive. See (https://en.wikipedia.org/wiki/Rotation_matrix) for more info
     * Note that the rotation occurs with respect to the origin. Therefore, if rotation around the
     * objects centre is required, the object must be translated such that the centre of the object
     * is at the origin.
     * @param Rotation_In_Degrees
     * @param Axis_Of_Rotation
     */
    void Initialise_As_Rotation_Matrix(double Rotation_In_Degrees, char Axis_Of_Rotation);
    
    /**
     * @brief Transpose_Matrix
     */
    void Transpose_Matrix(void);
    
    /**
     * @brief Get_Determinant
     * Using Sarrus' Rule, see (https://en.wikipedia.org/wiki/Rule_of_Sarrus) for more info
     * @return
     */
    double Get_Determinant(void);
    
    /**
     * @brief Inverse_Matrix
     * Method is as follows - Replace each element in matrix by it's co-factor;
     * trasnpose the matirx; and Divide matrix data by determinant
     */
    void Inverse_Matrix(void);
    
private:
    std::vector< std::vector<double> > MatrixData; ///<
};

#endif // Matrix_hpp
