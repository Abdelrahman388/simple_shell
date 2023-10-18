#include "shell.h"

/**
 * myPrintErrString - prints an input string to stderr
 * @myStr: the string to be printed
 *
 * Return: Nothing
 */
void myPrintErrString(char *myStr)
{
	int index = 0;

	if (!myStr)
		return;
	while (myStr[index] != '\0')
	{
		myPrintErrChar(myStr[index]);
		index++;
	}
}

/**
 * myPrintErrChar - writes the character to stderr
 * @myChar: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int myPrintErrChar(char myChar)
{
	static int currentIndex;
	static char buffer[MY_WRITE_BUF_SIZE];

	if (myChar == MY_BUF_FLUSH || currentIndex >= MY_WRITE_BUF_SIZE)
	{
		write(2, buffer, currentIndex);
		currentIndex = 0;
	}
	if (myChar != MY_BUF_FLUSH)
		buffer[currentIndex++] = myChar;
	return 1;
}

/**
 * myWriteToFD - writes the character to the given file descriptor
 * @myChar: The character to print
 * @myFD: The file descriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int myWriteToFD(char myChar, int myFD)
{
	static int currentIndex;
	static char buffer[MY_WRITE_BUF_SIZE];

	if (myChar == MY_BUF_FLUSH || currentIndex >= MY_WRITE_BUF_SIZE)
	{
		write(myFD, buffer, currentIndex);
		currentIndex = 0;
	}
	if (myChar != MY_BUF_FLUSH)
		buffer[currentIndex++] = myChar;
	return 1;
}

/**
 * myPrintToFD - prints an input string to the specified file descriptor
 * @myStr: the string to be printed
 * @myFD: the file descriptor to write to
 *
 * Return: the number of characters written
 */
int myPrintToFD(char *myStr, int myFD)
{
	int index = 0;

	if (!myStr)
		return 0;
	while (*myStr)
	{
		index += myWriteToFD(*myStr++, myFD);
	}
	return index;
}
