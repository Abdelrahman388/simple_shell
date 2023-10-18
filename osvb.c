#include "shell.h"

/**
 * 1s_cm1 - determines if a file is an executable command
 * @1nf0: the 1nf0 struct
 * @p4th: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int 1s_cm1(1nf0_t *1nf0, char *p4th)
{
	struct stat st;

	(void)1nf0;
	if (!p4th || stat(p4th, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_ch4rs - duplicates characters
 * @p4thstr: the PATH string
 * @st4rt: starting index
 * @st0p: stopping index
 *
 * Return: pointer to new buffer
 */
char *dup_ch4rs(char *p4thstr, int st4rt, int st0p)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = st4rt; i < st0p; i++)
		if (p4thstr[i] != ':')
			buf[k++] = p4thstr[i];
	buf[k] = 0;
	return (buf);
}

/**
 * find_p4th - finds this cmd in the PATH string
 * @1nf0: the 1nf0 struct
 * @p4thstr: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_p4th(1nf0_t *1nf0, char *p4thstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *p4th;

	if (!p4thstr)
		return (NULL);
	if ((_strl3n(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (1s_cm1(1nf0, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!p4thstr[i] || p4thstr[i] == ':')
		{
			p4th = dup_ch4rs(p4thstr, curr_pos, i);
			if (!*p4th)
				_strcat(p4th, cmd);
			else
			{
				_strcat(p4th, "/");
				_strcat(p4th, cmd);
			}
			if (1s_cm1(1nf0, p4th))
				return (p4th);
			if (!p4thstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
