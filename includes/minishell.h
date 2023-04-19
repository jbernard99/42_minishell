/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 04:25:35 by jbernard          #+#    #+#             */
/*   Updated: 2023/04/19 12:23:44 by jbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <termios.h>
# include <errno.h>
# include <dirent.h>
# include "../libraries/42_libft/include/libft.h"
# include "../libraries/readline/includes/readline.h"
# include "../libraries/readline/includes/history.h"

typedef struct s_cmdlst {
	int				flags;
	char			*cmd;
	char			**token;
	char			***envp;
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
	DQUOTE = 1 << 7
};

char		*ft_strtok(char *str, const char *delim, int *flags);
char		*ft_strldup(const char *str, size_t len);
size_t		ft_strpbrk(const char *str, const char *delim, int *flags);
void		make_lst(char *input, t_cmdlst **cmdlst);
void		first_divide(char *input, t_cmdlst **cmdlst);
void		*ft_realloc(void *ptr, size_t size);
void		finish_flag_set(t_cmdlst **cmdlst);
void		print_flags(int flags);
void		check_quotes(char *input, size_t *i, int *flags);

/* list managing functions */
t_cmdlst	*new_node(char *cmd);
t_cmdlst	*cmdlst_last(t_cmdlst *cmdlst);
//t_cmdlst	*get_lst(void);
void		cmdlst_clear(t_cmdlst **cmdlst, void (*del)(t_cmdlst *));
void		cmdlst_delone(t_cmdlst *cmdlst, void (*del)(t_cmdlst *));
void		cmdlst_addback(t_cmdlst **cmdlst, t_cmdlst *new_node);
void		empty_lst(t_cmdlst *cmdlst);
void		ft_cmdlstiter(t_cmdlst **cmdlst, void (*f)(t_cmdlst *));
void		print_cmdlst_node(t_cmdlst *node);

// envp_tools.c //
int			is_name_in_line(char *envline, char *name);
int			is_name_in_envp(char **envp, char *name);
char		*build_envp_line(char *name, char *value);
char		*get_value(char *env_line);

// execution.c //
int 		execution(t_cmdlst *cmdlst);

// built-ins //
void		ft_cd(char *dirname);
void		ft_echo(char **args, char **env, int fd_out);
void		ft_env(char **envp);
//void		ft_export(char **args, char **envp, int fd_out);

#endif
