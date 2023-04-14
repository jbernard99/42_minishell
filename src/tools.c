/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 06:43:50 by jbernard          #+#    #+#             */
/*   Updated: 2023/04/14 11:00:22 by mgagnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	finish_flag_set(t_cmdlst **cmdlst)
{
	t_cmdlst	*cur;

	cur = *cmdlst;
	while (cur->next != NULL)
	{
		if (cur->flags & PIPEI)
			cur->next->flags |= PIPEO;
		else if (cur->flags & ORI)
			cur->next->flags |= ORO;
		else if (cur->flags & ANDI)
			cur->next->flags |= ANDO;
		cur = cur->next;
	}
}

size_t	ft_strpbrk(const char *str, const char *delim, int *flags)
{
	const char	*ptr;
	size_t		token_nb;
	int		i;

	token_nb = 1;
	i = 0;
	while (str[i] != '\0')
	{
		ptr = delim;
		while (*ptr != '\0')
		{
			if (str[i] == '\'' || str[i] == '\"')
			{
				if (str[i] == '\'')
					*flags ^= QUOTE;
				else if (str[i] == '\"')
					*flags ^= DQUOTE;
			}
			if (str[i] == *ptr && (*flags & (QUOTE | DQUOTE)) == 0)
				token_nb++;
			ptr++;
		}
		(i)++;
	}
	printf("number of token -> %zu\n", token_nb);
	return (token_nb);
}

char	*ft_strtok(char *str, const char *delim, int *flags)
{
	static size_t	i = 0;
	int		origin;
	char		*token;

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
