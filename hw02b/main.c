#include <stdio.h>
#include <stdlib.h>

char middlePoint(double arr[]);

int main()
{
	double coords[6];
	printf("Bod A:\n");
	if ( scanf (" %lf %lf", &coords[0], &coords[1]) != 2)
	{
		printf("Nespravny vstup.\n");
		return EXIT_FAILURE;
	}
	
	printf("Bod B:\n");
	if ( scanf (" %lf %lf", &coords[2], &coords[3]) != 2)
	{
		printf("Nespravny vstup.\n");
		return EXIT_FAILURE;
	}
	
	printf("Bod C:\n");
	if ( scanf (" %lf %lf", &coords[4], &coords[5]) != 2)
	{
		printf("Nespravny vstup.\n");
		return EXIT_FAILURE;
	}
	
	if ((coords[0] == coords[2] && coords[1] == coords[3]) || (coords[2] == coords[4] && coords[3] == coords[5]) || (coords[0] == coords[4] && coords[1] == coords[5]))
	{
		printf("Nektere body splyvaji.\n");
		return EXIT_SUCCESS;
	}
	
	if ((coords[0] == coords [2] && coords[2] == coords[4]) || (coords[1] == coords[3] && coords[3] == coords[5]))
	{
		printf("Body lezi na jedne primce.\n");
		printf("Prostredni je bod %c.\n", middlePoint(coords));
		return EXIT_SUCCESS;
	}
	
	for (int i = 0; i < 6; i++) //check whether one of the numbers is decimal
	{							//since cramer's rule doesn't work with fractions
		if (coords[i] != (int) coords[i])
		{
			coords[0] *= 10;
			coords[1] *= 10;
			coords[2] *= 10;
			coords[3] *= 10;
			coords[4] *= 10;
			coords[5] *= 10;
			break;
		}
	}

	double det = (coords[0] * 1) - (1 * coords[2]);
	double det1 = (coords[1] * 1) - (1 * coords[3]);
	double det2 = (1 * coords[3]) - (coords[2] * coords[1]);
	
	double a = det1 / det;
	double b = det2 / det;
	
	if (coords[1] == (a * coords[0]) + b && coords[3] == (a * coords[2]) + b && coords[5] == ( a * coords[4]) + b)
	{
		printf("Body lezi na jedne primce.\n");
		printf("Prostredni je bod %c.\n", middlePoint(coords));
	}
	else
		printf("Body nelezi na jedne primce.\n");
		
	return EXIT_SUCCESS;
}

char middlePoint(double arr[])
{
	double small = 100;
	int sel = 0;
	if (arr[0] == arr[2] && arr[2] == arr[4])
	{
		double avrg = (arr[1] + arr[3] + arr[5]) / 3;
		for (int i = 1; i < 6; i += 2)
		{
			if (abs (avrg - arr[i]) < small)
			{
				sel = i;
				small = abs (avrg - arr[i]);
			}
		}
	}
	
	else
	{
		double avrg = (arr[0] + arr[2] + arr[4]) / 3;
		for (int i = 0; i < 6; i += 2)
		{
			if (abs (avrg - arr[i]) < small)
			{
				sel = i;
				small = abs (avrg - arr[i]);
			}
		}
	}
	
	switch (sel)
	{
		case 0:
		return 'A';
		break;
		case 2:
		return 'B';
		break;
		case 4:
		return 'C';
		break;
		case 1:
		return 'A';
		break;
		case 3:
		return 'B';
		break;
		case 5:
		return 'C';
		break;
	}
	
	return 'x';
}
