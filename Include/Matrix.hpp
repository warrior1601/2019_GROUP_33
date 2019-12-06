//
//  Matrix.hpp
//  Computing Project
//
//  Created by Junaid Afzal on 24/11/2019.
//  Copyright © 2019 Junaid Afzal. All rights reserved.
//
//  This header file contains the object Matrix3x3 which is a
//  3x3 matrix, with all the standard matrix functions. Operator
//  overloads for both matrix and double inputs and also vector
//  multiplication. Also includes the standard matrix operations
//  transpose, determinant, inverse of a matrix as well as the
//  the ability to initialise a matrix as a rotation matrix about
//  any axis and degrees.
//

#ifndef Matrix_hpp
#define Matrix_hpp

#include "../Include/Vectors.h"
#include <vector>

class Matrix3x3 {
public:
    //Constructors and destructors
    Matrix3x3(const double& One, const double& Two, const double& Three,
              const double& Four, const double& Five, const double& Six,
              const double& Seven, const double& Eight, const double& Nine);
    Matrix3x3(const Matrix3x3& aMatrix3x3);
    Matrix3x3(void);
    ~Matrix3x3(void);
    
    //Custom std::cout function
    friend std::ostream& operator<< (std::ostream& Output, const Matrix3x3& aMatrix3x3);
    
    //Custom operator functions
    Matrix3x3& operator = (const Matrix3x3& aMatrix3x3);
    
    Matrix3x3 operator+ (const Matrix3x3& aMatrix3x3);
    Matrix3x3 operator- (const Matrix3x3& aMatrix3x3);
    Matrix3x3 operator* (const Matrix3x3& aMatrix3x3);
    Vectors operator* (const Vectors& aVectors);
    
    Matrix3x3 operator+ (const double& aNumber);
    Matrix3x3 operator- (const double& aNumber);
    Matrix3x3 operator* (const double& aNumber);
    Matrix3x3 operator/ (const double& aNumber);
    
    Matrix3x3& operator+= (const Matrix3x3& aMatrix3x3);
    Matrix3x3& operator-= (const Matrix3x3& aMatrix3x3);
    Matrix3x3& operator*= (const Matrix3x3& aMatrix3x3);
    
    Matrix3x3 operator+= (const double& aNumber);
    Matrix3x3 operator-= (const double& aNumber);
    Matrix3x3 operator*= (const double& aNumber);
    Matrix3x3 operator/= (const double& aNumber);
    
    //Set and get functions
    void Set_MatrixData(std::vector< std::vector<double> >& aMatrixData);
    void Set_Matrix_Data_1(const double& aMatrixNumber);
    void Set_Matrix_Data_2(const double& aMatrixNumber);
    void Set_Matrix_Data_3(const double& aMatrixNumber);
    void Set_Matrix_Data_4(const double& aMatrixNumber);
    void Set_Matrix_Data_5(const double& aMatrixNumber);
    void Set_Matrix_Data_6(const double& aMatrixNumber);
    void Set_Matrix_Data_7(const double& aMatrixNumber);
    void Set_Matrix_Data_8(const double& aMatrixNumber);
    void Set_Matrix_Data_9(const double& aMatrixNumber);
    
    std::vector< std::vector<double> > Get_MatrixData(void);
    double Get_Matrix_Data_1(void);
    double Get_Matrix_Data_2(void);
    double Get_Matrix_Data_3(void);
    double Get_Matrix_Data_4(void);
    double Get_Matrix_Data_5(void);
    double Get_Matrix_Data_6(void);
    double Get_Matrix_Data_7(void);
    double Get_Matrix_Data_8(void);
    double Get_Matrix_Data_9(void);
    
    //Matrix3x3 specific functions
   
    //For column vectors, each of these basic vector rotations appears counterclockwise
    //when the axis about which they occur points toward the observer, the coordinate system is
    //right-handed, and the angle θ is positive. See https://en.wikipedia.org/wiki/Rotation_matrix for more info
    
    //Note that the rotation occurs with respect to the origin. Therefore, if rotation around the
    //objects centre is required, the object must be translated such that the centre of the object
    //is at the origin.
    void Initialise_As_Rotation_Matrix(double Rotation_In_Degrees, char Axis_Of_Rotation);//
    
    
    void Transpose_Matrix(void);
    
    //Using Sarrus' Rule, see https://en.wikipedia.org/wiki/Rule_of_Sarrus for more info
    double Get_Determinant(void);
    
    //Method is as follows - Replace each element in matrix by it's co-factor;
    //trasnpose the matirx; and Divide matrix data by determinant
    void Inverse_Matrix(void);
    
private:
    std::vector< std::vector<double> > MatrixData;
};

#endif // Matrix_hpp
