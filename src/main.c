/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 04:31:19 by jbernard          #+#    #+#             */
/*   Updated: 2023/03/24 13:18:59 by jbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int is_working;

void ctrlc_handle(){
	ft_putchar_fd('\n', 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
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

int main(int argc, char **argv, char **envp) {
	signal(SIGINT, ctrlc_handle);
	(void)argc;
	(void)argv;
	(void)envp;
	prompt_loop();
	return 0;
}