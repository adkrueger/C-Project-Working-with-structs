/*
 * tests.c
 *
 *  Created on: Feb 4, 2019
 *      Author: Aaron Krueger
 */


#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "tests.h"
#include "production.h"
#include "mystruct.h"

bool tests(void)
{
	bool ok = false;

	bool ok1 = testPrintEmployee();
	if (ok1) {
		puts("printEmployee() passed.");
	}

	bool ok2 = testMakeEmployee();
	if (ok2) {
		puts("makeEmployee() passed.");
	}

	bool ok3 = testRandomChar();
	if (ok3) {
		puts("randomChar() passed.");
	}

	bool ok4 = testMakeRandomEmployee();
	if (ok4) {
		puts("makeRandomEmployee() passed.");
	}

	bool ok5 = testMakeRandomArr();
	if(ok5) {
		puts("makeRandomEmployeeArr() passed.");
	}

	bool ok6 = testShallowCopyArr();
	if(ok6) {
		puts("shallowCopyArr() passed.");
	}


	bool ok7 = testFreeArr();
	if(ok7) {
		puts("freeArr() passed.");
	}

	bool ok8 = testDeepCopyArr();
	if(ok8) {
		puts("deepCopyArr() passed.");
	}

	bool ok9 = testPrintArr();
	if(ok9) {
		puts("printArr() passed.\n");
	}

	ok = ok1 && ok2 && ok3 && ok4 && ok5 && ok6 && ok7 && ok8 && ok9; // Did all tests pass?
	return ok;
}

/**
 * Test the printEmployee() function by creating a known struct and printing it.
 * @return true. The only way to tell if it succeeds is to look at the output.
 */

bool testPrintEmployee() {
	struct Employee e; // Variable to hold employee
	e.birth_year = 1952; // Put data into numeric fields
	e.start_year = 1999;

	printf("\nTesting printEmployee...");
	// Copy into string field. Be sure not to overflow it.
	strncpy(e.name, "Mike Ciaraldi", MAX_NAME);
	e.name[MAX_NAME] = '\0'; // Be sure string is terminated.

	printEmployee(&e);

	return true;
}


/** Test the make Employee() function by making an employee with known data and printing it.
 * @return true. The only way to tell if it succeeds is to look at the output.
 */
bool testMakeEmployee() {
	struct Employee *e;

	puts("\nTesting makeEmployee()...");
	e = makeEmployee(1952, 1999, "Mike Ciaraldi"); // create an employee "Mike Ciaraldi", born in 1952, and started in 199
	printEmployee(e);

	return true;
}

/** Test the output of randChar()
 * @return true, check output for whether or not "bad" characters are included
 */
bool testRandomChar() {
	puts("\nCharacters output by randomChar(): ");
	for(int i = 0; i < 10; i++) {
		printf("%c", randomChar()); // outputs a string of 10 random characters
	}
	puts("");

	return true;
}

/**
 * Test the ability of makeRandomEmployee()
 * @return true, check output for whether or not the employee was created properly
 */
bool testMakeRandomEmployee() {
	puts("\nTesting makeRandomEmployee...");
	puts("**NOTE: The employee name is made up of all printable characters. This includes symbols, punctuation, and numbers!**");
	struct Employee *randomEmployee = makeRandomEmployee();
	printEmployee(randomEmployee);

	return true;
}

/**
 * Tests the ability of makeRandomArr() to actually make a random array of employees
 * @return true, check output for whether or not the employee array was created properly
 */
bool testMakeRandomArr() {
	struct Employee** randEmpArr = makeRandomArr(2);

	puts("\nTesting makeRandomArr...");
	for(int i = 0; i < 2; i++) {
		printEmployee(*randEmpArr); // prints out each employee in the array
		randEmpArr++;
	}

	return true;
}

/**
 * Tests the ability of printArr()
 * @return true, check output for what was printed
 */
bool testPrintArr() {
	puts("\nTesting printArr...");
	struct Employee** randEmpArr = makeRandomArr(2); // a random array of employees
	printArr(randEmpArr, 2);
	return true;
}

/**
 * Tests the ability of shallowCopyArr to copy into a new array
 * @return true if the array is copied properly
 */
bool testShallowCopyArr() {
	puts("\nTesting shallowCopyArr...");
	bool results = true;
	struct Employee** randEmpArr = makeRandomArr(3); // the array
	struct Employee** copiedEmpArr = shallowCopyArr(randEmpArr, 3); // the shallow copied array

	for(int i = 0; i < 3; i++) {
		if(*randEmpArr != *copiedEmpArr) { // if any value doesn't equal its copied counterpart
			results = false;
		}

		randEmpArr++;
		copiedEmpArr++;
	}
	//decrement each array so we can demonstrate properly
	randEmpArr -= 3;
	copiedEmpArr -= 3;

	puts("**PRINTING ORIGINAL ARRAY**");
	printArr(randEmpArr, 3);
	puts("**PRINTING SHALLOW COPIED ARRAY**");
	printArr(copiedEmpArr, 3);

	//print values to demonstrate function's capability
	printf("Pointers to the data should be the exact same:\n");
	printf("Addresses of start years of each employee: \n %p\n %p\n", &(*randEmpArr)->start_year, &(*copiedEmpArr)->start_year);
	printf("Addresses of birth years of each employee: \n %p\n %p\n", &(*randEmpArr)->birth_year, &(*copiedEmpArr)->birth_year);
	printf("Addresses of names of each employee: \n %p\n %p\n", &(*randEmpArr)->name, &(*copiedEmpArr)->name);

	return results;
}

/**
 * Tests whether freeArr can run without error
 * @return true, but only if freeArr runs without errors
 */
bool testFreeArr() {
	puts("\nTesting freeArr...");
	struct Employee** randEmpArr = makeRandomArr(2);
	freeArr(randEmpArr, 2); // if this runs then freeArr works properly
	return true;
}

/**
 * Tests the ability of deepCopyArr to copy into a new array
 * @return true if the array is copied properly
 */
bool testDeepCopyArr() {
	puts("\nTesting deepCopyArr...");
	bool results = true;
	struct Employee** randEmpArr = makeRandomArr(3); //the original array
	struct Employee** copiedEmpArr = deepCopyArr(randEmpArr, 3); // the deep copied array

	for(int i = 0; i < 3; i++) {
		if((*randEmpArr)->birth_year != (*copiedEmpArr)->birth_year) { // if birth years aren't the same, fail
			results = false;
		}
		if((*randEmpArr)->start_year != (*copiedEmpArr)->start_year) { // if start years aren't the same, fail
			results = false;
		}
		if(strcmp((*copiedEmpArr)->name,(*randEmpArr)->name) != 0) { // if names aren't the same, fail
			results = false;
		}
		if(&(*copiedEmpArr)->name == &(*randEmpArr)->name ||
				&(*copiedEmpArr)->start_year == &(*randEmpArr)->start_year ||
				&(*copiedEmpArr)->birth_year == &(*randEmpArr)->birth_year) { // if any address of the variables is the same, fail
			results = false;
		}

		randEmpArr++;
		copiedEmpArr++;
	}
	//decrement each array so we can demonstrate properly
	randEmpArr -= 3;
	copiedEmpArr -= 3;

	puts("**PRINTING ORIGINAL ARRAY**");
	printArr(randEmpArr, 3);
	puts("**PRINTING DEEP COPIED ARRAY**");
	printArr(copiedEmpArr, 3);

	//print values to demonstrate function's capability
	printf("Pointers to the data should be different:\n");
	printf("Addresses of start years of each employee: \n %p\n %p\n", &(*randEmpArr)->start_year, &(*copiedEmpArr)->start_year);
	printf("Addresses of birth years of each employee: \n %p\n %p\n", &(*randEmpArr)->birth_year, &(*copiedEmpArr)->birth_year);
	printf("Addresses of names of each employee: \n %p\n %p\n", &(*randEmpArr)->name, &(*copiedEmpArr)->name);

	return results;
}

