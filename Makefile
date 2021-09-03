# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/21 15:57:36 by mdiallo           #+#    #+#              #
#    Updated: 2021/08/31 16:41:58 by mdiallo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, clean, fclean, re

NAME = minishell

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address 

LIBS = -lreadline

LIB_READLINE = -L /usr/local/Cellar/readline/8.1/lib/ -I /usr/local/Cellar/readline/8.1/include/

QUNUSED = -Qunused-arguments

SRC_NAME = minishell.c ft_split.c gnl.c root.c free_mem.c pipe.c ft_str.c str_replace.c var_env.c

OBJ_PATH = obj

OBJ_NAME = $(SRC_NAME:.c=.o)

OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

all: $(NAME)

$(NAME): $(OBJ)
	@echo $(NAME) ": Sources compiling..."
	@$(CC) $(CFLAGS) $(LIBS) $(LIB_READLINE) $^ -o $@
	@echo "Executable "$(NAME)" made"

$(OBJ_PATH)/%.o: %.c
	@mkdir -p $(OBJ_PATH) 2> /dev/null || true
	@$(CC) $(CFLAGS) $(LIB_READLINE) $(QUNUSED) -o $@ -c $<

clean:
	@rm -rf $(OBJ_PATH) || true
	@echo "$(OBJ_PATH) supprimé !"

fclean: clean
	@rm -f $(NAME)
	@echo "Executable de "$(NAME)" supprimé !"

re: fclean all
	@echo "Make re done !"