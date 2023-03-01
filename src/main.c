/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 04:31:19 by jbernard          #+#    #+#             */
/*   Updated: 2023/02/16 06:00:56 by jbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int main() {
    //Init Signals
    while (1){
        char* input = readline("minishell> ");
        //If null, quit (CTRL-D)
        printf("You entered: %s\n", input);
        add_history(input);
        free(input);
    }
        return 0;
}