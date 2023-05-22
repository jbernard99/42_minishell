/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 04:31:19 by jbernard          #+#    #+#             */
/*   Updated: 2023/05/22 16:42:33 by jbernard         ###   ########.fr       */
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

void	prompt_loop(t_envlst *envlst)
{
	t_cmdlst	*cmdlst;
	char		*input;

	while (1)
	{
		cmdlst = NULL;
		input = readline("minishell> \x1B[s");
		if (input == NULL)
		{
			free(input);
			printf("\x1B[u\x1B[Aexit\n");
			exit(0);
		}
		if (ft_strlen(input) != 0)
		{
			add_history(input);
			make_lst(input, &cmdlst, envlst);
			free(input);
			exec_fork(cmdlst);
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
	t_envlst		*envlst;


	create_envlst_from_envp(&envlst, envp);
	//char **n_envp = get_envp_from_envlst(envlst);
	//put_envp(n_envp);
	tcgetattr(STDIN_FILENO, &old_termios);
	set_new_termios(old_termios);
	signal(SIGINT, ctrlc_handle);
	(void)argc;
	(void)argv;
	prompt_loop(envlst);
	tcsetattr(STDIN_FILENO, TCSANOW, &old_termios);
	return (0);
}
