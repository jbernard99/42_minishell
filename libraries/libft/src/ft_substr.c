/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 16:54:43 by jbernard          #+#    #+#             */
/*   Updated: 2021/06/18 21:31:42 by kneegher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	slen;

	slen = ft_strlen(s);
	if (!s || slen <= start || !len)
		return (ft_strdup(""));
	if (len >= slen - start)
		len = slen - start;
	ptr = malloc(++len);
	if (!ptr)
		return (0);
	ft_strlcpy(ptr, s + start, len);
	return (ptr);
}
