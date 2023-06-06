/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:52:21 by mgagnon           #+#    #+#             */
/*   Updated: 2023/06/06 14:39:47 by jbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_tabstrcmp(char **token, const char *str)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (ft_strcmp(token[i], str) == 0)
			return (token[i]);
		i++;
	}
	return (NULL);
}

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
