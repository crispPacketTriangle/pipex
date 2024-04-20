#ifndef PIPEX_H
#define PIPEX_H

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>

typedef struct s_args
{
	char	**args1;
	char	**args2;
	char	**files;
	char	**paths;
	char	**cmd_path1; // all paths
	char	**cmd_path2; // 
	char	*path1;
	char	*path2;
}				arg;

void	get_path(arg *pdata, char *env[]);
int		get_valid_path(arg *pdata);
char	**ft_split(const char *str, char c);
char	**ft_split_p(const char *str, char c);
char	*ft_substr(const char *s, unsigned int st, size_t len);
char	*ft_strjoin(const char *s1, const char *s2);
size_t	ft_strlen(const char *str);
void	parse_cmds(arg *pdata, char *argv[]);
void	arg_init(arg *pdata, char *argv[], char *env[]);

#endif