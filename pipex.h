#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "libft/libft.h"

typedef struct t_args
{
	int		i;
	int		s;
	int		n;
	int		fd[2];
	int		pid1;
	int		pid2;
	int		ferr;
	int		serr;
	int		err1;
	int		err2;
	int		f_err1;
	int		f_err2;
	int		filein;
	int		fileout;
	char	**args1;
	char	**args2;
	char	**paths;
	char	**cmd_path1;
	char	**cmd_path2;
	char	*path1;
	char	*path2;
}				t_args;

int		args_false(int argc, char *argv[]);
void	setup(t_args *pdata, char *argv[], char *env[]);
void	init_data(t_args *pdata);
int		io_access(t_args *pdata, char *argv[]);
int		i_access(t_args *pdata, char *argv[]);
int		o_access(t_args *pdata, char *argv[]);
void	get_path(t_args *pdata, char *env[]);
char	**ft_split_p(const char *str, char c);
int		args1_init(t_args *pdata, char *argv[], char *env[]);
int		args2_init(t_args *pdata, char *argv[], char *env[]);
int		parse_cmds(char ***args_n, const char *args, t_args *pdata);
void	parser(char ***args_n, const char *args);
int		isin_str(const char *args);
int		get_cmd_path(t_args *pdata, char ***cmd_path, char ***args);
int		get_valid_path(t_args *pdata, char ***cmd_path, char **path);
void	add_valid_path(char *path, char ***arg);
int		process1(t_args *pdata, char *env[], char *argv[]);
int		process2(t_args *pdata, char *env[], char *argv[]);
int		pipe_setup_1(t_args *pdata, char *env[], char *argv[]);
int		pipe_setup_2(t_args *pdata, char *env[], char *argv[]);
void	struct_free(char **arr);
void	args_free(char **arr);
void	free_pdata(t_args *pdata);
void	wait_free(t_args *pdata);
void	print_debug(t_args *pdata);
void	errsub(const char *ln, const char *s, const char *err);
void	persub(const char *ln, const char *s);
void	awk_parser(const char *args, char ***prs_args, t_args *pdata);
int		first_pass(const char *args);
void	make_room(char ***pdata, int n);
void	make_sub(const char *args, char ***prs_args, t_args *pdata);
void	set_isn(t_args *pdata);

#endif
