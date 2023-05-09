/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 13:42:38 by jbernard          #+#    #+#             */
/*   Updated: 2023/05/09 11:02:27 by jbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/* NOTHING DONE YET */
void	ft_exit(char **args, t_envlst *envlst, int fd_out)
{
	(void)args;
	(void)envlst;
	// ft_putchar_fd('\n', fd_out);
	ft_putstr_fd("exit\n", fd_out);
	exit(0);
}
