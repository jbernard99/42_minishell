/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 06:43:50 by jbernard          #+#    #+#             */
/*   Updated: 2023/06/09 12:22:51 by jbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* if quotes or double quotes are used makes sure to skip */
/* over every part between 2 quotes or two double quotes */

void	check_quotes(char *input, size_t *i, int *flags)
{
	char	c;

	if (input[*i] == '\'' && (*flags & DQUOTE) == 0)
	{
		*flags ^= QUOTE;
		c = '\'';
	}
	else if (input[*i] == '\"')
	{
		*flags ^= DQUOTE;
		c = '\"';
	}
	(*i)++;
	while (input[*i] && input[*i] != c)
		(*i)++;
	if (input[*i] == '\'')
		*flags ^= QUOTE;
	else if (input[*i] == '\"')
		*flags ^= DQUOTE;
}

int	finish_flag_set(t_cmdlst **cmdlst)
{
	t_cmdlst	*cur;

	cur = *cmdlst;
	while (cur->next != NULL)
	{
		if (cur->flags & PIPEI)
			cur->next->flags |= PIPEO;
		cur = cur->next;
	}
	if (cur->flags & PIPEI)
		return (0);
	return (1);
}

size_t	ft_strpbrk(const char *str, const char *delim, int *flags)
{
	size_t	token_nb;
	int		i;

	token_nb = 1;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			if (str[i] == '\'' && *flags & ~DQUOTE)
				*flags ^= QUOTE;
			else if (str[i] == '\"' && *flags & ~QUOTE)
				*flags ^= DQUOTE;
		}
		if (str[i] == *delim && (*flags & (QUOTE | DQUOTE)) == 0)
			token_nb++;
		i++;
	}
	return (token_nb);
}

char	*ft_strtok(char *str, const char *delim, int *flags)
{
	static size_t	i = 0;
	int				origin;
	char			*token;

	origin = i;
	ft_strpbrk(str, delim, flags);
	if (str[i] == *delim)
		token = ft_strldup(&str[origin], (i - 1) - origin);
	else
		token = ft_strldup(&str[origin], i - origin);
	*str = *str + i;
	return (token);
}

char	*ft_strldup(const char *str, size_t len)
{
	char	*ptr;
	size_t	i;

	ptr = malloc(len + 1);
	if (!ptr)
		return (0);
	i = 0;
	while (len--)
		ptr[i++] = *str++;
	ptr[i] = 0;
	return (ptr);
}
