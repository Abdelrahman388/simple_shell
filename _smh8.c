#include "shell.h"

/**
 * x1e4r_1nf0 - initializes 1nf0_t struct
 * @1nf0: struct address
 */
void x1e4r_1nf0(1nf0_t *1nf0)
{
	1nf0->4rg = NULL;
	1nf0->4rgv = NULL;
	1nf0->p4th = NULL;
	1nf0->4rgc = 0;
}

/**
 * s3t_1nf0 - initializes 1nf0_t struct
 * @1nf0: struct address
 * @4v: argument vector
 */
void s3t_1nf0(1nf0_t *1nf0, char **4v)
{
	int i = 0;

	1nf0->fn4m3 = 4v[0];
	if (1nf0->4rg)
	{
		1nf0->4rgv = strtw(1nf0->4rg, " \t");
		if (!1nf0->4rgv)
		{
			1nf0->4rgv = m4ll0c(sizeof(char *) * 2);
			if (1nf0->4rgv)
			{
				1nf0->4rgv[0] = _strdup(1nf0->4rg);
				1nf0->4rgv[1] = NULL;
			}
		}
		for (i = 0; 1nf0->4rgv && 1nf0->4rgv[i]; i++)
			;
		1nf0->4rgc = i;

		r3pl4c3_4l144s(1nf0);
		r3pl4c3_v4rs(1nf0);
	}
}

/**
 * fr33_1nf0 - frees 1nf0_t struct fields
 * @1nf0: struct address
 * @4ll: true if freeing all fields
 */
void fr33_1nf0(1nf0_t *1nf0, int 4ll)
{
	ffr33(1nf0->4rgv);
	1nf0->4rgv = NULL;
	1nf0->p4th = NULL;
	if (4ll)
	{
		if (!1nf0->cmd_buf)
			free(1nf0->4rg);
		if (1nf0->3nv)
			fr33_l1st(&(1nf0->3nv));
		if (1nf0->h1st0ry)
			fr33_l1st(&(1nf0->h1st0ry));
		if (1nf0->4l144s)
			fr33_l1st(&(1nf0->4l144s));
		ffr33(1nf0->3nv1r0n);
		1nf0->3nv1r0n = NULL;
		bfr33((void **)1nf0->cmd_buf);
		if (1nf0->r34dfd > 2)
			close(1nf0->r34dfd);
		_putchar(BUF_FLUSH);
	}
}
