/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 13:40:17 by jbernard          #+#    #+#             */
/*   Updated: 2023/05/24 14:44:28 by jbernard         ###   ########.fr       */
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
	while (args[i])
	{
		if (ft_strcmp(args[i], "..") == 0)
			envlst->value = pwd_previous_directory(envlst->value);
		else if (ft_strcmp(args[i], ".") != 0)
		{
			if (ft_strlen(envlst->value) > 1)
				envlst->value = ft_strfreejoin(envlst->value, "/");
			envlst->value = ft_strfreejoin(envlst->value, args[i]);
		}
		i++;
	}
}

void	ft_cd(char **args, t_envlst *envlst, int fd_out)
{
	(void)fd_out;
	if (chdir(args[1]) == 0)
		manage_pwd(ft_split(args[1], '/'), envlst);
	else
		printf("minishell: cd: %s: Not a directory\n", args[1]);
}
