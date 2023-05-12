/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:37:01 by jbernard          #+#    #+#             */
/*   Updated: 2023/05/10 18:42:42 by jbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		pipex(int id)
{
	int		fd[2];
	pid_t 	pid;
	(void)id;
	(void)pid;
	return fd[0];
}