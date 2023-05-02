/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 16:37:35 by jbernard          #+#    #+#             */
/*   Updated: 2023/05/02 12:50:28 by jbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	(*get_built_in(char *name))(char **args, t_envlst *envlst, int fd_out)
{
	static void	(*funcs[6])() = {ft_cd, ft_echo, ft_env, ft_exit, ft_export, ft_pwd};
	static char	*funcs_name[6] = {"cd", "echo", "env", "exit", "export", "pwd"};
	int			i;
	
	i = 0;
	while (i < 6)
	{
		if (ft_strcmp(name, funcs_name[i]) == 0)
			return (funcs[i]);
		i++;
	}
	return (NULL);
}

void	execute_sh(t_cmdlst *cmdlst)
{
	pid_t	pid;
	char	*exec;
	int		status;
	int		e;

	exec = ft_strjoin("/bin/", cmdlst->token[0]);
	pid = fork();
	if (pid == -1)
		printf("Fork failed!\n");
	else if (pid == 0)
	{
		e = execve(exec, cmdlst->token, get_envp_from_envlst(cmdlst->envlst));
		if (e == -1)
		{
			printf("bash: %s: command not found\n", cmdlst->token[0]);
			exit(0);
		}
	}
	else
		pid = wait(&status);
}

void	execute_built_in(t_cmdlst *cmdlst, void (*func)())
{
	func(cmdlst->token, get_envp_from_envlst(cmdlst->envlst), 1);
}

int	execution(t_cmdlst *cmdlst)
{
	void	(*func)(char **, t_envlst *envlst, int);
	int		i;

	i = 1;
	while (i)	
	{
		func = get_built_in(cmdlst->token[0]);
		if (func)
			execute_built_in(cmdlst, func);
		else
			execute_sh(cmdlst);
		if (cmdlst->next != NULL)
		{
			cmdlst->next->envlst = cmdlst->envlst;
			cmdlst = cmdlst->next;
		}
		else
			i = 0;
	}
	return (1);
}
