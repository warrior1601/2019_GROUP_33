//  Testing_File_Functions.h
//  Computing Project
//  Created by Jedidiah Paterson on 23/03/2020.
//  Copyright @ 2020 Jedidiah Paterson. All rights reserved.
/**
 * @file This File contains functions that are only used in the
 * testing of the Model/Cell/Xatrix/Vectors/Material code.
 * @author Jedidiah Paterson
 */

#ifndef TESTING_FILE_FUNCTIONS_H
#define TESTING_FILE_FUNCTIONS_H
#include <iostream>
#include <string>
#include "double_equality_function.h"
#include <typeinfo>

//-------------------Common Code-------------------//

template <class T>
/** @brief This template is used to determine if two items are the same
 * this is used across all o the classes that make up a Model
 */
unsigned int Testing (T aItem, T bItem)
{
  return (aItem == bItem) ? 0 : 1;
  // put in equal testing after all operator over loads a created
}

//-------------------Material Required Code-------------------//

template <class M, class I, class D, class C, class N>
/** @brief Testing is a function that gets passed aMaterial and and the expected
 * values for its members and checks for equality.
 * A template is used here so this file does not need the class header file
 * @returns a 0 if no error in equality is detected
 */
unsigned int Testing (M aMaterial,  I ID, D Density, C Colour, N Name)
{
    if (aMaterial.GetID() != ID )
        return(1);
    if (Testing(aMaterial.GetDensity(), Density ))
        return(1);
    if (aMaterial.GetColour().compare(0,aMaterial.GetColour().size(), Colour) !=0 )
        return(1);
    if (aMaterial.GetName().compare(0,aMaterial.GetName().size(), Name) !=0 )
        return(1);
    return(0);
}

//-------------------Vectors Required Code-------------------//
template <class V, class U>
/** @brief Testing is a function that gets passed aVectors and and the expected
 * values for its members and checks for equality.
 * A template is used here so this file does not need the class header file
 * @returns a 0 if no error in equality is detected
 */
unsigned int Testing (V aVectors,  U X, U Y, U Z)
{
    if ( Testing(aVectors.GetXVector(), X) )
        return(1);
    if ( Testing(aVectors.GetYVector(), Y) )
        return(1);
    if ( Testing(aVectors.GetZVector(), Z) )
        return(1);

    return(0);
}

//-------------------Cell Required Code-------------------//

template <class C, class V, class I, class M>
/** @brief Testing function is usd to test if a Cell and its sub classes
 * have been set up properly
 * @returns a 0 if no error in equality is detected
 */
unsigned int Testing(C aCell, V aVectorArray, I aVecotorOrderArray, M aMaterial )
{
    if (aCell.Get_Vertices().size() == aVectorArray.size() )
    {
        if (aCell.Get_Vertices_Order().size() == aVecotorOrderArray.size() )
        {
            for (unsigned int j = 0 ; j < aCell.Get_Vertices_Order().size() ; j++ )
            {
                if (Testing(aCell.Get_Vertices_Order()[j], aVecotorOrderArray[j] ))
                    return (1);
            }

            for (unsigned int i = 0 ; i < aCell.Get_Vertices().size() ; i++ )
            {
                if (Testing(aCell.Get_Vertices()[i], aVectorArray[i]) )
                    return (1);
            }
        }
        else
           return (1);
    }
    else
       return (1);

    if(Testing(aCell.Get_Material(), aMaterial) )
       return (1);
    return (0);
}

template <class C, class M>
/** @brief Testing function used to test if a empty constructor of a cell
 * has been initialized correctly
 * @returns a 0 if no error in equality is detected
 */
unsigned int Testing(C aCell, M aMaterial)
{
    unsigned int Testing_For_Error = 0;
    unsigned int Error = 0;
    std::string ShapeType = typeid(aCell).name();

    std::size_t cell  = ShapeType.find("Cell");
    std::size_t tetrahedron = ShapeType.find("Tetrahedron");
    std::size_t pyramid = ShapeType.find("Pyramid");
    std::size_t hexahedron = ShapeType.find("Hexahedron");

    if (cell!=std::string::npos)
    {
        Testing_For_Error = aCell.Get_Vertices().empty();
    }
    else if (tetrahedron!=std::string::npos)
    {
        if (Testing(aCell.Get_Vertices().size(), std::size_t (4)) == 0)
        Testing_For_Error = 1;
    }
    else if (pyramid!=std::string::npos)
    {
        if (Testing(aCell.Get_Vertices().size(), std::size_t (5)) == 0)
        Testing_For_Error = 1;
    }
    else if(hexahedron!=std::string::npos)
    {
        if (Testing(aCell.Get_Vertices().size(), std::size_t (8)) == 0)
        Testing_For_Error = 1;
    }

    if (Testing_For_Error == 1)
       {
        std::cout << "Blank Constructor (Vertices Array) and Get Function Works Properly" << std::endl;
        Testing_For_Error = 0;
       }
    else
       {
        std::cout << "Blank Constructor (Vertices Array) and Get Function Does Not Working Properly" << std::endl;
        Error = 1;
       }

    Testing_For_Error = aCell.Get_Vertices_Order().empty();

    if (Testing_For_Error == 1)
       {
        std::cout << "Blank Constructor (VerticesOrder) and Get Function Works Properly" << std::endl;
        Testing_For_Error = 0;
       }
    else
       {
        std::cout << "Blank Constructor (VerticesOrder) and Get Function Does Not Working Properly" << std::endl;
        Error = 1;
       }

    Testing_For_Error = Testing(aCell.Get_Material(), aMaterial );

    if (Testing_For_Error == 0 )
        std::cout << "Blank Constructor (theMaterial) and Get Function Works Properly" << std::endl;
    else
       {
        std::cout << "Blank Constructor (theMaterial) and Get Function Does Not Working Properly" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
       }
    return (Error);
}

template <class C, class D, class V>
/** @brief Testing fuction used to check the Volume Weight nad center of a cell
 * @returns a 0 if no error in equality is detected
 */
unsigned int Testing(C aCell, D aVolume, D aWeight, V aVectors_Center_of_Cell)
{
    unsigned int Testing_For_Error = 0;
    unsigned int Error = 0;

    Testing_For_Error = Testing(aCell.Get_Volume() , aVolume);

    if (Testing_For_Error == 0)
        std::cout << "Get Volume Function Works Properly" << std::endl;
    else
        {
        std::cout << "Get Volume Function Does Not Working Properly" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
        }

    Testing_For_Error = Testing(aCell.Get_Weight() ,aWeight);

    if (Testing_For_Error == 0)
        std::cout << "Get Weight Function Works Properly" << std::endl;
    else
        {
        std::cout << "Get Weight Function Does Not Working Properly" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
        }

    Testing_For_Error = Testing(aCell.Get_Centre_Of_Gravity(), aVectors_Center_of_Cell);

    if (Testing_For_Error == 0)
        std::cout << "Get Centre Of Gravity Function Works Properly" << std::endl;
    else
        {
        std::cout << "Get Centre Of Gravity Function Does Not Working Properly" << std::endl;
        Error = 1;
        Testing_For_Error = 0;
        }
    return Error;
}

//-------------------Matrix3x3 Required Code-------------------//

template <class M, class D>
/**
 * @brief Testing determins if te Matrix3x3 values were set correctly
 * @returns a 0 if the test is successful
 */
unsigned int Testing(M aMatrix3x3, D One, D Two, D Three, D Four, D Five, D Six, D Seven, D Eight, D Nine)
{
    if (!(Testing(aMatrix3x3.Get_Matrix_Data_1(), One)))
        if (!(Testing(aMatrix3x3.Get_Matrix_Data_2(), Two)))
            if (!(Testing(aMatrix3x3.Get_Matrix_Data_3(), Three)))
                if (!(Testing(aMatrix3x3.Get_Matrix_Data_4(), Four)))
                    if (!(Testing(aMatrix3x3.Get_Matrix_Data_5(), Five)))
                        if (!(Testing(aMatrix3x3.Get_Matrix_Data_6(), Six)))
                            if (!(Testing(aMatrix3x3.Get_Matrix_Data_7(), Seven)))
                                if (!(Testing(aMatrix3x3.Get_Matrix_Data_8(), Eight)))
                                    if (!(Testing(aMatrix3x3.Get_Matrix_Data_9(), Nine)))
                                        return 0;
                                    else
                                        return 1;
                                else
                                    return 1;
                            else
                                return 1;
                        else
                            return 1;
                    else
                        return 1;
                else
                    return 1;
            else
                return 1;
        else
            return 1;
    else
        return 1;
}

//-------------------Model Required Code-------------------//

template <class M>
/** @brief Testing test to see a model and its members have been initilized correctly
 * @returns a 0 if no error in equality is detected
 */
unsigned int Testing(M aModel)
{
    unsigned int Testing_For_Error = 0;
    unsigned int Error = 0;

    Testing_For_Error = aModel.Get_Materials().empty();

    if (Testing_For_Error == 1)
       {
        std::cout << "Blank Constructor (Material List) and Get Function Works Properly" << std::endl;
        Testing_For_Error = 0;
       }
    else
       {
        std::cout << "Blank Constructor (Material List) and Get Function Does Not Working Properly" << std::endl;
        Error = 1;
       }

    Testing_For_Error = aModel.Get_Vectors().empty();

    if (Testing_For_Error == 1)
       {
        std::cout << "Blank Constructor (Vectors List) and Get Function Works Properly" << std::endl;
        Testing_For_Error = 0;
       }
    else
       {
        std::cout << "Blank Constructor (Vectors List) and Get Function Does Not Working Properly" << std::endl;
        Error = 1;
       }

    Testing_For_Error = aModel.Get_Cells().empty();

    if (Testing_For_Error == 1)
       {
        std::cout << "Blank Constructor (Cells List) and Get Function Works Properly" << std::endl;
        Testing_For_Error = 0;
       }
    else
       {
        std::cout << "Blank Constructor (Cells List) and Get Function Does Not Working Properly" << std::endl;
        Error = 1;
       }

    Testing_For_Error = aModel.Get_Cell_Order().empty();

    if (Testing_For_Error == 1)
       {
        std::cout << "Blank Constructor (Cells Order List) and Get Function Works Properly" << std::endl;
        Testing_For_Error = 0;
       }
    else
       {
        std::cout << "Blank Constructor (Cells Order List) and Get Function Does Not Working Properly" << std::endl;
        Error = 1;
       }
    return Error;
}

template <class M, class LoM, class LoV, class LoC, class CO>
/**
 * @brief This function test that the model has been set using the set fucntions
 * by evaluating them against the Lists that make up the model
 * @returns a 0 if the model has be set up as expected
 */
unsigned int Test(M aModel, LoM aListOfMaterials, LoV aListOfVectors, LoC aListOfCells, CO aCellOrder)
{
    if (aModel.Get_Materials().size() == aListOfMaterials.size() )
    {
        if (aModel.Get_Vectors().size() == aListOfVectors.size() )
        {
            if (aModel.Get_Cells().size() == aListOfCells.size() )
            {
                if (aModel.Get_Cell_Order().size() == aCellOrder.size() )
                {
                    for (unsigned int i = 0 ; i < aModel.Get_Materials().size() ; i++ )
                    {
                        if (Testing(aModel.Get_Materials()[i], aListOfMaterials[i]) )
                            return (1);
                    }
                    for (unsigned int j = 0 ; j < aModel.Get_Vectors().size() ; j++ )
                    {
                        if (Testing(aModel.Get_Vectors()[j], aListOfVectors[j]) )
                            return (1);
                    }
                    for (unsigned int k = 0 ; k < aModel.Get_Cells().size() ; k++ )
                    {
                        if (Testing(aModel.Get_Cells()[k], aListOfCells[k]) )
                            return (1);
                    }
                    for (unsigned int l = 0 ; l < aModel.Get_Cell_Order().size() ; l++ )
                    {
                        if (Testing(aModel.Get_Cell_Order()[l], aCellOrder[l]) )
                            return (1);
                    }
                }
                else
                    return (1);
            }
            else
                return (1);
        }
        else
            return (1);
    }
    else
        return (1);

    return (0);
}
#endif // TESTING_FILE_FUNCTIONS_H
