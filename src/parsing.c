/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagnon <mgagnon@student.42quebec.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 13:33:11 by mgagnon           #+#    #+#             */
/*   Updated: 2023/03/28 13:09:15 by mgagnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	second_divide(t_cmdlst *cmdlst)
{
	char	*token;
	size_t	old_size;

	old_size = 0;
	printf("cmd -> %s\n", cmdlst->cmd);
	token = ft_strtok(cmdlst->cmd, " ");
	printf(" -> %s\n", token);
	while (token != NULL)
	{
		cmdlst->token = realloc(cmdlst->token, old_size + 1);
		token = ft_strtok(NULL, " ");
		cmdlst->token[old_size] = token;
		printf(" -> %s\n", cmdlst->token[old_size]);
		old_size++;
	}
}

t_cmdlst	*get_lst(void)
{
	static t_cmdlst	*cmdlst = NULL;

	return (cmdlst);
}

	/* if quotes or double quotes are used makes sure to skip */ 
	/* over every part between 2 quotes or two double quotes */

void	check_quotes(char *input, size_t *i, int flags)
{
	char	c;

	if (input[*i] == '\'')
	{
		flags |= QUOTE;
		c = '\'';
	}
	else
	{
		flags |= DQUOTE;
		c = '\"';
	}
	(*i)++;
	while (input[*i] && input[*i] != c)
		(*i)++;
}

	/* identify what operand is being used and */ 
	/* if any quotes or double quotes are used */

void	what_is_it(char *input, size_t *i, int flags)
{
	if (input[*i] == '\'' || input[*i] == '\"')
		check_quotes(input, i, flags);
	else if (input[*i] == '&')
	{
		(*i)++;
		if (input[*i] == '&')
		{
			(*i)++;
			flags |= AND;
		}
	}
	else if (input[*i] == '|')
	{
		(*i)++;
		if (input[*i] == '|')
		{
			(*i)++;
			flags = OR;
		}
		else
			flags |= PIPE;
	}
}

	/* makes a first split to separate multiple cmd and looks */ 
	/* for PIPE, AND and OR operand */

void	first_divide(char *input)
{
	t_cmdlst	*cmdlst;
	t_cmdlst	*cur;
	size_t		i;
	size_t		origin;

	i = 0;
	cmdlst = get_lst();
	while (input[i])
	{
		origin = i;
		while (!ft_strrchr("\'\"|&", input[i]))
			i++;
		write(1, "separator found\n", 16);
		cmdlst_addback(&cmdlst, new_cmd_node(ft_strldup(&input[origin], \
						i - origin)));
		cur = cmdlst;
		if(cur->next != NULL)
			cur = cur->next;
		what_is_it(input, &i, cur->flags);
	}
	cur = cmdlst;
	while (cur != NULL)
	{
		second_divide(cur);
		cur = cur->next;
	}
}

/* int	main(int ac, char **av) */
/* { */
/* 	(void)ac; */
/* 	first_divide(av[1]); */
/* 	return (0); */
/* } */
