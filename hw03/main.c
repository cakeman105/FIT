#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <assert.h>
#endif /* __PROGTEST__ */

#define length 64

/** 
  * @function convert 
  * @abstract converts long long number to its version in given base, returns to arr
  * @param[in] u long long number
  * @param[in] int base
  * @param[out] pointer to arr
  */

void convert(unsigned long long num, int base, char *arr)
{
	char alph[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
					'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
	int rem;
	int index = 0;
	unsigned long long post = num;
	
	while (true)
	{
		rem = post % base;
		post = (unsigned long long) post / base;
		if (rem > 9)
			arr[index] = alph[rem - 10];
		else
			arr[index] = rem + '0';
		
		if (post == 0)
			break;
		index++;
	}
}

/**
  * @function calculateAmount
  * @abstract calculate the amount of '*' chars in char array
  * @param[in] ptr to char array
  */
  
int calculateAmount(char * arr)
{
	int am = 0;
	for (int i = length - 1; i >= 0; i--)
	{
		if (arr[i] == '*')
			am++;
	}
	
	return am;
}

/** 
  * @function sameArrays
  * @abstract compare two arrays, return 1 if same, 0 if not
  * @param[in] char * arr
  * @param[in] char * arrRev
  */
  
int sameArrays(char * arr, int am)
{
	for (int i = 0, j = (length - 1) - am ; i < length; i++, j--)
	{
		if (arr[i] == '*')
			break;
		if (arr[i] != arr[j])
			return 0;
	}
	
	return 1;
}

/**
  * @function nextPalindrome
  * @abstract find the nearest number to from that is a palindrome using the selected radix
  * @param[in] unsigned long long from
  * @param[in] int radix
  * @param[out] pointer to next
  */
  
int nextPalindrome ( unsigned long long from, 
                     int radix,
                     unsigned long long * next )
{
	if (radix > 36 || radix < 2)
		return 0;
	
	if (from == ULONG_MAX)
		return 0;
	
	char arr[length] = {};
	unsigned long long testNum = from + 1;
	
	while (true)
	{
		for (int i = 0; i < length; i++) //fill char array
			arr[i] = '*';
	
		convert(testNum, radix, arr); //convert long to base radix and save to char array
		if (sameArrays(arr, calculateAmount(arr)) == 1)
		{
			*next = testNum;
			printf("success\n");
			return 1;
		}
			
		testNum++;
	}

}

#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
  unsigned long long next;
  
  printf("%d\n", nextPalindrome(131, 10, &next));
  printf("done\n");
  printf("%llu\n", next);
  
  assert ( nextPalindrome ( 123, 10, &next ) == 1
           && next == 131 );
  assert ( nextPalindrome ( 188, 10, &next ) == 1
           && next == 191 );
  assert ( nextPalindrome ( 1441, 10, &next ) == 1
           && next == 1551 );
  assert ( nextPalindrome ( 95, 15, &next ) == 1
           && next == 96 ); /* 96 = 66 (radix 15) */
  assert ( nextPalindrome ( 45395, 36, &next ) == 1
           && next == 45431 ); /* 45431 = z1z (radix 36) */
  assert ( nextPalindrome ( 1027, 2, &next ) == 1
           && next == 1057 ); /* 1057 = 10000100001 (radix 2) */
  assert ( nextPalindrome ( 1000, 100, &next ) == 0
           && next == 1057 );
  assert ( nextPalindrome ( 18446744073709551614LLu, 2, &next ) == 1
           && next == 18446744073709551615LLu ); /* 18446744073709551615 = 1111111111111111111111111111111111111111111111111111111111111111 (radix 2) */
  assert ( nextPalindrome ( 18446744073709551615LLu, 2, &next ) == 0
           && next == 18446744073709551615LLu );

  return 0;
}
#endif /* __PROGTEST__ */
