/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 13:40:17 by jbernard          #+#    #+#             */
/*   Updated: 2023/08/26 15:04:14 by mgagnon          ###   ########.fr       */
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

char	*change_tild(char *arg)
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

void	manage_pwd(char **args, t_envlst *envlst)
{
	int	i;

	envlst = is_name_in_envlst(envlst, "PWD");
	i = 0;
	if (ft_strcmp(args[0], "Users") == 0)
		ft_sfree(envlst->value);
	while (args[i])
	{
		write(0, "hello\n", 6);
		if (ft_strcmp(args[i], "..") == 0)
			envlst->value = pwd_previous_directory(envlst->value);
		else if (ft_strcmp(args[i], ".") != 0)
		{
			write(0, "hello2\n", 7);
			if (envlst->value != NULL && ft_strlen(envlst->value) > 1)
			{
				write(0, "hello3\n", 7);
				envlst->value = ft_strfreejoin(envlst->value, "/");
				write(0, "hello4\n", 7);
			}
			else
				envlst->value = ft_strdup("/");
			envlst->value = ft_strfreejoin(envlst->value, args[i]);
		}
		i++;
	}
}

int	ft_cd(char **args, t_envlst *envlst, int fd_out)
{
	int	i;
	char	**split;

	i = 0;
	(void)fd_out;
	if (!args[1])
	{
		chdir(getenv("HOME"));
		split = ft_split(getenv("HOME"), '/');
		while (split[i])
		{
			printf("%s\n", split[i]);
			i++;
		}
		manage_pwd(split, envlst);
		ft_freetabstr(split);
		return (0);
	}
	if (args[1][0] == '~')
		args[1] = change_tild(args[1]);
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
