/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mng_envp_temp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 11:44:16 by jbernard          #+#    #+#             */
/*   Updated: 2023/05/08 11:33:42 by jbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// OK
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


// OK
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

// OK
t_envlst	*envlst_last(t_envlst *envlst)
{
	if (envlst)
	{
		while (envlst->next)
			envlst = envlst->next;
	}
	return (envlst);
}

// OK
t_envlst	*create_envlst_from_line(char *line)
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

// OK
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
	}
}

//OK
void	put_envlst(t_envlst *envlst)
{
	printf("Name: %s\nValue: %s\n", envlst->name, envlst->value);
}

// OK
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

// OK
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

// OK
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

// OK
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

// OK
t_envlst	*is_name_in_envlst(t_envlst *envlst, char *name)
{
	while (envlst)
	{
		if (ft_strcmp(name, envlst->name) == 0)
			return (envlst);
		else
			envlst = envlst->next;
	}
	return (NULL);
}

// OK
void	add_to_envlst(t_envlst *envlst, char *line)
{
	t_envlst	*proxy;

	proxy = is_name_in_envlst(envlst, get_name(line));
	if (!proxy)
	{
		envlst = envlst_last(envlst);
		envlst->next = create_envlst_from_line(line);
	}
	else
	{
		line = get_value(line);
		if (line)
			proxy->value = line;
	}
}

// OK
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