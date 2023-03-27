/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 04:31:19 by jbernard          #+#    #+#             */
/*   Updated: 2023/03/26 22:34:18 by jbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <termios.h>

void ctrlc_handle(){
	ft_putchar_fd('\n', 1); 							// Jump on a clean line
	rl_on_new_line();									// Tell readline we are on a new line
	rl_replace_line("", 0);								// Replace readline buffer with empty
	rl_redisplay();										// Rewrite prompt with empty str
}

void sigquit_handle(int sig){
	//It's not because a function does nothing that it's useless
	(void)sig;
}

void	prompt_loop(void){
	char *token;
	char *delim = " ";

	while (1){
		char* input = readline("minishell$ ");
		if (input == NULL)
			exit(0);
		add_history(input);								// Add current input to the history list
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
	new_termios.c_cc[VQUIT] = _POSIX_VDISABLE;			// Disable printing of ^\ when doing ctrl-\ --
	new_termios.c_lflag &= ~ECHOCTL;					// Disable printing of ^c when doing ctrl-c
	tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);		// Set new settings to current terminal
}

int main(int argc, char **argv, char **envp) {
	struct termios old_termios;
	
	tcgetattr(STDIN_FILENO, &old_termios);				// Get parent terminal settings
	set_new_termios(old_termios);
	
	signal(SIGINT, ctrlc_handle);
	signal(SIGQUIT, sigquit_handle);
	
	(void)argc;
	(void)argv;
	(void)envp;
	
	prompt_loop();
	tcsetattr(STDIN_FILENO, TCSANOW, &old_termios);		// Go back to old terminal settings.
	
	return 0;
}