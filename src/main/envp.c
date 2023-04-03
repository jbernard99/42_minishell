/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 14:11:53 by jbernard          #+#    #+#             */
/*   Updated: 2023/03/28 14:31:01 by jbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	envp_remove_line(char **envp, char *name)
{
	int		i_old;
	int		i_new;
	char	**n_envp;
	if (is_name_in_envp(envp, name) >= 0)
	{
		n_envp = (char **)malloc(sizeof(char *) * (ft_strtablen(envp)));
		if (!n_envp)
			return ;
		i_old = 0;
		i_new = 0;
		while (envp[i_old])
		{
			if (!is_name_in_line(envp[i_old], name))
				n_envp[i_new++] = envp[i_old];
			else
			{
				free(envp[i_old]);
				envp[i_old] = NULL;
			}
			i_old++;
		}
		n_envp[i_new] = NULL;
		free(envp);
		envp = n_envp;
	}
}

void	envp_set_line(char **envp, char *name, char *value)
{
	int		i;
	char	*n_line;
	char	**n_envp;
	
	i = is_name_in_envp(envp, name);
	if (i >= 0)
	{
		n_line = build_envp_line(name, value);
		free(envp[i]);
		envp[i] = n_line;
	}
	if (i < 0)
	{
		i = 0;
		n_envp = (char **)malloc(sizeof(char *) * (ft_strtablen(envp) + 2));
		if (!n_envp)
			return ;
		while (envp[i])
		{
			n_envp[i] = envp[i];
			i++;
		}
		n_envp[i++] = n_line;
		n_envp[i] = NULL;
		free(envp);
		envp = n_envp;
	}
}

char	*envp_get_value_line(char **envp, char *name)
{
	char	*ret;
	int		i;

	ret = NULL;
	i = is_name_in_envp(envp, name);
	if (i >= 0)
	{
		ret = &envp[i][ft_strlen(name) + 1];
		return (ret);
	}
	return (ret);
}