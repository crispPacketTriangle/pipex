/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lworden <lworden@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:53:27 by lworden           #+#    #+#             */
/*   Updated: 2024/05/24 17:28:09 by lworden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
int		i_access(t_args *pdata, char *argv[]);
int		o_access(t_args *pdata, char *argv[]);
int		get_path(t_args *pdata, char *env[]);
char	**ft_split_p(const char *str, char c);
int		args1_init(t_args *pdata, char *argv[], char *env[]);
int		args2_init(t_args *pdata, char *argv[], char *env[]);
int		parse_cmds(char ***args_n, const char *args, t_args *pdata);
int		get_cmd_path(t_args *pdata, char ***cmd_path, char ***args);
int		get_valid_path(t_args *pdata, char ***cmd_path, char **path);
int		process1(t_args *pdata, char *env[], char *argv[]);
int		process2(t_args *pdata, char *env[], char *argv[]);
int		pipe_setup_1(t_args *pdata, char *env[], char *argv[]);
int		pipe_setup_2(t_args *pdata, char *env[], char *argv[]);
void	args_free(char **arr);
void	free_pdata(t_args *pdata);
void	wait_free(t_args *pdata);
void	errsub(const char *ln, const char *s, const char *err);
void	persub(const char *ln, const char *s);
int		awk_parser(const char *args, char ***prs_args, t_args *pdata);
int		first_pass(const char *args);
int		make_room(char ***pdata, int n);
int		make_sub(const char *args, char ***prs_args, t_args *pdata);
void	set_isn(t_args *pdata);
int		str_n(const char *str, char c);
int		str_gen(const char *str, char c, char **arr, int n);
void	free_all(char **arr);
char	*ft_substr_p(const char *s, unsigned int st, size_t len);
char	*sub(const char *s, char *ptr, unsigned int st, unsigned int size);
char	*sngl_char(const char *s, char *ptr, unsigned int st);

#endif
