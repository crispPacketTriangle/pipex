
#include "pipex.h"

void	parse_cmds(arg *pdata, char *argv[])
{
	pdata->args1 = malloc(sizeof(char*));
	pdata->args1[0] = " ";
	if (ft_strlen(argv[2]) > 0)
		pdata->args1 = ft_split(argv[2], ' ');
	else
	{
		pdata->args1 = malloc(sizeof(char*));
		pdata->args1[0] = " ";
	}
	if (ft_strlen(argv[3]) > 0)
		pdata->args2 = ft_split(argv[3], ' ');
	else
	{
		pdata->args2 = malloc(sizeof(char*));
		pdata->args2[0] = " ";
	}
}

void	get_path(arg *pdata, char *env[])
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

void	get_cmd_path(arg *pdata)
{
	int		i;

	i = 0;
	while ((*pdata).paths[i])
		i++;
	(*pdata).cmd_path1 = malloc((i + 1) * sizeof(char *));
	(*pdata).cmd_path2 = malloc((i + 1) * sizeof(char *));
	i = 0;
	while ((*pdata).paths[i])
	{
		(*pdata).cmd_path1[i] = ft_strjoin((*pdata).paths[i],
			(*pdata).args1[0]);
		(*pdata).cmd_path2[i] = ft_strjoin((*pdata).paths[i],
			(*pdata).args2[0]);
		i++;
	}
	(*pdata).cmd_path1[i] = NULL;
	(*pdata).cmd_path2[i] = NULL;
}

// must check here for valid paths to commands and if no valid paths return error
// check for existence of command if not existing return correct error
// if existig check if executable and return correct error if not

// should pass in the cmd_path to the function and call in higher func
// also split passes to diff funcs
int	get_valid_path(arg *pdata)
{
	int	i;
	int	val1;
	int	val2;

	val1 = 0;
	val2 = 0;
	i = 0;
	while ((*pdata).cmd_path1[i])
	{
		if (access((*pdata).cmd_path1[i], F_OK) != -1) // && access((*pdata).cmd_path1[i], X_OK) != -1 )
		{
			(*pdata).path1 = (*pdata).cmd_path1[i];
			val1++;
		}
		if (access((*pdata).cmd_path2[i], F_OK) != -1) // && access((*pdata).cmd_path2[i], X_OK) != -1 )
		{
			(*pdata).path2 = (*pdata).cmd_path2[i];
			val2++;
		}
		i++;
	}
	if (val1 == 0 || val2 == 0)
		return (errno);
	i = 0;
	val1 = 0;
	val2 = 0;
	if (access((*pdata).path1, X_OK) != -1)
		val1++;
	if (access((*pdata).path2, X_OK) != -1)
		val2++;
	if (val1 == 0 || val2 == 0)
		return (errno);
	return (0);
}

void	add_valid_path(arg *pdata)
{
	free((*pdata).args1[0]);
	(*pdata).args1[0] = (*pdata).path1;
	free((*pdata).args2[0]);
	(*pdata).args2[0] = (*pdata).path2;
}

int	arg_init(arg *pdata, char *argv[], char *env[])
{
	int	err;
	// populates args1/args2 with commands and arguments
	parse_cmds(pdata, argv);
	// get_path populates pdata.paths with paths in PATH
	get_path(pdata, env);
	// get_cmd_path populates pdata.cmd_path with possible paths to commands
	get_cmd_path(pdata);
	// get_valid_path returns valid path to command in pdata.path
	err = get_valid_path(pdata);
	if (err != 0)
		return (err);
	// add valid path to cmds
	add_valid_path(pdata);
	return (0);
}
