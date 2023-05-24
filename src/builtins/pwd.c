/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 13:44:33 by jbernard          #+#    #+#             */
/*   Updated: 2023/05/24 14:35:03 by jbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/*
	Exemples:
		pwd : Show current working dir
		pwd x : Show current working dir
*/

void	ft_pwd(char **args, t_envlst *envlst, int fd_out)
{
	(void)args;
	ft_putstr_fd(is_name_in_envlst(envlst, "PWD")->value, fd_out);
	ft_putchar_fd('\n', fd_out);
}
