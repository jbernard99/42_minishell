/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:26:47 by jbernard          #+#    #+#             */
/*   Updated: 2023/04/03 15:30:55 by jbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void print_str_lst(char **lst)
{
	int i = 0;
	while (lst[i])
	{
		printf("List str #%d : %s\n", i, lst[i]);
		i++;
	}
}

// int cmd_is_builtin(char *cmd)
// {
// 	int i;

// 	i = 0;
// 	while (builtins[i])
// 	{
// 		if (!ft_strncmp(cmd, builtins[i], ft_strlen(cmd)))
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

void	ez_divide(t_cmdlst *cmdlst)
{
	char	*token;
	size_t	old_size;

	old_size = 0;
	token = ft_strtok(cmdlst->cmd, " ", &cmdlst->flags);
	// if (!cmd_is_builtin(token)){
	// 	token = ft_strjoin("/bin/", token);
	// 	printf("Result");
	// }
	while (token != NULL)
	{
		cmdlst->token = realloc(cmdlst->token, old_size + 1);
		cmdlst->token[old_size] = token;
		token = ft_strtok(NULL, " ", &cmdlst->flags);
		old_size++;
	}
}