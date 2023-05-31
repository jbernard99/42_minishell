/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_execution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:59:42 by jbernard          #+#    #+#             */
/*   Updated: 2023/05/31 10:46:12 by jbernard         ###   ########.fr       */
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

char	*get_file(t_cmdlst *cmdlst)
{
	int	i;

	i = 0;
	while (cmdlst->token[i])
	{
		if (cmdlst->flags & R_IN && ft_strcmp("<", cmdlst->token[i]))
		{
			
			return (cmdlst->token[i + 1]);
		}
		else if (cmdlst->flags & HR_DOC && ft_strcmp("<<", cmdlst->token[i]))
			return (cmdlst->token[i + 1]);
		else if (cmdlst->flags & R_OUT && ft_strcmp(">", cmdlst->token[i]))
			return (cmdlst->token[i + 1]);
		else if (cmdlst->flags & APP_OUT && ft_strcmp(">>", cmdlst->token[i]))
			return (cmdlst->token[i + 1]);
	}
}

void	work_redirection(t_cmdlst *cmdlst)
{
	int		fds[2];
	char	*file;
	
	pipe(fds);
	if (cmdlst->flags & R_IN)
		redirect_in(fds[1], );
}
