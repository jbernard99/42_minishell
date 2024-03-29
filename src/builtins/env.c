/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 13:42:15 by jbernard          #+#    #+#             */
/*   Updated: 2023/06/20 13:30:23 by jbernard         ###   ########.fr       */
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
	char	*val;
	char	**env;

	(void)args;
	(void)fd_out;
	i = 0;
	env = get_initiated_from_envlst(envlst);
	while (env[i])
	{
		val = get_value(env[i]);
		if (val != NULL)
			printf("%s\n", env[i]);
		ft_sfree(val);
		i++;
	}
	ft_freetabstr(env);
	return (0);
}
