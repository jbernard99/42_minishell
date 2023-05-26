/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_execution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:59:42 by jbernard          #+#    #+#             */
/*   Updated: 2023/05/25 10:56:46 by jbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	work_env_vars_calls(t_cmdlst *cmdlst)
{
	int i;

	while (cmdlst)
	{
		i = 0;
		while (cmdlst->token[i])
		{
			if (is_there_env_var(cmdlst->token[i]))
				rplc_env_var(cmdlst->envlst, cmdlst->token[i]);
			i++;
		}
		cmdlst = cmdlst->next;
	}
}