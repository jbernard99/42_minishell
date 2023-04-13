/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 13:33:11 by mgagnon           #+#    #+#             */
/*   Updated: 2023/04/13 16:41:16 by jbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	second_divide(t_cmdlst **cmdlst)
{
	char	*cmd;
	size_t	i;
	size_t	origin;
	size_t	end;

	i = 0;
	end = 0;
	origin = 0;
	cmd = ft_strdup((*cmdlst)->cmd);
	while (end < ft_strlen(cmd))
	{
		origin = end;
		(*cmdlst)->token = realloc((*cmdlst)->token, \
				(sizeof(char *) * (i + 1)));
		ft_strpbrk(cmd, " " , &(*cmdlst)->flags, &end);
		if (cmd[end] == ' '){
			(*cmdlst)->token[i] = ft_strldup(&cmd[origin], (end) - origin);
		}
		else{
			(*cmdlst)->token[i] = ft_strldup(&cmd[origin], end - origin);
			(*cmdlst)->token = realloc((*cmdlst)->token, (sizeof(char *) * (i + 2)));
			(*cmdlst)->token[i+2] = "\0";
		}
		i++;
		end++;
	}
	free(cmd);
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
		while (!ft_strrchr("|&><", input[i]))
			i++;
		if (ft_strrchr("|&", input[i]) && input[i])
			cmdlst_addback(cmdlst, \
					new_node(ft_strldup(&input[origin], \
							(i - 1) - origin)));
		else
			cmdlst_addback(cmdlst, new_node(ft_strldup(&input[origin], \
							i - origin)));
		cur = cmdlst_last(*cmdlst);
		what_is_it(input, &i, &cur->flags);
	}
}

void	make_lst(char *input, t_cmdlst **cmdlst)
{
	t_cmdlst	*cur;

	first_divide(input, cmdlst);
	finish_flag_set(cmdlst);
	cur = *cmdlst;
	while (cur != NULL)
	{
		second_divide(&cur);
		cur = cur->next;
	}
}
