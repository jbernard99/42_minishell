/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 13:40:17 by jbernard          #+#    #+#             */
/*   Updated: 2023/08/25 16:15:59 by mgagnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Exemples :
	cd: Return to /home
	cd 'invalid folder': "cd: {invalid folder}: No such file or directory"
	cd 'valid folder': Moves current working div to selected folder
	cd 'valid folder' 'invalid folder': Moves current working div to selected 
					    folder.
*/

#include "../../includes/minishell.h"

char	*remake_arg(char *arg)
{
	char	*new_arg;

	arg++;
	new_arg = ft_strjoin(getenv("HOME"), arg);
	arg--;
	ft_sfree(arg);
	return (new_arg);
}

char	*pwd_previous_directory(char *pwd)
{
	int	i;

	i = ft_strlen(pwd) - 1;
	while (pwd[i] != '/' && pwd[i])
		i--;
	if (i != 0)
		pwd[i] = '\0';
	else
	{
		pwd[i] = '/';
		pwd[i + 1] = '\0';
	}
	return (pwd);
}

void	absolute_path(char **args, t_envlst *envlst)
{
}

void	manage_pwd(char **args, t_envlst *envlst)
{
	int	i;

	envlst = is_name_in_envlst(envlst, "PWD");
	i = 0;
	if (ft_strcmp(args[0], "Users") != 0)
	{
		while (args[i])
		{
			if (ft_strcmp(args[i], "..") == 0)
				envlst->value = pwd_previous_directory(envlst->value);
			else if (ft_strcmp(args[i], ".") != 0)
			{
				if (i == 0)
				{
					ft_sfree(envlst->value);
					envlst->value = ft_strdup(args[0]);
				}
				if (ft_strlen(envlst->value) > 1)
					envlst->value = ft_strfreejoin(envlst->value, "/");
				envlst->value = ft_strfreejoin(envlst->value, args[i]);
			}
			i++;
		}
	}
	else
		absolute_path(args, envlst);
}

int	ft_cd(char **args, t_envlst *envlst, int fd_out)
{
	char	**split;

	(void)fd_out;
	if (!args[1])
	{
		chdir(getenv("HOME"));
		split = ft_split(getenv("HOME"), '/');
		manage_pwd(split, envlst);
		ft_freetabstr(split);
		return (0);
	}
	if (args[1][0] == '~')
		args[1] = remake_arg(args[1]);
	if (chdir(args[1]) == 0)
	{
		split = ft_split(args[1], '/');
		manage_pwd(split, envlst);
		ft_freetabstr(split);
	}
	else
		printf("minishell: cd: %s: Not a directory\n", args[1]);
	return (0);
}
