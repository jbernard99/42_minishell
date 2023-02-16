# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/16 04:45:18 by jbernard          #+#    #+#              #
#    Updated: 2023/02/16 04:58:51 by jbernard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

gcc -o minishell -I./libraries/readline/include ./src/main.c -L./libraries/readline/lib -lreadline -lncurses
