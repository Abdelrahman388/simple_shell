#include "custom_shell.h"

int custom_string_length(char *custom_str)
{
	int custom_i = 0;

	if (!custom_str)
		return (0);

	while (*custom_str++)
		custom_i++;
	return (custom_i);
}

<<<<<<< HEAD
=======
/**
 * custom_string_compare - performs lexicographic comparison of two c strings.
 * @custom_str1: the first custom string
 * @custom_str2: the second custom string
 *
 * Return:-1 if c_str1 < c_str2,+1 if c_str1 > c_str2, 0 if c_str1 == c_str2
 */
>>>>>>> ae1b1cc57aa1eef374cded65fcca685565cdfbfe
int custom_string_compare(char *custom_str1, char *custom_str2)
{
	while (*custom_str1 && *custom_str2)
	{
		if (*custom_str1 != *custom_str2)
			return (*custom_str1 - *custom_str2);
		custom_str1++;
		custom_str2++;
	}
	if (*custom_str1 == *custom_str2)
		return (0);
	else
		return (*custom_str1 < *custom_str2 ? -1 : 1);
}

char *custom_starts_with(const char *custom_haystack, const char *custom_needle)
{
	while (*custom_needle)
		if (*custom_needle++ != *custom_haystack++)
			return (NULL);
<<<<<<< HEAD
	return (char *custom_haystack);
=======
		return ((char *)custom_haystack);
>>>>>>> ae1b1cc57aa1eef374cded65fcca685565cdfbfe
}

char *custom_string_concatenate(char *custom_dest, char *custom_src)
{
	char *custom_ret = custom_dest;

	while (*custom_dest)
		custom_dest++;
	while (*custom_src)
		*custom_dest++ = *custom_src++;
<<<<<<< HEAD
	*custom_dest = '\0';
=======
	*custom_dest = *custom_src;
>>>>>>> ae1b1cc57aa1eef374cded65fcca685565cdfbfe
	return (custom_ret);
}
