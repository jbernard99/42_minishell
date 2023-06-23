/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 13:44:33 by jbernard          #+#    #+#             */
/*   Updated: 2023/06/23 14:31:30 by jbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/*
	Exemples:
		pwd : Show current working dir
		pwd x : Show current working dir
*/

int	ft_pwd(char **args, t_envlst *envlst, int fd_out)
{
	char	pwd[PATH_MAX];

	(void)args;
	envlst = is_name_in_envlst(envlst, "PWD");
	if (envlst)
		ft_putstr_fd(envlst->value, fd_out);
	else
		ft_putstr_fd(getcwd(pwd, 999), fd_out);
	ft_putchar_fd('\n', fd_out);
	return (0);
}
