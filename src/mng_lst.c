/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mng_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagnon <mgagnon@student.42quebec.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 11:17:41 by mgagnon           #+#    #+#             */
/*   Updated: 2023/03/27 14:47:43 by mgagnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cmdlst_delone(t_cmdlst *cmdlst)
{
	if (!cmdlst)
		return ;
	free(cmdlst);
}

void	cmdlst_clear(t_cmdlst **cmdlst)
{
	t_cmdlst	*proxy;

	if (cmdlst)
	{
		while (*cmdlst)
		{
			proxy = (*cmdlst)->next;
			cmdlst_delone(*cmdlst);
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

t_cmdlst	*new_cmd_node(void)
{
	t_cmdlst	*new_node;

	new_node = ft_calloc(1, sizeof(t_cmdlst));
	if (!new_node)
		return (NULL);
	new_node->next = NULL;
	return (new_node);
}
