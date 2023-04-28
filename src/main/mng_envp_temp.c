/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mng_envp_temp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:44:16 by jbernard          #+#    #+#             */
/*   Updated: 2023/04/28 13:54:34 by jbernard         ###   ########.fr       */
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
	printf("Name: %s\nValue: %s\n", envlst->name, envlst->value);
}

char	*get_fomatted_env(t_envlst *envlst)
{
	char	*line;
	
	if (envlst->value)
	{
		line = ft_strjoin(envlst->name, "=");
		if (envlst->value)
		{}
	}
	return (line);
}

char	**get_envp_from_envlst_for_env(t_envlst *envlst)
{
	char	**envp;
	char	*temp;
	int		i;
	
	i = 0;
	envp = malloc(sizeof(char *) * (ft_envlstlen(envlst)));
	while (envlst)
	{
		temp = ft_strjoin(envlst->name, "=");
		if (envlst->value)
			temp = ft_strfreejoin(temp, envlst->value);
		else
			temp = ft_strfreejoin(temp, "\'\'");
		envp[i] = temp;
		envlst = envlst->next;
		i++;
	}
	return (envp);
}

void	envlst_iter(t_envlst **envlst, void (*f)(t_envlst *))
{
	t_envlst	*curr;
	
	if (!envlst || !f)
		return ;
	curr = *envlst;
	while (curr)
	{
		f(curr);
		curr = curr->next;
	}
}