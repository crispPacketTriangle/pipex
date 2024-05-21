#include "pipex.h"

// error handling in parser with malloc, split, etc
int	parse_cmds(char ***args_n, const char *args, t_args *pdata)
{
	int	n;

	if (ft_strlen(args) > 0)
	{
		n = first_pass(args);
		make_room(args_n, n);
		awk_parser(args, args_n, pdata);
		return (0);
	}
	return (69);
}

void	get_path(t_args *pdata, char *env[])
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (strstr(env[i], "PATH=") && env[i][4] == '=')
		{
			env[i] += 5;
			(*pdata).paths = ft_split_p(env[i], ':');
		}
		i++;
	}
}

int	get_cmd_path(t_args *pdata, char ***cmd_path, char ***args)
{
	int	i;

	i = 0;
	while (pdata->paths[i])
		i++;
	*cmd_path = malloc((i + 1) * sizeof(char *));
	i = 0;
	while (pdata->paths[i])
	{
		(*cmd_path)[i] = ft_strjoin(pdata->paths[i],
				(*args)[0]);
		i++;
	}
	(*cmd_path)[i] = NULL;
	return (0);
}

int	get_valid_path(t_args *pdata, char ***cmd_path, char **path)
{
	int	i;
	int	val;

	i = 0;
	val = 0;
	while ((*cmd_path)[i])
	{
		if (access((*cmd_path)[i], F_OK) != -1)
		{
			*path = (*cmd_path)[i];
			val++;
		}
		i++;
	}
	if (val == 0)
		return (127);
	if (access(*path, X_OK) == -1)
		return (errno);
	return (0);
}

void	add_valid_path(char *path, char ***arg)
{
	free((*arg)[0]);
	(*arg)[0] = path;
}
