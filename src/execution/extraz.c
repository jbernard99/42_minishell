/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extraz.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 11:24:11 by jbernard          #+#    #+#             */
/*   Updated: 2023/08/23 14:25:20 by mgagnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	tell_me_why(int *i, char *file, char *type, t_cmdlst *cmdlst)
{
	if (ft_strcmp(type, "<<") != 0 && check_file(file, type) == 1)
	{
		remove_redirection_from_tokens(cmdlst);
		*i = -1;
	}
	else if (ft_strcmp(type, "<<") == 0)
	{
		remove_redirection_from_tokens(cmdlst);
		*i = -1;
	}
	else
	{
		printf("minishell: syntax error: unexpected token\n");
		close(cmdlst->red_fd[0]);
		close(cmdlst->red_fd[1]);
		return (0);
	}
	return (1);
}

char	*get_type(char *token)
{
	if (ft_strcmp("<", token) == 0)
		return (token);
	else if (ft_strcmp("<<", token) == 0)
		return (token);
	else if (ft_strcmp(">", token) == 0)
		return (token);
	else if (ft_strcmp(">>", token) == 0)
		return (token);
	return (NULL);
}

int	token_is_redirection(char *token)
{
	if (ft_strcmp(token, "<") == 0)
		return (1);
	else if (ft_strcmp(token, "<<") == 0)
		return (1);
	else if (ft_strcmp(token, ">") == 0)
		return (1);
	else if (ft_strcmp(token, ">>") == 0)
		return (1);
	return (0);
}
