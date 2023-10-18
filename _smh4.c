#include "shell.h"

/**
 * myConvertStrToInt - converts a string to an integer
 * @myStr: the string to be converted
 *
 * Return: 0 if no numbers in the string, converted number otherwise
 *       -1 on error
 */
int myConvertStrToInt(char *myStr)
{
	int index = 0;
	unsigned long int result = 0;

	if (*myStr == '+')
		myStr++;
	for (index = 0;  myStr[index] != '\0'; index++)
	{
		if (myStr[index] >= '0' && myStr[index] <= '9')
		{
			result *= 10;
			result += (myStr[index] - '0');
			if (result > INT_MAX)
				return -1;
		}
		else
			return -1;
	}
	return result;
}

/**
 * myPrintError - prints an error message
 * @myInfo: the parameter & return info struct
 * @myErrorString: string containing specified error type
 *
 * Return: Nothing
 */
void myPrintError(info_t *myInfo, char *myErrorString)
{
	myPrintErrString(myInfo->myFileName);
	myPrintErrString(": ");
	myPrintInt(myInfo->lineCount, STDERR_FILENO);
	myPrintErrString(": ");
	myPrintErrString(myInfo->myArgv[0]);
	myPrintErrString(": ");
	myPrintErrString(myErrorString);
}

/**
 * myPrintInt - function prints a decimal (integer) number (base 10)
 * @myInput: the input
 * @myFD: the file descriptor to write to
 *
 * Return: number of characters printed
 */
int myPrintInt(int myInput, int myFD)
{
	int (*myPutChar)(char) = myPutChar;
	int index, count = 0;
	unsigned int myAbs, current;

	if (myFD == STDERR_FILENO)
		myPutChar = myPrintErrChar;
	if (myInput < 0)
	{
		myAbs = -myInput;
		myPutChar('-');
		count++;
	}
	else
		myAbs = myInput;
	current = myAbs;
	for (index = 1000000000; index > 1; index /= 10)
	{
		if (myAbs / index)
		{
			myPutChar('0' + current / index);
			count++;
		}
		current %= index;
	}
	myPutChar('0' + current);
	count++;

	return count;
}

/**
 * myConvertNumber - converter function, a clone of itoa
 * @myNum: number
 * @myBase: base
 * @myFlags: argument flags
 *
 * Return: string
 */
char *myConvertNumber(long int myNum, int myBase, int myFlags)
{
	static char *myArray;
	static char myBuffer[50];
	char mySign = 0;
	char *myPtr;
	unsigned long myN = myNum;

	if (!(myFlags & MY_CONVERT_UNSIGNED) && myNum < 0)
	{
		myN = -myNum;
		mySign = '-';
	}
	myArray = myFlags & MY_CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	myPtr = &myBuffer[49];
	*myPtr = '\0';

	do {
		*--myPtr = myArray[myN % myBase];
		myN /= myBase;
	} while (myN != 0);

	if (mySign)
		*--myPtr = mySign;
	return myPtr;
}

/**
 * myRemoveComments - function replaces first instance of '#' with '\0'
 * @myBuf: address of the string to modify
 *
 * Return: Always 0;
 */
void myRemoveComments(char *myBuf)
{
	int index;

	for (index = 0; myBuf[index] != '\0'; index++)
		if (myBuf[index] == '#' && (!index || myBuf[index - 1] == ' '))
		{
			myBuf[index] = '\0';
			break;
		}
}
