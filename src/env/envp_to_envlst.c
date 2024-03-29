/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_to_envlst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:44:16 by jbernard          #+#    #+#             */
/*   Updated: 2023/06/22 14:39:29 by jbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_name(char *env_line)
{
	size_t	i;

	i = 0;
	while (env_line[i] != '=' && env_line[i] != '\0')
		i++;
	return (ft_strldup(env_line, i));
}

char	*get_value(char *env_line)
{
	size_t	i;
	char	*ret;

	i = 0;
	if (!ft_strchr(env_line, '='))
		return (NULL);
	while (env_line[i] != '=')
		i++;
	if (!env_line[i + 1])
	{
		ret = ft_strdup("\"\"");
		return (ret);
	}
	i++;
	ret = ft_strdup(&env_line[i]);
	if (ret[0] == '\"' || ret[0] == '\'')
		ret = rmv_quotes(ret);
	return (ret);
}

t_envlst	*create_envlst_from_line(char *line)
{
	t_envlst	*envlst;

	envlst = ft_calloc(1, sizeof(t_envlst));
	if (!envlst)
		return (NULL);
	envlst->name = get_name(line);
	envlst->value = get_value(line);
	envlst->next = NULL;
	return (envlst);
}

void	create_envlst_from_envp(t_envlst **envlst, char **envp)
{
	int			i;
	t_envlst	*proxy;

	i = 0;
	if (envlst)
	{
		if (!*envlst)
			*envlst = create_envlst_from_line(envp[i++]);
		proxy = envlst_last(*envlst);
		while (envp[i])
		{
			proxy->next = create_envlst_from_line(envp[i]);
			proxy = proxy->next;
			i++;
		}
		proxy->next = create_envlst_from_line("?=0");
	}
}

void	add_to_envlst(t_envlst *envlst, char *line)
{
	t_envlst	*proxy;
	char		*name;
	char		*val;

	name = get_name(line);
	proxy = is_name_in_envlst(envlst, name);
	ft_sfree(name);
	if (!proxy)
	{
		envlst = envlst_last(envlst);
		envlst->next = create_envlst_from_line(line);
	}
	else
	{
		val = get_value(line);
		if (val != NULL)
		{
			ft_sfree(proxy->value);
			proxy->value = ft_strdup(val);
			ft_sfree(val);
		}
	}
}
