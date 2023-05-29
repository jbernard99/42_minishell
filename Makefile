# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbernard <jbernard@student.42quebec.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/16 04:45:18 by jbernard          #+#    #+#              #
#    Updated: 2023/05/29 11:14:33 by mgagnon          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


#gcc -o minishell -I./libraries/readline/include ./src/main.c -L./libraries/readline/lib -lreadline -lncurses

include settings.mk

# Compiler and compiler flags
CC = clang
CFLAGS = -Wall -Wextra -Werror
NAME = minishell

# Directories
SRC_DIR = src/

MAIN_DIR = $(SRC_DIR)/main
PARSE_DIR = $(SRC_DIR)/parsing
CMD_DIR = $(SRC_DIR)/cmdlst
ENV_DIR = $(SRC_DIR)/env
EXEC_DIR = $(SRC_DIR)/execution
RD_DIR = $(SRC_DIR)/redirect
BI_DIR = $(SRC_DIR)/builtins

INC_DIR = includes/
OBJ_DIR = obj/
LIBFT_DIR = ./libraries/42_libft
RL_DIR = ./libraries/readline

# Files
MAIN_FILES = 	main.c					\
				tools.c
				
PARSE_FILES = 	cmd_parsing.c			\
				quotes.c
				
CMD_FILES =		mng_lst.c				\
				mng_lst2.c

ENV_FILES = 	envlst_to_envp.c		\
				envp_to_envlst.c		\
				envlst_tools.c			\
				env_var_parse.c

EXEC_FILES = 	execution.c				\
				execution_fork.c		\
				pre_execution.c

RD_FILES =		pipe.c					\
				redirect_parsing.c		\
				redirect_out_tools.c	\
				redirect_in_tools.c
			
BI_FILES = 		echo.c					\
				export.c				\
				env.c					\
				cd.c					\
				pwd.c					\
				unset.c					\
				exit.c		

#SRC_FILES = $(wildcard $(MAIN_DIR)/*.c) $(wildcard $(BI_DIR)/*.c)

OBJ_FILES = $(MAIN_FILES:%.c=$(OBJ_DIR)%.o)		\
			$(PARSE_FILES:%.c=$(OBJ_DIR)%.o)	\
			$(CMD_FILES:%.c=$(OBJ_DIR)%.o)		\
			$(ENV_FILES:%.c=$(OBJ_DIR)%.o)		\
			$(EXEC_FILES:%.c=$(OBJ_DIR)%.o)		\
			$(RD_FILES:%.c=$(OBJ_DIR)%.o)		\
			$(BI_FILES:%.c=$(OBJ_DIR)%.o)		

LIB_FILES = -L$(LIBFT_DIR) -lft -L$(RL_DIR) -lreadline -lncurses

VPATH =	$(SRC_DIR) 		\
		$(MAIN_DIR) 	\
		$(PARSE_DIR)	\
		$(CMD_DIR)		\
		$(ENV_DIR)		\
		$(EXEC_DIR) 	\
		$(RD_DIR) 		\
		$(BI_DIR)

# Build rule
all: $(NAME)

$(NAME): $(RL_DIR)/libreadline.a $(OBJ_FILES)
	@ printf "$(GREEN) Almost done ......\r$(RESET)"
	@ $(MAKE) -C $(LIBFT_DIR)
	@ $(CC) $(CFLAGS) $(OBJ_FILES) $(LIB_FILES) -o $(NAME)
	@ printf "$(GREEN) - ✅✅✅ -> Compilation of $(PURPLE)$(NAME)$(GREEN) complete!                      						      $(RESET)\n"

$(OBJ_DIR)%.o: %.c | $(OBJ_DIR)
	@ printf "$(GREEN)- ⚡⚡⚡ -> Compiling $(PURPLE)$(notdir $@)$(GREEN) using $(PURPLE)$(notdir $<)$(GREEN)...                                                                             \r$(RESET)"
	@ $(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

obj:
	@ mkdir -p $(OBJ_DIR)

# Download and install readline library
$(RL_DIR)/libreadline.a:
	@ curl -O https://ftp.gnu.org/gnu/readline/readline-8.1.tar.gz
	@ tar -xf readline-8.1.tar.gz
	@ rm readline-8.1.tar.gz
	@ cd readline-8.1 && bash configure && make
	@ mv readline-8.1/libreadline.a ./libraries/readline/
	@ rm -rf readline-8.1

#Management Rules
clean:
	@ rm -rf $(OBJ_DIR)
	@ $(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@ rm -f $(NAME)
	@ rm -f $(RL_DIR)/libreadline.a
	@ $(MAKE) -C $(LIBFT_DIR) fclean

re: clean all

.PHONY:		all clean fclean re obj
