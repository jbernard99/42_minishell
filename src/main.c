/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 04:31:19 by jbernard          #+#    #+#             */
/*   Updated: 2023/04/14 14:06:56 by mgagnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void ctrlc_handle(){
	ft_putchar_fd('\n', 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	prompt_loop(void)
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
			ft_cmdlstiter(&cmdlst, &print_cmdlst_node);
			free(input);
			cmdlst_clear(&cmdlst, &empty_lst);
		}
	}
}

int main(int argc, char **argv, char **envp) {
	signal(SIGINT, ctrlc_handle);
	(void)argc;
	(void)envp;
	(void)argv;
	prompt_loop();
	return 0;
}
