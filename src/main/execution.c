/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 16:37:35 by jbernard          #+#    #+#             */
/*   Updated: 2023/04/19 14:43:53 by mgagnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	(*get_built_in(char *name))(char **args, char **env, int fd_out)
{
	static void	(*funcs[3])() = {ft_cd, ft_echo, ft_env};
	static char	*funcs_name[3] = {"cd", "echo", "env"};
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
		e = execve(exec, cmdlst->token, *cmdlst->envp);
		if (e == -1)
		{
			perror(cmdlst->token[0]);
			exit(0);
		}
	}
	else
		pid = wait(&status);
}

void	execute_built_in(t_cmdlst *cmdlst, void (*func)())
{
	func(cmdlst->token, *cmdlst->envp, 1);
}

int	execution(t_cmdlst *cmdlst)
{
	void	(*func)(char **, char **, int);

	func = get_built_in(cmdlst->token[0]);
	if (func)
		execute_built_in(cmdlst, func);
	else
		execute_sh(cmdlst);
	return (1);
}
