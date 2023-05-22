/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 04:25:35 by jbernard          #+#    #+#             */
/*   Updated: 2023/05/22 16:52:35 by mgagnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <termios.h>
# include <errno.h>
# include <dirent.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include "../libraries/42_libft/include/libft.h"
# include "../libraries/readline/includes/readline.h"
# include "../libraries/readline/includes/history.h"

typedef struct s_envlst {
	char				*name;
	char				*value;
	int					index;
	struct s_envlst	*next;
}	t_envlst;

typedef struct s_cmdlst {
	int				flags;
	int				pipefd[2];
	char			*cmd;
	char			**token;
	t_envlst		*envlst;
	struct s_cmdlst	*next;
}		t_cmdlst;

enum	e_flags{
	PIPEI = 1 << 0,
	PIPEO = 1 << 1,
	ANDI = 1 << 2,
	ANDO = 1 << 3,
	ORI = 1 << 4,
	ORO = 1 << 5,
	QUOTE = 1 << 6,
	DQUOTE = 1 << 7,
	R_IN = 1 << 8,
	R_OUT = 1 << 9,
	APP_OUT = 1 << 10,
	HR_DOC = 1 << 11
};

// execution.c //
int			execution(t_cmdlst *cmdlst);

// execution_fork.c //
int			exec_fork(t_cmdlst *cmdlst);

// built-ins //
void		ft_cd(char **args, t_envlst *envlst, int fd_out);
void		ft_echo(char **args, t_envlst *envlst, int fd_out);
void		ft_exit(char **args, t_envlst *envlst, int fd_out);
void		ft_env(char **args, t_envlst *envlst, int fd_out);
void		ft_pwd(char **args, t_envlst *envlst, int fd_out);
void		ft_export(char **args, t_envlst *envlst, int fd_out);
void		ft_unset(char **args, t_envlst *envlst, int fd_out);

// tools.c //
int			finish_flag_set(t_cmdlst **cmdlst);
size_t		ft_strpbrk(const char *str, const char *delim, int *flags);
char		*ft_strtok(char *str, const char *delim, int *flags);
char		*ft_strldup(const char *str, size_t len);

// mng_lst.c //
void		cmdlst_delone(t_cmdlst *cmdlst, void (*del)(t_cmdlst *));
void		cmdlst_clear(t_cmdlst **cmdlst, void (*del)(t_cmdlst *));
t_cmdlst	*cmdlst_last(t_cmdlst *cmdlst);
void		cmdlst_addback(t_cmdlst **cmdlst, t_cmdlst *new_node);
t_cmdlst	*new_node(char *cmd, t_envlst *envlst);

// mng_lst2.c //
void		print_flags(int flags); // TEMPORARY
void		print_cmdlst_node(t_cmdlst *node);
void		ft_cmdlstiter(t_cmdlst **cmdlst, void (*f)(t_cmdlst *));
void		empty_lst(t_cmdlst *cmdlst);
int			lst_len(t_cmdlst *cmdlst);

// envlst_tools.c //
size_t		count_total_envlst(t_envlst *envlst);
size_t		count_initiated_envlst(t_envlst *envlst);
t_envlst	*envlst_last(t_envlst *envlst);
t_envlst	*is_name_in_envlst(t_envlst *envlst, char *name);
void		envlst_iter(t_envlst **envlst, void (*f)(t_envlst *));
void		put_envlst(t_envlst *envlst);

// envp_to_envlst.c //
char		*get_name(char *env_line);
char		*get_value(char *env_line);
t_envlst	*create_envlst_from_line(char *line);
void		create_envlst_from_envp(t_envlst **envlst, char **envp);
void		add_to_envlst(t_envlst *envlst, char *line);

// envlst_to_envp.c //
char		**get_initiated_from_envlst(t_envlst *envlst);
char		**get_all_from_envlst(t_envlst *envlst);

// cmd_parsing.c //
int			make_lst(char *input, t_cmdlst **cmdlst, t_envlst *envlst);
void		first_divide(char *input, t_cmdlst **cmdlst, t_envlst *envlst);
void		*ft_realloc(void *ptr, size_t size);
void		check_quotes(char *input, size_t *i, int *flags);

// env_var_parse.c //
char		*get_var_name(char *str);
char		*rplc_env_var(t_envlst *envlst, char *str);
int			is_there_env_var(char *str);
char		*m_get_value(t_envlst **envp, char *name);

// quotes.c //
char		*rmv_quotes(char *str);

// redirect_parsing.c //
void		scan_redirect(t_cmdlst *cmdlst);

// pipe.c //
void		pipe_it(t_cmdlst *cmdlst);
int			reset_stdin(int old_fd);
int			change_stdin(int new_fd);
int			reset_stdout(int old_fd);
int			change_stdout(int new_fd);

#endif
