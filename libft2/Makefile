# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: esivre <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/27 15:48:13 by esivre            #+#    #+#              #
#    Updated: 2021/11/30 17:05:39 by esivre           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=   ft_strtrim.c ft_strnstr.c ft_strlcat.c ft_substr.c \
			ft_calloc.c ft_strmapi.c ft_strjoin.c ft_split.c \
			ft_itoa.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
			ft_putstr_fd.c ft_strdup.c ft_isalpha.c \
			ft_memcpy.c ft_strlcpy.c ft_tolower.c ft_atoi.c \
			ft_isascii.c ft_memccpy.c ft_memmove.c ft_strlen.c \
			ft_toupper.c ft_bzero.c ft_isdigit.c ft_memchr.c \
			ft_memset.c ft_strncmp.c ft_isalnum.c ft_isprint.c \
			ft_memcmp.c ft_strchr.c ft_strrchr.c

OBJS	=	${SRCS:.c=.o}

BONUS			=	ft_lstlast.c ft_lstsize.c ft_lstnew.c \
					ft_lstadd_front.c ft_lstadd_back.c \
					ft_lstclear.c \
					ft_lstdelone.c ft_lstiter.c ft_lstmap.c \
					ft_straddchar.c ft_chartostr.c \
					get_next_line.c get_next_line_utils.c

BONUS_OBJS		= $(BONUS:.c=.o)

NAME    =	libft.a
CC	=	gcc
CFLAGS	=	-Wall -Wextra -Werror

.c.o:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all:		${NAME}

${NAME}:	${OBJS}
		ar -rc ${NAME} ${OBJS}
		ranlib ${NAME}

bonus:			$(OBJS) $(BONUS_OBJS)
				ar -rc $(NAME) $(OBJS) $(BONUS_OBJS)
				ranlib $(NAME)

clean:
	        	rm -f ${OBJS} ${BONUS_OBJS}

fclean:         clean
	        	rm -f ${NAME}

re:             fclean all

.PHONY:         all clean fclean re
