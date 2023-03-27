/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 06:43:50 by jbernard          #+#    #+#             */
/*   Updated: 2023/03/06 11:03:39 by jbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strpbrk(const char *str, const char *delim)
{
	const char *ptr1;
	const char *ptr2;
	
	ptr1 = str;
	while (*ptr1 != '\0'){
		ptr2 = delim;
		while (*ptr2 != '\0'){
			if (*ptr1 == *ptr2){
				return ((char*)ptr1);
			}
			ptr2++;
		}
		ptr1++;
	}
	return (NULL);
}

char	*ft_strtok(char *str, const char *delim){
	static char	*last_token;
	char		*token;

	if (str != NULL)
		last_token = str;
	else if(last_token == NULL)
		return (NULL);
	
	token = last_token;
	last_token = ft_strpbrk(last_token, delim);
	if (last_token)
		*last_token++ = '\0';
	return (token);
}
