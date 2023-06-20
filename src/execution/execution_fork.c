/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_fork.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:31:54 by jbernard          #+#    #+#             */
/*   Updated: 2023/06/20 14:06:01 by jbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	child_execute(t_cmdlst *cmdlst)
{
	signal(SIGINT, ctrl_c_heredoc);
	if (cmdlst->flags & HR_DOC)
		cmdlst->red_fd[1] = here_doc(cmdlst->infile);
	if (cmdlst->flags & PIPEI && cmdlst->flags & ~(R_OUT | APP_OUT))
		change_stdout(cmdlst->pipefd[1]);
	if (cmdlst->flags & PIPEO)
		change_stdin(cmdlst->pipefd[0]);
	if (cmdlst->flags & R_IN)
		cmdlst->red_fd[1] = redirect_in(cmdlst->infile);
	if (cmdlst->flags & R_OUT)
	{
		cmdlst->red_fd[0] = redirect_out(cmdlst->outfile);
		change_stdout(cmdlst->red_fd[0]);
	}
	if (cmdlst->flags & APP_OUT)
	{
		cmdlst->red_fd[0] = append(cmdlst->outfile);
		change_stdout(cmdlst->red_fd[0]);
	}
	execution(cmdlst);
	exit(0);
}

void	parent_execute(t_cmdlst *cmdlst)
{
	int	status;

	wait(&status);
	read_result(cmdlst->envlst, status % 256);
	if (cmdlst->flags & PIPEI)
		close(cmdlst->pipefd[1]);
	if (cmdlst->flags & PIPEO)
		close(cmdlst->pipefd[0]);
	if (cmdlst->flags & (R_OUT | APP_OUT | R_IN | HR_DOC))
	{
		printf("Closing...\n");
		close(cmdlst->red_fd[0]);
		close(cmdlst->red_fd[1]);
	}
}

int	(*is_singled_out(t_cmdlst *cmdlst))(char **args, \
		t_envlst *envlst, int fd_out)
{
	static int	(*funcs[4])() = {ft_cd, ft_exit, \
		ft_export, ft_unset};
	static char	*funcs_name[4] = {"cd", "exit", \
		"export", "unset"};
	int			i;

	i = 0;
	if (ft_strcmp("exit", cmdlst->token[0]) == 0)
			cmdlst->exit = 1;
	if (ft_strcmp("export", cmdlst->token[0]) == 0 && \
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

void	pre_exec_fork(t_cmdlst *cmdlst, t_envlst *envlst)
{
	int	status;
	int	(*func)(char **, t_envlst *, int);

	status = 0;
	if (cmdlst->next)
		cmdlst->next->flags &= ~PIPEO;
	func = is_singled_out(cmdlst);
	if (func)
	{
		status = func(cmdlst->token, cmdlst->envlst, 1);
	}
	else
		exec_fork(cmdlst, envlst);
	read_result(envlst, status);
}

int	exec_fork(t_cmdlst *cmdlst, t_envlst *envlst)
{
	signal(SIGINT, ok);
	while (cmdlst != NULL)
	{
		if (cmdlst->flags & PIPEI)
			pipe_it(cmdlst);
		if (cmdlst->flags & (R_IN | R_OUT | APP_OUT | HR_DOC))
		{
			if (work_redirection(cmdlst) == 0)
				return (0);
		}		
		if (is_singled_out(cmdlst) != NULL)
			pre_exec_fork(cmdlst, envlst);
		else
			exec_patch(cmdlst);
		cmdlst = cmdlst->next;
	}
	return (1);
}
