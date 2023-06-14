/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mng_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 11:17:41 by mgagnon           #+#    #+#             */
/*   Updated: 2023/06/14 14:11:02 by mgagnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cmdlst_delone(t_cmdlst *cmdlst, void (*del)(t_cmdlst *))
{
	if (!cmdlst)
		return ;
	ft_sfree(cmdlst->outfile);
	ft_sfree(cmdlst->infile);
	cmdlst->outfile = NULL;
	cmdlst->infile = NULL;
	del(cmdlst);
	ft_sfree(cmdlst);
	cmdlst = NULL;
}

void	cmdlst_clear(t_cmdlst **cmdlst, void (*del)(t_cmdlst *))
{
	t_cmdlst	*proxy;

	if (cmdlst)
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
	new_node->cmd = cmd;
	ft_sfree(cmd);
	cmd = NULL;
	new_node->exit = 0;
	new_node->pipefd[0] = 0;
	new_node->pipefd[1] = 0;
	new_node->envlst = envlst;
	new_node->outfile = NULL;
	new_node->infile = NULL;
	new_node->next = NULL;
	new_node->dont_pipe_it = 0;
	return (new_node);
}
