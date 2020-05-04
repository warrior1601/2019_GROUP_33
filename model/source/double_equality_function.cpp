//  double_equality_function.cpp
//  Computing Project
//
//  Created by Jedidiah Paterson on 23/23/2020.
//  Copyright @ 2019 Jedidiah Paterson. All rights reserved.
//  This File contains the functions that are need in order
//  to test that two doubles are equal to each other.
//  NOTE Just because (a == b) and (b == c) does not mean
//  (a == c)

#include <cmath>
#include "double_equality_function.h"
double my_DBL_EPSILON = Calc_DBL_EPSILON_For_Machine();
#include <iostream>

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
return( (Relative_Difference(aValue, bValue) > my_DBL_EPSILON) ? 1 : 0);
}

double Calc_DBL_EPSILON_For_Machine()
{
    double prev_epsilon;
    double epsilon = 1.0;

        while ((1.0+epsilon) != 1)
        {
            prev_epsilon = epsilon;
            epsilon /= 2.0;
        }
        // The user can set how accurate they want the progam here.
        // As the number appoaches 0.0 the program becomes more accurate
        // Although, it may become more accurate there will be a point when the accuracy causes failure
        if(prev_epsilon < 1e-13)  // This is a typical DBL_EPSILON value: 2.2204460492503131e-16
           {
            // This is the largest recommended value for DBL_EPSILON
            return (1e-13);
           }

        else
        {
            std::cout << "The Machine’s double precision is not accurate enough to run this program." << std::endl;
            exit(1);
        }
}
