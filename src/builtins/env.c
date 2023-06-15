/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 13:42:15 by jbernard          #+#    #+#             */
/*   Updated: 2023/06/07 15:15:44 by mgagnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Exemples: 
			env : prints env variables without uninitiated vars
			env {invalid folder} :	env: {invalid folder}: No such file or directory
			env {valid folder} :	env: {valid folder}: Permission denied 
			                                            EVEN WITH CHMOD 777?
			env {valid file} 	: Nothing, unknown???
*/

#include "../../includes/minishell.h"

int	ft_env(char **args, t_envlst *envlst, int fd_out)
{
	int		i;
	char	**env;

	(void)args;
	(void)fd_out;
	i = 0;
	env = get_initiated_from_envlst(envlst);
	while (env[i])
	{
		if (get_value(env[i]))
			printf("%s\n", env[i]);
		i++;
	}
	return (errno);
}
