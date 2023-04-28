/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mng_envp_temp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:44:16 by jbernard          #+#    #+#             */
/*   Updated: 2023/04/27 22:12:31 by jbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t		ft_envlstlen(t_envlst *envlst)
{
	size_t	i;

	i = 0;	
	if (envlst)
	{
		while (envlst->next)
		{
			i++;
			envlst = envlst->next;	
		}
	}
	return (i);
}

t_envlst	*envlst_last(t_envlst *envlst)
{
	if (envlst)
	{
		while (envlst->next)
			envlst = envlst->next;
	}
	return (envlst);
}

t_envlst	*create_envplst_from_line(char *line)
{
	t_envlst 	*envlst;

	envlst = ft_calloc(1, sizeof(t_envlst));
	if (!envlst)
		return (NULL);
	envlst->name = get_name(line);
	envlst->value = get_value(line);
	envlst->next = NULL;

	return (envlst);
}

void	create_envplst_from_envp(t_envlst **envlst, char **envp)
{
	int			i;
	t_envlst	*proxy;

	i = 0;
	if (envlst)
	{
		if (!*envlst)
			*envlst = create_envplst_from_line(envp[i++]);
		proxy = envlst_last(*envlst);
		while (envp[i])
		{
			proxy->next = create_envplst_from_line(envp[i]);
			proxy = proxy->next;
			i++;
		}
	}
}

void	put_envlst(t_envlst *envlst)
{
	while (envlst)
	{
		printf("Name: %s\nValue: %s\n", envlst->name, envlst->value);
		envlst = envlst->next;
	}
}

char	**get_envp_from_envlst(t_envlst *envlst)
{
	char	**envp;
	
	envp = malloc(sizeof(char *) * (ft_envlstlen(envlst)));
	while (envlst)
	{
	}
}