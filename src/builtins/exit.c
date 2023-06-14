/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 13:42:38 by jbernard          #+#    #+#             */
/*   Updated: 2023/06/14 13:02:21 by jbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/* NOTHING DONE YET */
int	ft_exit(char **args, t_envlst *envlst, int fd_out)
{
	(void)args;
	ft_putstr_fd("exit\n", fd_out);
	ft_end(NULL, envlst);
	return (0);
}
