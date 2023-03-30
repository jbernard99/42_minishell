/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:26:47 by jbernard          #+#    #+#             */
/*   Updated: 2023/03/30 16:02:30 by jbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include "mng_lst.c"
#include "../../libraries/42_libft/include/libft.h"
//#include "../libraries/readline/includes/readline.h"
//#include "../libraries/readline/includes/history.h"

char	*ft_strpbrk(const char *str, const char *delim)
{
	const char *ptr1;
	const char *ptr2;
	
	ptr1 = str;
	while (*ptr1 != '\0'){
		ptr2 = delim;
		while (*ptr2 != '\0'){
			if (*ptr1 == *ptr2){
				return ((char*)ptr1);
			}
			ptr2++;
		}
		ptr1++;
	}
	return (NULL);
}

char	*ft_strtok(char *str, const char *delim){
	static char	*last_token;
	char		*token;

	if (str != NULL)
		last_token = str;
	else if(last_token == NULL)
		return (NULL);
	
	token = last_token;
	last_token = ft_strpbrk(last_token, delim);
	if (last_token)
		*last_token++ = '\0';
	return (token);
}

t_cmdlst	*get_lst(void)
{
	static t_cmdlst	*cmdlst = NULL;

	return (cmdlst);
}

void print_str_lst(char **lst)
{
	int i = 0;
	while (lst[i])
	{
		printf("List str #%d : %s\n", i, lst[i]);
		i++;
	}
}

void	ez_divide(t_cmdlst *cmdlst){
	char	*token;
	size_t	old_size;

	old_size = 0;
	token = ft_strtok(cmdlst->cmd, " ");
	//token = ft_strjoin("/bin/", token);
	while (token != NULL)
	{
		cmdlst->token = realloc(cmdlst->token, old_size + 1);
		cmdlst->token[old_size] = token;
		token = ft_strtok(NULL, " ");
		old_size++;
	}
	cmdlst->token = realloc(cmdlst->token, old_size + 1);
}

char *get_exec_path(char *exec)
{
	char *ret;
	
	ret = "/bin/";
	ret = ft_strjoin(ret, exec);
	return (ret);
}

int	execute(t_cmdlst *cmdlst, char **envp)
{
	char *path = ft_strjoin("/bin/", cmdlst->token[0]);
	printf("Path Sent to execve: %s\n", cmdlst->token[0]);
	path = realloc(path, ft_strlen(path) + 1);
	path[ft_strlen(path) + 1] = '\0';
	return (execve(path, cmdlst->token, envp));
}

int main(int argc, char **argv, char **envp)
{
	int		i;
	
	if (argc == 2){
		t_cmdlst	*cmdlst;
		
		cmdlst = get_lst();
		cmdlst = new_cmd_node(argv[1]);
		ez_divide(cmdlst);

		print_str_lst(cmdlst->token);
		
		// EXECUTION //
		write(1, "Execve:\n", 8);
		i = execute(cmdlst, envp);
		if (i == -1)
			perror("execve error");
	}
}