#ifndef __PROGTEST__
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#endif /* __PROGTEST__ */

/**
  * struct for storing substring index in replace[][2] and its location in initial text
  * int word, int index
  */
  
struct Instances
{
	int word;
	int index;
};

/**
  * check whether a word is a substring of another word in replace[][0]
  * @param[in] const char * (*replace)[2]
  * @return 0 on success, -1 on failure
  */
  
int checkList(const char * (*replace)[2])
{
	int i = 0, j = 0, sub = 0;
	
	const char * ptr;
	while (replace[i][0] != NULL)
	{
		while (replace[j][0] != NULL)
		{
			if ((ptr = strstr(replace[j][0],replace[i][0])) && ptr == replace[j][0])
				sub++;
			if (sub >= 2)
				return -1;
			j++;
		}
		sub = 0;
		j = 0;
		i++;
	}
	return 0;
}

/**
  * a comparison function for comparing Instances->index
  * @param[in] const void * a
  * @param[in] const void * b
  * @return (instA->index > instB->index) - (instA->index < instB->index)
  */
  
int compare(const void * a, const void * b)
{
	const Instances * instA = (Instances *) a;
	const Instances * instB = (Instances *) b;
	
	return (instA->index > instB->index) - (instA->index < instB->index);
}

/**
  * finds all instances of words in the given text and adds their indexes to arr
  * @param[in] ptr to Instances * arr
  * @param[in] char * text
  * @param[in] const char * (*replace)[2]
  * @return amount of elements saved in arr
  */
  
int findInstances(Instances ** arr, char * text, const char * (*replace)[2])
{
	int i = 0;
	int amount = 0;
	Instances * tmp = *arr;
	while (replace[i][0] != NULL)
	{
		char * ptr = strstr(text, replace[i][0]);
		while (ptr)
		{
			if (text[ptr - text])
			{
				tmp[amount].word = i;
				tmp[amount].index = ptr - text; //pointer arithmetic
				tmp = (Instances *) realloc(*arr, (amount + 2) * sizeof(Instances));
				amount++;
				*arr = tmp;
			}
			ptr = strstr(ptr + 1, replace[i][0]);
		}
		
		i++;
	}
	
	tmp = NULL;
	return amount;
}

/**
  * calculates size of string post replacement
  * @param[in] char * text
  * @param[in] Instances ** arr
  * @param[in] const char * (*replace)[2]
  */
  
int calculatePost(char * text, Instances ** arr, const char * (*replace)[2], int size)
{
	int newLength = strlen(text) + 1;
	for (int i = 0; i < size; i++)
	{
		newLength += (strlen(replace[(*arr)[i].word][1]) - strlen(replace[(*arr)[i].word][0]));
	}
	
	return newLength;
}  

/**
  * replaces all instances of words mentioned in Instances * arr
  * @param[in] char * text
  * @param[out] char ** textCpyOut
  * @param[in] const char * (*replace)[2]
  * @param[in] Instances ** arr
  * @param[in] int size
  * @return 0 on success
  */

char * replaceInstances(char * textInit, const char * (*replace)[2], Instances ** arr, int length, int size)
{
	char * textCpyOut = (char *) calloc(length + 1, sizeof(char));
    int startingPointOut = 0;
    int startingPointIn = 0;
    for (int i = 0; i <= size; i++)
    {
    	if (i == size)
    	{
    		for (int j = startingPointOut, k = startingPointIn; textInit[k] != '\0'; j++, k++) //copy the rest of the string
         	   textCpyOut[j] = textInit[k];
         	break;
    	}
        for (int j = startingPointOut, k = startingPointIn; j < (*arr)[i].index + (startingPointOut - startingPointIn); j++, k++) //copy the chars before substring instance
        {
            textCpyOut[j] = textInit[k];
            startingPointOut++;
            startingPointIn++;
        }
        
        strcat(textCpyOut, replace[(*arr)[i].word][1]); //copy the substring replacement
        startingPointOut += strlen(replace[(*arr)[i].word][1]); 
        startingPointIn += strlen(replace[(*arr)[i].word][0]); 
    }
   	textCpyOut[length] = '\0';
	return textCpyOut;
}

/**
  * take a string and replace instances of substring with defined counterparts
  * @param[in] const char * text
  * @param[in] const char * (*replace)[2]
  * @return edited string or NULL on error
  */

char * newSpeak ( const char * text, const char * (*replace)[2])
{	
	if (checkList(replace) == -1) //check whether a string is a part 
		return NULL;
		
	char * textCpy = (char *) malloc((strlen(text) + 1) * sizeof(char));
	strcpy(textCpy, text);
	Instances * arr = (Instances *) malloc (sizeof(Instances));
	
	int size = findInstances(&arr, textCpy, replace);
	if (size == 0) //return the initial text if nothing is found
		return textCpy;
	
	qsort(arr, size, sizeof(Instances), compare); //sort struct array to improve replacement
	int newLen = calculatePost(textCpy, &arr, replace, size);
	char * out = replaceInstances(textCpy, replace, &arr, newLen, size);
	free(arr);
	free(textCpy);
	return out;
}

#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
  char * res;

  const char * d1 [][2] =
  {
    { "murderer", "termination specialist" },
    { "failure", "non-traditional success" },
    { "specialist", "person with certified level of knowledge" },
    { "dumb", "cerebrally challenged" },
    { "teacher", "voluntary knowledge conveyor" },
    { "evil", "nicenest deprived" },
    { "incorrect answer", "alternative answer" },
    { "student", "client" },
    { NULL, NULL }
  };


  const char * d2 [][2] =
  {
    { "fail", "suboptimal result" },
    { "failure", "non-traditional success" },
    { NULL, NULL }
  };
  
  const char * d3 [][2] = 
  {
    { "failure", "non-traditional success" },
    { "fail", "suboptimal result" },
    { NULL, NULL }
  };
  /*
  const char * tbl [][2] =
  {
    { "son", "offspring with both X and Y chromosomes" },
    { "prisoner", "client of the correctional system" },
    { NULL, NULL }
  };

  res = newSpeak("son of a prisoner", tbl);
  assert (!strcmp(res, "offspring with both X and Y chromosomes of a client of the correctional system"));
  free(res);
*/
  res = newSpeak ( "Hello.", d2 );
  assert ( ! res );
  
  res = newSpeak("Hello.", d3);
  assert(!res);
  
  res = newSpeak ( "Everybody is happy.", d1 );
  assert ( ! strcmp ( res, "Everybody is happy." ) );
  free ( res );
  
  res = newSpeak ( "The student answered an incorrect answer.", d1 );
  assert ( ! strcmp ( res, "The client answered an alternative answer." ) );
  free ( res );

  res = newSpeak ( "He was dumb, his failure was expected.", d1 );
  assert ( ! strcmp ( res, "He was cerebrally challenged, his non-traditional success was expected." ) );
  free ( res );

  res = newSpeak ( "The evil teacher became a murderer.", d1 );
  assert ( ! strcmp ( res, "The nicenest deprived voluntary knowledge conveyor became a termination specialist." ) );
  free ( res );

  res = newSpeak ( "Devil's advocate.", d1 );
  assert ( ! strcmp ( res, "Dnicenest deprived's advocate." ) );
  free ( res );

  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
