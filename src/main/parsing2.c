/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagnon <mgagnon@student.42quebec.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 12:09:57 by mgagnon           #+#    #+#             */
/*   Updated: 2023/05/01 09:07:30 by mgagnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_var_name(char *str)
{
	char	*name;
	int	i;

	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	name = ft_strldup(str, i);
	return (name);
}

char	*rplc_env_var(t_envlst *envplst, char *str)
{
	int	i;
	char	*old;
	char	*var;
	char	*replacement;

	i = 0;
	replacement = NULL;
	while (str[i] != '$')
		i++;
	var = get_var_name(&str[++i]);
	if (m_is_name_in_envp(&envplst, var))
		replacement = ft_strdup(m_get_value(&envplst, var));
	free(var);
	old = ft_strldup(str, --i);
	var = ft_strjoinfree(old, replacement);
	while (str[i] && str[i] != ' ')
		i++;
	if (!str[i])
	{
		free(str);
		return (var);
	}
	replacement = ft_strjoinfree(var, &str[i]);
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
