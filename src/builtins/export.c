/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 13:43:19 by jbernard          #+#    #+#             */
/*   Updated: 2023/06/27 11:09:51 by mgagnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Export : 
	Working Export cases:
		"export test" 	: Var test will be created without any value ->
		                  MUST NOT SHOW IN "env" AFTER, ONLY IN "export"
		"export"		: print envp in order
		"export x =123" : OR "export x= 123" ERROR '=' must follow var name
		                                               (No spaces)
		"export x="		: No value, x will equal ""
		"export x=2"	: 2 will become string "2"
		"export x='Bonjour''Allo'123" : Var x will be 'BonjourAllo123'
*/

#include "../../includes/minishell.h"

void	put_export_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("declare -x %s\n", envp[i]);
		i++;
	}
}

char	**get_alpha_envp(t_envlst *envlst)
{
	char	**envp;
	char	*temp;
	int		i;
	int		j;

	envp = get_all_from_envlst(envlst);
	i = 0;
	while (envp[i] != NULL)
	{
		j = i + 1;
		while (envp[j] != NULL)
		{
			if (ft_strcmp(envp[i], envp[j]) > 0)
			{
				temp = ft_strdup(envp[i]);
				ft_sfree(envp[i]);
				envp[i] = ft_strdup(envp[j]);
				ft_sfree(envp[j]);
				envp[j] = temp;
			}
			j++;
		}
		i++;
	}
	return (envp);
}

int	scan_new_var(char *arg, t_envlst *envlst)
{
	int	i;

	i = 0;
	if (ft_strchr(arg, ' ') == 0 && arg[0] != '=')
	{
		while (arg[i] && arg[i] != '=')
		{
			if (ft_isalpha(arg[i]) == 0 && arg[i] != '_')
				return (1);
			i++;
		}
		add_to_envlst(envlst, arg);
	}
	else
		return (1);
	return (0);
}

int	work_export(char **args, t_envlst *envlst)
{
	int	i;
	int	argc;

	i = 0;
	while (args[++i])
	{
		argc = scan_new_var(args[i], envlst);
		if (argc != 0)
		{
			printf("minishell: export: not a valid identifier\n");
			return (1);
		}
	}
	return (0);
}

// NEED TO MAKE export x=""5"" -> x=5
int	ft_export(char **args, t_envlst *envlst, int fd_out)
{
	char		**alpha_envp;
	int			argc;

	(void)fd_out;
	argc = ft_strtablen(args);
	if (argc > 1)
	{
		if (work_export(args, envlst) == 1)
			return (1);
		else
			return (0);
	}
	else
	{
		alpha_envp = get_alpha_envp(envlst);
		put_export_envp(alpha_envp);
		ft_freetabstr(alpha_envp);
	}
	return (0);
}
