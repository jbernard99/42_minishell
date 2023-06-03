/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:52:21 by mgagnon           #+#    #+#             */
/*   Updated: 2023/06/02 20:28:54 by jbernard         ###   ########.fr       */
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

int	redirect_in(char *file)
{
	int		fd;

	fd = open(file, O_RDONLY);
	if (change_stdin(fd) == 0)
		return (0);
	if (fd == -1)
	{
		perror("open");
		return (0);
	}
	return (fd);
}
