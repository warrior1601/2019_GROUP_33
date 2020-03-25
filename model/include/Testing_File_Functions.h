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
/**
 *@brief This template is used to determine if two items are the same
 * this is used across all o the classes that make up a Model
 */
template <class T>
unsigned int Testing (T aItem, T bItem)
{
  return (aItem == bItem) ? 0 : 1;
  // put in equal testing after all operator over loads a created
}

//-------------------Material Required Code-------------------//


template <class M, class I, class D, class C, class N>
/**
 * @brief Testing is a function that gets passed aMaterial and and the expected
 * values for its members and checks for equality.
 * A template is used here so this file does not need the class header file
 * @returns a 0 if no error in equality is detected
 */
unsigned int Testing (M aMaterial,  I ID, D Density, C Colour, N Name)
{
    unsigned int Error = 0;
    if (aMaterial.GetID() != ID )
        Error++;
    if (Testing(aMaterial.GetDensity(), Density ))
        Error++;
    if (aMaterial.GetColour().compare(0,aMaterial.GetColour().size(), Colour) !=0 )
        Error++;
    if (aMaterial.GetName().compare(0,aMaterial.GetName().size(), Name) !=0 )
        Error++;
    return (Error==0) ? 0 : 1;
}

//-------------------Vectors Required Code-------------------//
template <class V, class U>
/**
 * @brief Testing is a function that gets passed aVectors and and the expected
 * values for its members and checks for equality.
 * A template is used here so this file does not need the class header file
 * @returns a 0 if no error in equality is detected
 */
unsigned int Testing (V aVectors,  U X, U Y, U Z)
{
    unsigned int Error = 0;
    if ( Testing(aVectors.GetXVector(), X) )
        Error++;
    if ( Testing(aVectors.GetYVector(), Y) )
        Error++;
    if ( Testing(aVectors.GetZVector(), Z) )
        Error++;

    return (Error==0) ? 0 : 1;
}

//-------------------Cell Required Code-------------------//
/** @brief Testing function is usd to test if a Cell and its sub classes
 * have been set up properly
 * @returns a 0 if no error in equality is detected
 */
template <class C, class V, class I, class M>
unsigned int Testing(C aCell, V aVectorArray, I aVecotorOrderArray, M aMaterial )
{
    unsigned int Error = 0;

    if (aCell.Get_Vertices().size() == aVectorArray.size() )
    {
        for (unsigned int i = 0 ; i < aCell.Get_Vertices().size() ; i++ )
        {
            if (Testing(aCell.Get_Vertices()[i], aVectorArray[i]) )
                Error++;
        }

        if (aCell.Get_Vertices_Order().size() == aVecotorOrderArray.size() )
        {
            for (unsigned int j = 0 ; j < aCell.Get_Vertices_Order().size() ; j++ )
            {
                if (Testing(aCell.Get_Vertices_Order()[j], aVecotorOrderArray[j] ))
                    Error++;
            }
        }
        else
           Error++;
    }
    else
       Error++;

    if(Testing(aCell.Get_Material(), aMaterial) )
       Error++;
    return (Error==0) ? 0 : 1;
}

/** @brief Testing function used to test if a empty constructor of a cell
 * has been initialized correctly
 * @returns a 0 if no error in equality is detected
 */
template <class C, class M>
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

/** @brief Testing fuction used to check the Volume Weight nad center of a cell
 * @returns a 0 if no error in equality is detected
 */

template <class C, class D, class V>
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
#endif // TESTING_FILE_FUNCTIONS_H
