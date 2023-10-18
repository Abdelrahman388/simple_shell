#include "shell.h"

/**
 * l1st_l3n - determines length of linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t l1st_l3n(const l1st_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->n3xt;
		i++;
	}
	return (i);
}

/**
 * l1st_t0_str1ngs - returns an array of strings of the l1st_t->str
 * @h34d: pointer to first node
 *
 * Return: array of strings
 */
char **l1st_t0_str1ngs(l1st_t *h34d)
{
	l1st_t *n0d3 = h34d;
	size_t i = l1st_l3n(h34d), j;
	char **strs;
	char *str;

	if (!h34d || !i)
		return (NULL);
	strs = m4ll0c(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; n0d3; n0d3 = n0d3->n3xt, i++)
	{
		str = m4ll0c(_strl3n(n0d3->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, n0d3->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}

/**
 * pr1nt_l1st - prints all elements of a l1st_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t pr1nt_l1st(const l1st_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(c0nv3rt_numb3r(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->n3xt;
		i++;
	}
	return (i);
}

/**
 * n0d3_st4rts_w1th - returns node whose string starts with prefix
 * @n0d3: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
l1st_t *n0d3_st4rts_w1th(l1st_t *n0d3, char *prefix, char c)
{
	char *p = NULL;

	while (n0d3)
	{
		p = st4rts_with(n0d3->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (n0d3);
		n0d3 = n0d3->n3xt;
	}
	return (NULL);
}

/**
 * g3t_n0d3_1nd3x - gets the index of a node
 * @h34d: pointer to list head
 * @n0d3: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t g3t_n0d3_1nd3x(l1st_t *h34d, l1st_t *n0d3)
{
	size_t i = 0;

	while (h34d)
	{
		if (h34d == n0d3)
			return (i);
		h34d = h34d->n3xt;
		i++;
	}
	return (-1);
}
