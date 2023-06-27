/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 04:31:19 by jbernard          #+#    #+#             */
/*   Updated: 2023/06/27 12:01:59 by mgagnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_readline(char **input)
{
	*input = readline("minishell> ");
	if (!*input)
	{
		printf("\x1B[A\x1B[11Cexit\n");
		return (2);
	}
	if (ft_strcmp(*input, "") == 0)
		return (1);
	if (ft_strlen(*input) > 0)
		add_history(*input);
	return (0);
}

void	prompt_loop(t_envlst *envlst, struct termios o_t, struct termios n_t)
{
	t_cmdlst	*cmdlst;
	char		*input;
	int			yes_or_no;

	while (1)
	{
		cmdlst = NULL;
		yes_or_no = ft_readline(&input);
		if (!yes_or_no)
		{
			yes_or_no = make_lst(input, &cmdlst, envlst);
			ft_sfree(input);
			if (yes_or_no > 0)
				yes_or_no = exec_launch(cmdlst, o_t, n_t);
			else if (yes_or_no == 0)
				perror("syntax error");
			if (cmdlst != NULL && cmdlst->exit != 0)
				return (cmdlst_clear(&cmdlst, &empty_lst));
			cmdlst_clear(&cmdlst, &empty_lst);
		}
		else if (yes_or_no == 2)
			return ;
	}
}

// Disable printing of ^\ when doing ctrl-\ --
// Disable printing of ^c when doing ctrl-c
// Set new settings to current terminal
struct termios	set_new_termios(struct termios old_termios)
{
	struct termios	new_termios;

	new_termios = old_termios;
	new_termios.c_cc[VQUIT] = _POSIX_VDISABLE;
	new_termios.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
	return (new_termios);
}

// first tcgetattr() Get parent terminal settings
//  second one Go back to old terminal settings.
int	main(int argc, char **argv, char **envp)
{
	struct termios	n_term;
	struct termios	o_term;
	t_envlst		*envlst;
	int				e;

	envlst = NULL;
	if (argc > 1 || !*envp)
		return (1);
	create_envlst_from_envp(&envlst, envp);
	tcgetattr(STDIN_FILENO, &o_term);
	n_term = set_new_termios(o_term);
	signal(SIGINT, ctrlc_handle);
	(void)argc;
	(void)argv;
	prompt_loop(envlst, o_term, n_term);
	e = ft_atoi(is_name_in_envlst(envlst, "?")->value);
	free_envlst(envlst);
	tcsetattr(STDIN_FILENO, TCSANOW, &o_term);
	exit(e);
	return (0);
}
