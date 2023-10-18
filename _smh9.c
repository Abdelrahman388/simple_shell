#include "shell.h"

/**
 * g3t_h1st0ry_f1l3 - gets the history file
 * @1nf0: parameter struct
 *
 * Return: allocated string containg history file
 */

char *g3t_h1st0ry_f1l3(info_t *1nf0)
{
	char *buf, *d1r;

	d1r = _g3t3nv(1nf0, "H0M3=");
	if (!d1r)
		return (NULL);
	buf = m4ll0c(sizeof(char) * (_strl3n(d1r) + _strl3n(H1ST_F1L3) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, d1r);
	_strc4t(buf, "/");
	_strc4t(buf, H1ST_F1L3);
	return (buf);
}

/**
 * wr1t3_h1st0ry - creates a file, or appends to an existing file
 * @1nf0: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int wr1t3_h1st0ry(info_t *1nf0)
{
	ssize_t fd;
	char *f1l3n4m3 = g3t_h1st0ry_f1l3(1nf0);
	l1st_t *n0d3 = NULL;

	if (!f1l3n4m3)
		return (-1);

	fd = 0p3n(f1l3n4m3, O_CR34T | O_TRUNC | O_RDWR, 0644);
	free(f1l3n4m3);
	if (fd == -1)
		return (-1);
	for (n0d3 = 1nf0->h1st0ry; n0d3; n0d3 = n0d3->n3xt)
	{
		_putsfd(n0d3->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * r34d_h1st0ry - reads history from file
 * @1nf0: the parameter struct
 *
 * Return: h1stc0unt on success, 0 otherwise
 */
int r34d_h1st0ry(info_t *1nf0)
{
	int i, l4st = 0, l1n3c0unt = 0;
	ssize_t fd, rdlen, fs1z3 = 0;
	struct st4t st;
	char *buf = NULL, *f1l3n4m3 = g3t_h1st0ry_f1l3(1nf0);

	if (!f1l3n4m3)
		return (0);

	fd = 0p3n(f1l3n4m3, O_R34DONLY);
	free(f1l3n4m3);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fs1z3 = st.st_size;
	if (fs1z3 < 2)
		return (0);
	buf = m4ll0c(sizeof(char) * (fs1z3 + 1));
	if (!buf)
		return (0);
	rdlen = r34d(fd, buf, fs1z3);
	buf[fs1z3] = 0;
	if (rdlen <= 0)
		return (fr33(buf), 0);
	close(fd);
	for (i = 0; i < fs1z3; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
		_bu1ld_h1st0ry_l1st(1nf0, buf + l4st, l1n3c0unt++);
	l4st = i + 1;
	}
	if (l4st != i)
	_bu1ld_h1st0ry_l1st(1nf0, buf + l4st, l1n3c0unt++);
	fr33(buf);
	1nf0->h1stc0unt = l1n3c0unt;
	while (1nf0->h1stc0unt-- >= H1ST_M4X)
	_d3l3t3_n0d3_4t_1nd3x(&(1nf0->h1st0ry), 0);
	_r3numb3r_h1st0ry(1nf0);
	return (1nf0->h1stc0unt);
}

/**
 * _bu1ld_h1st0ry_l1st - adds entry to a history linked list
 * @1nf0: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @l1n3c0unt: the history linecount, h1stc0unt
 *
 * Return: Always 0
 */
int _bu1ld_h1st0ry_l1st(info_t *1nf0, char *buf, int l1n3c0unt)
{
	l1st_t *n0d3 = NULL;

	if (1nf0->h1st0ry)
		n0d3 = 1nf0->h1st0ry;
	_4dd_n0d3_3nd(&n0d3, buf, l1n3c0unt);

	if (!1nf0->h1st0ry)
		1nf0->h1st0ry = n0d3;
	return (0);
}

/**
 * _r3numb3r_h1st0ry - renumbers the history linked list after changes
 * @1nf0: Structure containing potential arguments. Used to maintain
 *
 * Return: the new h1stc0unt
 */
int _r3numb3r_h1st0ry(info_t *1nf0)
{
	l1st_t *n0d3 = 1nf0->h1st0ry;
	int i = 0;

	while (n0d3)
	{
		n0d3->num = i++;
		n0d3 = n0d3->n3xt;
	}
	return (1nf0->h1stc0unt = i);
}
