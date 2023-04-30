/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mng_envp_temp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:44:16 by jbernard          #+#    #+#             */
/*   Updated: 2023/04/29 19:19:48 by jbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t		count_total_envlst(t_envlst *envlst)
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

size_t		count_initiated_envlst(t_envlst *envlst)
{
	size_t	i;

	i = 0;	
	if (envlst)
	{
		while (envlst->next)
		{
			if (envlst->value != NULL)
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

char	*get_formatted_env(t_envlst *envlst)
{
	char	*line;

	if (envlst->value != NULL)
	{
		line = ft_strjoin(envlst->name, "=");
		if (ft_strcmp(envlst->value, "\"\"") != 0)
			line = ft_strfreejoin(line, envlst->value);
		else
			line = ft_strfreejoin(line, "\"\"");
	}
	else
		return (NULL);
	return (line);
}

char	**get_envp_from_envlst(t_envlst *envlst)
{
	char	**envp;
	char	*line;
	int 	i;

	i = 0;
	envp = ft_calloc(count_initiated_envlst(envlst) + 1, sizeof(char *));
	while (envlst)
	{
		line = get_formatted_env(envlst);
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