/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagnon <mgagnon@student.42quebec.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 10:09:47 by mgagnon           #+#    #+#             */
/*   Updated: 2023/05/12 13:59:47 by mgagnon          ###   ########.fr       */
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
	if (wr_bytes == -1)
	{
		perror("write");
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}

void	here_doc(const char *delim)
{
	char	*input;

	write(1, "\n", 1);
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
