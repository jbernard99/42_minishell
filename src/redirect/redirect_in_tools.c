/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:52:21 by mgagnon           #+#    #+#             */
/*   Updated: 2023/09/26 20:32:59 by jbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	loop_here_doc(char **eof)
{
	int		i;
	int		fd[2];
	char	*input;

	pipe(fd);
	i = 0;
	while (eof[i] != NULL)
	{
		input = here_doc(eof[i]);
		i++;
	}
	write(fd[1], input, ft_strlen(input));
	ft_sfree2(input);
	close(fd[1]);
	change_stdin(fd[0]);
	return (fd[0]);
}

char	*here_doc(const char *delim)
{
	char	*input;
	char	*ret;

	ret = ft_calloc(1, sizeof(char *));
	input = readline("> ");
	while (ft_strcmp(input, delim) != 0)
	{
		if (input == NULL)
		{
			ft_sfree(input);
			return (0);
		}
		input = ft_strfreejoin(input, "\n");
		ret = ft_strfreejoinfree(ret, input);
		input = readline("> ");
	}
	return (ret);
}

int	redirect_in(char *file)
{
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror("open in");
		return (0);
	}
	if (change_stdin(fd) == 0)
		return (0);
	return (fd);
}
