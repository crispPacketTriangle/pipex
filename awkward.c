#include <stdio.h>
#include "pipex.h"

void	awk_parser(const char *args, char ***prs_args, t_args *pdata)
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
		make_sub(args, prs_args, pdata);
		pdata->n++;
		while (args[pdata->i] && args[pdata->i] == ' ')
			pdata->i++;
		pdata->s = pdata->i;
	}
	(*prs_args)[pdata->n] = NULL;
}

void	make_sub(const char *args, char ***prs_args, t_args *pdata)
{
	if (pdata->s - 1 > 0 && (args[pdata->s] == '\''
			|| args[pdata->s] == '\"') && args[pdata->s - 1] == ' ')
		(*prs_args)[pdata->n] = ft_substr(args, pdata->s + 1,
				(pdata->i - pdata->s) - 2);
	else
		(*prs_args)[pdata->n] = ft_substr(args, pdata->s,
				pdata->i - pdata->s);
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

void	make_room(char ***pdata, int n)
{
	*pdata = malloc((n + 1) * sizeof(char *));
}

void	set_isn(t_args *pdata)
{
	pdata->i = 0;
	pdata->s = 0;
	pdata->n = 0;
}
// void	print_debug(t_args *pdata)
// {
// 	int	i;
//
// 	i = 0;
// 	while (pdata->args1[i])
// 	{
// 		printf("args1: %s\n", pdata->args1[i]);
// 		i++;
// 	}
// 	i = 0;
// 	while (pdata->args2[i])
// 	{
// 		printf("args2: %s\n", pdata->args2[i]);
// 		i++;
// 	}
// 	i = 0;
// 	while (pdata->cmd_path1[i])
// 	{
// 		printf("cmd1: %s\n", pdata->cmd_path1[i]);
// 		i++;
// 	}
// 	i = 0;
// 	while (pdata->cmd_path2[i])
// 	{
// 		printf("cmd2: %s\n", pdata->cmd_path2[i]);
// 		i++;
// 	}
// }

// int	main()
// {
// 	t_args	data;
//
// 	int n = first_pass("awk -F, -v OFS='\t' '{print $1, $2}' data.csv");
// 	//int n = first_pass("a.out");
//
// 	make_room(&data.args1, n);
// 	
// 	awk_parser("awk -F, -v OFS='\t' '{print $1, $2}' data.csv", &data.args1);
// 	//awk_parser("a.out", &data.args1);
// 	
// 	printf("n: %d\n", n);
// 	print_debug(&data);
// }
