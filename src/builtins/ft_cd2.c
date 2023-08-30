/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagnon <mgagnon@student.42quebec.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 14:04:35 by mgagnon           #+#    #+#             */
/*   Updated: 2023/08/30 16:08:45 by mgagnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*change_tild(char *arg)
{
	char	*new_arg;

	new_arg = ft_strjoin(getenv("HOME"), &arg[1]);
	arg = ft_sfree2(arg);
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

void	no_arg(t_envlst *envlst)
{
	chdir(getenv("HOME"));
	envlst->value = ft_sfree2(envlst->value);
	envlst->value = ft_strdup(getenv("HOME"));
}
 
int	absolute_path(char *arg, t_envlst *envlst)
{
	int	i;

	i = 0;
	if (arg[0] == '~')
		arg = change_tild(arg);
	while (arg[i] && arg[i] == '/')
		i++;
	if (!arg[i])
	{
		chdir("/");
		envlst->value = ft_sfree2(envlst->value);
		envlst->value = strdup("/");
	}
	else if (chdir(arg) != 0)
	{
		printf("minishell: cd: %s: Not a directory\n", arg);
		return (1);
	}
	change_pwd(arg, envlst);
	return (0);
}

int	ft_cd(char **args, t_envlst *envlst, int fd_out)
{
	if (!args[1])
		no_arg(envlst);
	else if (args[1][0] == '/' || args[1][0] == '~')
		return (absolute_path(args[1], envlst));
	return (0)
}
