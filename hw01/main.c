#include <stdio.h>
#include <stdlib.h>

int main()
{
	double creditInterest, debitInterest;
	int total = 0, day, amount, previousDay = 0;
	
	printf("Zadejte kreditni urok [%%]:\n");
	if (scanf("%lf", &creditInterest) != 1)
	{
		printf("Nespravny vstup.\n");
		return EXIT_FAILURE;			
	}
	
	printf("Zadejte debetni urok [%%]:\n");
	if (scanf("%lf", &debitInterest) != 1)
	{			
		printf("Nespravny vstup.\n");
		return EXIT_FAILURE;
	}
	
	debitInterest /= 100;
	creditInterest /= 100;
	printf("Zadejte transakce:\n");
	
	while(1)
	{
		if (scanf("%d, %d", &day, &amount) != 2 || previousDay > day || day < 0)
		{
			printf("Nespravny vstup.\n");
			return EXIT_FAILURE;
		}
		
		amount *= 100;

		for (int i = 0; i < (day - previousDay); i++)
		{
			if (total > 0)
				total += (int)((double)total * creditInterest);
			else
				total += (int)((double)total * debitInterest);
		}
		
		if (amount == 0)
			break;
			
		previousDay = day;
		total += amount;
	}
	
	printf("Zustatek: %.2f\n", (double)total / 100);
	return EXIT_SUCCESS;
}
