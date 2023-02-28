/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 11:56:03 by jbernard          #+#    #+#             */
/*   Updated: 2021/05/31 11:56:12 by jbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	get_len(int n)
{
	if (n == 0)
		return (0);
	else
		return (1 + get_len(n / 10));
}

char	*ft_itoa(int n)
{
	char			*ptr;
	int				len;
	unsigned int	temp;

	len = 1 + get_len(n / 10);
	if (n < 0)
	{
		++len;
		temp = -n;
	}
	else
		temp = n;
	ptr = malloc(len + 1);
	if (!(ptr))
		return (0);
	ptr[len] = 0;
	if (n < 0)
		ptr[0] = '-';
	ptr[--len] = '0' + (temp % 10);
	while (temp >= 10)
	{
		temp = temp / 10;
		ptr[--len] = '0' + (temp % 10);
	}
	return (ptr);
}
