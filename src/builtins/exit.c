/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 13:42:38 by jbernard          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/05/16 14:03:22 by jbernard         ###   ########.fr       */
=======
/*   Updated: 2023/05/16 15:17:04 by mgagnon          ###   ########.fr       */
>>>>>>> master
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/* NOTHING DONE YET */
void	ft_exit(char **args, t_envlst *envlst, int fd_out)
{
	(void)args;
<<<<<<< HEAD
	(void)envlst;
=======
	(void)envlst	;
	(void)fd_out;
	sigquit_handle();
	// ft_putchar_fd('\n', fd_out);
>>>>>>> master
	ft_putstr_fd("exit\n", fd_out);
	exit(0);
}
