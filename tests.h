/*
 * tests.h
 *
 *  Created on: Feb 4, 2019
 *      Author: Aaron Krueger
 */

#ifndef TESTS_H_
#define TESTS_H_

#include <stdbool.h>
#include "production.h"

// Function prototypes:
bool tests(void);
bool testPrintEmployee(void);
bool testMakeEmployee();
bool testRandomChar();
bool testMakeRandomEmployee();
bool testMakeRandomArr();
bool testShallowCopyArr();
bool testFreeArr();
bool testDeepCopyArr();
bool testPrintArr();

#endif /* TESTS_H_ */
