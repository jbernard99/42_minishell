/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 04:25:35 by jbernard          #+#    #+#             */
/*   Updated: 2023/03/28 12:49:48 by mgagnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
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
	PIPE = 1 << 0,
	AND = 1 << 1,
	OR = 1 << 2,
	QUOTE = 1 << 3,
	DQUOTE = 1 << 4
};

char	*ft_strtok(char *str, const char *delim);

/* list managing functions */
t_cmdlst	*new_cmd_node(char *cmd);
void	cmdlst_addback(t_cmdlst **cmdlst, t_cmdlst *new_node);
t_cmdlst	*cmdlst_last(t_cmdlst *cmdlst);
void	cmdlst_clear(t_cmdlst **cmdlst);
void	cmdlst_delone(t_cmdlst *cmdlst);
t_cmdlst	*get_lst(void);

char	*ft_strldup(const char *str, size_t len);
void	first_divide(char *input);
