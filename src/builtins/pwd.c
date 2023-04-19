/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 13:44:33 by jbernard          #+#    #+#             */
/*   Updated: 2023/04/19 12:26:39 by mgagnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/*
	Exemples:
		pwd : Show current working dir
		pwd x : Show current working dir
*/

void	ft_pwd(char **args, char **env, int fd_out)
{
	char	*pwd;

	pwd = envp_get_value_line(env, "PWD");
	ft_putstr_fd(pwd, fd_out);
	ft_putchar_fd('\n', fd_out);
}
