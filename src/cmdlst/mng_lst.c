/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mng_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 11:17:41 by mgagnon           #+#    #+#             */
/*   Updated: 2023/08/31 14:01:23 by mgagnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cmdlst_delone(t_cmdlst *cmdlst, void (*del)(t_cmdlst *))
{
	int	i;

	i = 0;
	if (!cmdlst)
		return ;
	ft_sfree(cmdlst->outfile);
	ft_sfree(cmdlst->infile);
	cmdlst->outfile = NULL;
	cmdlst->infile = NULL;
	if (cmdlst->eof && cmdlst->eof[i])
	{
		while (cmdlst->eof[i])
		{
			free(cmdlst->eof[i]);
			cmdlst->eof[i] = NULL;
			i++;
		}
	}
	free(cmdlst->eof);
	cmdlst->eof = NULL;
	del(cmdlst);
	ft_sfree(cmdlst);
	cmdlst = NULL;
}

void	cmdlst_clear(t_cmdlst **cmdlst, void (*del)(t_cmdlst *))
{
	t_cmdlst	*proxy;

	if (*cmdlst != NULL)
	{
		while (*cmdlst)
		{
			proxy = (*cmdlst)->next;
			cmdlst_delone(*cmdlst, del);
			(*cmdlst) = proxy;
		}
	}
}

t_cmdlst	*cmdlst_last(t_cmdlst *cmdlst)
{
	if (cmdlst)
	{
		while (cmdlst->next)
			cmdlst = cmdlst->next;
	}
	return (cmdlst);
}

void	cmdlst_addback(t_cmdlst **cmdlst, t_cmdlst *new_node)
{
	t_cmdlst	*proxy;

	if (cmdlst)
	{
		if (*cmdlst == NULL)
			*cmdlst = new_node;
		else
		{
			proxy = cmdlst_last(*(cmdlst));
			proxy->next = new_node;
		}
	}
}

t_cmdlst	*new_node(char *cmd, t_envlst *envlst)
{
	t_cmdlst	*new_node;

	new_node = ft_calloc(1, sizeof(t_cmdlst));
	if (!new_node)
		return (NULL);
	new_node->cmd = ft_strdup(cmd);
	ft_sfree(cmd);
	cmd = NULL;
	new_node->exit = 0;
	new_node->pipefd[0] = 0;
	new_node->pipefd[1] = 0;
	new_node->envlst = envlst;
	new_node->outfile = NULL;
	new_node->infile = NULL;
	new_node->eof = NULL;
	new_node->next = NULL;
	new_node->dont_pipe_it = 0;
	return (new_node);
}
