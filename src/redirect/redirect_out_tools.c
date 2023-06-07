/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_out_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 10:09:47 by mgagnon           #+#    #+#             */
/*   Updated: 2023/06/06 15:02:24 by jbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	append(char *file)
{
	int		fd;

	fd = 0;
	fd = open(file, O_WRONLY | O_APPEND);
	if (fd == -1)
	{
		perror("open");
		return (0);
	}
	return (fd);
}

int	redirect_out(char *file)
{
	int		fd;
	
	fd = open(file, O_WRONLY | O_TRUNC);
	if (fd == -1)
	{
		perror("open");
		return (0);
	}
	change_stdout(fd);
	return (fd);
}
