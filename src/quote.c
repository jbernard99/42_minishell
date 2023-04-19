/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagnon <mgagnon@student.42quebec.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 17:13:19 by mgagnon           #+#    #+#             */
/*   Updated: 2023/04/14 17:19:45 by mgagnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	trailin_quotes(char **arr)
{
	int	i;
	int	j;

	i = 0;
	while(arr[i])
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
