/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lworden <lworden@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:46:40 by lworden           #+#    #+#             */
/*   Updated: 2024/05/24 16:22:27 by lworden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	args_free(char **arr)
{
	int	i;

	if (arr)
	{
		i = 0;
		while (arr[i])
		{
			free(arr[i]);
			i++;
		}
		free(arr);
	}
}

void	free_pdata(t_args *pdata)
{
	args_free(pdata->paths);
	pdata->paths = NULL;
	args_free(pdata->cmd_path1);
	pdata->cmd_path1 = NULL;
	args_free(pdata->cmd_path2);
	pdata->cmd_path2 = NULL;
	args_free(pdata->args1);
	pdata->args1 = NULL;
	args_free(pdata->args2);
	pdata->args2 = NULL;
	close(pdata->filein);
	close(pdata->fileout);
}

void	wait_free(t_args *pdata)
{
	close(pdata->fd[0]);
	close(pdata->fd[1]);
	waitpid(pdata->pid1, &pdata->ferr, 0);
	waitpid(pdata->pid2, &pdata->serr, 0);
	free_pdata(pdata);
}
