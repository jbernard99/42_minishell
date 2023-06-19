/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_patch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagnon <mgagnon@student.42quebec.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 10:47:45 by mgagnon           #+#    #+#             */
/*   Updated: 2023/06/19 10:51:48 by mgagnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_patch(t_cmdlst *cmdlst)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		perror("ERROR");
	else if (pid == 0)
		child_execute(cmdlst);
	else
		parent_execute(cmdlst);
}