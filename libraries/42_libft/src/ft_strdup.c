/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 14:03:43 by jbernard          #+#    #+#             */
/*   Updated: 2021/05/18 10:30:41 by jbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*ptr;
	size_t	len_str;
	size_t	i;

	len_str = ft_strlen(str);
	ptr = malloc(len_str + 1);
	if (!ptr)
		return (0);
	i = 0;
	while (len_str--)
		ptr[i++] = *str++;
	ptr[i] = 0;
	return (ptr);
}
