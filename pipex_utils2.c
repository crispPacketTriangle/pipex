/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lworden <lworden@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:46:29 by lworden           #+#    #+#             */
/*   Updated: 2024/05/24 16:22:26 by lworden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	setup(t_args *pdata, char *argv[], char *env[])
{
	init_data(pdata);
	pdata->err1 = args1_init(pdata, argv, env);
	pdata->err2 = args2_init(pdata, argv, env);
	pdata->f_err1 = i_access(pdata, argv);
	pdata->f_err2 = o_access(pdata, argv);
}

int	pipe_setup_1(t_args *pdata, char *env[], char *argv[])
{
	dup2(pdata->filein, STDIN_FILENO);
	dup2(pdata->fd[1], STDOUT_FILENO);
	close(pdata->fd[0]);
	close(pdata->fd[1]);
	return (process1(pdata, env, argv));
}

int	pipe_setup_2(t_args *pdata, char *env[], char *argv[])
{
	dup2(pdata->fd[0], STDIN_FILENO);
	dup2(pdata->fileout, STDOUT_FILENO);
	close(pdata->fd[0]);
	close(pdata->fd[1]);
	return (process2(pdata, env, argv));
}

int	process1(t_args *pdata, char *env[], char *argv[])
{
	if (pdata->err1 == 0 && pdata->f_err1 == 0)
		execve(pdata->path1, pdata->args1, env);
	if (pdata->err1 == 69)
		return (0);
	if (pdata->f_err1 != 0)
	{
		free_pdata(pdata);
		return (pdata->f_err1);
	}
	if (pdata->err1 == 127)
	{
		errsub("pipex: 1: ", argv[2], ": command not found\n");
		free_pdata(pdata);
		return (pdata->err1);
	}
	persub("pipex_utils2: ", argv[2]);
	free_pdata(pdata);
	return (pdata->err1);
}

int	process2(t_args *pdata, char *env[], char *argv[])
{
	if (pdata->err2 == 0 && pdata->f_err2 == 0)
		execve(pdata->path2, pdata->args2, env);
	if (pdata->err2 == 69)
		return (0);
	if (pdata->err2 == 127)
	{
		errsub("pipex: 1: ", argv[3], ": command not found\n");
		free_pdata(pdata);
		return (pdata->err2);
	}
	if (pdata->err2 != 0)
	{
		persub("pipex: 1: ", argv[3]);
		free_pdata(pdata);
		return (pdata->err2);
	}
	free_pdata(pdata);
	return (pdata->f_err2);
}
