/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 13:43:19 by jbernard          #+#    #+#             */
/*   Updated: 2023/05/24 14:45:09 by jbernard         ###   ########.fr       */
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
				envp[i] = ft_strdup(envp[j]);
				envp[j] = ft_strdup(temp);
			}
			j++;
		}
		i++;
	}
	return (envp);
}

// NEED TO MAKE export x=""5"" -> x=5
void	ft_export(char **args, t_envlst *envlst, int fd_out)
{
	char		**alpha_envp;
	int			argc;
	int			i;

	(void)fd_out;
	argc = ft_strtablen(args);
	i = 1;
	if (argc > 1)
	{
		while (args[i])
		{
			if (ft_strchr(args[i], ' ') == 0)
				add_to_envlst(envlst, args[i]);
			else
				printf("minishell: export: \'%s\': not a valid identifier\n", args[i]);
			i++;
		}
	}
	else
	{
		alpha_envp = get_alpha_envp(envlst);
		put_export_envp(alpha_envp);
		free(alpha_envp);
	}
}
