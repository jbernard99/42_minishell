/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagnon <mgagnon@student.42quebec.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 14:04:35 by mgagnon           #+#    #+#             */
/*   Updated: 2023/09/01 12:53:04 by mgagnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	change_pwd(char *arg, t_envlst *envlst)
{
	int		i;
	char	**args;

	i = 0;
	args = ft_split(arg, '/');
	i = 0;
	while (args[i])
	{
		if (ft_strcmp(args[i], "..") == 0)
			envlst->value = pwd_previous_directory(envlst->value);
		else if (ft_strcmp(args[i], ".") != 0)
		{
			if (envlst->value == NULL)
				envlst->value = ft_strdup("/");
			else
				envlst->value = ft_strfreejoin(envlst->value, "/");
			envlst->value = ft_strfreejoin(envlst->value, args[i]);
		}
		i++;
	}
	ft_freetabstr(args);
}

int	absolute_path(char *arg, t_envlst *envlst)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] == '/')
		i++;
	if (arg[i] == '\0')
	{
		chdir("/");
		envlst->value = ft_sfree2(envlst->value);
		envlst->value = strdup("/");
		return (0);
	}
	else if (chdir(arg) != 0)
	{
		printf("minishell: cd: %s: Not a directory\n", arg);
		return (1);
	}
	envlst->value = ft_sfree2(envlst->value);
	change_pwd(&arg[i], envlst);
	return (0);
}

int	relative_path(char *arg, t_envlst *envlst)
{
	if (chdir(arg) != 0)
	{
		printf("minishell: cd: %s: Not a directory\n", arg);
		return (1);
	}
	change_pwd(arg, envlst);
	return (0);
}

int	ft_cd(char **args, t_envlst *envlst, int fd_out)
{
	char	*new_arg;

	(void)fd_out;
	envlst = is_name_in_envlst(envlst, "PWD");
	if (!args[1])
	{
		chdir(getenv("HOME"));
		envlst->value = ft_sfree2(envlst->value);
		envlst->value = ft_strdup(getenv("HOME"));
		return (0);
	}
	if (args[1][0] == '~')
	{
		new_arg = ft_strjoin(getenv("HOME"), &args[1][1]);
		args[1] = ft_sfree2(args[1]);
		args[1] = new_arg;
	}
	if (args[1][0] == '/')
		return (absolute_path(args[1], envlst));
	return (relative_path(args[1], envlst));
}
