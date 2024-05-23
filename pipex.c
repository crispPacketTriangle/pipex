#include "pipex.h"

// adjust line numbers once header added

int	main(int argc, char *argv[], char *env[])
{
	t_args	pdata;

	if (args_false(argc, argv))
		return (1);
	setup(&pdata, argv, env);
	dup2(pdata.filein, STDIN_FILENO);
	if (pipe(pdata.fd) == -1)
		return (1);
	pdata.pid1 = fork();
	if (pdata.pid1 < 0)
		return (2);
	if (pdata.pid1 == 0)
		exit(pipe_setup_1(&pdata, env, argv));
	pdata.pid2 = fork();
	if (pdata.pid2 < 0)
		return (3);
	if (pdata.pid2 == 0)
		exit(pipe_setup_2(&pdata, env, argv));
	wait_free(&pdata);
	return (WEXITSTATUS(pdata.serr));
}

void	init_data(t_args *pdata)
{
	pdata->ferr = 0;
	pdata->serr = 0;
	pdata->err1 = 0;
	pdata->err2 = 0;
	pdata->f_err1 = 0;
	pdata->f_err2 = 0;
	pdata->args1 = NULL;
	pdata->args2 = NULL;
	pdata->paths = NULL;
	pdata->cmd_path1 = NULL;
	pdata->cmd_path2 = NULL;
	pdata->filein = -1;
	pdata->fileout = -1;
}

int	i_access(t_args *pdata, char *argv[])
{
	if (access(argv[1], F_OK) == -1)
	{
		persub("pipex: line 46: ", argv[1]);
		return (1);
	}
	if (access(argv[1], R_OK) == -1)
	{
		persub("pipex: line 51: ", argv[1]);
		return (1);
	}
	pdata->filein = open(argv[1], O_RDONLY);
	return (0);
}

int	o_access(t_args *pdata, char *argv[])
{
	mode_t	c_umask;
	mode_t	perm;

	c_umask = umask(0);
	umask(c_umask);
	perm = (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP
			| S_IROTH | S_IWOTH) & ~c_umask;
	pdata->fileout = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, perm);
	if (pdata->fileout == -1)
	{
		persub("pipex: line 70: ", argv[4]);
		return (1);
	}
	return (0);
}

int	args_false(int argc, char *argv[])
{
	if (argc < 5)
	{
		ft_printf("Error: Invalid input\n");
		return (1);
	}
	if (ft_strlen(argv[1]) == 0 || ft_strlen(argv[4]) == 0)
	{
		ft_printf("Error: Invalid input\n");
		return (1);
	}
	if (argc > 5)
	{
		ft_printf("Error: Invalid input\n");
		return (1);
	}
	return (0);
}
