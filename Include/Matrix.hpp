//
//  Matrix.hpp
//  Computing Project
//
//  Created by Junaid Afzal on 24/11/2019.
//  Copyright © 2019 Junaid Afzal. All rights reserved.
//
//  This header file contains the object Matrix3x3 which is a
//  3x3 matrix, with all the standard matrix functions. Operator
//  overloads for both matrix and float inputs and also vector
//  multiplication. Also includes the standard matrix operations
//  transpose, determinant, inverse of a matrix as well as the
//  the ability to initialise a matrix as a rotation matrix about
//  any axis and degrees.
//

#ifndef Matrix_hpp
#define Matrix_hpp

#include "Vectors.h"
#include <vector>

class Matrix3x3 {
public:
    //Constructors and destructors
    Matrix3x3(const float& One, const float& Two, const float& Three,
              const float& Four, const float& Five, const float& Six,
              const float& Seven, const float& Eight, const float& Nine);
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
    
    Matrix3x3 operator+ (const float& aNumber);
    Matrix3x3 operator- (const float& aNumber);
    Matrix3x3 operator* (const float& aNumber);
    Matrix3x3 operator/ (const float& aNumber);
    
    Matrix3x3& operator+= (const Matrix3x3& aMatrix3x3);
    Matrix3x3& operator-= (const Matrix3x3& aMatrix3x3);
    Matrix3x3& operator*= (const Matrix3x3& aMatrix3x3);
    
    Matrix3x3 operator+= (const float& aNumber);
    Matrix3x3 operator-= (const float& aNumber);
    Matrix3x3 operator*= (const float& aNumber);
    Matrix3x3 operator/= (const float& aNumber);
    
    //Set and get functions
    void Set_MatrixData(std::vector< std::vector<float> >& aMatrixData);
    void Set_Matrix_Data_1(const float& aMatrixNumber);
    void Set_Matrix_Data_2(const float& aMatrixNumber);
    void Set_Matrix_Data_3(const float& aMatrixNumber);
    void Set_Matrix_Data_4(const float& aMatrixNumber);
    void Set_Matrix_Data_5(const float& aMatrixNumber);
    void Set_Matrix_Data_6(const float& aMatrixNumber);
    void Set_Matrix_Data_7(const float& aMatrixNumber);
    void Set_Matrix_Data_8(const float& aMatrixNumber);
    void Set_Matrix_Data_9(const float& aMatrixNumber);
    
    std::vector< std::vector<float> > Get_MatrixData(void);
    float Get_Matrix_Data_1(void);
    float Get_Matrix_Data_2(void);
    float Get_Matrix_Data_3(void);
    float Get_Matrix_Data_4(void);
    float Get_Matrix_Data_5(void);
    float Get_Matrix_Data_6(void);
    float Get_Matrix_Data_7(void);
    float Get_Matrix_Data_8(void);
    float Get_Matrix_Data_9(void);
    
    //Matrix3x3 specific functions
   
    //For column vectors, each of these basic vector rotations appears counterclockwise
    //when the axis about which they occur points toward the observer, the coordinate system is
    //right-handed, and the angle θ is positive. See https://en.wikipedia.org/wiki/Rotation_matrix for more info
    
    //Note that the rotation occurs with respect to the origin. Therefore, if rotation around the
    //objects centre is required, the object must be translated such that the centre of the object
    //is at the origin.
    void Initialise_As_Rotation_Matrix(float Rotation_In_Degrees, char Axis_Of_Rotation);//
    
    
    void Transpose_Matrix(void);
    
    //Using Sarrus' Rule, see https://en.wikipedia.org/wiki/Rule_of_Sarrus for more info
    float Get_Determinant(void);
    
    //Method is as follows - Replace each element in matrix by it's co-factor;
    //trasnpose the matirx; and Divide matrix data by determinant
    void Inverse_Matrix(void);
    
private:
    std::vector< std::vector<float> > MatrixData {3}; //3 is required for initialisation
};

#endif // Matrix_hpp
