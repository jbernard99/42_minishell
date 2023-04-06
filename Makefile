# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/16 04:45:18 by jbernard          #+#    #+#              #
#    Updated: 2023/04/06 10:32:23 by jbernard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#gcc -o minishell -I./libraries/readline/include ./src/main.c -L./libraries/readline/lib -lreadline -lncurses

# Compiler and compiler flags
CC = clang
CFLAGS = -Wall -Wextra -Werror
NAME = minishell

# Directories
SRC_DIR = src/
BI_DIR = $(SRC_DIR)/builtin
MAIN_DIR = $(SRC_DIR)/main
INC_DIR = includes/
OBJ_DIR = obj/
LIBFT_DIR = ./libraries/42_libft
RL_DIR = ./libraries/readline

# Files
MAIN_FILES = main.c			\
			envp.c			\
			tools.c			\
			mng_lst.c		\
			envp_tools.c	

#BI_FILES = cd.c		\
			echo.c		\
			env.c		\
			exit.c		\
			export.c	\
			pwd.c		\
			unset.c

#SRC_FILES = $(wildcard $(MAIN_DIR)/*.c) $(wildcard $(BI_DIR)/*.c)

OBJ_FILES = $(MAIN_FILES:%.c=$(OBJ_DIR)%.o)	\
			$(BI_FILES:%.c=$(OBJ_DIR)%.o)

LIB_FILES = -L$(LIBFT_DIR) -lft -L$(RL_DIR) -lreadline -lncurses

VPATH =	$(SRC_DIR) $(MAIN_DIR) $(BI_DIR)

# Build rule
all: $(NAME)

$(NAME): $(RL_DIR)/libreadline.a $(OBJ_FILES)
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJ_FILES) $(LIB_FILES) -o $(NAME)

$(OBJ_DIR)%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

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

re: clean all
