#include "shell.h"

/**
 * myBufferInput - buffers chained commands
 * @myInfo: parameter struct
 * @myBuf: address of buffer
 * @myLen: address of len var
 *
 * Return: bytes read
 */
ssize_t myBufferInput(info_t *myInfo, char **myBuf, size_t *myLen)
{
	ssize_t myRead = 0;
	size_t myLenP = 0;

	if (!*myLen) /* if nothing left in the buffer, fill it */
	{
		free(*myBuf);
		*myBuf = NULL;
		signal(SIGINT, mySigintHandler);
#if USE_GETLINE
		myRead = getline(myBuf, &myLenP, stdin);
#else
		myRead = myGetline(myInfo, myBuf, &myLenP);
#endif
		if (myRead > 0)
		{
			if ((*myBuf)[myRead - 1] == '\n')
			{
				(*myBuf)[myRead - 1] = '\0'; /* remove trailing newline */
				myRead--;
			}
			myInfo->linecount_flag = 1;
			removeComments(*myBuf);
			buildHistoryList(myInfo, *myBuf, myInfo->histcount++);
			{
				*myLen = myRead;
				myInfo->cmd_buf = myBuf;
			}
		}
	}
	return myRead;
}

/**
 * myGetInput - gets a line minus the newline
 * @myInfo: parameter struct
 *
 * Return: bytes read
 */
ssize_t myGetInput(info_t *myInfo)
{
	static char *myBuf; /* the ';' command chain buffer */
	static size_t myI, myJ, myLen;
	ssize_t myRead = 0;
	char **myBufP = &(myInfo->arg), *myP;

	_putchar(BUF_FLUSH);
	myRead = myBufferInput(myInfo, &myBuf, &myLen);
	if (myRead == -1) /* EOF */
		return -1;
	if (myLen)
	{
		myJ = myI;
		myP = myBuf + myI;
		checkChain(myInfo, myBuf, &myJ, myI, myLen);
		while (myJ < myLen)
		{
			if (isChain(myInfo, myBuf, &myJ))
				break;
			myJ++;
		}
		myI = myJ + 1;
		if (myI >= myLen)
		{
			myI = myLen = 0;
			myInfo->cmd_buf_type = CMD_NORM;
		}
		*myBufP = myP;
		return myStrlen(myP);
	}
	*myBufP = myBuf;
	return myRead;
}

/**
 * myReadBuf - reads a buffer
 * @myInfo: parameter struct
 * @myBuf: buffer
 * @myI: size
 *
 * Return: myRead
 */
ssize_t myReadBuf(info_t *myInfo, char *myBuf, size_t *myI)
{
	ssize_t myRead = 0;
	if (*myI)
		return 0;
	myRead = read(myInfo->readfd, myBuf, READ_BUF_SIZE);
	if (myRead >= 0)
		*myI = myRead;
	return myRead;
}

/**
 * myGetline - gets the next line of input from STDIN
 * @myInfo: parameter struct
 * @myPtr: address of pointer to buffer, preallocated or NULL
 * @myLength: size of preallocated myPtr buffer if not NULL
 *
 * Return: myS
 */
int myGetline(info_t *myInfo, char **myPtr, size_t *myLength)
{
	static char myBuf[READ_BUF_SIZE];
	static size_t myI, myLen;
	size_t myK;
	ssize_t myRead = 0, myS = 0;
	char *myP = NULL, *myNewP = NULL, *myC;

	myP = *myPtr;
	if (myP && myLength)
		myS = *myLength;
	if (myI == myLen)
		myI = myLen = 0;
	myRead = myReadBuf(myInfo, myBuf, &myLen);
	if (myRead == -1 || (myRead == 0 && myLen == 0))
		return -1;

	myC = myFindCharacter(myBuf + myI, '\n');
	myK = myC ? 1 + (unsigned int)(myC - myBuf) : myLen;
	myNewP = myRealloc(myP, myS, myS ? myS + myK : myK + 1);
	if (!myNewP) /* MALLOC FAILURE! */
		return (myP ? free(myP), -1 : -1);

	if (myS)
		myStrncat(myNewP, myBuf + myI, myK - myI);
	else
		myStrncpy(myNewP, myBuf + myI, myK - myI + 1);

	myS += myK - myI;
	myI = myK;
	myP = myNewP;
	if (myLength)
		*myLength = myS;
	*myPtr = myP;
	return myS;
}

/**
 * mySigintHandler - blocks ctrl-C
 * @mySigNum: the signal number
 *
 * Return: void
 */
void mySigintHandler(__attribute__((unused))int mySigNum)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
