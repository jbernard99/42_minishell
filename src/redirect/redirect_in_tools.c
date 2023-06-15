/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:52:21 by mgagnon           #+#    #+#             */
/*   Updated: 2023/06/10 22:11:17 by jbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	here_doc(const char *delim)
{
	char	*input;
	int		fd[2];

	pipe(fd);
	input = readline("> ");
	while (ft_strcmp(input, delim) != 0)
	{
		input = ft_strfreejoin(input, "\n");
		if (input == NULL)
		{
			ft_sfree(input);
			return (0);
		}
		write(fd[1], input, ft_strlen(input));
		ft_sfree(input);
		input = readline("> ");
	}
	ft_sfree(input);
	close(fd[1]);
	change_stdin(fd[0]);
	return (fd[0]);
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
