# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/16 04:45:18 by jbernard          #+#    #+#              #
#    Updated: 2023/04/10 13:31:33 by mgagnon          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#gcc -o minishell -I./libraries/readline/include ./src/main.c -L./libraries/readline/lib -lreadline -lncurses

# Compiler and compiler flags
CC = clang
CFLAGS = -Wall -Wextra -Werror
NAME = minishell

# Directories
SRC_DIR = ./src
INC_DIR = ./includes
OBJ_DIR = ./obj
LIBFT_DIR = ./libraries/42_libft
RL_DIR = ./libraries/readline

# Files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))
LIB_FILES = -L$(LIBFT_DIR) -lft -L$(RL_DIR) -lreadline -lncurses

# Build rule
all: $(NAME)

$(NAME): $(RL_DIR)/libreadline.a $(OBJ_FILES)
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJ_FILES) $(LIB_FILES) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/minishell.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Download and install readline library
$(RL_DIR)/libreadline.a:
	curl -O https://ftp.gnu.org/gnu/readline/readline-8.1.tar.gz 
	tar -xf readline-8.1.tar.gz
	rm readline-8.1.tar.gz
	cd readline-8.1 && bash configure && make
	mv readline-8.1/libreadline.a ./libraries/readline/
	rm -rf readline-8.1

#Management Rules
clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

debug:
	$(CC) $(CFLAGS) -g -o $(NAME) $(SRC_FILES) -Iinclude/ -I$(LIBFT_DIR) $(LIBFT_DIR)/libft.a
re: clean all
