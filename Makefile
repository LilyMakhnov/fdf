# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: esivre <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/27 16:19:19 by esivre            #+#    #+#              #
#    Updated: 2021/11/25 14:36:52 by esivre           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
NAME = FdF

SRCS	=	main.c

OBJS	=	$(SRCS:.c=.o)

%.o: %.c
	gcc -Wall -Wextra -Werror -I/usr/include -Imlx -O3 -c $< -o $@

all:		 $(NAME)


$(NAME): $(OBJ)
	gcc -Lmlx_linux -lmlx_linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz $(OBJ) -o $(NAME)

clean:
			/bin/rm -f $(OBJS)

fclean:			clean
			/bin/rm -f $(NAME) 

re:			fclean all

.PHONY:		all clean fclean re
