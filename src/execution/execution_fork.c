/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_fork.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:31:54 by jbernard          #+#    #+#             */
/*   Updated: 2023/06/02 22:47:48 by jbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	child_execute(t_cmdlst *cmdlst)
{
	if (cmdlst->flags & PIPEI && cmdlst->flags & ~(R_OUT | APP_OUT))
		change_stdout(cmdlst->pipefd[1]);
	if (cmdlst->flags & PIPEO)
		change_stdin(cmdlst->pipefd[0]);
	if (cmdlst->flags & R_IN)
	{
		cmdlst->pipefd[1] = redirect_in(cmdlst->infile);
	}
	if (cmdlst->flags & R_OUT)
	{
		cmdlst->pipefd[0] = redirect_out(cmdlst->outfile);
		change_stdout(cmdlst->pipefd[0]);
	}
	if (cmdlst->flags & APP_OUT)
	{
		cmdlst->pipefd[0] = append(cmdlst->outfile);
		change_stdout(cmdlst->pipefd[0]);
	}
	if (cmdlst->flags & HR_DOC)
	{
		here_doc(cmdlst->pipefd[1], cmdlst->infile);
		change_stdin(cmdlst->pipefd[1]);
	}
	execution(cmdlst);
	write(1, "NO\n", 3);
	exit(0);
}

void	parent_execute(t_cmdlst *cmdlst, int *old_stds)
{
	(void)old_stds;
	wait(NULL);
	if (cmdlst->flags & PIPEI)
		close(cmdlst->pipefd[1]);
	if (cmdlst->flags & (R_OUT | APP_OUT))
	{
		close(cmdlst->pipefd[0]);
	}
	if (cmdlst->flags & PIPEO || cmdlst->flags & R_IN)
		close(cmdlst->pipefd[1]);
}

void	(*is_singled_out(t_cmdlst *cmdlst))(char **args, \
		t_envlst *envlst, int fd_out)
{
	static void	(*funcs[4])() = {ft_cd, ft_exit, \
		ft_export, ft_unset};
	static char	*funcs_name[4] = {"cd", "exit", \
		"export", "unset"};
	int			i;

	i = 0;
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

void	pre_exec_fork(t_cmdlst *cmdlst)
{
	void	(*func)(char **, t_envlst *, int);

	if (cmdlst->next)
		cmdlst->next->flags &= ~PIPEO;
	func = is_singled_out(cmdlst);
	if (func)
		func(cmdlst->token, cmdlst->envlst, 1);
	else
		exec_fork(cmdlst);
}

int	exec_fork(t_cmdlst *cmdlst)
{
	pid_t	pid;
	int		old_stds[2];

	while (cmdlst != NULL)
	{
		if (is_singled_out(cmdlst) != NULL)
			pre_exec_fork(cmdlst);
		else
		{
			if (cmdlst->flags & PIPEI)
				pipe_it(cmdlst);
			if (cmdlst->flags & (R_IN | R_OUT | APP_OUT | HR_DOC))
				work_redirection(cmdlst);
			pid = fork();
			if (pid < 0)
				perror("ERROR");
			else if (pid == 0)
				child_execute(cmdlst);
			else
				parent_execute(cmdlst, old_stds);
		}
		cmdlst = cmdlst->next;
	}
	return (1);
}
