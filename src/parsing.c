/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagnon <mgagnon@student.42quebec.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 13:33:11 by mgagnon           #+#    #+#             */
/*   Updated: 2023/04/05 11:20:30 by mgagnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_flags(int flags)
{
	if (flags & PIPEI)
		printf("PIPEI: ON, ");
	else
		printf("PIPEI: OFF, ");
	if (flags & PIPEO)
		printf("PIPEO: ON, ");
	else
		printf("PIPEO: OFF, ");
	if (flags & ANDI)
		printf("ANDI: ON, ");
	else
		printf("ANDI: OFF, ");
	if (flags & ANDO)
		printf("ANDO: ON, ");
	else
		printf("ANDO: OFF, ");
	if (flags & ORI)
		printf("ORI: ON, ");
	else
		printf("ORI: OFF, ");
	if (flags & ORO)
		printf("ORO: ON\n");
	else
		printf("ORO: OFF\n");
}

void	second_divide(t_cmdlst **cmdlst)
{
	char	*token;
	char	*cmd;
	size_t	i;

	i = 1;
	cmd = ft_strdup((*cmdlst)->cmd);
	/* printf("cmd -> %s\n", (*cmdlst)->cmd); */
	token = ft_strtok(cmd, " ", &(*cmdlst)->flags);
	while (token != NULL)
	{
		(*cmdlst)->token = realloc((*cmdlst)->token, (sizeof(char *) * (i + 1)));
		(*cmdlst)->token[(i - 1)] = ft_strdup(token);
		token = ft_strtok(NULL, " ", &(*cmdlst)->flags);
		/* printf(" -> %s\n", (*cmdlst)->token[i]); */
		i++;
	}
	/* printf(" -> %s\n", (*cmdlst)->token[i]); */
}

t_cmdlst	*get_lst(void)
{
	static t_cmdlst	*cmdlst = NULL;

	return (cmdlst);
}

	/* if quotes or double quotes are used makes sure to skip */ 
	/* over every part between 2 quotes or two double quotes */

void	check_quotes(char *input, size_t *i, int *flags)
{
	char	c;

	if (input[*i] == '\'')
	{
		*flags |= QUOTE;
		c = '\'';
	}
	else
	{
		*flags |= DQUOTE;
		c = '\"';
	}
	(*i)++;
	while (input[*i] && input[*i] != c)
		(*i)++;
}

	/* identify what operand is being used and */ 
	/* if any quotes or double quotes are used */

void	what_is_it(char *input, size_t *i, int *flags)
{
	if (input[*i] == '&')
	{
		(*i)++;
		if (input[*i] == '&')
		{
			(*i)++;
			*flags |= ANDI;
		}
		(*i)++;
	}
	else if (input[*i] == '|')
	{
		(*i)++;
		if (input[*i] == '|')
		{
			(*i)++;
			*flags |= ORI;
		}
		else
			*flags |= PIPEI;
		(*i)++;
	}
}
void	finish_flag_set(t_cmdlst **cmdlst)
{
	t_cmdlst	*cur;

	cur = *cmdlst;
	while (cur->next != NULL)
	{
		if (cur->flags & PIPEI)
			cur->next->flags |= PIPEO;
		else if (cur->flags & ORI)
			cur->next->flags |= ORO;
		else if (cur->flags & ANDI)
			cur->next->flags |= ANDO;
		cur = cur->next;
	}
}

	/* makes a first split to separate multiple cmd and looks */ 
	/* for PIPE, AND and OR operand */

void	first_divide(char *input, t_cmdlst **cmdlst)
{
	t_cmdlst	*cur;
	size_t		i;
	size_t		origin;

	i = 0;
	while (input[i])
	{
		origin = i;
		while (!ft_strrchr("|&", input[i]))
			i++;
		if (ft_strrchr("|&", input[i]))
			cmdlst_addback(cmdlst, \
					new_node(ft_strldup(&input[origin], \
							(i - 1) - origin)));
		else
			cmdlst_addback(cmdlst, new_node(ft_strldup(&input[origin], \
							i - origin)));
		cur = cmdlst_last(*cmdlst);
		what_is_it(input, &i, &cur->flags);
	}
	cur = *cmdlst;
	finish_flag_set(cmdlst);
	while (cur != NULL)
	{
		second_divide(&cur);
		cur = cur->next;
	}
}

/* int	main(int ac, char **av) */
/* { */
/* 	(void)ac; */
/* 	first_divide(av[1]); */
/* 	return (0); */
/* } */
