#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NAME_LENGTH 199
#define EQUATION2 sqrt( pow(arr[j + 1].coordX - arr[i].coordX, 2) + pow(arr[j + 1].coordY - arr[i].coordY, 2))

struct Plane
{
	char name[NAME_LENGTH];
	double coordX;
	double coordY;
	double distance;
};

/**
  * Compares two double values
  * @param[in] double a
  * @param[in] double b
  * @return true or false
  */
  
bool isEqual(double a, double b)
{
	double epsilon = (double) (0.001f * (abs(a) + abs(b)));
	
	return fabsl(a - b) <= epsilon ? true : false;
}

/**
  * takes vals from stdin and reallocs the array based on the amount of data
  * @param[in] Plane ** arr
  */

int input(Plane ** arr) //fix return on fail
{
	int count = 0;
	Plane * tmp = *arr;
	while (true)
	{
		if (scanf("%lf,%lf: %199s", &tmp[count].coordX, &tmp[count].coordY, tmp[count].name) != 3)
		{
			if (feof(stdin))
				break;
					
			else
				return -1;
		}
		
		count++;
		tmp = (Plane *) realloc(*arr, (count + 1) * sizeof(Plane));
		*arr = tmp;
	}
	
	tmp = NULL; //honestly what, fsanitize reports no leaks
	return count;
}

/**
  * calculates the distance between two planes
  * @param[in] Plane * arr
  * @param[in] int count
  */
    
double findSmallest(Plane * arr, int count, int * pairs)
{
	double min = 0;
	double dist = 0;
	int tmp = 0;
	for (int i = 0; i < count - 1; i++)
		for (int j = i; j < count - 1; j++)
		{
			dist = EQUATION2;
			if (j == 0)
				min = dist;
			else if (dist < min)
				min = dist;
		}
	
	for (int i = 0; i < count - 1; i++)
		for (int j = i; j < count - 1; j++)
		{
			dist = EQUATION2;
			if (isEqual(dist, min))
				tmp++;
		}
		
	*pairs = tmp;
	return min;
}

void findPairs(Plane * arr, int count, double min)
{
	double dist = 0;
	for (int i = 0; i < count - 1; i++)
		for (int j = i; j < count - 1; j++)
		{
			dist = EQUATION2;
			if (isEqual(dist, min))
				printf("%s - %s\n", arr[i].name, arr[j + 1].name);
			
		}
}

int main()
{
	printf("Pozice letadel:\n");
	Plane * planes = (Plane *) malloc(1 * sizeof(Plane));
	int count = input(&planes);
	
	if (count == -1 || count == 1)
	{
		printf("Nespravny vstup.\n");
		return 0;
	}
	
	int pairs = 0;
	double min = findSmallest(planes, count, &pairs);
	printf("Vzdalenost nejblizsich letadel: %lf\n", min);
	printf("Nalezenych dvojic: %d\n", pairs);
	findPairs(planes, count, min);
	free(planes);
	return EXIT_SUCCESS;
}
