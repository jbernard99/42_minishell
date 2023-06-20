/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 13:45:05 by jbernard          #+#    #+#             */
/*   Updated: 2023/06/20 14:23:17 by jbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	envlst_unset(t_envlst *envlst, char *name)
{
	t_envlst	*temp;

	if (is_name_in_envlst(envlst, name))
	{
		while (envlst)
		{
			if (ft_strcmp(envlst->next->name, name) == 0)
			{
				temp = envlst->next;
				if (temp->next)
					envlst->next = temp->next;
				else
					envlst->next = NULL;
				ft_sfree(temp->name);
				ft_sfree(temp->value);
				ft_sfree(temp);
				break ;
			}
			envlst = envlst->next;
		}
	}
	return (errno);
}

int	ft_unset(char **args, t_envlst *envlst, int fd_out)
{
	int	i;

	(void)fd_out;
	i = 1;
	while (args[i])
	{
		if (ft_strchr(args[i], ' ') == 0)
			envlst_unset(envlst, args[i]);
		else
			printf("minishell: unset: \'%s\': not a valid identifier\n", args[i]);
		i++;
	}
	return (0);
}
