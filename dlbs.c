#include "shell.h"

/**
 * _bfre3 - frees a pointer and NULLs the address
 * @p: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int _bfre3(void **p)
{
	if (p && *p)
	{
<<<<<<< HEAD
		free(*p);
=======
		fr33(*p);
>>>>>>> ae1b1cc57aa1eef374cded65fcca685565cdfbfe
		*p = NULL;
		return (1);
	}
	return (0);
}
