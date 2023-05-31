/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagnon <mgagnon@student.42quebec.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:36:53 by mgagnon           #+#    #+#             */
/*   Updated: 2023/05/31 16:24:08 by mgagnon          ###   ########.fr       */
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

int	scan_redirect(t_cmdlst *cmdlst)
{
	int		i;

	i = 0;
	while (cmdlst->token[i])
	{
		if (ft_strrchr("<>", cmdlst->token[i][0]))
		{
			set_redirect_flags(cmdlst->token[i], &cmdlst->flags);
			if ((cmdlst->flags & (APP_OUT | HR_DOC)) \
					&& ft_strlen(cmdlst->token[i]) > 2)
				return (0);
			else if ((cmdlst->flags & (R_IN | R_OUT)) && \
					ft_strlen(cmdlst->token[i]) > 1)
				return (0);
		}
		i++;
	}
	return (1);
}
