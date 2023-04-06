/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 06:43:50 by jbernard          #+#    #+#             */
/*   Updated: 2023/04/06 11:06:44 by jbernard         ###   ########.fr       */
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

char	*ft_strpbrk(const char *str, const char *delim, int *flags)
{
	const char	*ptr1;
	const char	*ptr2;

	ptr1 = str;
	while (*ptr1 != '\0')
	{
		ptr2 = delim;
		while (*ptr2 != '\0')
		{
			if (*ptr1 == '\'' || *ptr1 == '\"')
			{
				if (*ptr1 == '\'')
					*flags ^= QUOTE;
				else if (*ptr1 == '\"')
					*flags ^= DQUOTE;
			}
			if (*ptr1 == *ptr2 && (*flags & (QUOTE | DQUOTE)) == 0)
				return ((char *)ptr1);
			ptr2++;
		}
		ptr1++;
	}
	return (NULL);
}

char	*ft_strtok(char *str, const char *delim, int *flags)
{
	static char	*last_token;
	char		*token;

	if (str != NULL)
		last_token = ft_strdup(str);
	else if (last_token == NULL)
	{
		free(last_token);
		return (NULL);
	}
	token = last_token;
	last_token = ft_strpbrk(last_token, delim, flags);
	if (last_token)
		*last_token++ = '\0';
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