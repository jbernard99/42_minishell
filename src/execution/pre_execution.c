/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_execution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:59:42 by jbernard          #+#    #+#             */
/*   Updated: 2023/06/02 22:52:29 by jbernard         ###   ########.fr       */
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

void	remove_redirection_from_tokens(t_cmdlst *cmdlst)
{
	char	**n_token;
	size_t	i;
	int		j;

	i = ft_strtablen(cmdlst->token);
	n_token = ft_calloc(i - 2, sizeof(char*));
	i = 0;
	j = 0;
	write(1, "ok\n", 3);
	while (cmdlst->token[i])
	{
		printf("cmdlst->token[%zu] = %s\n", i, cmdlst->token[i]);
		if (ft_strcmp(cmdlst->token[i], ">>") == 0 || ft_strcmp(cmdlst->token[i], ">") == 0)
			cmdlst->outfile = ft_strdup(cmdlst->token[++i]);
		else if (ft_strcmp(cmdlst->token[i], "<<") == 0 || ft_strcmp(cmdlst->token[i], "<") == 0)
			cmdlst->infile = ft_strdup(cmdlst->token[++i]);
		else
		{
			n_token[j] = ft_strdup(cmdlst->token[i]);
			j++;
		}
		i++;
	}
	n_token[j] = NULL;
	cmdlst->token = n_token;
}

char	*get_file(t_cmdlst *cmdlst)
{
	int	i;

	i = 0;
	while (cmdlst->token[i])
	{
		if (cmdlst->flags & R_IN && ft_strcmp("<", cmdlst->token[i]) == 0)
			return (cmdlst->token[i + 1]);
		else if (cmdlst->flags & HR_DOC && ft_strcmp("<<", cmdlst->token[i]) == 0)
			return (cmdlst->token[i + 1]);
		else if (cmdlst->flags & R_OUT && ft_strcmp(">", cmdlst->token[i]) == 0)
			return (cmdlst->token[i + 1]);
		else if (cmdlst->flags & APP_OUT && ft_strcmp(">>", cmdlst->token[i]) == 0)
			return (cmdlst->token[i + 1]);
		i++;
	}
	return (NULL);
}

void	work_redirection(t_cmdlst *cmdlst)
{
	int	fds[2];

	cmdlst->outfile = get_file(cmdlst);
	check_file(cmdlst, cmdlst->outfile);
	pipe(fds);
	cmdlst->pipefd[0] = fds[0];
	cmdlst->pipefd[1] = fds[1];
	if (cmdlst->flags & R_IN && ft_tabstrcmp(cmdlst->token, "<"))
	{
		remove_redirection_from_tokens(cmdlst);
		write(1, "OK\n", 3);
		ft_cmdlstiter(&cmdlst, &print_cmdlst_node);
	}
	else if (cmdlst->flags & R_OUT && ft_tabstrcmp(cmdlst->token, ">"))
	{
		remove_redirection_from_tokens(cmdlst);
		ft_cmdlstiter(&cmdlst, &print_cmdlst_node);
	}
	else if (cmdlst->flags & APP_OUT && ft_tabstrcmp(cmdlst->token, ">>"))
	{
		remove_redirection_from_tokens(cmdlst);
		ft_cmdlstiter(&cmdlst, &print_cmdlst_node);
	}
	else if (cmdlst->flags & HR_DOC && ft_tabstrcmp(cmdlst->token, "<<"))
	{
		remove_redirection_from_tokens(cmdlst);
		ft_cmdlstiter(&cmdlst, &print_cmdlst_node);
	}
}
