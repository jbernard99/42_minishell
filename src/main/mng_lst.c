/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mng_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 11:17:41 by mgagnon           #+#    #+#             */
/*   Updated: 2023/04/03 15:38:08 by jbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"	

void	ft_bzero(void *str, size_t n)
{
	while (n--)
		*(char *)str++ = 0;
}

void	*ft_calloc(size_t nb, size_t size)
{
	void	*ptr;

	ptr = malloc(nb * size);
	if (!ptr)
		return (0);
	ft_bzero(ptr, nb * size);
	return (ptr);
}

void	cmdlst_delone(t_cmdlst *cmdlst)
{
	if (!cmdlst)
		return ;
	free(cmdlst);
}

t_cmdlst	*get_lst(void)
{
	static t_cmdlst	*cmdlst = NULL;

	return (cmdlst);
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

t_cmdlst	*new_cmd_node(char *cmd)
{
	t_cmdlst	*new_node;

	new_node = ft_calloc(1, sizeof(t_cmdlst)); 
	if (!new_node)
		return (NULL);
	new_node->cmd = cmd;
	new_node->next = NULL;
	return (new_node);
}