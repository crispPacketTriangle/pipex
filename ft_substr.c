
#include "pipex.h"

static char	*sub(const char *s, char *ptr, unsigned int st, unsigned int size);
static char	*sngl_char(const char *s, char *ptr, unsigned int st);

char	*ft_substr(const char *s, unsigned int st, size_t len)
{
	unsigned int	sz;
	unsigned int	size;
	unsigned int	i;
	char			*ptr;

	sz = 0;
	while (s[sz])
		sz++;
	if (st > sz || len == 0)
	{
		st = sz;
		size = 1;
	}
	else if (len > (sz - st))
		size = (sz - st) + 1;
	else
		size = len + 1;
	ptr = (char *)malloc(size * sizeof(char));
	if (!ptr)
		return (NULL);
	i = 0;
	if (len == 1 && st == 1)
		return (sngl_char(s, ptr, st));
	else
		return (sub(s, ptr, st, size));
}

static char	*sub(const char *s, char *ptr, unsigned int st, unsigned int size)
{
	unsigned int	i;

	i = 0;
	while (s[st] && i < (size - 1))
	{
		ptr[i] = s[st];
		st++;
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

static char	*sngl_char(const char *s, char *ptr, unsigned int st)
{
	ptr[0] = s[st];
	ptr[1] = '\0';
	return (ptr);
}