# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/16 04:45:18 by jbernard          #+#    #+#              #
#    Updated: 2023/02/16 07:34:02 by jbernard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#gcc -o minishell -I./libraries/readline/include ./src/main.c -L./libraries/readline/lib -lreadline -lncurses

# Compiler and compiler flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror


NAME = minishell
# Directories
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
LIBFT_DIR = ./libraries/libft
RL_DIR = ./libraries/readline

# Files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))
LIB_FILES = -L$(LIBFT_DIR) -L$(RL_DIR)/lib -lreadline -lncurses


# Build rule
all: $(BUILD_DIR) $(NAME)

$(NAME): $(OBJ_FILES)
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJ_FILES) $(LIB_FILES) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/minishell.h
	$(CC) $(CFLAGS) -I$(INC_DIR) -I$(RL_DIR)/include -I$(LIBFT_DIR)/include -c $< -o $@

# Create build directory
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Download and install readline library
readline_install:
	curl -O https://ftp.gnu.org/gnu/readline/readline-8.1.tar.gz
	tar -xf readline-8.1.tar.gz
	rm readline-8.1.tar.gz
	cd readline-8.1 && ./configure --prefix=$(RL_DIR) && make && make install

# Clean rule
clean:
	rm -rf $(BUILD_DIR)
	rm $(NAME)

# Clean and rebuild
re: clean all