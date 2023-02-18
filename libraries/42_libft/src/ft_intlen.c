/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 12:25:49 by jbernard          #+#    #+#             */
/*   Updated: 2022/09/10 12:30:33 by jbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_intlen(int x)
{
	if (x >= 1000000000)
		return 10;
	if (x >= 100000000)
		return 9;
	if (x >= 10000000)
		return 8;
	if (x >= 1000000)
		return 7;
	if (x >= 100000)
		return 6;
	if (x >= 10000)
		return 5;
	if (x >= 1000)
		return 4;
	if (x >= 100)
		return 3;
	if (x >= 10)
		return 2;
	return 1;
}