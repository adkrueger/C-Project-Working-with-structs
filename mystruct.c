/**
 * mystruct.c
 * @author Aaron Krueger
 */


#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "mystruct.h"

/**
 * Allocates an Employee struct and fills in its fields
 * @param birth Year the employee was born.
 * @param start Year the employee started with the company.
 * @param name String containing employee's name
 * @return A pointer to an Employee struct, newly allocated from the heap
 */
struct Employee* makeEmployee(int birth, int start, const char *name) {
	struct Employee* newEmp = (struct Employee*) malloc(sizeof(newEmp)); // the employee we are making
	newEmp->birth_year = birth;
	newEmp->start_year = start;
	strcpy(newEmp->name, name);

	return newEmp;
}

/**
 * Generates a random character, restricted to ASCII characters 32-126
 * (all printable characters)
 * @return A random printable character
 */
char randomChar(void) {
	return (char)(rand() % 94) + 32; // chooses a random integer between 32 and 126 and casts it to a char
}

/**
 * Generates a random employee struct, consisting of a string of random characters,
 * a random birth year (1903-2019), and a random start year (1921-2019).
 * The name consists of all printable characters (ASCII characters 32-126), and is
 * 99 characters long (including the null terminator).
 * @return A struct pointer to the freshly allocated random employee
 */
struct Employee* makeRandomEmployee(void) {
	struct Employee* randEmp = (struct Employee*) malloc(sizeof(struct Employee*)); // the random employee

	randEmp->birth_year = (int)(rand() % 116) + OLDEST_YEAR; // creating a random birth year
	randEmp->start_year = (int)(rand() % 98) + BASE_START; // creating a random start year
	char* randName = (char*) calloc(MAX_NAME, sizeof(char));
	char* namePtr = randName;   // a pointer to the first element of randName
	for(int i = 0; i <= MAX_NAME; i++) {
		*namePtr = randomChar();
		namePtr++;
	}
	*namePtr = '\0';
	strcpy(randEmp->name, randName); // copy the random name into the employee's name

	return randEmp;
}

/**
 * Prints the birth year, starting year, and the name of the employee
 * @param e The given employee
 */
void printEmployee(struct Employee *e) {
	printf("Birth year = %d\n", e->birth_year);
	printf("Starting year = %d\n", e->start_year);
	printf("Name = %s\n", e->name);
}

/**
 * Allocates space for an array of size count
 * @param count The size of the array
 * @return The newly allocated array
 */
struct Employee** makeRandomArr(int count) {
	struct Employee** employeeArr = (struct Employee**) calloc(count, sizeof(struct Employee*)); // allocating space for the new array
	struct Employee** arrPtr = employeeArr; // a pointer to the first element of the array
	for(int i = 0; i < count; i++) {
		*arrPtr = makeRandomEmployee(); // don't need to malloc again, already called in makeRandomEmployee
		arrPtr++;
	}

	return employeeArr;
}

/**
 * Prints out each pointer of the given array, which contains count elements
 * @param a The array of employees that will be printed
 * @param count The number of employees in said array
 */
void printArr(struct Employee** a, int count) {
	for(int i = 0; i < count; i++) { // loop through the array, printing each employee
		printf("Employee #%d of the given array:\n", i + 1);
		printEmployee(*a);
		a++;
	}
}

/**
 * Duplicates an array of pointers by copying each element's value into the
 * new array (known as a shallow copy)
 * @param arr The array to be copied
 * @param size The number of Employees in the array
 * @return The duplicated array
 */
struct Employee** shallowCopyArr(struct Employee** arr, int size) {
	struct Employee** newArr = (struct Employee**) calloc(size, sizeof(struct Employee*));
	struct Employee** arrPtr = newArr;
	for(int i = 0; i < size; i++) {
		*arrPtr = (struct Employee*) malloc(sizeof(struct Employee));
		*arrPtr = *arr;
		arrPtr++;
		arr++;
	}

	return newArr;
}

/**
 * Frees an array of pointers
 * @param arr The array to be freed
 * @param size The size of the array
 */
void freeArr(struct Employee** arr, int size) {
	for(int i = 0; i < size; i++) {
		free(*arr);
		arr++;
	}
}

/**
 * Copies an array of pointers by copying each pointer's address into a new array
 * (known as a deep copy)
 * @param arr The array to be copied
 * @param size The number of Employees in the array
 * @return The deep copied array
 */
struct Employee** deepCopyArr(struct Employee** arr, int size) {
	struct Employee** newArr = (struct Employee**) calloc(size, sizeof(struct Employee*)); // the array to hold the deep copied array
	struct Employee** arrPtr = newArr; // a pointer that will move through the contents of newArr

	for(int i = 0; i < size; i++) {
		*arrPtr = (struct Employee*) malloc(sizeof(struct Employee));
		(*arrPtr)->birth_year = (*arr)->birth_year;
		(*arrPtr)->start_year = (*arr)->start_year;
		strcpy((*arrPtr)->name, (*arr)->name);

		arrPtr++;
		arr++;
	}

	return newArr;
}
