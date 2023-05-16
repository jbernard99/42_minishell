/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagnon <mgagnon@student.42quebec.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 12:09:57 by mgagnon           #+#    #+#             */
/*   Updated: 2023/05/09 11:18:29 by mgagnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h>

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

char	*rplc_env_var(t_envlst *envlst, char *str)
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
	if (is_name_in_envlst(envlst, var) != NULL)
		replacement = m_get_value(&envlst, var);
	free(var);
	old = ft_strldup(str, --i);
	printf("old -> %s\n", old);
	var = ft_strjoinfree(old, replacement);
	printf("var -> %s\n", var);
	while (str[i] && str[i] != ' ')
		i++;
	if (!str[i])
	{
		free(str);
		return (var);
	}
	replacement = ft_strjoin(var, &str[i]);
	free(var);
	free(str);
	printf("replacement -> %s\n", replacement);
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
