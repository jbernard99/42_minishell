/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 13:42:15 by jbernard          #+#    #+#             */
/*   Updated: 2023/03/28 14:55:54 by jbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Exemples: 
			env : prints env variables without uninitiated vars
			env {invalid folder} :	env: {invalid folder}: No such file or directory
			env {valid folder} :	env: {valid folder}: Permission denied 				EVEN WITH CHMOD 777?
			env {valid file} 	: Nothing, unknown???
*/

#include <stdio.h>
#include <dirent.h>

int	ft_env(char **envp){
	int	i;

	i = 0;
	while (envp[i]){
		if (ft_strlen(get_value(envp[i])) > 0){
			printf("%s\n", envp[i]);
		}
		i++;
	}
	return (0);
}
