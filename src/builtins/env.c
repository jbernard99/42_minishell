/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 13:42:15 by jbernard          #+#    #+#             */
/*   Updated: 2023/04/19 17:07:42 by jbernard         ###   ########.fr       */
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

void	ft_env(char **args, char **env, int fd_out)
{
	int	i;

	(void)args;
	(void)fd_out;
	i = 0;
	while (env[i])
	{
		if (ft_strlen(get_value(env[i])) > 0)
			printf("%s\n", env[i]);
		i++;
	}
	return ;
}
