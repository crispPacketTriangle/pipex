#include "pipex.h"
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



int	main(int argc, char *argv[], char *env[])
{
	if (argc != 5)
		return (1);

	int fd[2];
	arg pdata;
	arg_init(&pdata, argv, env);

	// char	**args1;
	// char	**args2;
	// char	**files;
	// char	**paths;
	// char	**cmd_path1;
	// char	**cmd_path2;

	int	i;
	i = 0;
	while (pdata.cmd_path1[i]){
		printf("cmd1: %s\n", pdata.cmd_path1[i]);
		i++;
	}
	i = 0;
	while (pdata.cmd_path2[i]){
		printf("cmd2: %s\n", pdata.cmd_path2[i]);
		i++;
	}
	//printf("path1: %s\n", pdata.path1);
	//printf("path2: %s\n", pdata.path2);

	//char	*args[] = {"/bin/ls", "-l", NULL};
	//char	*args2[] = {"/bin/grep", "f", NULL};

	//return(0);

	int		file = open("file.txt", O_RDONLY);
	int		fileout = open("fileout.txt", O_WRONLY);
	dup2(file, STDIN_FILENO);

	// create pipe by populating fd
	if (pipe(fd) == -1) {
		return (1);
	}
	
	// create fork, duplicating programme
	int	pid1 = fork();
	if (pid1 < 0) {
		return (2);
	}
	
	// child process
	if (pid1 == 0) {
		// reroute the output in the file descriptor table*
		// to fd[1] (the input of the child process)
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]); // closed as not in use
		close(fd[1]); // closing duplicated version -- need some clarification on this
		// execute ls -l command
		execve(pdata.args1[0], pdata.args1, NULL);
		//execve(args[0], args, NULL);
	}
	int pid2 = fork();
	if (pid2 < 0) {
		return (3);
	}
	
	// child process 2 (grep)
	if (pid2 == 0) {
		// this time rerouting the input (for this process) to be fd[0]
		dup2(fd[0], STDIN_FILENO);
		dup2(fileout, STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execve(pdata.args2[0], pdata.args2, NULL);
		//execve(args2[0], args2, NULL);
	}
	// grep will continue to wait for input until all open file descriptors
	// are closed so we must close the open fd and any fds not in use
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);

	struct_free(pdata.paths);
	pdata.paths = NULL;
	struct_free(pdata.cmd_path1);
	pdata.cmd_path1 = NULL;
	struct_free(pdata.cmd_path2);
	pdata.cmd_path2 = NULL;
	// free(pdata.path1);
	// pdata.path1 = NULL;
	// free(pdata.path2);
	// pdata.path2 = NULL;

	args_free(pdata.args1);
	pdata.args1 = NULL;
	args_free(pdata.args2);
	pdata.args2 = NULL;
	close(file);
	close(fileout);
}

void	struct_free(char **arr)
{
	int	i;

	if (*arr)
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

void	args_free(char **arr)
{
	int	i;

	if (*arr)
	{
		i = 1;
		while (arr[i])
		{
			free(arr[i]);
			i++;
		}
		free(arr);
	}
}
