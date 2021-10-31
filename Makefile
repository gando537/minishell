# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/21 15:57:36 by mdiallo           #+#    #+#              #
#    Updated: 2021/10/29 17:16:35 by mdiallo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, clean, fclean, re

NAME = minishell

CC = clang

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address 

QUNUSED = -Qunused-arguments

SRC_NAME =  gnl.c  			  keys_up_down.c    search_varenv.c\
			backspace.c       gnl_bis.c         move_cursor.c     quotes.c\
			builti.c          history.c         lst_wp.c		  parse_jok.c\
			checker_pip.c     inidata_bis.c     manager.c         var_bis.c\
			create_lst.c      init_data.c       manager_bis.c     parse.c\
			free_mem.c        init_term.c       var_env.c         pipe.c\
			gestion_var.c     keys_left_right.c minishell.c       read_line.c

OBJ_PATH = obj

OBJ_NAME = $(SRC_NAME:.c=.o)

OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

LIB_READLINE = -L /usr/local/Cellar/readline/8.1.1/lib/ -I /usr/local/Cellar/readline/8.1.1/include/ -lncurses

HEADER	=	Includes/minishell.h

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libutils/
	@echo "libutils compilation done..."
	@echo $(NAME) ": Sources compiling..."
	@$(CC) $(CFLAGS) $(LIB_READLINE) $^ -o $@ -Llibutils/ -lutils
	@echo "Executable "$(NAME)" made"

$(OBJ_PATH)/%.o: %.c  $(HEADER)
	@mkdir -p $(OBJ_PATH) 2> /dev/null || 1
	@$(CC) $(CFLAGS) $(LIB_READLINE) $(QUNUSED) -o $@ -c $< 

clean:
	@rm -rf $(OBJ_PATH) || 1
	@make clean -C libutils/
	@echo "$(OBJ_PATH) supprimé !"

fclean: clean
	@rm -f $(NAME)
	@make fclean -C libutils/
	@echo "Executable de "$(NAME)" supprimé !"

re: fclean all
	@echo "Make re done !"
