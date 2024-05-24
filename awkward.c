/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   awkward.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lworden <lworden@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:47:48 by lworden           #+#    #+#             */
/*   Updated: 2024/05/24 17:47:51 by lworden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	awk_parser(const char *args, char ***prs_args, t_args *pdata)
{
	set_isn(pdata);
	while (args[pdata->i] && args[pdata->i] == ' ')
		pdata->i++;
	while (args[pdata->i])
	{
		while (args[pdata->i] && args[pdata->i] != ' ')
		{
			if (args[pdata->i] == '\'' || args[pdata->i] == '\"')
			{
				pdata->i++;
				while (args[pdata->i] && (args[pdata->i] != '\''
						&& args[pdata->i] != '\"'))
					pdata->i++;
			}
			pdata->i++;
		}
		if (make_sub(args, prs_args, pdata) == 1)
			return (1);
		pdata->n++;
		while (args[pdata->i] && args[pdata->i] == ' ')
			pdata->i++;
		pdata->s = pdata->i;
	}
	(*prs_args)[pdata->n] = NULL;
	return (0);
}

int	make_sub(const char *args, char ***prs_args, t_args *pdata)
{
	if (pdata->s - 1 > 0 && (args[pdata->s] == '\''
			|| args[pdata->s] == '\"') && args[pdata->s - 1] == ' ')
	{
		(*prs_args)[pdata->n] = ft_substr(args, pdata->s + 1,
				(pdata->i - pdata->s) - 2);
		if (!((*prs_args)[pdata->n]))
			return (1);
	}
	else
		(*prs_args)[pdata->n] = ft_substr(args, pdata->s,
				pdata->i - pdata->s);
	if (!((*prs_args)[pdata->n]))
		return (1);
	return (0);
}

int	first_pass(const char *args)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (args[i])
	{
		while (args[i] && args[i] != ' ')
		{
			if (args[i] == '\'' || args[i] == '\"')
			{
				i++;
				while (args[i] && (args[i] != '\'' && args[i] != '\"'))
					i++;
			}
			i++;
		}
		n++;
		while (args[i] && args[i] == ' ')
			i++;
	}
	return (n);
}

int	make_room(char ***pdata, int n)
{
	*pdata = malloc((n + 1) * sizeof(char *));
	if (!(*pdata))
		return (1);
	return (0);
}

void	set_isn(t_args *pdata)
{
	pdata->i = 0;
	pdata->s = 0;
	pdata->n = 0;
}
