/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlst_to_envp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:11:12 by jbernard          #+#    #+#             */
/*   Updated: 2023/05/08 11:27:04 by jbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_formatted_env_var(t_envlst *envlst)
{
	char	*line;

	if (envlst->value != NULL)
	{
		line = ft_strjoin(envlst->name, "=");
		if (ft_strcmp(envlst->value, "\"\"") != 0)
			line = ft_strfreejoin(line, envlst->value);
	}
	else
		return (NULL);
	return (line);
}

char	**get_initiated_from_envlst(t_envlst *envlst)
{
	char	**envp;
	char	*line;
	int 	i;

	i = 0;
	envp = ft_calloc(count_initiated_envlst(envlst) + 1, sizeof(char *));
	while (envlst)
	{
		line = get_formatted_env_var(envlst);
		if (line)
		{
			envp[i] = line;
			i++;
		}
		envlst = envlst->next;
	}
	envp[i] = NULL;

	return (envp);
}

char	*get_formatted_exp_var(t_envlst *envlst)
{
	char	*line;

	if (envlst->value != NULL)
	{
		line = ft_strjoin(envlst->name, "=");
		line = ft_strfreejoin(line, "\"");
		if (ft_strcmp(envlst->value, "\"\"") != 0)
			line = ft_strfreejoin(line, envlst->value);
		line = ft_strfreejoin(line, "\"");
		return (line);
	}
	else
		return (ft_strdup(envlst->name));
}

char	**get_all_from_envlst(t_envlst *envlst)
{
	char	**envp;
	char	*line;
	int		i;

	i = 0;
	envp = ft_calloc(count_total_envlst(envlst) + 2, sizeof(char *));
	while (envlst)
	{
		line = get_formatted_exp_var(envlst);
		envp[i] = line;
		i++;
		envlst = envlst->next;
	}
	envp[i] = NULL;
	return (envp);
}