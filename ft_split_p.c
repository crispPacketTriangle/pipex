
#include "pipex.h"

// DO NOT LIKE THIS UGLY HACK
// to do > split funcs across 2 files

static int	str_n(const char *str, char c);
static int	str_gen(const char *str, char c, char **arr, int n);
static void	free_all(char **arr);
char	*ft_substr_p(const char *s, unsigned int st, size_t len);
static char	*sub(const char *s, char *ptr, unsigned int st, unsigned int size);
static char	*sngl_char(const char *s, char *ptr, unsigned int st);

char	**ft_split_p(const char *str, char c)
{
	char	**arr;
	int		n;
	int		t;

	n = str_n(str, c);
	arr = (char **)malloc((n + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	arr[n] = NULL;
	t = str_gen(str, c, arr, n);
	if (!t)
	{
		free_all(arr);
		return (NULL);
	}
	return (arr);
}

static int	str_n(const char *str, char c)
{
	int		n;
	int		i;

	i = 0;
	n = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i])
			n++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (n);
}

static int	str_gen(const char *str, char c, char **arr, int n)
{
	int		i;
	int		str_i;
	int		j;

	i = 0;
	str_i = 0;
	while (n--)
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i])
		{
			j = i;
			while (str[i] && str[i] != c)
				i++;
			arr[str_i] = ft_substr_p(str, j, i - j);
			if (!(arr[str_i]))
				return (0);
		}
		str_i++;
		while (str[i] == c)
			i++;
	}
	return (1);
}

static void	free_all(char **arr)
{
	int	i;

	i = 0;
	while (arr)
	{
		free(arr[i++]);
	}
	free(arr);
}

char	*ft_substr_p(const char *s, unsigned int st, size_t len)
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
	ptr = (char *)malloc((size + 1) * sizeof(char));
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
	ptr[i] = '/';
	ptr[i + 1] = '\0';
	return (ptr);
}

static char	*sngl_char(const char *s, char *ptr, unsigned int st)
{
	ptr[0] = s[st];
	ptr[1] = '\0';
	return (ptr);
}