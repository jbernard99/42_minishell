/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagnon <mgagnon@student.42quebec.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 13:33:11 by mgagnon           #+#    #+#             */
/*   Updated: 2023/03/27 14:47:45 by mgagnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmdlst	**get_lst(void)
{
	static t_cmdlst	**cmdlst = NULL;
	
	return (cmdlst);
}

void	check_quotes(char *input, int *i, int flags)
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

void	what_is_it(char *input, int *i, int flags)
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

void	first_divide(char *input)
{
	t_cmdlst	**cmdlst;
	int			i;

	i = 0;
	cmdlst = get_lst();
	while (input[i])
	{
		cmdlst_addback(cmdlst,new_cmd_node());
		while (!ft_strrchr("\'\"|&", input[i]))
			i++;
		printf("separator found\n");
		what_is_it(input, &i, (*cmdlst)->flags);
	}
}

int main(int ac, char **av)
{
	(void)ac;
	first_divide(av[1]);
	return (0);
}
