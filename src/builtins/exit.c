/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 13:42:38 by jbernard          #+#    #+#             */
/*   Updated: 2023/06/19 16:56:20 by mgagnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/* NOTHING DONE YET */
int	ft_exit(char **args, t_envlst *envlst, int fd_out)
{
	int	argc;
	int	ret;

	(void)envlst;
	argc = ft_strtablen(args);
	if (argc > 1)
		ret = ft_atoi(args[1]);
	else
		ret = 0;
	ft_putstr_fd("exit\n", fd_out);
	return (ret);
}
