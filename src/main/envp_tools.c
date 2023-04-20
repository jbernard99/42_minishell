/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 13:06:54 by jbernard          #+#    #+#             */
/*   Updated: 2023/04/20 15:33:04 by jbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// This fonction checks if the 'envline' has the variable name similar to 'name'
int	is_name_in_line(char *envline, char *name)
{
	int	len;

	len = ft_strlen(name);
	if (!ft_strncmp(envline, name, len) && envline[len] == '=')
	{
		return (1);
	}
	return (0);
}

//This function checks if a variable name is present in the envp
int	is_name_in_envp(char **envp, char *name)
{	
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

//This function format a line in envp style so that it can be added to the envp
char	*build_envp_line(char *name, char *value)
{
	char	*line;

	line = ft_strjoin(name, "=");
	line = ft_strjoin(line, value);
	return (line);
}

// This function get the variable name of a line found in the envp
char	*get_name(char *env_line)
{
	int	i;

	i = 0;
	while (env_line[i])
	{
		if (env_line[i] == '=')
			env_line[i] = '\0';
		i++;
	}
	return (&env_line[0]);
}

// This function get the value of a line found in the envp.
char	*get_value(char *env_line)
{
	int		i;

	i = 0;
	while (env_line[i] != '=')
	{
		i++;
	}
	if (!env_line[i + 1])
		return ("");
	return (&env_line[i++]);
}

// This function prints the envp !!! FOR DEVELOPMENT USAGE ONLY !!!
void	put_envp(char **envp)
{
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
