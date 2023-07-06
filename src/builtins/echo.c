/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 13:40:48 by jbernard          #+#    #+#             */
/*   Updated: 2023/07/06 13:22:02 by jbernard         ###   ########.fr       */
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

void	do_echo(int argc, char **args, int i, int fd_out)
{
	while (i < argc)
	{
		ft_putstr_fd(args[i], fd_out);
		if (++i != argc)
			ft_putchar_fd(' ', fd_out);
	}
}

int	ft_echo(char **args, t_envlst *envlst, int fd_out)
{
	int	argc;
	int	i;
	int	nl;

	(void)envlst;
	nl = 1;
	argc = ft_strtablen(args);
	i = 1;
	if (argc > 1)
	{
		if (!ft_strncmp(args[1], "-n", 2))
		{
			nl = 0;
			args++;
			argc--;
		}
		do_echo(argc, args, i, fd_out);
	}
	if (nl)
		ft_putchar_fd('\n', fd_out);
	return (0);
}
