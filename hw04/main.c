#include <stdio.h>
#include <stdlib.h>

#define ARRAY_LENGTH 2000

/**
  * @function inputToArray
  * @abstract takes values from stdin and saves them to array
  * @param[in] pointer to int array
  * @return number of values stored in arr
  */

int inputToArray(int * arr)
{
	int inx = 0;
	printf("Posloupnost:\n");
	
	while (scanf("%d", &arr[inx]) == 1 && inx < ARRAY_LENGTH)
	{
		inx++;	
	}
	
	if (!feof(stdin) || inx == 0)
	{
		printf("Nespravny vstup.\n");
		return EXIT_FAILURE;
	}
	
	if (inx == 1)
	{
		printf("Pocet dvojic: 0\n");
		return EXIT_FAILURE;
	}
	return inx;
}

/**
  * @function calculateCombination
  * @abstract calculates the combination number of n choose k
  * @param[in] n
  * @param[in] k
  * @return final combination number value
  */
int calculateCombination(int n, int k)
{
	int num = 1;
	
	if (k > (n / 2))
		k = n -k;
	
	for (int i = 0; i < k; i++)
	{
		num *= n - i;
		num /= i + 1;
	}
	
	return num;
		
}

/**
  * @function findCombinations
  * @abstract finds all combinations of a sequence
  * @param[in] amount of values in array
  * @param[in] pointer to array
  * @return 1 on successful exit
  */
  
int findCombinations(int am, int * arr, int * arrRes)
{
	bool maxedOut = true;
	int inx = 0;
	for (int i = 0; i < am - 1; i++) //why did this take me so long to make
	{
		for (int j = i; j < am - 1; j++)
		{
			if (maxedOut)
				arrRes[inx] = arr[j] + arr[j + 1];
			else
				arrRes[inx] = arrRes[inx - 1] + arr[j + 1];
			
			inx++;
			maxedOut = false;
		}
		
		maxedOut = true;
	}
	
	return 1;
}

/**
  * @function findPairs
  * @abstract finds the total amount of pairs in a sorted array
  * @param[in] int * arr
  * @param[in] int combAm
  * @return total amount of pairs
  */
int findPairs(int * arr, int combAm)
{
	int total = 0;
	for (int i = 0; i < combAm; i++)
	{
		for (int j = i + 1; j < combAm; j++)
		{
			if (arr[i] == arr[j])
				total++;
			if (arr[i] != arr[j])
				break;
		}
	}
	
	return total;
}

/**
  * @function comparison
  * @abstract a comparison function for qsort
  * @param[in] const void * a
  * @param[in] const void * b
  */
int comparison (const void * a, const void * b)
{
	return (* (int *) a - * (int *) b);
}

int main()
{
	int arr[ARRAY_LENGTH] = {}; //initalize and zero out	
	int am = inputToArray(arr);
	
	if (am == 2)
	{
		printf("Pocet dvojic: 0\n");
		return EXIT_SUCCESS;
	}
	if (am == EXIT_FAILURE)
		return EXIT_FAILURE;
	
	int combAm = calculateCombination(am , 2);
	int * arrRes = (int *)calloc(combAm, sizeof(int));
	
	findCombinations(am, arr, arrRes);
	qsort(arrRes, combAm, sizeof(int), comparison); 
	printf("Pocet dvojic: %d\n", findPairs(arrRes, combAm));
	
	free(arrRes);
	return EXIT_SUCCESS;
}
