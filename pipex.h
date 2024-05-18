#ifndef PIPEX_H
#define PIPEX_H

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "libft/libft.h"

typedef struct t_args
{
	int		err;
	int		err1;
	int		err2;
	int		f_err1;
	int		f_err2;
	int		filein;
	int		fileout;
	char	**args1;
	char	**args2;
	char	**paths;
	char	**cmd_path1; // all paths
	char	**cmd_path2; // 
	char	*path1;
	char	*path2;
}				t_args;

int		args_false(int argc, char *argv[]);
void	init_data(t_args *pdata);
int		io_access(t_args *pdata, char *argv[]);
int		i_access(t_args *pdata, char *argv[]);
int		o_access(t_args *pdata, char *argv[]);
void	get_path(t_args *pdata, char *env[]);
//int		get_valid_path(t_args *pdata);
char	**ft_split_p(const char *str, char c);
//void	parse_cmds(t_args *pdata, char *argv[]);
int		args1_init(t_args *pdata, char *argv[], char *env[]);
int		args2_init(t_args *pdata, char *argv[], char *env[]);

int		parse_cmds(char ***args_n, const char *args);
int		get_cmd_path(t_args *pdata, char ***cmd_path, char ***args);
//void	get_cmd_path(t_args *pdata);
int		get_valid_path(t_args *pdata, char ***cmd_path, char **path);
void	add_valid_path(char *path, char ***arg);

void	print_debug(t_args *pdata);

#endif
