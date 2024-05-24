/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lworden <lworden@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:46:17 by lworden           #+#    #+#             */
/*   Updated: 2024/05/24 17:26:56 by lworden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	parse_cmds(char ***args_n, const char *args, t_args *pdata)
{
	int	n;
	int	merr;

	if (ft_strlen(args) > 0)
	{
		n = first_pass(args);
		merr = make_room(args_n, n);
		if (merr == 1)
			return (merr);
		merr = awk_parser(args, args_n, pdata);
		return (merr);
	}
	return (69);
}

int	get_path(t_args *pdata, char *env[])
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
	if (!((*pdata).paths))
		return (1);
	return (0);
}

int	get_cmd_path(t_args *pdata, char ***cmd_path, char ***args)
{
	int	i;

	i = 0;
	while (pdata->paths[i])
		i++;
	*cmd_path = malloc((i + 1) * sizeof(char *));
	if (!(*cmd_path))
		return (1);
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
