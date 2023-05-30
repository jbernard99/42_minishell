/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 12:08:53 by jbernard          #+#    #+#             */
/*   Updated: 2023/05/30 11:05:11 by jbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_envlst(t_envlst *envlst)
{
	t_envlst	*proxy;

	while (envlst)
	{
		ft_sfree(envlst->name);
		ft_sfree(envlst->value);
		proxy = envlst->next;
		ft_sfree(envlst);
		envlst = proxy;
	}
}

void	ft_end(t_cmdlst	*cmdlst, t_envlst *envlst)
{
	free_envlst(envlst);
	ft_sfree(cmdlst);
	exit(0);
}
