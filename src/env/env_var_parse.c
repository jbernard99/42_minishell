/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 12:09:57 by mgagnon           #+#    #+#             */
/*   Updated: 2023/06/12 12:17:56 by mgagnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h>

char	*get_var_name(char *str)
{
	char	*name;
	int		i;

	i = 0;
	while (ft_isalpha(str[i]) || str[i] == '_' || str[i] == '?')
		i++;
	name = ft_strldup(str, i);
	return (name);
}

char	*rplc_env_var(t_envlst *envlst, char *str)
{
	int		i;
	char	*old;
	char	*var;
	char	*replacement;

	i = 0;
	replacement = NULL;
	while (str[i] != '$')
		i++;
	var = get_var_name(&str[++i]);
	if (is_name_in_envlst(envlst, var) != NULL)
		replacement = m_get_value(&envlst, var);
	ft_sfree(var);
	old = ft_strldup(str, --i);
	var = ft_strfreejoinfree(old, replacement);
	while (str[i] == '$' || str[i] == '?' || ft_isalpha(str[i]))
		i++;
	if (!str[i])
	{
		ft_sfree(str);
		return (var);
	}
	replacement = ft_strfreejoin(var, &str[i]);
	ft_sfree(str);
	return (replacement);
}

int	is_there_env_var(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

char	*m_get_value(t_envlst **envlst, char *name)
{
	t_envlst	*proxy;
	char		*ret;

	proxy = *envlst;
	while (proxy)
	{
		if (ft_strcmp(name, proxy->name) == 0)
		{
			ret = strdup(proxy->value);
			return (ret);
		}
		proxy = proxy->next;
	}
	return (NULL);
}
