#include "shell.h"

/**
 * _m3mset - fills m3m0ry with a c0nst4nt byte
 * @s: th3 p01nt3r to th3 m3m0ry 4r34
 * @b: th3 byt3 to fill *s with
 * @n: th3 4m0unt 0f byt3s to b3 fill3d
 * R3turn: (s) a p01nt3r to th3 m3m0ry 4r34 s
 */
char *_m3mset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * ffr33 - fr33s a string of strings
 * @pp: string of strings
 */
void ffr33(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * _r34lloc - r34llocates a block of m3m0ry
 * @ptr: p01nt3r to pr3v1ous malloc'4t3d block
 * @old_size: byt3 siz3 of pr3v1ous block
 * @new_size: byt3 siz3 of n3w block
 *
 * R3turn: p01nt3r to da 0l'block n4m33n.
 */
void *_r34lloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (m4ll0c(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = m4ll0c(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}
