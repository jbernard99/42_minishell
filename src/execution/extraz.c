/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extraz.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 11:24:11 by jbernard          #+#    #+#             */
/*   Updated: 2023/08/22 12:45:44 by jbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_type(char *token)
{
	if (ft_strcmp("<", token) == 0)
		return (token);
	else if (ft_strcmp("<<", token) == 0)
		return (token);
	else if (ft_strcmp(">", token) == 0)
		return (token);
	else if (ft_strcmp(">>", token) == 0)
		return (token);
	return (NULL);
}

int	token_is_redirection(char *token)
{
	if (ft_strcmp(token, "<") == 0)
		return (1);
	else if (ft_strcmp(token, "<<") == 0)
		return (1);
	else if (ft_strcmp(token, ">") == 0)
		return (1);
	else if (ft_strcmp(token, ">>") == 0)
		return (1);
	return (0);
}