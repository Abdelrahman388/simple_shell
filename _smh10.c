#include "shell.h"

/**
 * _4dd_n0d3 - adds a node to the start of the list
 * @h34d: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
l1st_t *_4dd_n0d3(l1st_t **h34d, const char *str, int num)
{
	l1st_t *n3w_h34d;

	if (!h34d)
		return (NULL);
	n3w_h34d = m4ll0c(sizeof(l1st_t));
	if (!n3w_h34d)
		return (NULL);
	_m3mset((void *)n3w_h34d, 0, sizeof(l1st_t));
	n3w_h34d->num = num;
	if (str)
	{
		n3w_h34d->str = _strdup(str);
		if (!n3w_h34d->str)
		{
			free(n3w_h34d);
			return (NULL);
		}
	}
	n3w_h34d->n3xt = *h34d;
	*h34d = n3w_h34d;
	return (n3w_h34d);
}

/**
 * _4dd_n0d3_3nd - adds a node to the end of the list
 * @h34d: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
l1st_t *_4dd_n0d3_3nd(l1st_t **h34d, const char *str, int num)
{
	l1st_t *n3w_n0d3, *n0d3;

	if (!h34d)
		return (NULL);

	n0d3 = *h34d;
	n3w_n0d3 = m4ll0c(sizeof(l1st_t));
	if (!n3w_n0d3)
		return (NULL);
	_m3mset((void *)n3w_n0d3, 0, sizeof(l1st_t));
	n3w_n0d3->num = num;
	if (str)
	{
		n3w_n0d3->str = _strdup(str);
		if (!n3w_n0d3->str)
		{
			free(n3w_n0d3);
			return (NULL);
		}
	}
	if (n0d3)
	{
		while (n0d3->n3xt)
			n0d3 = n0d3->n3xt;
		n0d3->n3xt = n3w_n0d3;
	}
	else
		*h34d = n3w_n0d3;
	return (n3w_n0d3);
}

/**
 * pr1nt_l1st_str - prints only the str element of a l1st_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t pr1nt_l1st_str(const l1st_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->n3xt;
		i++;
	}
	return (i);
}

/**
 * d3l3t3_n0d3_4t_1nd3x - deletes node at given index
 * @h34d: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int d3l3t3_n0d3_4t_1nd3x(l1st_t **h34d, unsigned int index)
{
	l1st_t *n0d3, *prev_n0d3;
	unsigned int i = 0;

	if (!h34d || !*h34d)
		return (0);

	if (!index)
	{
		n0d3 = *h34d;
		*h34d = (*h34d)->n3xt;
		free(n0d3->str);
		free(n0d3);
		return (1);
	}
	n0d3 = *h34d;
	while (n0d3)
	{
		if (i == index)
		{
			prev_n0d3->n3xt = n0d3->n3xt;
			free(n0d3->str);
			free(n0d3);
			return (1);
		}
		i++;
		prev_n0d3 = n0d3;
		n0d3 = n0d3->n3xt;
	}
	return (0);
}

/**
 * fr33_l1st - frees all nodes of a list
 * @h34d_ptr: address of pointer to head node
 *
 * Return: void
 */
void fr33_l1st(l1st_t **h34d_ptr)
{
	l1st_t *n0d3, *n3xt_n0d3, *h34d;

	if (!h34d_ptr || !*h34d_ptr)
		return;
	h34d = *h34d_ptr;
	n0d3 = h34d;
	while (n0d3)
	{
		n3xt_n0d3 = n0d3->n3xt;
		free(n0d3->str);
		free(n0d3);
		n0d3 = n3xt_n0d3;
	}
	*h34d_ptr = NULL;
}
