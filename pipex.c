#include "pipex.h"

//cd .. && make fclean && make && cd PIPEXaminator && bash all_tests.sh

// add error checking to split
void	struct_free(char **arr);
void	args_free(char **arr);
// *
//  0 = stdin        0 = stdin
//  1 = stdout  -->  1 = fd[1]
//  2 = stderr       2 = stderr
//  3 = ...			 3 = ...
//
//  > every process has it's own file descriptor table

// cc pipex.c ft_split.c ft_strjoin.c ft_strlen.c ft_substr.c pipex_utils.c ft_split_p.c
// ./a.out file.txt "ls -l" "grep" fileout.txt

void	init_data(t_args *pdata)
{
	pdata->err = 0;
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

int erro = 0;

int	main(int argc, char *argv[], char *env[])
{
	int 	fd[2];
	t_args 	pdata;

	if (args_false(argc, argv))
		return (1);
	init_data(&pdata);
	pdata.err1 = args1_init(&pdata, argv, env);
	if (pdata.err1 != 0)
		pdata.err = pdata.err1;
	pdata.err2 = args2_init(&pdata, argv, env);
	if (pdata.err2 != 0)
		pdata.err = pdata.err2;
	pdata.f_err1 = i_access(&pdata, argv);
	if (pdata.f_err1 != 0)
		pdata.err = pdata.f_err1;
	pdata.f_err2 = o_access(&pdata, argv);
	if (pdata.f_err2 != 0)
		pdata.err = pdata.f_err2;
	//print_debug(&pdata);

	dup2(pdata.filein, STDIN_FILENO);
	// create pipe by populating fd
	if (pipe(fd) == -1)
		return (1);
	// create fork, duplicating programme
	int	pid1 = fork();
	if (pid1 < 0)
		return (2);
	// child process
	if (pid1 == 0) 
	{
		// reroute the output in the file descriptor table*
		// to fd[1] (the input of the child process)
		dup2(pdata.filein, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]); // closed as not in use
		close(fd[1]); // closing duplicated version -- need some clarification on this
		if (pdata.err1 == 0 && pdata.f_err1 == 0)
			execve(pdata.args1[0], pdata.args1, env);
		if (pdata.err1 != 0)
			_exit(pdata.err1);
		_exit(pdata.f_err1);
	}

	int pid2 = fork();
	if (pid2 < 0) {
		return (3);
	}
	
	// child process 2 (grep)
	if (pid2 == 0)
	{
		// this time rerouting the input (for this process) to be fd[0]
		dup2(fd[0], STDIN_FILENO);
		dup2(pdata.fileout, STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		if (pdata.err2 == 0 && pdata.f_err2 == 0)
			execve(pdata.args2[0], pdata.args2, env);
		if (pdata.err2 != 0)
			_exit(pdata.err2);
		_exit(pdata.f_err2);
	}
	// grep will continue to wait for input until all open file descriptors
	// are closed so we must close the open fd and any fds not in use
	close(fd[0]);
	close(fd[1]);
	// if (waitpid(pid1, NULL, 0) == -1)
	// 	exit(pdata.err);
	// if (waitpid(pid2, NULL, 0) == -1)
	// 	exit(pdata.err);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);

	//printf("..\n");
	//print_debug(&pdata);

	struct_free(pdata.paths);
	pdata.paths = NULL;
	struct_free(pdata.cmd_path1);
	pdata.cmd_path1 = NULL;
	struct_free(pdata.cmd_path2);
	pdata.cmd_path2 = NULL;
	args_free(pdata.args1);
	pdata.args1 = NULL;
	args_free(pdata.args2);
	pdata.args2 = NULL;
	close(pdata.filein);
	close(pdata.fileout);
	
	//printf("..\n");
	printf("err: %d\n", pdata.err1);

	return (pdata.err);
}

void	struct_free(char **arr)
{
	int	i;

	if (arr)
	{
		//printf("not null\n");
		i = 0;
		while (arr[i])
		{
			//printf("element exists\n");
			free(arr[i]);
			i++;
		}
		free(arr);
	}
}

void	args_free(char **arr)
{
	int	i;

	if (arr)
	{
		//printf("not null\n");
		i = 1;
		while (arr[i])
		{
			//printf("element exists\n");
			free(arr[i]);
			i++;
		}
		free(arr);
	}
}
// separate out checks and return errors
int	i_access(t_args *pdata, char *argv[])
{
	// should we say != 0
	if (access(argv[1], F_OK) == -1)
	{
		printf("errno: %d\n", errno);
		return (errno);
	}
	printf("??\n");
	if (access(argv[1], R_OK) == -1)
		return (errno);
	pdata->filein = open(argv[1], O_RDONLY);
	return (0);
}

int	o_access(t_args *pdata, char *argv[])
{
	mode_t	c_umask = umask(0);
	mode_t	perm;

	umask(c_umask);
	perm = (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH) & ~c_umask;
	pdata->fileout = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, perm);
	if (access(argv[4], W_OK) == -1)
		return (errno);
	return (0);
}

int	io_access(t_args *pdata, char *argv[])
{
	mode_t	c_umask = umask(0);
	mode_t	perm;
	int		n;

	umask(c_umask);
	perm = (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH) & ~c_umask;
	if (access(argv[1], F_OK | R_OK) == -1)
		return (errno);
	pdata->fileout = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, perm);
	if (access(argv[4], W_OK) == -1)
		return (errno);
	pdata->filein = open(argv[1], O_RDONLY);
	return (0);
}

int	args_false(int argc, char *argv[])
{
	if (argc != 5)
		return (1);
	if (ft_strlen(argv[1]) == 0 || ft_strlen(argv[3]) == 0)
		return (1);
	return (0);
}

void	print_debug(t_args *pdata)
{
	int i;
	i = 0;
	while (pdata->args1[i]){
		printf("args1: %s\n", pdata->args1[i]);
		i++;
	}
	i = 0;
	while (pdata->args2[i]){
		printf("args2: %s\n", pdata->args2[i]);
		i++;
	}
	
	i = 0;
	while (pdata->cmd_path1[i]){
		printf("cmd1: %s\n", pdata->cmd_path1[i]);
		i++;
	}
	i = 0;
	while (pdata->cmd_path2[i]){
		printf("cmd2: %s\n", pdata->cmd_path2[i]);
		i++;
	}
}
