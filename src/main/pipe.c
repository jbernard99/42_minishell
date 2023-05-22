/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:37:01 by jbernard          #+#    #+#             */
/*   Updated: 2023/05/22 16:45:32 by mgagnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pipe_it(t_cmdlst *cmdlst)
{
	int	fd[2];

	pipe(fd);
	cmdlst->pipefd[1] = fd[1];
	cmdlst->next->pipefd[0] = fd[0];
}

int	reset_stdin(int old_fd)
{
	if (dup2(old_fd, STDIN_FILENO) == -1)
	{
		perror("reset STDIN");
		return (0);
	}
	return (1);
}

int	change_stdin(int new_fd)
{
	if (dup2(new_fd, STDIN_FILENO) == -1)
	{
		perror("dup2 change STDIN");
		return (0);
	}
	return (1);
}

int	reset_stdout(int old_fd)
{
	if (dup2(old_fd, STDOUT_FILENO) == -1)
	{
		perror("STDOUT reset");
		return (0);
	}
	return (1);
}

int	change_stdout(int new_fd)
{
	if (dup2(new_fd, STDOUT_FILENO) == -1)
	{
		perror("dup2 change STDOUT");
		return (0);
	}
	return (1);
}
