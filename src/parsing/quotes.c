/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:57:20 by mgagnon           #+#    #+#             */
/*   Updated: 2023/07/06 12:33:21 by mgagnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	trailing_quotes(char **arr)
{
	int	i;
	int	j;

	i = 0;
	while (arr[i])
	{
		j = 0;
		while (arr[i][j])
		{
			if (arr[i][j] == '\'' || arr[i][j] == '\"')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	work_trailing_quotes(t_cmdlst *cmdlst)
{
	while (cmdlst)
	{
		if (trailing_quotes(cmdlst->token) == 1)
			return (0);
		cmdlst = cmdlst->next;
	}
	return (1);
}

char	*rmv_quotes(char *str)
{
	char	*proxy;

	if (!str || str[0] == '\0')
		return (NULL);
	if (str[0] == '\'' || str[0] == '\"')
	{
		proxy = ft_strldup(&str[1], ft_strlen(str) - 2);
		ft_sfree(str);
		return (proxy);
	}
	return (str);
}

void	quote_handle(char *cmd, size_t *end, int *flags)
{
	if (cmd[*end] == '\'' || cmd[*end] == '\"')
	{
		if (cmd[*end] == '\'')
			*flags |= QUOTE;
		else if (cmd[*end] == '\"')
			*flags |= DQUOTE;
		check_quotes(cmd, end, flags);
	}
	(*end)++;
}
