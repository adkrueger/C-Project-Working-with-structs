/** mystruct.h
 * @author Aaron Krueger
 * Sample structs
*/

// Struct definition:

// Maximum number of characters in an employee name
#define MAX_NAME (99)
#define OLDEST_YEAR (1903)
#define BASE_START (1921)

struct Employee {
	int birth_year; // Year the employee was born
	int start_year; // When employee started with the company.
	char name[MAX_NAME + 1];
};

// Function prototype(s):
struct Employee *makeEmployee(int birth, int start, const char* name);
void printEmployee(struct Employee *e);
char randomChar(void);
struct Employee* makeRandomEmployee(void);
struct Employee** makeRandomArr(int count);
void printArr(struct Employee** a, int count);
struct Employee** shallowCopyArr(struct Employee** arr, int size);
void freeArr(struct Employee** a, int size);
struct Employee** deepCopyArr(struct Employee** arr, int size);
