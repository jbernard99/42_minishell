/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 16:37:35 by jbernard          #+#    #+#             */
/*   Updated: 2023/05/22 15:59:36 by jbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	(*get_built_in(char *name))(char **args, t_envlst *envlst, int fd_out)
{
	static void	(*funcs[7])() = {ft_cd, ft_echo, ft_env, ft_exit, \
		ft_export, ft_pwd, ft_unset};
	static char	*funcs_name[7] = {"cd", "echo", "env", "exit", \
		"export", "pwd", "unset"};
	int			i;

	i = 0;
	while (i < 7)
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

char	*get_exec_location(t_envlst *envlst, char *exec)
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
		cmdlst->token[0] = get_exec_location(cmdlst->envlst, cmdlst->token[0]);
	e = execve(cmdlst->token[0], cmdlst->token, get_initiated_from_envlst(cmdlst->envlst));
	if (e == -1)
	{
		printf("bash: %s: command not found\n", &cmdlst->token[0][1]);
		exit(0);
	}
}

// ----------------------

int	reset_stdin(int old_fd)
{
	if (dup2(old_fd, STDIN_FILENO) == -1)
	{
		perror("reset STDIN");
		return (0);
	}
	return (1);
}

int	change_stdin(int *new_fd)
{
	if (dup2(*new_fd, STDIN_FILENO) == -1)
	{
		perror("dup2 change STDIN");
		return (0);
	}
	return (1);
}

void	pipe_it(t_cmdlst *cmdlst)
{
	int	fd[2];

	pipe(fd);
	cmdlst->pipefd[1] = fd[1];
	cmdlst->next->pipefd[0] = fd[0];
}

int	change_stdout(int *new_fd)
{
	if (dup2(*new_fd, STDOUT_FILENO) == -1)
	{
		perror("dup2 change STDOUT");
		return (0);
	}
	return (1);
}

int	reset_stdout(int old_fd)
{
	if (dup2(old_fd, STDOUT_FILENO) == -1)
	{
		perror("STDOUT reset");
		return (0);
	}
	return (1);
}

int exectry(t_cmdlst *cmdlst)
{
	pid_t	pid;
	int 	old_stds[2];
	
	while (cmdlst != NULL)
	{
		if (cmdlst->flags & PIPEI)
			pipe_it(cmdlst);
		pid = fork();
		if (pid < 0)
			perror("ERROR");
		else if (pid == 0)
		{
			if (cmdlst->flags & PIPEI)
			{
				old_stds[1] = dup(STDOUT_FILENO);
				change_stdout(&cmdlst->pipefd[1]);
			}
			if (cmdlst->flags & PIPEO)
			{
				old_stds[0] = dup(STDIN_FILENO);
				change_stdin(&cmdlst->pipefd[0]);
			}
			execution(cmdlst);
		}
		else
		{
			wait(NULL);
			if (cmdlst->flags & PIPEI)
			{
				reset_stdin(old_stds[0]);
				close(cmdlst->pipefd[1]);	
			}
			if (cmdlst->flags & PIPEO)
			{
				reset_stdout(old_stds[1]);
				close(cmdlst->pipefd[0]);
			}
			
		}
		cmdlst = cmdlst->next;
	}
	return (1);
}


void	execution(t_cmdlst *cmdlst)
{
	void	(*func)(char **, t_envlst *envlst, int);
	
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
