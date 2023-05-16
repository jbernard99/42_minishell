/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagnon <mgagnon@student.42quebec.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:17:28 by mgagnon           #+#    #+#             */
/*   Updated: 2023/05/15 15:37:33 by mgagnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	create_pipes(t_cmdlst *cmdlst)
{
	int	len;

	len = lst_len(cmdlst);
	while (len > 1)
	{
		if (pipe(cmdlst->pipefd) == -1)
		{
			perror("pipe creation");
			return (0);
		}
		cmdlst = cmdlst->next;
		len--;
	}
	return (1);
}
