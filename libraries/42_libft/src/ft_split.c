/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 10:41:31 by jbernard          #+#    #+#             */
/*   Updated: 2021/06/18 22:25:56 by kneegher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_word_count(char const *str, char c)
{
	size_t	cnt;

	cnt = 0;
	while (*str)
	{
		if (*str != c)
		{
			++cnt;
			while (*str && *str != c)
				++str;
		}
		else
			++str;
	}
	return (cnt);
}

static size_t	len_until_char(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (*s && *s != c)
	{
		s++;
		i++;
	}
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	size_t	i;
	size_t	nb_words;

	if (!s)
		return (NULL);
	nb_words = get_word_count(s, c);
	ptr = (char **)malloc(sizeof(char *) * (nb_words + 1));
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < nb_words)
	{
		while (*s == c && *s)
			s++;
		ptr[i] = ft_substr(s, 0, len_until_char(s, c));
		s += len_until_char(s, c);
		i++;
	}
	ptr[i] = 0;
	return (ptr);
}
