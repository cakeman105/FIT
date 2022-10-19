#include <stdio.h>
#include <stdlib.h>

void OddDisplay(int x, int y); //x for amount of squares on board, y for square size
void EvenDisplay(int x, int y);
void HeaderFooterDisplay(int x);
int main()
{
	int selAm, selSqrSize, whichOne = -1;
	
	printf("Zadejte pocet poli:\n");
	if (scanf("%i", &selAm) != 1 || selAm <= 0)
	{
		printf("Nespravny vstup.\n");
		return EXIT_FAILURE;
	}
	
	printf("Zadejte velikost pole:\n");
	if (scanf("%i", &selSqrSize) != 1 || selSqrSize <= 0)
	{
		printf("Nespravny vstup.\n");
		return EXIT_FAILURE;
	}
	

	HeaderFooterDisplay(selAm * selSqrSize);
		
	for (int j = 0; j < selAm; j++)
	{
		if (whichOne < 0)
			OddDisplay(selAm, selSqrSize);
		else
			EvenDisplay(selAm, selSqrSize);
				
		whichOne = -whichOne;
	}
		
	HeaderFooterDisplay(selAm * selSqrSize);
	return EXIT_SUCCESS;
}

void OddDisplay(int x, int y) //for displaying odd rows
{
	int whichOne = -1;
	
	for (int i = 0; i < y; i++)
	{
		printf("|");
		for (int j = 0; j < x * y; j++)
		{
			if (j % y == 0)
				whichOne = -whichOne;
				
			if (whichOne == -1)
				printf("X");
			else
				printf(" ");
		}
		whichOne = -1;
		
		printf("|\n");
	}
}

void EvenDisplay(int x, int y) //for displaying even rows
{
		int whichOne = -1;
	
	for (int i = 0; i < y; i++)
	{
		printf("|");
		for (int j = 0; j < x * y; j++)
		{
			if (j % y == 0)
				whichOne = -whichOne;
				
			if (whichOne == -1)
				printf(" ");
			else
				printf("X");
		}
		
		whichOne = -1;
		
		printf("|\n");
	}
}

void HeaderFooterDisplay(int x) // displays top and bottom
{
	printf("+");
		for (int i = 0; i < x; i++)
			printf("-");
		printf("+\n");
}
