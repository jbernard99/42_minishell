/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 13:42:38 by jbernard          #+#    #+#             */
/*   Updated: 2023/05/16 14:03:22 by jbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/* NOTHING DONE YET */
void	ft_exit(char **args, t_envlst *envlst, int fd_out)
{
	(void)args;
	(void)envlst;
	ft_putstr_fd("exit\n", fd_out);
	exit(0);
}
