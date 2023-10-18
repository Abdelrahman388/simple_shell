#include "shell.h"

/**
 * myEnvironment - prints the current environment
 * @infoData: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int myEnvironment(info_t *infoData)
{
	printListStr(infoData->environment);
	return 0;
}

/**
 * getEnvironmentValue - gets the value of an environment variable
 * @infoData: Structure containing potential arguments. Used to maintain
 * @name: env var name
 * Return: the value
 */
char *getEnvironmentValue(info_t *infoData, const char *name)
{
	list_t *environmentNode = infoData->environment;
	char *variableValue;

	while (environmentNode)
	{
		variableValue = startsWith(environmentNode->str, name);
		if (variableValue && *variableValue)
			return variableValue;
		environmentNode = environmentNode->next;
	}
	return NULL;
}

/**
 * mySetEnvironment - Initialize a new environment variable,
 *             or modify an existing one
 * @infoData: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int mySetEnvironment(info_t *infoData)
{
	if (infoData->argumentCount != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return 1;
	}
	if (_setEnvironment(infoData, infoData->arguments[1], infoData->arguments[2]))
		return 0;
	return 1;
}

/**
 * myUnsetEnvironment - Remove an environment variable
 * @infoData: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int myUnsetEnvironment(info_t *infoData)
{
	int i;

	if (infoData->argumentCount == 1)
	{
		_eputs("Too few arguments.\n");
		return 1;
	}
	for (i = 1; i <= infoData->argumentCount; i++)
		_unsetEnvironment(infoData, infoData->arguments[i]);

	return 0;
}

/**
 * populateEnvironmentList - populates environment linked list
 * @infoData: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int populateEnvironmentList(info_t *infoData)
{
	list_t *environmentNode = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		addNodeEnd(&environmentNode, environ[i], 0);
	infoData->environment = environmentNode;
	return 0;
}
