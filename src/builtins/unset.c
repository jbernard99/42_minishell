/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 13:45:05 by jbernard          #+#    #+#             */
/*   Updated: 2023/04/19 15:01:07 by mgagnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/*
unset : 
	Working unset  cases:
		"export test" 	: Var test will be created without any value -> 
		                  MUST NOT SHOW IN "env" AFTER, ONLY IN "export"
		"export"	: print envp in order
		"export x =123" : OR "export x= 123" ERROR '=' must follow var
		                  name (No spaces)
		"export x="	: No value, x will equal ""
		"export x=2"	: 2 will become string "2"
		"export x='Bonjour''Allo'123" : Var x will be 'BonjourAllo123'
*/

void	ft_unset(char **args, char **env, int fd_out)
{
	(void)fd_out;
	envp_remove_line(env, args[0]);
}
