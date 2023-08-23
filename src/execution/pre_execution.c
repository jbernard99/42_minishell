/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_execution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:59:42 by jbernard          #+#    #+#             */
/*   Updated: 2023/08/23 13:27:19 by mgagnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	work_env_vars_calls(t_cmdlst *cmdlst)
{
	int	i;

	while (cmdlst)
	{
		i = 0;
		while (cmdlst->token[i])
		{
			if (cmdlst->token[i][0] != '\'')
			{
				cmdlst->token[i] = rmv_quotes(cmdlst->token[i]);
				while (is_there_env_var(cmdlst->token[i]) != 0)
				{
					cmdlst->token[i] = rplc_env_var(cmdlst->envlst, \
						cmdlst->token[i]);
				}
			}
			else
				cmdlst->token[i] = rmv_quotes(cmdlst->token[i]);
			i++;
		}
		cmdlst = cmdlst->next;
	}
}

void	remove_redirection_from_tokens(t_cmdlst *cmdlst)
{
	char	**n_token;
	size_t	i;
	int		j;

	n_token = ft_calloc(ft_strtablen(cmdlst->token) - 1, sizeof(char *));
	i = 0;
	j = 0;
	while (cmdlst->token[i] && !token_is_redirection(cmdlst->token[i]))
		n_token[j++] = ft_strdup(cmdlst->token[i++]);
		
	if (ft_strcmp(cmdlst->token[i], ">>") == 0 || \
				ft_strcmp(cmdlst->token[i], ">") == 0)
			cmdlst->outfile = ft_strdup(cmdlst->token[++i]);
	else if (ft_strcmp(cmdlst->token[i], "<<") == 0 || \
			ft_strcmp(cmdlst->token[i], "<") == 0)
		cmdlst->infile = ft_strdup(cmdlst->token[++i]);
	while (cmdlst->token[++i])
			n_token[j++] = ft_strdup(cmdlst->token[i]);
	ft_freetabstr(cmdlst->token);
	n_token[j] = NULL;
	cmdlst->token = ft_tabstrdup(n_token);
	ft_freetabstr(n_token);
}

char	*get_file(t_cmdlst *cmdlst, char *type)
{
	int	i;

	i = 0;
	while (cmdlst->token[i + 1])
	{
		if (ft_strcmp(cmdlst->token[i], type) == 0)
			return (cmdlst->token[i + 1]);
		i++;
	}
	return (NULL);
}

void	work_work_redirection(t_cmdlst *cmdlst)
{
	if (cmdlst->flags & R_IN && ft_tabstrcmp(cmdlst->token, "<"))
	{
		remove_redirection_from_tokens(cmdlst);
		//close(cmdlst->red_fd[1]);
	}
	else if (cmdlst->flags & R_OUT && ft_tabstrcmp(cmdlst->token, ">"))
	{
		remove_redirection_from_tokens(cmdlst);
		//close(cmdlst->red_fd[0]);
	}
	else if (cmdlst->flags & APP_OUT && ft_tabstrcmp(cmdlst->token, ">>"))
	{
		remove_redirection_from_tokens(cmdlst);
		//close(cmdlst->red_fd[0]);
	}
	else if (cmdlst->flags & HR_DOC && ft_tabstrcmp(cmdlst->token, "<<"))
	{
		remove_redirection_from_tokens(cmdlst);
		//close(cmdlst->red_fd[1]);
	}
}

int	work_redirection(t_cmdlst *cmdlst)
{
	char	*file;
	char	*type;
	int		i;

	pipe(cmdlst->red_fd);
	i = 0;
	while (cmdlst->token[i])
	{
		if (token_is_redirection(cmdlst->token[i]))
		{
			printf("Token is redirection : %s\n", cmdlst->token[i]);
			type = get_type(cmdlst->token[i]);
			file = get_file(cmdlst, type);
			printf("File name is : %s\n", file);
			if (tell_me_why(&i, file, type, cmdlst) != 1)
				return (0);
		}
		i++;
		ft_cmdlstiter(&cmdlst, print_cmdlst_node);
		printf("Cmdlst->infile : %s\nCmdlst->outfile : %s\n", cmdlst->infile, cmdlst->outfile);
	}
	return (1);
}
