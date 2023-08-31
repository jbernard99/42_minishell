/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 16:37:35 by jbernard          #+#    #+#             */
/*   Updated: 2023/08/31 12:49:05 by jbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	(*get_built_in(char *name))(char **args, t_envlst *envlst, int fd_out)
{
	static int	(*funcs[4])() = {ft_echo, ft_env, ft_pwd, ft_export};
	static char	*funcs_name[4] = {"echo", "env", "pwd", "export"};
	int			i;

	i = 0;
	while (i < 4 && name)
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
	char		**path;
	char		*n_exec;
	int			i;

	exec = ft_strjoinfree("/", exec);
	envlst = is_name_in_envlst(envlst, "PATH");
	if (envlst)
		path = ft_split(envlst->value, ':');
	else
		return (exec);
	i = 0;
	while (path[i])
	{
		n_exec = ft_strjoin(path[i], exec);
		if (exec_exists(n_exec))
		{
			ft_sfree(exec);
			path = ft_freetabstr(path);
			return (n_exec);
		}
		ft_sfree(n_exec);
		i++;
	}
	path = ft_freetabstr(path);
	return (exec);
}

void	execute_sh(t_cmdlst *cmdlst)
{
	int			e;
	char		**envp;

	e = 0;
	if (cmdlst->token[0])
	{
		if (!ft_strchr(cmdlst->token[0], '/'))
			cmdlst->token[0] = get_exec_location(cmdlst->token[0], \
					cmdlst->envlst);
		envp = get_initiated_from_envlst(cmdlst->envlst);
		e = execve(cmdlst->token[0], cmdlst->token, envp);
		ft_freetabstr(envp);
	}
	if (cmdlst->flags & PIPEI)
		close(cmdlst->pipefd[1]);
	if (e == -1)
	{
		ft_putstr_fd("minishell: Command not found.\n", 2);
		ft_end(cmdlst, cmdlst->envlst, 127);
	}
}

void	execution(t_cmdlst *cmdlst)
{
	int	status;
	int	(*func)(char **, t_envlst *, int);

	status = 0;
	func = get_built_in(cmdlst->token[0]);
	if (func)
	{
		if (cmdlst->flags & (R_OUT | APP_OUT))
			status = func(cmdlst->token, cmdlst->envlst, cmdlst->red_fd[0]);
		else if (cmdlst->flags & PIPEI)
			status = func(cmdlst->token, cmdlst->envlst, cmdlst->pipefd[1]);
		else
			status = func(cmdlst->token, cmdlst->envlst, 1);
	}
	else
		execute_sh(cmdlst);
	if (status != 0)
		exit(1);
	exit(0);
}
