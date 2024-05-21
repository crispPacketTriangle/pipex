#include "pipex.h"

int	main(int argc, char *argv[], char *env[])
{
	t_args 	pdata;

	if (args_false(argc, argv))
		return (1);
	setup(&pdata, argv, env);

	//print_debug(&pdata);
	//return (0);

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

}


int	i_access(t_args *pdata, char *argv[])
{
	if (access(argv[1], F_OK) == -1)
	{
		persub("pipex: line 52: ", argv[1]); // adj line number after norm
		return (1);
	}
	if (access(argv[1], R_OK) == -1)
	{
		persub("pipex: line 57: ", argv[1]); // adj line number after norm
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
		persub("pipex: line 70: ", argv[4]); // adj line number after norm
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

void	print_debug(t_args *pdata)
{
	int	i;

	i = 0;
	while (pdata->args1[i])
	{
		printf("args1: %s\n", pdata->args1[i]);
		i++;
	}
	i = 0;
	while (pdata->args2[i])
	{
		printf("args2: %s\n", pdata->args2[i]);
		i++;
	}
	i = 0;
	while (pdata->cmd_path1[i])
	{
		printf("cmd1: %s\n", pdata->cmd_path1[i]);
		i++;
	}
	i = 0;
	while (pdata->cmd_path2[i])
	{
		printf("cmd2: %s\n", pdata->cmd_path2[i]);
		i++;
	}
}
//
// void	free_pdata(t_args *pdata)
// {
// 	struct_free(pdata->paths);
// 	pdata->paths = NULL;
// 	struct_free(pdata->cmd_path1);
// 	pdata->cmd_path1 = NULL;
// 	struct_free(pdata->cmd_path2);
// 	pdata->cmd_path2 = NULL;
// 	args_free(pdata->args1);
// 	pdata->args1 = NULL;
// 	args_free(pdata->args2);
// 	pdata->args2 = NULL;
// 	close(pdata->filein);
// 	close(pdata->fileout);
// }
//
// void	setup(t_args *pdata, char *argv[], char *env[])
// {
// 	init_data(pdata);
// 	pdata->err1 = args1_init(pdata, argv, env);
// 	pdata->err2 = args2_init(pdata, argv, env);
// 	pdata->f_err1 = i_access(pdata, argv);
// 	pdata->f_err2 = o_access(pdata, argv);
// }
//
// int	process1(t_args *pdata, char *env[])
// {
// 	if (pdata->err1 == 0 && pdata->f_err1 == 0)
// 		execve(pdata->args1[0], pdata->args1, env);
// 	if (pdata->err1 == 69)
// 		return (0);
// 	if (pdata->f_err1 != 0)
// 	{
// 		perror("error: ");
// 		return (pdata->f_err1);
// 	}
// 	if (pdata->err1 == 127)
// 	{
// 		write(2, "command not found\n", 18);
// 		return (pdata->err1);
// 	}
// 	perror("error: ");
// 	return (pdata->err1);
// }
//
// int	process2(t_args *pdata, char *env[])
// {
// 	if (pdata->err2 == 0 && pdata->f_err2 == 0)
// 		execve(pdata->args2[0], pdata->args2, env);
// 	if (pdata->err2 == 69)
// 		return (0);
// 	if (pdata->err2 == 127)
// 	{
// 		write(2, "command not found\n", 18);
// 		return (pdata->err2);
// 	}
// 	if (pdata->err2 != 0)
// 	{
// 		perror("error: ");
// 		return (pdata->err2);
// 	}
// 	perror("error");
// 	return (pdata->f_err2);
// }
//
// void	wait_free(t_args *pdata)
// {
// 	close(pdata->fd[0]);
// 	close(pdata->fd[1]);
// 	waitpid(pdata->pid1, &pdata->ferr, 0);
// 	waitpid(pdata->pid2, &pdata->serr, 0);
// 	free_pdata(pdata);
// }
//
// int	pipe_setup_1(t_args *pdata, char *env[])
// {
// 	dup2(pdata->filein, STDIN_FILENO);
// 	dup2(pdata->fd[1], STDOUT_FILENO);
// 	close(pdata->fd[0]);
// 	close(pdata->fd[1]);
// 	return (process1(pdata, env));
// }
//
// int	pipe_setup_2(t_args *pdata, char *env[])
// {
// 	dup2(pdata->fd[0], STDIN_FILENO);
// 	dup2(pdata->fileout, STDOUT_FILENO);
// 	close(pdata->fd[0]);
// 	close(pdata->fd[1]);
// 	return (process2(pdata, env));
// }
