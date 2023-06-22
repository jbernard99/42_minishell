/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 13:25:19 by jbernard          #+#    #+#             */
/*   Updated: 2023/06/22 15:12:19 by jbernard         ###   ########.fr       */
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
	ft_putchar_fd('\n', 1);
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

void	read_result(t_envlst *envlst, int status)
{
	envlst = is_name_in_envlst(envlst, "?");
	ft_sfree(envlst->value);
	envlst->value = ft_itoa(status);
}

void	ctrl_bckslsh(int sig)
{
	(void)sig;
	printf("Quit : 3\n");
}
