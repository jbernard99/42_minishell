/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 13:40:17 by jbernard          #+#    #+#             */
/*   Updated: 2023/05/09 12:23:40 by jbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Exemples :
	cd: Return to /home
	cd 'invalid folder': "cd: {invalid folder}: No such file or directory"
	cd 'valid folder': Moves current working div to selected folder
	cd 'valid folder' 'invalid folder': Moves current working div to selected 
					    folder.
*/

#include "../../includes/minishell.h"

void	manage_pwd(t_envlst *envlst, char *arg)
{
	int	i;

	envlst = is_name_in_envlst(envlst, "PWD");
	i = ft_strlen(envlst->value) - 1;
	if (ft_strcmp(arg, "..") == 0)
	{
		while (envlst->value[i] != '/')
			i--;
		envlst->value[i] = '\0';
	}
	else if (ft_strcmp(arg, ".") != 0)
	{
		envlst->value = ft_strfreejoin(envlst->value, "/");
		envlst->value = ft_strfreejoin(envlst->value, arg);
	}
}

void	ft_cd(char **args, t_envlst *envlst, int fd_out)
{
	(void)fd_out;
	(void)envlst;
	if (chdir(args[1]) == 0)
	{
		manage_pwd(envlst, args[1]);
	}
	else
		printf("minishell: cd: %s: No such file or directory\n", args[1]);
}

/*
	 opendir, readdir, closedir
	 chdir, 
*/






/*
void print_folder_content(void){
	DIR *dir;
	struct dirent *entry;

	dir = opendir(".");
	if (dir == NULL){
		printf("Error");
	}
	while ((entry = readdir(dir)) != NULL){
		printf("%s\n", entry->d_name);
	}
	printf("\n\n\n\n");
	closedir(dir);
}

int main(int argc, char **argv, char **envp){
	(void)argc;
	(void)argv;
	(void)envp;
	
	ft_cd("..");
	print_folder_content();
	ft_cd("main");
	print_folder_content();
	ft_cd("/Users/jbernard/Documents/Cursus/42_minishell");
	printf("%s\n", getenv("PWD"));
	print_folder_content();
	
	return (0);
}
*/
