/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 12:08:53 by jbernard          #+#    #+#             */
/*   Updated: 2023/06/22 13:40:39 by jbernard         ###   ########.fr       */
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

void	ft_end(t_cmdlst *cmdlst, t_envlst *envlst, int status)
{
	free_envlst(envlst);
	cmdlst_clear(&cmdlst, &empty_lst);
	exit(status);
}
