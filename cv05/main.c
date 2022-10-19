#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
	double x, y, z;
	char op;
	
	printf("Zadejte rovnici:\n");
	if (scanf("%lf %c %lf = %lf", &x, &op, &y, &z) == 4)
	{
		switch(op)
		{
			case '+':
			if (x + y == z)
				printf("Rovnice je spravne.\n");
			else
				printf("%lf != %lf\n", x + y, z);
			break;
			case '-':
			if (x - y == z)
				printf("Rovnice je spravne.\n");
			else
				printf("%lf != %lf\n", x - y, z);
			break;
			case '*':
			if (x * y == z)
				printf("Rovnice je spravne.\n");
			else
				printf("%lf != %lf\n", x * y, z);
			break;
			case '/':
			if ((x - (y*z)) == fmod(x, y) && y != 0)
				printf("Rovnice je spravne.\n");
			else if (y == 0)
			{
				printf("Nespravny vstup.\n");
				return EXIT_FAILURE;
			}	
			else
				printf("%lf != %lf\n", x / y, z);
			break;
			default:
			printf("Nespravny vstup.\n");
			break;
		}
		
		return EXIT_SUCCESS;
	}	
	
	else
	{
		printf("Nespravny vstup.\n");
		return EXIT_FAILURE;
	}
}
