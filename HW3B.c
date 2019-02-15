#include <stdio.h>
#include <stdlib.h>
#include "tests.h"
#include "production.h"
#include "mystruct.h"

int main(int argc, char *argv[]) {
	puts("!!!Hello class, we are working HW3B!!!"); /* prints !!!Hello World!!! */
	if(tests())
	{
		puts("Tests succeeded.");
		if(production(argc, argv))
		{
			puts("Production successful.");
		}
		else
		{
			puts("Tests succeeded, but production didn't");
		}
	}
	else
	{
		puts("Tests did not succeed.");
	}

	return EXIT_SUCCESS;
}
