/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagnon <mgagnon@student.42quebec.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:36:53 by mgagnon           #+#    #+#             */
/*   Updated: 2023/05/11 14:15:13 by mgagnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_redirect_flags(char *symbol, int *flags)
{
	if (symbol[0] == '>')
	{
		if (symbol[1] && symbol[1] == '>')
			*flags |= APP_OUT;
		else
			*flags |= R_OUT;
	}
	else if (symbol[0] == '<')
	{
		if (symbol[1] && symbol[1] == '<')
			*flags |= HR_DOC;
		else
			*flags |= R_IN;
	}
}

void	scan_redirect(t_cmdlst *cmdlst)
{
	int		i;

	i = 0;
	while (cmdlst->token[i])
	{
		if (ft_strrchr("<>", cmdlst->token[i][0]))
			set_redirect_flags(cmdlst->token[i], &cmdlst->flags);
		i++;
	}
}
