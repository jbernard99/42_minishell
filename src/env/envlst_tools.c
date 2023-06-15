/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlst_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 10:58:07 by jbernard          #+#    #+#             */
/*   Updated: 2023/06/15 12:20:55 by jbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	count_total_envlst(t_envlst *envlst)
{
	size_t	i;

	i = 0;
	if (envlst)
	{
		while (envlst->next)
		{
			i++;
			envlst = envlst->next;
		}
	}
	return (i);
}

size_t	count_initiated_envlst(t_envlst *envlst)
{
	size_t	i;

	i = 0;
	if (envlst)
	{
		while (envlst->next)
		{
			if (envlst->value != NULL)
				i++;
			envlst = envlst->next;
		}
	}
	return (i);
}

t_envlst	*envlst_last(t_envlst *envlst)
{
	if (envlst)
	{
		while (envlst->next)
			envlst = envlst->next;
	}
	return (envlst);
}

t_envlst	*is_name_in_envlst(t_envlst *envlst, char *name)
{
	while (envlst)
	{
		if (ft_strcmp(name, envlst->name) == 0)
			return (envlst);
		else
			envlst = envlst->next;
	}
	return (NULL);
}

void	envlst_iter(t_envlst **envlst, void (*f)(t_envlst *))
{
	t_envlst	*curr;

	if (!envlst || !f)
		return ;
	curr = *envlst;
	while (curr)
	{
		f(curr);
		curr = curr->next;
	}
}
