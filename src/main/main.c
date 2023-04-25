/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 04:31:19 by jbernard          #+#    #+#             */
/*   Updated: 2023/04/23 14:05:43 by jbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Jump on a clean line
// Tell readline we are on a new line
// Replace readline buffer with empty
// Rewrite prompt with empty str
void	ctrlc_handle(int sig)
{
	(void)sig;
	ft_putchar_fd('\n', 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

//It's not because a function does nothing that it's useless
void	sigquit_handle(int sig)
{
	write(1, "exit\n", 5);
	(void)sig;
}

void	prompt_loop(char **envp)
{
	t_cmdlst	*cmdlst;
	char		*input;

	while (1)
	{
		cmdlst = NULL;
		input = readline("minishell> ");
		if (input == NULL)
		{
			free(input);
			exit(0);
		}
		if (ft_strlen(input) != 0)
		{
			add_history(input);
			make_lst(input, &cmdlst);
			free(input);
			cmdlst->envp = &envp;
			execution(cmdlst);
			cmdlst_clear(&cmdlst, &empty_lst);
		}
	}
}

// Disable printing of ^\ when doing ctrl-\ --
// Disable printing of ^c when doing ctrl-c
// Set new settings to current terminal
void	set_new_termios(struct termios old_termios)
{
	struct termios	new_termios;

	new_termios = old_termios;
	new_termios.c_cc[VQUIT] = _POSIX_VDISABLE;
	new_termios.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
}

// first tcgetattr() Get parent terminal settings
//  second one Go back to old terminal settings.
int	main(int argc, char **argv, char **envp)
{
	struct termios	old_termios;

	tcgetattr(STDIN_FILENO, &old_termios);
	set_new_termios(old_termios);
	signal(SIGINT, ctrlc_handle);
	signal(SIGQUIT, sigquit_handle);
	(void)argc;
	(void)argv;
	envp = ft_tabstrdup(envp);
	prompt_loop(envp);
	tcsetattr(STDIN_FILENO, TCSANOW, &old_termios);
	return (0);
}
