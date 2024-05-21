#include "pipex.h"

// int	parse_cmds(char ***args_n, const char *args)
// {
// 	if (ft_strlen(args) > 0)
// 	{
// 		*args_n = ft_split(args, ' ');
// 		return (0);
// 	}
// 	return (69);
// }

void	parser(char ***args_n, const char *args)
{
	char	*temp;
	int		i;

	i = 1;
	while ((*args_n)[i])
	{
		temp = ft_strtrim((*args_n)[i], "\'\"");
		free((*args_n)[i]);
		(*args_n)[i] = temp;
		//free(temp);
		i++;
	}
}

int	isin_str(const char *args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (args[i] == '\"' || args[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}
