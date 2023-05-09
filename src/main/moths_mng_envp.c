/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moths_mng_envp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 13:06:54 by jbernard          #+#    #+#             */
/*   Updated: 2023/05/09 10:38:42 by mgagnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//This function checks if a variable name is present in the envp
int	m_is_name_in_envp(t_envlst **envp, char *name)
{	
	t_envlst	*proxy;

	proxy = *envp;
	while (proxy)
	{
		if (strcmp(name, proxy->name) == 0)
			return (1);
		proxy = proxy->next;
	}
	return (0);
}

// This function get the value of a line found in the envp.
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
