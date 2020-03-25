//  Testing_File_Functions.cpp
//  Computing Project
//
//  Created by Jedidiah Paterson on 23/03/2020.
//  Copyright @ 2020 Jedidiah Paterson. All rights reserved.
//  This File contains functions that are only used in the
//  testing of the Model/Cell/Xatrix/Vectors/Material code.

#include <string>
#include <iostream>
#include <typeinfo>
#include "double_equality_function.h"

//-------------------Common Code-------------------//
template <class T>
unsigned int Testing (T aItem,  T bItem)
{
  //if (typeid(aItem).name() == d)
      std::cout << "I was here" << std::endl;

  return (aItem==bItem) ? 0 : 1;
}

//-------------------Material Required Code-------------------//

template <class T, class I, class D, class C, class N>
unsigned int Testing (T aMaterial,  I ID, D Density, C Colour, N Name)
{
    unsigned int Error = 0;
    if (aMaterial.GetID() != ID )
        Error++;
    if (aMaterial.GetDensity() != Density )
        Error++;
    if (aMaterial.GetColour().compare(0,aMaterial.GetColour().size(), Colour) !=0 )
        Error++;
    if (aMaterial.GetName().compare(0,aMaterial.GetName().size(), Name) !=0 )
        Error++;
    return (Error==0) ? 0 : 1;
}

//-------------------Vectors Required Code-------------------//
template <class T, class U>
unsigned int Testing (T aVectors,  U X, U Y, U Z)
{
    unsigned int Error = 0;
    if ( Relative_Difference(aVectors.GetXVector(), X) > __DBL_EPSILON__)
    {Error++;
        std::cout << "X is wrong" << std::endl;}
    if ( Relative_Difference(aVectors.GetYVector(), Y) > __DBL_EPSILON__)
    {Error++;
        std::cout << "Y is wrong: " << aVectors.GetYVector() - Y << std::endl;}
    if ( Relative_Difference(aVectors.GetZVector(), Z) > __DBL_EPSILON__)
    {Error++;
        std::cout << "Z is wrong" << std::endl;}

    return (Error==0) ? 0 : 1;
}
