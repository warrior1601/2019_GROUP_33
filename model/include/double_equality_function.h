//  double_equality_function.h
//  Computing Project
//  Created by Jedidiah Paterson on 23/03/2020.

#ifndef DOUBLE_EQUALITY_FUNCTION_H
#define DOUBLE_EQUALITY_FUNCTION_H

/**
 * @file These functions help determine if a double is equal to another
 * double value by using a relative difference so that it can be
 * compared to the machines "double epsilon" value.
 * warning to the console Just because (a == b) and (b == c) does not mean (a == c)
 *  @author Jedidiah Paterson
 */

/**
 * @brief Determines the Max value between to doubles
 * @returns The larger value
 */
double Max( double aValue , double bValue);

/**
 * @brief Determins the relative difference between the numbers
 * @returns The relative difference between the two values
 */
double Relative_Difference (double aValue, double bValue);

/**
 * @brief Since doubles need to be tested in a certain way they
 * are rerouted to this function
 * @returns a error code if the two values differ by more than the
 * machines tolerance for determining a differnt double value
 */
unsigned int Testing (double aValue, double bValue);

/**
 * @brief Calculates the machines _DBL_EPSILON_ value
 * @returns The minimum value that seperates two doubles on a given machine
 */
double Calc_DBL_EPSILON_For_Machine(void);

#endif // DOUBLE_EQUALITY_FUNCTION_H
