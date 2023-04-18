/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 13:40:17 by jbernard          #+#    #+#             */
/*   Updated: 2023/04/18 12:43:03 by jbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
		Exemples :
			cd 									: Return to /home
			cd 'invalid folder' 				: "cd: {invalid folder}: No such file or directory"
			cd 'valid folder'					: Moves current working div to selected folder
			cd 'valid folder' 'invalid folder' 	: Moves current working div to selected folder.
*/


#include "../../includes/minishell.h"

void	ft_cd(char *dirname)
{
	if (chdir(dirname) == 0){
		printf("Not working");
	}
	else{
		printf("Working");
	}
}

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