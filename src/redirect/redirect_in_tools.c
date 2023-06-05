/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:52:21 by mgagnon           #+#    #+#             */
/*   Updated: 2023/06/05 11:20:52 by mgagnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	here_doc(int input_fd, const char *delim)
{
	char	*input;

	input = readline("> ");
	while (ft_strcmp(input, delim) != 0)
	{
		if (input == NULL)
		{
			ft_sfree(input);
			return (0);
		}
		write(input_fd, input, sizeof(input));
		ft_sfree(input);
		input = readline("> ");
	}
	ft_sfree(input);
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
