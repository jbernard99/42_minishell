/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_out_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgagnon <mgagnon@student.42quebec.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 10:09:47 by mgagnon           #+#    #+#             */
/*   Updated: 2023/05/18 10:57:10 by mgagnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	reset_stdout(int old_fd)
{
	if (dup2(old_fd, STDOUT_FILENO) == -1)
	{
		perror("STDOUT reset");
		return (0);
	}
	return (1);
}

int	change_stdout(int new_fd)
{
	if (dup2(new_fd, STDOUT_FILENO) == -1)
	{
		perror("dup2 change STDOUT");
		return (0);
	}
	return (1);
}

int	append(int input_fd, char *file)
{
	char	buffer[1024];
	int	fd;
	int	stdout_cpy;
	size_t	rd_bytes;

	stdout_cpy = dup(STDOUT_FILENO);
	if (stdout_cpy == -1)
	{
		perror("stdout dup");
		return (0);
	}
	if (change_stdout(fd) == 0)
		return (0);
	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("open");
		return (0);
	}
	while ((rd_bytes = read(input_fd, buffer, sizeof(buffer))) > 0)
		write(STDOUT_FILENO, buffer, rd_bytes);
	close(fd);
	if (reset_stdout(stdout_cpy) == 0)
		return (0);
	return (1);
}

int	redirect_out(int input_fd, char *file)
{
	char	buffer[1024];
	int	fd;
	int	stdout_cpy;
	size_t	rd_bytes;

	stdout_cpy = dup(STDOUT_FILENO);
	if (stdout_cpy == -1)
	{
		perror("stdout dup");
		return (0);
	}
	if (change_stdout(fd) == 0)
		return (0);
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("open");
		return (0);
	}
	while ((rd_bytes = read(input_fd, buffer, sizeof(buffer))) > 0)
		write(STDOUT_FILENO, buffer, rd_bytes);
	close(fd);
	if (reset_stdout(stdout_cpy) == 0)
		return (0);
	return (1);
}
