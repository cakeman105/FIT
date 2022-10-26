#include <stdio.h>
#include <stdlib.h>
#include <math.h>

bool isPrime (int in);
int sumDivisors (int in);

int main()
{
	int startInterval, endInterval, sum = 0, count = 0;
	char sel;
	printf ("Intervaly:\n");
	
	while (true)
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
					
				sum = sumDivisors(i);
				
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

bool isPrime (int in) //determines whether a number is prime, returns bool
{					 //needs improvement
	if (in == 2)
		return true;
	
	if (in % 2 == 0)
		return false;
		
	for (int i = 3; i <= sqrt (in); i += 2) //run to sqrt (in) to reduce time
	{										//some O(n^1/2)
		if (in % i == 0)
			return false;
	}
	
	return true;
}

int sumDivisors (int in) //calculate the sum of all proper divisors of natural number
{
    int res = 0;
    
    if (in == 1)
      return res;
      
    for (int i = 2; i <= sqrt (in); i++) //run to sqrt (in), ditto
    {
        if (in % i == 0)
        {
            if (i == ( in / i))
                res += i;
            else
                res += (i + in / i);
        }
    }
    return (res + 1);
}
