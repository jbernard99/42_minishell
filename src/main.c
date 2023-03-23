/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 04:31:19 by jbernard          #+#    #+#             */
/*   Updated: 2023/03/23 13:25:24 by jbernard         ###   ########.fr       */
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
		free(input);
		token = ft_strtok(input, delim);
		printf(" -> %s\n", token);
		while (token != NULL){
			token = ft_strtok(NULL, delim);
			printf(" -> %s\n", token);
		}
	}
}

int main() {
	signal(SIGINT, ctrlc_handle);
	prompt_loop();
	return 0;
}