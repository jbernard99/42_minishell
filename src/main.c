/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 04:31:19 by jbernard          #+#    #+#             */
/*   Updated: 2023/03/02 11:03:23 by jbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int is_working;

void ctrlc_handle(){
	is_working = 0
}

int main() {
    //Init Signals
	while (1){
		is_working = 1;
		signal(SIGINT, ctrlc_handle);
		while (is_working){
			char* input = readline("minishell> ");
			//If null, quit (CTRL-D)
			printf("You entered: %s\n", input);
			add_history(input);
			free(input);
		}
	}
        return 0;
}