/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 11:36:59 by jbernard          #+#    #+#             */
/*   Updated: 2021/05/17 15:04:05 by jbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char	*ptr;

	ptr = 0;
	while (1)
	{
		if (*str == (unsigned char)c)
			ptr = (char *)str;
		if (*str == 0)
			break ;
		str++;
	}
	return (ptr);
}
