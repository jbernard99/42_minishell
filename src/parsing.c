/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagnon <mgagnon@student.42quebec.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 13:33:11 by mgagnon           #+#    #+#             */
/*   Updated: 2023/03/24 17:38:49 by mgagnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

enum	e_flags{
	PIPE = 1 << 0,
	AND = 1 << 1,
	OR = 1 << 2,
	QUOTE = 1 << 3,
	DQUOTE = 1 << 4
};

void	check_quotes(char *input, int *i)
{
	char	c;

	if (input[*i] == '\'')
		c = '\'';
	else
		c = '\"';
	(*i)++;
	while (input[*i] && input[*i] != c)
		(*i)++;
}

void	what_is_it(char *input, int *i, int flags)
{
	if (input[*i] == '\'' || input[*i] == '\"')
		check_quotes(input, i);
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

void	first_divide(char *input, int flags)
{
	int	i;

	i = 0;
	while (input[i])
	{
		while (!ft_strrchr("\'\"|&", input[i]))
			i++;
		printf("separator found\n");
		what_is_it(input, &i, flags);
	}
}

int main(int ac, char **av)
{
	int	flags = 0;
	(void)ac;
	first_divide(av[1], flags);
	return (0);
}
