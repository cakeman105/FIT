#include <stdio.h>
#include <stdlib.h>
//i am checking for a lot of stuff

bool isPrime(int in); //this is hell

int main()
{
	int startInterval, endInterval, sum = 0, count = 0;
	char sel;
	printf ("Intervaly:\n");
	
	while (1)
	{
		if (scanf (" %c %d %d", &sel, &startInterval, &endInterval) == 3 && startInterval <= endInterval && startInterval >= 1)
		{		
			if (sel != '?' && sel != '#')
			{
				printf("Nespravny vstup.\n");
				return EXIT_FAILURE;
			}
		
			for (int i = startInterval; i <= endInterval; i++)
			{
				if (isPrime (i) == true) //exclude primes from testing
					continue;
					
				for (int j = 1; j < i; j++) //sum proper divisors
				{
					if (i % j == 0)
					{
						sum += j;
					}
				}
				
				if (isPrime (sum) == true) //test whether sum is prime
				{
					if (sel == '?')
						printf("%d\n", i);
					count++;
				}
				
				sum = 0;
			}
			
			printf("Celkem: %d\n", count);
			count = 0;
		}
		
		else if (getchar() == EOF) //check for eof
			return EXIT_SUCCESS;
			
		else
		{
			printf("Nespravny vstup.\n");
			return EXIT_FAILURE; 	
		}
	}
}

bool isPrime(int in) //determines whether a number is prime, returns bool
{
	for (int i = 2; i < in; i++)
	{
		if (in % i == 0)
			return false;
	}
	
	return true;
}
