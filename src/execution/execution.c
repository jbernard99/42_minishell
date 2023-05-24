/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 16:37:35 by jbernard          #+#    #+#             */
/*   Updated: 2023/05/24 14:31:47 by jbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	(*get_built_in(char *name))(char **args, t_envlst *envlst, int fd_out)
{
	static void	(*funcs[3])() = {ft_echo, ft_env, ft_pwd};
	static char	*funcs_name[3] = {"echo", "env", "pwd"};
	int			i;

	i = 0;
	while (i < 3)
	{
		if (ft_strcmp(name, funcs_name[i]) == 0)
			return (funcs[i]);
		i++;
	}
	return (NULL);
}

int	exec_exists(char *exec)
{
	struct stat	buf;

	if (lstat(exec, &buf) == 0)
		return (1);
	else
		return (0);
}

char	*get_exec_location(char *exec, t_envlst *envlst)
{
	char	**path;
	char 	*t_p;
	int		i;

	exec = ft_strjoin("/", exec);
	t_p = is_name_in_envlst(envlst, "PATH")->value;
	if (t_p)
		path = ft_split(t_p, ':');
	else
		path = NULL;
	i = 0;
	while (path && path[i])
	{
		if (exec_exists(ft_strjoin(path[i], exec)))
			return (ft_strjoin(path[i], exec));
		i++;
	}
	return (exec);
}

void	execute_sh(t_cmdlst *cmdlst)
{
	int		e;

	if (!ft_strchr(cmdlst->token[0], '/'))
		cmdlst->token[0] = get_exec_location(cmdlst->token[0], cmdlst->envlst);
	e = execve(cmdlst->token[0], cmdlst->token, get_initiated_from_envlst(cmdlst->envlst));
	if (e == -1)
	{
		printf("bash: %s: command not found\n", &cmdlst->token[0][1]);
		exit(0);
	}
}

void	execution(t_cmdlst *cmdlst)
{
	void	(*func)(char **, t_envlst *, int);

	func = get_built_in(cmdlst->token[0]);
	if (func)
		if (cmdlst->flags & PIPEI)
			func(cmdlst->token, cmdlst->envlst, cmdlst->pipefd[1]);
		else
			func(cmdlst->token, cmdlst->envlst, 1);
	else
		execute_sh(cmdlst);
	exit(0);
}
