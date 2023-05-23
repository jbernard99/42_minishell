/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_fork.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:31:54 by jbernard          #+#    #+#             */
/*   Updated: 2023/05/23 11:27:37 by mgagnon          ###   ########.fr       */
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

int exec_fork(t_cmdlst *cmdlst)
{
	pid_t	pid;
	int 	old_stds[2];
	
	while (cmdlst != NULL)
	{
		if (cmdlst->flags & PIPEI)
			pipe_it(cmdlst);
		pid = fork();
		if (pid < 0)
		{
			perror("fork error");
			return (0);
		}
		else if (pid == 0)
			child_execute(cmdlst, old_stds);
		else
			parent_execute(cmdlst, old_stds);
		cmdlst = cmdlst->next;
	}
	return (1);
}
