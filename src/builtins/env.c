/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 13:42:15 by jbernard          #+#    #+#             */
/*   Updated: 2023/03/24 13:42:23 by jbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Exemples: 
			env : prints env variables without uninitiated vars
			env {invalid folder} :	env: {invalid folder}: No such file or directory
			env {valid folder} :	env: {valid folder}: Permission denied 				EVEN WITH CHMOD 777?
			env {valid file} 	: Nothing, unknown???
*/