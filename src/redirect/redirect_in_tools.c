/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagnon <mgagnon@student.42quebec.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:52:21 by mgagnon           #+#    #+#             */
/*   Updated: 2023/05/22 13:25:56 by mgagnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	process_here_doc(void)
{
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

int	redirect_in(int input_fd, char *file)
{
	char	buffer[1024];
	int	fd;
	int	stdin_cpy;
	size_t	rd_bytes;

	stdin_cpy = dup(STDIN_FILENO);
	if (stdin_cpy == -1)
	{
		perror("stdin dup");
		return (0);
	}
	if (change_stdin(&fd) == 0)
		return (0);
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		return (0);
	}
	while ((rd_bytes = read(input_fd, buffer, sizeof(buffer))) > 0)
		write(STDIN_FILENO, buffer, rd_bytes);
	close(fd);
	if (reset_stdin(stdin_cpy) == 0)
		return (0);
	return (1);
}
