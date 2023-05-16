/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:37:01 by jbernard          #+#    #+#             */
/*   Updated: 2023/05/14 14:41:02 by jbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		pipex(pid_t pid)
{
	int		fd[2];
	if (pipe(fd) == -1) {
		perror("pipe");
	}
	if (pid == 0) {
		close(fd[1]);
		if (dup2(fd[0], STDIN_FILENO) == -1)
			perror("dup2");
	}
	else {
		close(fd[0]);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			perror("dup2");
	}
	return fd[0];
}