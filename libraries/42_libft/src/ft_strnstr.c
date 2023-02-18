/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 23:37:05 by jbernard          #+#    #+#             */
/*   Updated: 2021/05/17 14:49:45 by jbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <string.h>

char	*ft_strnstr(const char *str, const char *to_find, size_t n)
{
	char	*ptr1;
	char	*ptr2;
	size_t	len_to_find;

	if (!*to_find)
		return ((char *)str);
	len_to_find = ft_strlen(to_find);
	if (!ft_strlen(str) || n < len_to_find)
		return (0);
	n -= --len_to_find;
	while (n-- && *str)
	{
		ptr1 = (char *)str;
		ptr2 = (char *)to_find;
		while (*ptr2 && *ptr1 == *ptr2)
		{
			ptr1++;
			ptr2++;
		}
		if (*ptr2 == 0)
			return ((char *)str);
		str++;
	}
	return (0);
}
