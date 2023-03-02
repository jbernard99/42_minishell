# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/16 04:45:18 by jbernard          #+#    #+#              #
#    Updated: 2023/03/02 12:17:57 by jbernard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#gcc -o minishell -I./libraries/readline/include ./src/main.c -L./libraries/readline/lib -lreadline -lncurses

# Compiler and compiler flags
CC = clang
CFLAGS = -Wall -Wextra -Werror
NAME = minishell

# Directories
SRC_DIR = ./src
INC_DIR = ./include
OBJ_DIR = ./obj
LIBFT_DIR = ./libraries/42_libft
RL_DIR = ./libraries/readline-8.1

# Files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))
LIB_FILES = -L$(LIBFT_DIR) -lft -L$(RL_DIR) -lreadline -lncurses

# Build rule
all: $(NAME)

$(NAME): $(RL_DIR) $(OBJ_FILES)
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJ_FILES) $(LIB_FILES) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/minishell.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(LIB_FILES) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Download and install readline library
$(RL_DIR):
	curl -O https://ftp.gnu.org/gnu/readline/readline-8.1.tar.gz 
	tar -xf readline-8.1.tar.gz
	rm readline-8.1.tar.gz
	cd readline-8.1 && bash configure && make
	mv readline-8.1/readline.a ./libraries/readline

#Management Rules
clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm $(NAME)

re: clean all