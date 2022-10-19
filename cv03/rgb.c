#include <stdio.h>
#include <stdlib.h>

int main( void )
{
	int r, g, b;
	char bracket;
	
	printf("Zadejte barvu v RGB formatu:\n");
	
	int z = scanf(" rgb ( %i , %i , %i%c ", &r, &g, &b, &bracket);
	if (z == 4)
	{
		if (r < 256 && g < 256 && b < 256 && r > -1 && g > -1 && b > -1)
		{
			printf("#%.2X%.2X%.2X\n", r, g, b);
		}
		
		else
		{
			printf("Nespravny vstup.\n");
			return EXIT_FAILURE;
		}
	}
	
	else
	{
		printf("Nespravny vstup.\n");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
