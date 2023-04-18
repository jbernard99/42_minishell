/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 16:37:35 by jbernard          #+#    #+#             */
/*   Updated: 2023/04/18 16:24:54 by jbernard         ###   ########.fr       */
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

int execution(t_cmdlst *cmdlst)
{
	pid_t		pid;
	void 		(*func)();
	int			status;
	int			e;
	
	pid = 0;
	status = 0;
	func = get_built_in(cmdlst->token[0]);
	if (func)
	{
		//printf("Funtion found!, PID : %d\n", getpid());
		func(cmdlst->token, *cmdlst->envp, 1);
	}	
	else
	{
		cmdlst->token[0] = ft_strjoin("/bin/", cmdlst->token[0]);
		pid = fork();
		if (pid == 0)
		{
			e = execve(cmdlst->token[0], cmdlst->token, *cmdlst->envp);
			if (e == -1)
				perror(cmdlst->token[0]);
		}
		wait(&status);
	}
	return (1);
}

