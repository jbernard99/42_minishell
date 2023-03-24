/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 13:40:17 by jbernard          #+#    #+#             */
/*   Updated: 2023/03/24 13:40:25 by jbernard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
		Exemples :
			cd 									: Return to /home
			cd 'invalid folder' 				: "cd: {invalid folder}: No such file or directory"
			cd 'valid folder'					: Moves current working div to selected folder
			cd 'valid folder' 'invalid folder' 	: Moves current working div to selected folder.
*/