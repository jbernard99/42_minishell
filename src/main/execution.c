/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:26:47 by jbernard          #+#    #+#             */
/*   Updated: 2023/04/03 14:03:08 by jbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include "mng_lst.c"
#include "../../libraries/42_libft/include/libft.h"
//#include "../libraries/readline/includes/readline.h"
//#include "../libraries/readline/includes/history.h"

char *builtins[7] = {"cd", "notecho", "env", "exit", "export", "pwd", "unset"};

char	*ft_strpbrk(const char *str, const char *delim, int *flags)
{
	const char *ptr1;
	const char *ptr2;
	
	ptr1 = str;
	while (*ptr1 != '\0')
	{
		ptr2 = delim;
		while (*ptr2 != '\0')
		{
			if (*ptr1 == '\'' || *ptr1 =='\"')
			{
				if (*ptr1 == '\'')
					*flags ^= QUOTE;
				else if(*ptr1 == '\"')
					*flags ^= DQUOTE;
			}
			if (*ptr1 == *ptr2 && (*flags & (QUOTE | DQUOTE)) == 0)
				return ((char*)ptr1);
			ptr2++;
		}
		ptr1++;
	}
	return (NULL);
}

char	*ft_strtok(char *str, const char *delim, int *flags)
{
	static char	*last_token;
	char		*token;

	if (str != NULL)
		last_token = str;
	else if(last_token == NULL)
		return (NULL);	
	token = last_token;
	last_token = ft_strpbrk(last_token, delim, flags);
	if (last_token)
		*last_token++ = '\0';
	return (token);
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

int cmd_is_builtin(char *cmd)
{
	int i;

	i = 0;
	while (builtins[i])
	{
		if (!ft_strncmp(cmd, builtins[i], ft_strlen(cmd)))
			return (1);
		i++;
	}
	return (0);
}

void	ez_divide(t_cmdlst *cmdlst){
	char	*token;
	size_t	old_size;

	old_size = 0;
	token = ft_strtok(cmdlst->cmd, " ");
	// if (!cmd_is_builtin(token)){
	// 	token = ft_strjoin("/bin/", token);
	// 	printf("Result");
	// }
	while (token != NULL)
	{
		cmdlst->token = realloc(cmdlst->token, old_size + 1);
		cmdlst->token[old_size] = token;
		token = ft_strtok(NULL, " ");
		old_size++;
	}
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
		cmdlst->token[0] = ft_strjoin("/bin/", cmdlst->token[0]);
		printf("Executing execve with path: \"%s\"\n", cmdlst->token[0]);
		i = execve(cmdlst->token[0], cmdlst->token, envp);
		if (i == -1)
			perror("execve error");
	}
}