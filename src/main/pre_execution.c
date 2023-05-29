/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_execution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:59:42 by jbernard          #+#    #+#             */
/*   Updated: 2023/05/29 09:22:44 by mgagnon          ###   ########.fr       */
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
			if (cmdlst->token[i][0] != '\'')
			{
				cmdlst->token[i] = rmv_quotes(cmdlst->token[i]);
				while(is_there_env_var(cmdlst->token[i]) != 0)	
					cmdlst->token[i] = rplc_env_var(cmdlst->envlst, \
						cmdlst->token[i]);
			}
			else
				cmdlst->token[i] = rmv_quotes(cmdlst->token[i]);
			i++;
		}
		cmdlst = cmdlst->next;
	}
}
