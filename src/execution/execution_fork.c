/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_fork.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:31:54 by jbernard          #+#    #+#             */
/*   Updated: 2023/05/25 10:51:35 by jbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	child_execute(t_cmdlst *cmdlst, int *old_stds)
{
	if (cmdlst->flags & PIPEI)
	{
		old_stds[1] = dup(STDOUT_FILENO);
		change_stdout(cmdlst->pipefd[1]);
	}
	if (cmdlst->flags & PIPEO)
	{
		old_stds[0] = dup(STDIN_FILENO);
		change_stdin(cmdlst->pipefd[0]);
	}
	execution(cmdlst);
}

void	parent_execute(t_cmdlst *cmdlst, int *old_stds)
{
	wait(NULL);
	if (cmdlst->flags & PIPEI)
	{
		reset_stdin(old_stds[0]);
		close(cmdlst->pipefd[1]);	
	}
	if (cmdlst->flags & PIPEO)
	{
		reset_stdout(old_stds[1]);
		close(cmdlst->pipefd[0]);
	}
}

void	(*is_singled_out(t_cmdlst *cmdlst))(char **args, t_envlst *envlst, int fd_out)
{
	static void	(*funcs[4])() = {ft_cd, ft_exit, \
		ft_export, ft_unset};
	static char	*funcs_name[4] = {"cd", "exit", \
		"export", "unset"};
	int			i;

	i = 0;
	if (ft_strcmp("export", cmdlst->token[0]) && \
		ft_strtablen(cmdlst->token) == 1)
		return (NULL);
	while (i < 4)
	{
		if (ft_strcmp(cmdlst->token[0], funcs_name[i]) == 0)
			return (funcs[i]);
		i++;
	}
	return (NULL);
}

void	pre_exec_fork(t_cmdlst *cmdlst)
{
	void	(*func)(char **, t_envlst *, int);


	func = is_singled_out(cmdlst);
	if (func)
		func(cmdlst->token, cmdlst->envlst, 1);
	else
		exec_fork(cmdlst);
}

int exec_fork(t_cmdlst *cmdlst)
{
	pid_t	pid;
	int 	old_stds[2];
	
	while (cmdlst != NULL)
	{
		if (is_singled_out(cmdlst) != NULL)
			pre_exec_fork(cmdlst);
		else
		{
			if (cmdlst->flags & PIPEI)
				pipe_it(cmdlst);
			pid = fork();
			if (pid < 0)
				perror("ERROR");
			else if (pid == 0)
				child_execute(cmdlst, old_stds);
			else
				parent_execute(cmdlst, old_stds);
		}
		cmdlst = cmdlst->next;
	}
	return (1);
}
