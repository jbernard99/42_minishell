/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_patch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 10:47:45 by mgagnon           #+#    #+#             */
/*   Updated: 2023/08/23 13:48:00 by mgagnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_patch(t_cmdlst *cmdlst)
{
	pid_t	pid;

	pid = fork();
	cmdlst->pid = pid;
	if (pid < 0)
		perror("ERROR");
	else if (pid == 0)
		child_execute(cmdlst);
	else
		parent_execute(cmdlst);
}

void	waiting(t_cmdlst *cmdlst, int status)
{
	t_cmdlst	*head;
	int			other_status;

	other_status = 0;
	head = cmdlst;
	while (cmdlst != NULL)
	{
		waitpid(cmdlst->pid, &other_status, 0);
		cmdlst = cmdlst->next;
	}
	signal(SIGINT, ctrlc_handle);
	if (status == -1)
		read_result(head->envlst, (other_status % 255));
	else
		read_result(head->envlst, (status % 255));
}

int	exec_launch(t_cmdlst *cmdlst, struct termios o_t, struct termios n_t)
{
	int	x;

	tcsetattr(STDIN_FILENO, TCSANOW, &o_t);
	work_env_vars_calls(cmdlst);
	x = exec_fork(cmdlst, cmdlst->envlst);
	tcsetattr(STDIN_FILENO, TCSANOW, &n_t);
	if (x == 0)
		signal(SIGINT, ctrlc_handle);
	return (x);
}
