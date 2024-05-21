#include <stdio.h>
#include "pipex.h"

void	awk_parser(const char *args, char ***prs_args)
{
	int	i;
	int	s;
	int n;

	i = 0;
	s = 0;
	n = 0;
	// incase typo leading space
	while (args[i] && args[i] == ' ')
			i++;
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
		if (s - 1 > 0 && (args[s] == '\'' || args[s] == '\"') && args[s - 1] == ' ')
			(*prs_args)[n] = ft_substr(args, s + 1, (i - s) - 2);
		else
			(*prs_args)[n] = ft_substr(args, s, i - s);
		//s = i + 1;
		n++;
		while (args[i] && args[i] == ' ')
			i++;
		s = i;
	}
	(*prs_args)[n] = NULL;
}

int	first_pass(const char *args)
{
	int	i;
	int n;

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
		//ft_printf("%c\n", args[i]);
	}
	return (n);
}

void	make_room(char ***pdata, int n)
{
	*pdata = malloc((n + 1) * sizeof(char *));
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
// }
//
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
