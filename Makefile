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

# Directories
SRC_DIR = src
INC_DIR = include
LIBFT_DIR = ./libraries/libft
RL_DIR = ./libraries/readline
BUILD_DIR = build

# Source files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC_FILES))

# Library files
LIB_FILES = -L$(LIBFT_DIR) -L$(RL_DIR)/lib -lreadline -lncurses

# Target executable
TARGET = minishell

# Build rule
all: $(BUILD_DIR) $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) $(OBJ_FILES) $(LIB_FILES) -o $(TARGET)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/minishell.h
	$(CC) $(CFLAGS) -I$(INC_DIR) -I$(RL_DIR)/include -I$(LIBFT_DIR)/include -c $< -o $@

# Create build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Clean rule
clean:
	rm -rf $(BUILD_DIR)
	rm $(TARGET)

# Clean and rebuild
re: clean all