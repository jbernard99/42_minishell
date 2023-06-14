/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 12:08:53 by jbernard          #+#    #+#             */
/*   Updated: 2023/06/14 14:07:51 by mgagnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_envlst(t_envlst *envlst)
{
	t_envlst	*proxy;

	while (envlst)
	{
		printf("Freeing : %s, ", envlst->name);
		printf("%s\n", envlst->value);
		ft_sfree(envlst->name);
		ft_sfree(envlst->value);
		proxy = envlst->next;
		ft_sfree(envlst);
		envlst = proxy;
	}
}
