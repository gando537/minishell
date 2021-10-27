# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/21 15:57:36 by mdiallo           #+#    #+#              #
#    Updated: 2021/10/24 13:55:26 by mdiallo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a

CC = clang

OBJ_PATH = obj

CFLAGS	= -Wall -Wextra -Werror

SRCS	=	free_str.c ft_str2.c joker_bis.c root.c banner.c\
			checker_red.c ft_split.c ft_str3.c str_replace.c\
			create_pip.c ft_str.c get_path.c replace_1.c utils.c\
			display.c ft_str1.c joker.c replace_2.c joker_parse.c

HEADER	= ../Includes/libft.h

OBJS	= $(SRCS:.c=.o)

OBJ 	= $(addprefix $(OBJ_PATH)/,$(OBJS))

all		: $(NAME)

$(NAME)	: $(OBJ)
	@ar rcs $(NAME) $(OBJ)

$(OBJ_PATH)/%.o	: %.c $(HEADER)
	@mkdir -p $(OBJ_PATH) 2> /dev/null || 1
	@$(CC) $(CFLAGS) -o $@ -c $<

clean	:
	@rm -rf $(OBJ_PATH) || 1

fclean	:	clean 
	@rm -f $(NAME)

re		:	fclean all


