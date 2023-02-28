/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dectohex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 14:22:31 by jbernard          #+#    #+#             */
/*   Updated: 2022/09/19 14:25:03 by jbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_dectohex(unsigned long long n, char *base)
{
	int		temp;
	char	rtrn[99];
	char	*ptr;
	int		i;

	if (n == 0)
	{
		ptr = malloc(2 * sizeof(char));
		ptr[0] = '0';
		ptr[1] = '\0';
		return (ptr);
	}
	i = 0;
	while (n > 0)
	{
		temp = n % 16;
		rtrn[i++] = base[temp];
		n = n / 16;
	}
	rtrn[i] = '\0';
	ptr = ft_strrev(rtrn);
	return (ptr);
}