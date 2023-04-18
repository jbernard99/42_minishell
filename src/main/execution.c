/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 16:37:35 by jbernard          #+#    #+#             */
/*   Updated: 2023/04/18 13:11:25 by jbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void (*get_built_in(char *name))()
{
	static void	(*funcs[3])() = {ft_cd, ft_echo, ft_env};
	static char *funcs_name[3] = {"cd", "echo", "env"};
	int			i;
	
	i = 0;
	while (i < 3)
	{
		if (ft_strcmp(name, funcs_name[i]) == 0)
			return (funcs[i]);
		i++;
	}
	return (NULL);
}

int execution(t_cmdlst *cmdlst, char **envp)
{
	pid_t		pid;
	void 	*func;
	(void)envp;
	
	func = get_built_in(cmdlst->token[0]);
	if (func)
		printf("Funtion found!, PID : %d\n", getpid());
		
	else
	{
		pid = fork();
		printf("Function not found... -> PID : %d\n", getpid());
	}
	return (1);
}