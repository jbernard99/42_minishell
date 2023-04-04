/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 06:43:50 by jbernard          #+#    #+#             */
/*   Updated: 2023/04/04 15:06:33 by mgagnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdint.h>

void	print_cmdlst_node(t_cmdlst *node)
{
	int	i;

	if (!node)
		return ;
	i = 0;
	if (node->cmd)
		printf("cmd -> %s\n", node->cmd);
	while(node->token[i])
	{
		if (node->token[i] != NULL)
			printf("token[%i] -> %s\n", i, node->token[i]);
		i++;
	}
	print_flags(node->flags);
}

void	ft_cmdlstiter(t_cmdlst **cmdlst, void (*f)(t_cmdlst *))
{
	t_cmdlst	*cur;

	if (!cmdlst || !f)
		return ;
	cur = *cmdlst;
	while (cur)
	{
		f(cur);
		cur = cur->next;
	}
}

void	empty_lst(t_cmdlst *cmdlst)
{
	int	i;

	i = 0;
	if (cmdlst->cmd)
		free(cmdlst->cmd);
	if (cmdlst->token)
	{
		while(cmdlst->token[i])
		{
			free(cmdlst->token[i]);
			i++;
		}
	}
}

char	*ft_strpbrk(const char *str, const char *delim, int *flags)
{
	const char *ptr1;
	const char *ptr2;
	
	ptr1 = str;
	while (*ptr1 != '\0')
	{
		ptr2 = delim;
		while (*ptr2 != '\0')
		{
			if (*ptr1 == '\'' || *ptr1 =='\"')
			{
				if (*ptr1 == '\'')
					*flags ^= QUOTE;
				else if(*ptr1 == '\"')
					*flags ^= DQUOTE;
			}
			if (*ptr1 == *ptr2 && (*flags & (QUOTE | DQUOTE)) == 0)
				return ((char*)ptr1);
			ptr2++;
		}
		ptr1++;
	}
	return (NULL);
}

char	*ft_strtok(char *str, const char *delim, int *flags)
{
	static char	*last_token;
	char		*token;

	if (str != NULL)
		last_token = ft_strdup(str);
	else if(last_token == NULL)
	{
		free(last_token);
		return (NULL);
	}
	token = last_token;
	last_token = ft_strpbrk(last_token, delim, flags);
	if (last_token)
		*last_token++ = '\0';
	return (token);
}

char	*ft_strldup(const char *str, size_t len)
{
	char	*ptr;
	size_t	i;

	ptr = malloc(len + 1);
	if (!ptr)
		return (0);
	i = 0;
	while (len--)
		ptr[i++] = *str++;
	ptr[i] = 0;
	return (ptr);
}
