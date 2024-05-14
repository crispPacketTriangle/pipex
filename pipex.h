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

typedef struct s_args
{
	int		filein;
	int		fileout;
	char	**args1;
	char	**args2;
	char	**files;
	char	**paths;
	char	**cmd_path1; // all paths
	char	**cmd_path2; // 
	char	*path1;
	char	*path2;
}				arg;

int		args_false(int argc, char *argv[]);
int		io_access(arg *pdata, char *argv[]);
void	get_path(arg *pdata, char *env[]);
int		get_valid_path(arg *pdata);
char	**ft_split_p(const char *str, char c);
void	parse_cmds(arg *pdata, char *argv[]);
int		arg_init(arg *pdata, char *argv[], char *env[]);

#endif