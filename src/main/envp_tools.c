/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 13:06:54 by jbernard          #+#    #+#             */
/*   Updated: 2023/04/03 15:30:59 by jbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_name_in_line(char *envline, char *name)
{
	// This fonction checks if the 'envline' has the variable name similar to 'name'
	int	len;

	len = ft_strlen(name);
	if (!ft_strncmp(envline, name, len) && envline[len] == '=')
	{
		return (1);
	}
	return (0);
}

int	is_name_in_envp(char **envp, char *name)
{	
	//This function checks if a variable name is present in the envp
	int	i;

	i = 0;
	while (envp[i])
	{
		if (is_name_in_line(envp[i], name))
			return (i);
		i++;
	}
	return (-1);
}

char	*build_envp_line(char *name, char *value)
{
	//This function format a line in envp style so that it can be added to the envp
	char	*line;

	line = ft_strjoin(name, "=");
	line = ft_strjoin(line, value);
	return (line);
}

char	*get_name(char *env_line)
{
	// This function get the variable name of a line found in the envp
	int	i;

	i = 0;
	while (env_line[i])
	{
		if(env_line[i] == '=')
			env_line[i] = '\0';
	}
	return (&env_line[0]);
}

char	*get_value(char *env_line)
{
	// This function get the value of a line found in the envp.
	int		i;
	int		len;

	len = ft_strlen(env_line);
	i = 0;
	while (env_line[i] != '=')
	{
		i++;
	}
	if (!env_line[i + 1])
		return ("");
	return (&env_line[i++]);
}

void	put_envp(char **envp)
{
	// This function prints the envp !!! FOR DEVELOPMENT USAGE ONLY !!!
	int	i;

	i = 0;
	printf("************ Envp beginning : ***************\n");
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
	printf("************ Line count (i) : %d ***************\n\n", i);
}

/* _____________________________________________________________________________________________*/