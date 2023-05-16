/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mng_lst2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 20:22:14 by mgagnon           #+#    #+#             */
/*   Updated: 2023/05/15 15:21:51 by mgagnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_flags(int flags)
{
	if (flags & PIPEI)
		printf("PIPEI: ON, ");
	else
		printf("PIPEI: OFF, ");
	if (flags & PIPEO)
		printf("PIPEO: ON, ");
	else
		printf("PIPEO: OFF, ");
	if (flags & ANDI)
		printf("ANDI: ON, ");
	else
		printf("ANDI: OFF, ");
	if (flags & ANDO)
		printf("ANDO: ON, ");
	else
		printf("ANDO: OFF, ");
	if (flags & ORI)
		printf("ORI: ON, ");
	else
		printf("ORI: OFF, ");
	if (flags & ORO)
		printf("ORO: ON, ");
	else
		printf("ORO: OFF, ");
	if (flags & APP_OUT)
		printf("APP_OUT: ON, ");
	else
		printf("APP_OUT: OFF, ");
	if (flags & HR_DOC)
		printf("HR_DOC: ON, ");
	else
		printf("HR_DOC: OFF, ");
	if (flags & R_IN)
		printf("R_IN: ON, ");
	else
		printf("R_IN: OFF, ");
	if (flags & R_OUT)
		printf("R_OUT: ON\n");
	else
		printf("R_OUT: OFF\n");
}

void	print_cmdlst_node(t_cmdlst *node)
{
	int	i;

	if (!node)
		return ;
	i = 0;
	if (node->cmd)
		printf("cmd -> %s\n", node->cmd);
	while (node->token[i])
	{
		if (node->token[i] != NULL)
			printf("token[%i] -> %s\n", i, node->token[i]);
		i++;
	}
	printf("token[%i] -> %s\n", i, node->token[i]);
	print_flags(node->flags);
}

void	ft_cmdlstiter(t_cmdlst **cmdlst, void (*f)(t_cmdlst *))
{
	t_cmdlst	*cur;

	if (!cmdlst || !f)
		return ;
	cur = *cmdlst;
	while (cur)
	{
		f(cur);
		cur = cur->next;
	}
}

void	empty_lst(t_cmdlst *cmdlst)
{
	int	i;

	i = 0;
	if (cmdlst->cmd)
		free(cmdlst->cmd);
	if (cmdlst->token)
	{
		while (cmdlst->token[i])
		{
			free(cmdlst->token[i]);
			i++;
		}
	}
}

int	lst_len(t_cmdlst *cmdlst)
{
	int	i;

	i = 0;
	while (cmdlst)
	{
		i++;
		cmdlst = cmdlst->next;
	}
	return (i);
}
