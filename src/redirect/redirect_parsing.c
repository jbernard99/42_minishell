/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:36:53 by mgagnon           #+#    #+#             */
/*   Updated: 2023/08/29 13:25:11 by jbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_redirect_flags(char *symbol, int *flags)
{
	if (symbol[0] == '>')
	{
		if (symbol[1] && symbol[1] == '>')
			*flags |= APP_OUT;
		else
			*flags |= R_OUT;
	}
	else if (symbol[0] == '<')
	{
		if (symbol[1] && symbol[1] == '<')
			*flags |= HR_DOC;
		else
			*flags |= R_IN;
	}
}

int	check_filename(char *file)
{
	int	i;

	i = 0;
	while (file[i])
	{
		if (ft_isalnum(file[i]) == 0 && file[i] != '.' && file[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	check_file(char *file, char *type)
{
	int	status;
	int	fd;

	if (file == NULL || check_filename(file) == 0)
		return (0);
	if (ft_strcmp("<", type) == 0)
	{
		status = access(file, F_OK | R_OK);
		if (status == -1)
			return (0);
	}
	else if (ft_strcmp(">", type) == 0 || ft_strcmp(">>", type) == 0)
	{
		status = access(file, F_OK);
		if (status == -1)
		{
			fd = open(file, O_CREAT, S_IRUSR | S_IWUSR);
			close(fd);
		}
		status = access(file, W_OK);
		if (status == -1)
			return (0);
	}
	return (1);
}

int	scan_redirect(t_cmdlst *cmdlst)
{
	int		i;

	i = 0;
	while (cmdlst->token[i])
	{
		if (ft_strrchr("<>", cmdlst->token[i][0]))
		{
			set_redirect_flags(cmdlst->token[i], &cmdlst->flags);
			if ((cmdlst->flags & (APP_OUT | HR_DOC)) \
					&& ft_strlen(cmdlst->token[i]) > 2)
				return (0);
			else if ((cmdlst->flags & (R_IN | R_OUT)) && \
					ft_strlen(cmdlst->token[i]) > 1)
				return (0);
		}
		i++;
	}
	return (1);
}
