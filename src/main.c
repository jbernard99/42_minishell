/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 04:31:19 by jbernard          #+#    #+#             */
/*   Updated: 2023/03/24 15:15:25 by jbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <termios.h>

int is_working;

void ctrlc_handle(){
	ft_putchar_fd('\n', 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void ctrlslash_handle(int sig){
	(void)sig;
}

void	prompt_loop(void){
	char *token;
	char *delim = " ";

	while (1){
		char* input = readline("minishell> ");
		if (input == NULL)
			exit(0);
		add_history(input);
		token = ft_strtok(input, delim);
		printf(" -> %s\n", token);
		while (token != NULL){
			token = ft_strtok(NULL, delim);
			printf(" -> %s\n", token);
		}
		free(input);
	}
}

void set_new_termios(struct termios old_termios){
	struct termios new_termios;
	
	new_termios = old_termios;
	new_termios.c_cc[VQUIT] = _POSIX_VDISABLE;
	new_termios.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
}

int main(int argc, char **argv, char **envp) {
	struct termios old_termios;
	
	tcgetattr(STDIN_FILENO, &old_termios);
	set_new_termios(old_termios);
	
	signal(SIGINT, ctrlc_handle);
	signal(SIGQUIT, ctrlslash_handle);
	
	(void)argc;
	(void)argv;
	(void)envp;
	
	prompt_loop();
	tcsetattr(STDIN_FILENO, TCSANOW, &old_termios);
	
	return 0;
}