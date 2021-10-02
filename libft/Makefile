# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdiallo <mdiallo@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/21 15:57:36 by mdiallo           #+#    #+#              #
#    Updated: 2021/10/02 21:11:09 by mdiallo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a
CFLAGS	= -Wall -Wextra -Werror

SRCS	=	free_str.c ft_str2.c joker_bis.c root.c\
			checker_red.c ft_split.c ft_str3.c str_replace.c\
			create_pip.c ft_str.c get_path.c replace_1.c utils.c\
			display.c ft_str1.c joker.c replace_2.c joker_parse.c

HEADER	= Includes/libft.h

OBJS	= $(SRCS:.c=.o)

all		: $(NAME)

$(NAME)	: $(OBJS)
		@ar rcs $(NAME) $(OBJS)

%.o		: %.c $(HEADER)
		@gcc $(CFLAGS) -o $@ -c $<

clean	:
			rm -f $(OBJS)

fclean	:	clean 
			rm -f $(NAME)

re		:	fclean all
