/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:52:21 by mgagnon           #+#    #+#             */
/*   Updated: 2023/06/03 11:15:13 by jbernard         ###   ########.fr       */
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

	input = readline(">> ");
	while (ft_strcmp(input, delim) != 0)
	{
		if (input == NULL)
		{
			free(input);
			return (0);
		}
		write(input_fd, input, sizeof(input));
		free(input);
		input = readline(">> ");
	}
	return (1);
}

int	redirect_in(char *file)
{
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		return (0);
	}
	if (change_stdin(fd) == 0)
		return (0);
	return (fd);
}
