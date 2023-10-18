#include "shell.h"

/**
 * myCopyString - copies a string
 * @myDestination: the destination string to be copied to
 * @mySource: the source string
 * @myLength: the amount of characters to be copied
 *
 * Return: the concatenated string
 */
char *myCopyString(char *myDestination, char *mySource, int myLength)
{
	int myIndex1, myIndex2;
	char *myResult = myDestination;

	myIndex1 = 0;
	while (mySource[myIndex1] != '\0' && myIndex1 < myLength - 1)
	{
		myDestination[myIndex1] = mySource[myIndex1];
		myIndex1++;
	}
	if (myIndex1 < myLength)
	{
		myIndex2 = myIndex1;
		while (myIndex2 < myLength)
		{
			myDestination[myIndex2] = '\0';
			myIndex2++;
		}
	}
	return myResult;
}

/**
 * myConcatenateStrings - concatenates two strings
 * @myDestination: the first string
 * @mySource: the second string
 * @myMaxLength: the amount of bytes to be maximally used
 *
 * Return: the concatenated string
 */
char *myConcatenateStrings(char *myDestination, char *mySource, int myMaxLength)
{
	int myIndex1, myIndex2;
	char *myResult = myDestination;

	myIndex1 = 0;
	myIndex2 = 0;
	while (myDestination[myIndex1] != '\0')
		myIndex1++;
	while (mySource[myIndex2] != '\0' && myIndex2 < myMaxLength)
	{
		myDestination[myIndex1] = mySource[myIndex2];
		myIndex1++;
		myIndex2++;
	}
	if (myIndex2 < myMaxLength)
		myDestination[myIndex1] = '\0';
	return myResult;
}

/**
 * myFindCharacter - locates a character in a string
 * @myString: the string to be parsed
 * @myChar: the character to look for
 *
 * Return: (myString) a pointer to the memory area myString
 */
char *myFindCharacter(char *myString, char myChar)
{
	do {
		if (*myString == myChar)
			return myString;
	} while (*myString++ != '\0');

	return NULL;
}
