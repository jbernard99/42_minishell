/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 13:33:11 by mgagnon           #+#    #+#             */
/*   Updated: 2023/07/03 11:06:04 by mgagnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* identify what operand is being used and */
/* if any quotes or double quotes are used */

void	what_is_it(char *input, size_t *i, int *flags)
{
	if (input[*i] == '|')
	{
		(*i)++;
		*flags |= PIPEI;
	}
}

void	quote_handle(char *cmd, size_t *end, int *flags)
{
	if (cmd[*end] == '\'' || cmd[*end] == '\"')
	{
		if (cmd[*end] == '\'')
			*flags |= QUOTE;
		else if (cmd[*end] == '\"')
			*flags |= DQUOTE;
		check_quotes(cmd, end, flags);
	}
	(*end)++;
}

/* problem still in second_divide : */
/* 1- don't work with quotes doubles quotes */

int	second_divide(t_cmdlst **cmdlst)
{
	char	*cmd;
	size_t	i;
	size_t	origin;
	size_t	end;

	i = 0;
	end = 0;
	cmd = ft_strdup((*cmdlst)->cmd);
	while (cmd[end] && ft_is_whtspc(cmd[end]))
		end++;
	if (!cmd[end])
		return (0);
	(*cmdlst)->token = ft_calloc((ft_strpbrk(cmd, " ", \
					&(*cmdlst)->flags) + 1), sizeof(char *));
	while (end < ft_strlen(cmd) && &(*cmdlst)->token[i])
	{
		origin = end;
		while (cmd[end] && !ft_is_whtspc(cmd[end]))
			quote_handle(cmd, &end, &(*cmdlst)->flags);
		(*cmdlst)->token[i] = ft_strldup(&cmd[origin], end - origin);
		i++;
		while (ft_is_whtspc(cmd[end]))
			end++;
	}
	return (ft_sfree(cmd), 1);
}

/* makes a first split to separate multiple cmd and looks */
/* for PIPE */

int	first_divide(char *input, t_cmdlst **cmdlst, t_envlst *envlst)
{
	t_cmdlst	*cur;
	size_t		i;
	size_t		origin;
	char		*tmp;

	i = 0;
	while (input[i])
	{
		while (ft_is_whtspc(input[i]))
			i++;
		origin = i;
		while (input[i] && !ft_strrchr("|", input[i]))
			i++;
		if (i == origin)
			return (0);
		else
		{
			tmp = ft_strldup(&input[origin], i - origin);
			cmdlst_addback(cmdlst, new_node(tmp, envlst));
			free(tmp);
		}
		cur = cmdlst_last(*cmdlst);
		what_is_it(input, &i, &cur->flags);
	}
	return (1);
}

int	make_lst(char *input, t_cmdlst **cmdlst, t_envlst *envlst)
{
	t_cmdlst	*cur;

	if (!first_divide(input, cmdlst, envlst))
		return (0);
	if (finish_flag_set(cmdlst) == 0)
		return (0);
	cur = *cmdlst;
	while (cur != NULL)
	{
		if (second_divide(&cur) == 0)
			return (-1);
		else if ((*cmdlst)->flags & (QUOTE | DQUOTE))
			return (0);
		if (scan_redirect(cur) == 0)
			return (0);
		cur = cur->next;
	}
	return (1);
}
