/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagnon <mgagnon@student.42quebec.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:52:21 by mgagnon           #+#    #+#             */
/*   Updated: 2023/05/16 15:14:10 by mgagnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	reset_stdin(int old_fd)
{
	if (dup2(old_fd, STDIN_FILENO) == -1)
	{
		perror("reset STDIN");
		return (0);
	}
	return (1);
}

int	change_stdin(int new_fd)
{
	if (dup2(new_fd, STDIN_FILENO) == -1)
	{
		perror("dup2 change STDIN");
		return (0);
	}
	return (1);
}

int	here_doc(int input_fd, const char *delim)
{
	char	*input;
	int	pipefd[2];
	pid_t	pid;

	while (ft_strcmp(input, delim) != 0)
	{
		input = readline("> ");
		if (input == NULL)
		{
			free(input);
			return (0);
		}
		write(input_fd, input, sizeof(input));
	}
	return (1);
}
