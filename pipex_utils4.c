#include "pipex.h"

int	args1_init(t_args *pdata, char *argv[], char *env[])
{
	int	err;

	err = parse_cmds(&pdata->args1, argv[2], pdata);
	if (err == 69)
		return (err);
	get_path(pdata, env);
	get_cmd_path(pdata, &pdata->cmd_path1, &pdata->args1);
	err = get_valid_path(pdata, &pdata->cmd_path1, &pdata->path1);
	if (err != 0)
	{
		return (err);
	}
	return (0);
}

int	args2_init(t_args *pdata, char *argv[], char *env[])
{
	int	err;

	err = parse_cmds(&pdata->args2, argv[3], pdata);
	if (err == 69)
		return (err);
	get_path(pdata, env);
	get_cmd_path(pdata, &pdata->cmd_path2, &pdata->args2);
	err = get_valid_path(pdata, &pdata->cmd_path2, &pdata->path2);
	if (err != 0)
	{
		return (err);
	}
	return (0);
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
	int		n;
	char	*str;

	n = ft_strlen(ln) + ft_strlen(s);
	str = ft_strjoin(ln, s);
	perror(str);
	free(str);
}
