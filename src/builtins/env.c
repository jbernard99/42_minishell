/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 13:42:15 by jbernard          #+#    #+#             */
/*   Updated: 2023/04/19 16:11:50 by jbernard         ###   ########.fr       */
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

	i = 0;
	while (env[i])
	{
		if (ft_strlen(get_value(envp[i])) > 0)
			printf("%s\n", envp[i]);
		i++;
	}
	return ;
}
