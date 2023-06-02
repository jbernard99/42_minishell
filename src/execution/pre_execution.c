/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_execution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:59:42 by jbernard          #+#    #+#             */
/*   Updated: 2023/06/02 16:59:37 by jbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	work_env_vars_calls(t_cmdlst *cmdlst)
{
	int	i;

	while (cmdlst)
	{
		i = 0;
		while (cmdlst->token[i])
		{
			if (cmdlst->token[i][0] != '\'')
			{
				cmdlst->token[i] = rmv_quotes(cmdlst->token[i]);
				while (is_there_env_var(cmdlst->token[i]) != 0)
					cmdlst->token[i] = rplc_env_var(cmdlst->envlst, \
						cmdlst->token[i]);
			}
			else
				cmdlst->token[i] = rmv_quotes(cmdlst->token[i]);
			i++;
		}
		cmdlst = cmdlst->next;
	}
}
void	remove_redirection_from_tokens(char **token)
{
	char	**n_token;
	size_t	i;
	int		j;
	int		next_is_file;	

	next_is_file = 0;
	i = ft_strtablen(token);
	n_token = ft_calloc(i - 2, sizeof(char*));
	j = 0;
	while (token[i])
	{
		if (ft_strcmp(token[i], "<") == 0 || ft_strcmp(token[i], ">") == 0)
			i++;
		else if (ft_strcmp(token[i], "<<") == 0 || ft_strcmp(token[i], ">>") == 0)
			i++;
		else
		{
			n_token[j] = token[i];
			j++;
		}
		i++;
	}
}

char	*ft_tabstrcmp(char **tab, char *str)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (tab[i])
	{
		j = 0;
		if (ft_strcmp(tab[i], str) == 0)
			return tab[i];
	}
	return (0);
}

char	*get_file(t_cmdlst *cmdlst)
{
	int	i;

	i = 0;
	while (cmdlst->token[i])
	{
		if (cmdlst->flags & R_IN && ft_strcmp("<", cmdlst->token[i]))
			return (cmdlst->token[i + 1]);
		else if (cmdlst->flags & HR_DOC && ft_strcmp("<<", cmdlst->token[i]))
			return (cmdlst->token[i + 1]);
		else if (cmdlst->flags & R_OUT && ft_strcmp(">", cmdlst->token[i]))
			return (cmdlst->token[i + 1]);
		else if (cmdlst->flags & APP_OUT && ft_strcmp(">>", cmdlst->token[i]))
			return (cmdlst->token[i + 1]);
		i++;
	}
	return (NULL);
}

void	work_redirection(t_cmdlst *cmdlst)
{
	int		fds[2];
	
	pipe(fds);
	if (cmdlst->flags & R_IN && ft_tabstrchr(cmdlst->token, ">"))
	{
		redirect_in(fds[1], get_file(cmdlst));
		remove_redirection_from_tokens(cmdlst->token);
	}
	else if (cmdlst->flags & R_OUT && ft_tabstrchr(cmdlst->token, "<"))
	{
		redirect_out(fds[0], get_file(cmdlst));
		write(1, "in redirect out\n", 16);
		remove_redirection_from_tokens(cmdlst->token);
		cmdlst->flags &= ~R_OUT;
		cmdlst->dont_pipe_it = 1;
	}
	else if (cmdlst->flags & APP_OUT)
	{
		append(fds[0], get_file(cmdlst));
		remove_redirection_from_tokens(cmdlst->token);
		cmdlst->flags &= ~APP_OUT;
		cmdlst->dont_pipe_it = 1;
	}
	close(fds[0]);
	close(fds[1]);
	scan_redirect(cmdlst);
}
