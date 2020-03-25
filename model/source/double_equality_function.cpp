//  double_equality_function.cpp
//  Computing Project
//
//  Created by Jedidiah Paterson on 23/23/2020.
//  Copyright @ 2019 Jedidiah Paterson. All rights reserved.
//  This File contains the functions that are need in order
//  to test that two doubles are equal to each other.
//  NOTE Just because (a == b) and (b == c) does not mean
// (a == c)

#include <cmath>
#include "double_equality_function.h"
//#define __DBL_EPSILON__ 2.2204460492503131e-16

double Max( double aValue , double bValue)
{
     return ((aValue) > (bValue) ? (aValue) : (bValue));
}

double Relative_Difference (double aValue, double bValue)
{
    double cValue = fabs(aValue);
    double dValue = fabs(bValue);

    dValue = Max(cValue, dValue);

    return dValue == 0.0 ? 0.0 : fabs(aValue - bValue) / dValue;
}

unsigned int Testing (double aValue, double bValue)
{
return( (Relative_Difference(aValue, bValue) > __DBL_EPSILON__) ? 1 : 0);
}
