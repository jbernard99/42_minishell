/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 13:33:11 by mgagnon           #+#    #+#             */
/*   Updated: 2023/06/12 13:45:53 by mgagnon          ###   ########.fr       */
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
		if (input[*i] == ' ')
			*flags |= PIPEI;
		(*i)++;
	}
}

void	quote_handle(char *cmd, size_t *end, int *flags)
{
	if (cmd[*end] == '\'' || cmd[*end] == '\"')
	{
		if (cmd[*end] == '\'')
			*flags ^= QUOTE;
		else if (cmd[*end] == '\"')
			*flags ^= DQUOTE;
		check_quotes(cmd, end, flags);
	}
	(*end)++;
}

/* problem still in second_divide : */
/* 1- don't work with quotes doubles quotes */

void	second_divide(t_cmdlst **cmdlst)
{
	char	*cmd;
	size_t	i;
	size_t	origin;
	size_t	end;

	i = 0;
	end = 0;
	cmd = ft_strdup((*cmdlst)->cmd);
	while (ft_is_whtspc(cmd[end]))
		end++;
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
	ft_sfree(cmd);
}

/* makes a first split to separate multiple cmd and looks */
/* for PIPE */

void	first_divide(char *input, t_cmdlst **cmdlst, t_envlst *envlst)
{
	t_cmdlst	*cur;
	size_t		i;
	size_t		origin;

	i = 0;
	while (input[i])
	{
		origin = i;
		while (!ft_strrchr("|", input[i]) && input[i])
			i++;
		if (ft_strrchr("|", input[i]) && input[i])
			cmdlst_addback(cmdlst, new_node(ft_strldup(&input[origin], \
							(i - 1) - origin), envlst));
		else
			cmdlst_addback(cmdlst, new_node(ft_strldup(&input[origin], \
							i - origin), envlst));
		cur = cmdlst_last(*cmdlst);
		what_is_it(input, &i, &cur->flags);
	}
}

int	make_lst(char *input, t_cmdlst **cmdlst, t_envlst *envlst)
{
	t_cmdlst	*cur;

	first_divide(input, cmdlst, envlst);
	if (finish_flag_set(cmdlst) == 0)
		return (0);
	cur = *cmdlst;
	while (cur != NULL)
	{
		second_divide(&cur);
		if (scan_redirect(cur) == 0)
			return (0);
		cur = cur->next;
	}
	return (1);
}
