/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 04:31:19 by jbernard          #+#    #+#             */
/*   Updated: 2023/05/30 11:04:03 by jbernard         ###   ########.fr       */
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

int		ft_readline(char **input, t_envlst *envlst)
{
	*input = readline("minishell> ");
	if (!*input)
	{
		printf("\x1B[u\x1B[Aexit\n");
		ft_end(NULL, envlst);
	}
	if (ft_strcmp(*input, "") == 0)
		return (1);
	if (ft_strlen(*input) > 0)
		add_history(*input);
	return (0);
}

// \x1B = start escape sequence 
// 	printf escape sequence on line 42
// 		[s = save cursor current position
// 	printf escape sequence on line 46
// 		[u = return cursor last position 
// 		[A = bring cursor up a line
void	prompt_loop(t_envlst *envlst)
{
	t_cmdlst	*cmdlst;
	char		*input;
	int			yes_or_no;

	while (1)
	{
		cmdlst = NULL;
		yes_or_no = ft_readline(&input, envlst);
		if (!yes_or_no)
		{
			yes_or_no = make_lst(input, &cmdlst, envlst);
			free(input);
			work_env_vars_calls(cmdlst);
			if (yes_or_no > 0)
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

	if (argc > 1 || !*envp)
		return (1);
	create_envlst_from_envp(&envlst, envp);
	tcgetattr(STDIN_FILENO, &old_termios);
	set_new_termios(old_termios);
	signal(SIGINT, ctrlc_handle);
	(void)argc;
	(void)argv;
	prompt_loop(envlst);
	tcsetattr(STDIN_FILENO, TCSANOW, &old_termios);
	return (0);
}
