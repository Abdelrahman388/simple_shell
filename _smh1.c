#include "shell.h"

/**
 * myExitFunction - exits the shell
 * @infoData: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: exits with a given exit status
 * (0) if infoData->argv[0] != "exit"
 */
int myExitFunction(info_t *infoData)
{
	int exitCode;

	if (infoData->argv[1]) /* If there is an exit argument */
	{
		exitCode = _errorAtoi(infoData->argv[1]);
		if (exitCode == -1)
		{
			infoData->status = 2;
			printErrorMessage(infoData, "Illegal number: ");
			_eputs(infoData->argv[1]);
			_eputchar('\n');
			return 1;
		}
		infoData->errNumber = _errorAtoi(infoData->argv[1]);
		return -2;
	}
	infoData->errNumber = -1;
	return -2;
}

/**
 * myChangeDir - changes the current directory of the process
 * @dataInfo: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int myChangeDir(info_t *dataInfo)
{
	char *currentDir, *newDir, buffer[1024];
	int chdirResult;

	currentDir = getcwd(buffer, 1024);
	if (!currentDir)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!dataInfo->argv[1])
	{
		newDir = _getEnvironment(dataInfo, "HOME=");
		if (!newDir)
			chdirResult = /* TODO: what should this be? */
				chdir((newDir = _getEnvironment(dataInfo, "PWD=")) ? newDir : "/");
		else
			chdirResult = chdir(newDir);
	}
	else if (_strcmp(dataInfo->argv[1], "-") == 0)
	{
		if (!_getEnvironment(dataInfo, "OLDPWD="))
		{
			_puts(currentDir);
			_putchar('\n');
			return 1;
		}
		_puts(_getEnvironment(dataInfo, "OLDPWD="));
		_putchar('\n');
		chdirResult = /* TODO: what should this be? */
			chdir((newDir = _getEnvironment(dataInfo, "OLDPWD=")) ? newDir : "/");
	}
	else
		chdirResult = chdir(dataInfo->argv[1]);
	if (chdirResult == -1)
	{
		printErrorMessage(dataInfo, "can't cd to ");
		_eputs(dataInfo->argv[1]);
		_eputchar('\n');
	}
	else
	{
		_setEnvironment(dataInfo, "OLDPWD", _getEnvironment(dataInfo, "PWD="));
		_setEnvironment(dataInfo, "PWD", getcwd(buffer, 1024));
	}
	return 0;
}

/**
 * myHelper - displays a help message
 * @infoData: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int myHelper(info_t *infoData)
{
	char **argumentArray;

	argumentArray = infoData->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*argumentArray); /* temp att_unused workaround */
	return 0;
}
