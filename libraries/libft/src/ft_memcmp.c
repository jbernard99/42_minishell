/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 10:09:55 by jbernard          #+#    #+#             */
/*   Updated: 2021/05/17 14:31:29 by jbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	int	rtrn;

	while (n--)
	{
		if (*(char *)str1 != *(char *)str2)
		{
			rtrn = (unsigned char)*(char *)str1 - (unsigned char)*(char *)str2;
			return (rtrn);
		}
		str1++;
		str2++;
	}
	return (0);
}
