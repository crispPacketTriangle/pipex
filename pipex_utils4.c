/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lworden <lworden@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:46:51 by lworden           #+#    #+#             */
/*   Updated: 2024/05/24 17:46:03 by lworden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	args1_init(t_args *pdata, char *argv[], char *env[])
{
	int	err;

	err = parse_cmds(&pdata->args1, argv[2], pdata);
	if (err == 69)
		return (err);
	if (get_path(pdata, env) != 0)
		return (1);
	if (get_cmd_path(pdata, &pdata->cmd_path1, &pdata->args1) != 0)
		return (1);
	err = get_valid_path(pdata, &pdata->cmd_path1, &pdata->path1);
	return (err);
}

int	args2_init(t_args *pdata, char *argv[], char *env[])
{
	int	err;

	err = parse_cmds(&pdata->args2, argv[3], pdata);
	if (err == 69)
		return (err);
	if (get_path(pdata, env) != 0)
		return (1);
	if (get_cmd_path(pdata, &pdata->cmd_path2, &pdata->args2) != 0)
		return (1);
	err = get_valid_path(pdata, &pdata->cmd_path2, &pdata->path2);
	return (err);
}

void	errsub(const char *ln, const char *s, const char *err)
{
	int		n;
	char	*str;
	char	*error;

	n = ft_strlen(ln) + ft_strlen(s) + ft_strlen(err);
	str = ft_strjoin(ln, s);
	error = ft_strjoin(str, err);
	free(str);
	write(2, error, n);
	free(error);
}

void	persub(const char *ln, const char *s)
{
	char	*str;

	str = ft_strjoin(ln, s);
	perror(str);
	free(str);
}
