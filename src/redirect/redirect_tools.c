/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagnon <mgagnon@student.42quebec.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 10:09:47 by mgagnon           #+#    #+#             */
/*   Updated: 2023/05/15 15:18:36 by mgagnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	append(char *input, char *file)
{
	int	input_len;
	int	fd;
	size_t	wr_bytes;

	input_len = ft_strlen(input);
	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("open");
		return (0);
	}
	wr_bytes = write(fd, input, input_len);
	close(fd);
	if (wr_bytes == -1)
	{
		perror("write");
		return (0);
	}
	return (1);
}

void	here_doc(const char *delim)
{
	char	*input;
	int	pipefd[2];
	pid_t	pid;

	/* write(1, "\n", 1); */
	while (ft_strcmp(input, delim) != 0)
	{
		input = readline("> ");
		if (input == NULL)
		{
			free(input);
			return ;
		}

	}
}
