/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 16:37:35 by jbernard          #+#    #+#             */
/*   Updated: 2023/04/18 12:25:00 by jbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void (*get_built_in(char *name))()
{
	static void	(*funcs[7])() = {ft_cd, ft_echo, ft_env, ft_export};
	static char *funcs_name[7] = {"cd", "echo", "env", "export"};
	int			i;
	
	i = 0;
	while (i < 7)
	{
		if (ft_strncmp(name, funcs_name[i], ft_strlen(name)) == 0)
			return (funcs[i]);
		i++;
	}
	return (NULL);
}

int execution(t_cmdlst *cmdlst, char **envp)
{
	int		e;
	void 	*func;

	func = get_built_in(cmdlst->token[0]);
	if (func)
		return (1);
	else
		return (0);
}