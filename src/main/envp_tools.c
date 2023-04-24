/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 13:06:54 by jbernard          #+#    #+#             */
/*   Updated: 2023/04/24 15:10:44 by jbernard         ###   ########.fr       */
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
	if (value)
		line = ft_strjoin(line, value);
	return (line);
}

char	*get_name(char *env_line)
{
	size_t	i;

	i = 0;
	while (env_line[i + 1] != '=' && env_line[i + 1])
		i++;
	return (ft_strldup(env_line, i + 1));
}

// This function get the value of a line found in the envp.
char	*get_value(char *env_line)
{
	int		i;

	i = 0;
	while (env_line[i] != '=')
		i++;
	if (!env_line[i + 1])
		return ("");
	i++;
	return (&env_line[i]);
}

// This function prints the envp !!! FOR DEVELOPMENT USAGE ONLY !!!
void	put_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
		printf("declare -x %s\n", envp[i++]);
}
