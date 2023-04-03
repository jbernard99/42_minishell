/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 04:25:35 by jbernard          #+#    #+#             */
/*   Updated: 2023/04/03 15:35:14 by jbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <termios.h>
#include <errno.h>
#include "../libraries/42_libft/include/libft.h"
#include "../libraries/readline/includes/readline.h"
#include "../libraries/readline/includes/history.h"

typedef struct s_cmdlst {
	int			flags;
	char			*cmd;
	char			**token;
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

// tools.c
char	*ft_strtok(char *str, const char *delim, int *flags);

//envp.c
void	envp_remove_line(char **envp, char *name);
void	envp_set_line(char **envp, char *name, char *value);
char	*envp_get_value_line(char **envp, char *name);

// envp_tools.c
int		is_name_in_line(char *envline, char *name);
int		is_name_in_envp(char **envp, char *name);
char	*build_envp_line(char *name, char *value);
char	*get_name(char *env_line);
char	*get_value(char *env_line);
void	put_envp(char **envp); // TEMPORARY

// mng_lst.c
t_cmdlst	*get_lst(void);