/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:57:20 by mgagnon           #+#    #+#             */
/*   Updated: 2023/05/26 12:03:55 by jbernard         ###   ########.fr       */
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

char	*rmv_quotes(char *str)
{
	char	*proxy;

	if (!str || str[0] == '\0')
		return (NULL);
	if (str[0] == '\'' || str[0] == '\"')
	{
		proxy = ft_strldup(&str[1], ft_strlen(str) - 2);
		free(str);
		return (proxy);
	}
	return (str);
}
