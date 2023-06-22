/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_patch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 10:47:45 by mgagnon           #+#    #+#             */
/*   Updated: 2023/06/22 11:08:34 by mgagnon          ###   ########.fr       */
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
