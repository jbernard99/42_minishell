/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:52:21 by mgagnon           #+#    #+#             */
/*   Updated: 2023/05/22 16:46:47 by jbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	here_doc(int input_fd, const char *delim)
{
	char	*input;

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

	fd = 0;
	stdin_cpy = dup(STDIN_FILENO);
	if (stdin_cpy == -1)
	{
		perror("stdin dup");
		return (0);
	}
	if (change_stdin(fd) == 0)
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
