/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 13:25:19 by jbernard          #+#    #+#             */
/*   Updated: 2023/06/22 11:35:36 by mgagnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ctrl_c_heredoc(int sig)
{
	(void)sig;
	ft_putchar_fd('\n', 1);
	exit(0);
}

void	ok(int sig)
{
	(void)sig;
}

// Jump on a clean line
// Tell readline we are on a new line
// Replace readline buffe prompt with emr with empty
// Rewritepty str
void	ctrlc_handle(int sig)
{
	(void)sig;
	ft_putchar_fd('\n', 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	write_result(int e)
{
	int		fd;
	char	*w;

	w = ft_itoa(e);
	fd = open("e", (O_WRONLY | O_CREAT | O_TRUNC), S_IRUSR | S_IWUSR);
	write(fd, w, ft_strlen(w));
	close(fd);
}

void	read_result(t_envlst *envlst, int status)
{
	envlst = is_name_in_envlst(envlst, "?");
	ft_sfree(envlst->value);
	envlst->value = ft_itoa(status);
}
