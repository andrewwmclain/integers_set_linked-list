/*
 * Title:   Lab 7 - test.h
 *
 * Purpose: Declares a single function use for the unit tests
 *
 * Class:   CSC 2430 Winter 2020
 * Author:  Carlos Arias
 */

#ifndef LAB7_SOLUTION_TEST_H
#define LAB7_SOLUTION_TEST_H

#include <iostream>
using std::ostream;
using std::cout;

// Tests the condition, if it is true, the test is passed and the meesage 
// is output to the output stream (by default cout), if the condition
// is false, then it will output the message with the workd "Failed"
bool Test(bool condition, const char* message, ostream& output= cout);

#endif //LAB7_SOLUTION_TEST_H
