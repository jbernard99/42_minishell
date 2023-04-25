/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 13:40:48 by jbernard          #+#    #+#             */
/*   Updated: 2023/04/24 16:23:52 by jbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	# Options
		-n
	
	Exemples:
				echo : prints empty newline
				echo x : prints "x\n"
				echo bonjour x : prints "bonjour x\n"
				echo -n : Prints nothing
				echo -n bonjour : prints "bonjour" (No newline)
				echo "Bonjour" "Allo" : prints "Bonjour Allo"
				               (With space in between each args)
*/

#include "../../includes/minishell.h"

void	ft_echo(char **args, char ***envp, int fd_out)
{
	int	argc;
	int	i;
	int	nl;
	
	(void)envp;
	nl = 1;
	if (!ft_strncmp(args[1], "-n", 2))
	{
		nl = 0;
		args++;
	}
	argc = ft_strtablen(args);
	i = 1;
	while (i < argc)
	{
		ft_putstr_fd(args[i], fd_out);
		if (i != argc - 1)
			ft_putchar_fd(' ', fd_out);
		i++;
	}
	if (nl)
		ft_putchar_fd('\n', fd_out);
}
