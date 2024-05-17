
#include "pipex.h"

// void	parse_cmds(t_args*pdata, char *argv[])
// {
// 	if (ft_strlen(argv[2]) > 0)
// 	{
// 		pdata->args1 = ft_split(argv[2], '\'');
// 		pdata->args1 = ft_split(argv[2], ' ');
// 		if (pdata->args1[1])
// 			pdata->args1[1] = ft_strtrim(pdata->args1[1], "\'\"");
// 	}
// 	if (ft_strlen(argv[3]) > 0)
// 	{
// 		pdata->args2 = ft_split(argv[3], ' ');
// 		if (pdata->args2[1])
// 			pdata->args2[1] = ft_strtrim(pdata->args2[1], "\'\"");
// 	}
// }

int	parse_cmds(char ***args_n, const char *args)
{
	if (ft_strlen(args) > 0)
	{
	*args_n = ft_split(args, ' ');
	if ((*args_n)[1])
		(*args_n)[1] = ft_strtrim((*args_n)[1], "\'\"");
	}
	return (0);
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

// void	get_cmd_path(t_args *pdata)
// {
// 	int		i;
//
// 	i = 0;
// 	while ((*pdata).paths[i])
// 		i++;
// 	(*pdata).cmd_path1 = malloc((i + 1) * sizeof(char *));
// 	(*pdata).cmd_path2 = malloc((i + 1) * sizeof(char *));
// 	i = 0;
// 	while ((*pdata).paths[i])
// 	{
// 		(*pdata).cmd_path1[i] = ft_strjoin((*pdata).paths[i],
// 			(*pdata).args1[0]);
// 		(*pdata).cmd_path2[i] = ft_strjoin((*pdata).paths[i],
// 			(*pdata).args2[0]);
// 		i++;
// 	}
// 	(*pdata).cmd_path1[i] = NULL;
// 	(*pdata).cmd_path2[i] = NULL;
// }

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
// must check here for valid paths to commands and if no valid paths return error
// check for existence of command if not existing return correct error
// if existig check if executable and return correct error if not

// should pass in the cmd_path to the function and call in higher func
// also split passes to diff funcs
int	get_valid_path(t_args*pdata)
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
	if (val1 == 0)
	{
		// this is not satisfying francinette
		ft_printf("bash: %s: command not found...\n", pdata->args1[0]);
		return (errno);
	}
	if (val2 == 0)
	{
		ft_printf("bash: %s: command not found...\n", pdata->args2[0]);
		return (errno);	
	}
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

// if there are multiple binaries at diff locations
// does the cycle through them and in the case that one
// is not executable tries the other(s)
int	gen_get_valid_path(t_args *pdata, char ***cmd_path, char **path)
{
	int	i;
	int	val;

	i = 0;
	while ((*cmd_path)[i])
	{
		if (access((*cmd_path)[i], F_OK) != -1) // && access((*pdata).cmd_path1[i], X_OK) != -1 )
		{
			*path = (*cmd_path)[i];
			val++;
		}
		i++;
	}
	if (val == 0)
	{
		return (errno);
	}
	if (access(*path, X_OK) == -1)
		return (errno);
	return (0);
}

void	add_valid_path(t_args*pdata)
{
	free((*pdata).args1[0]);
	(*pdata).args1[0] = (*pdata).path1;
	free((*pdata).args2[0]);
	(*pdata).args2[0] = (*pdata).path2;
}

int	args_init(t_args *pdata, char *argv[], char *env[])
{
	int	err;
	// populates args1/args2 with commands and arguments
	//parse_cmds(pdata, argv);
	parse_cmds(&pdata->args1, argv[2]);
	parse_cmds(&pdata->args2, argv[3]);
	//get_path populates pdata.paths with paths in PATH
	get_path(pdata, env);
	// get_cmd_path populates pdata.cmd_path with possible paths to commands
	get_cmd_path(pdata, &pdata->cmd_path1, &pdata->args1);
	get_cmd_path(pdata, &pdata->cmd_path2, &pdata->args2);
	// get_valid_path returns valid path to command in pdata.path
	
	err = gen_get_valid_path(pdata, &pdata->cmd_path1, &pdata->path1);
	err = gen_get_valid_path(pdata, &pdata->cmd_path2, &pdata->path2);
	
//	err = get_valid_path(pdata);
	if (err != 0)
		return (err);
	// add valid path to cmds
	add_valid_path(pdata);
	return (0);
}


// IF IT EXISTS AS A PATH BUT IS NOT A COMMAND
