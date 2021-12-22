# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: esivre <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/27 16:19:19 by esivre            #+#    #+#              #
#    Updated: 2021/12/21 18:39:13 by esivre           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
NAME = fdf

SRCS	=	main.c color.c draw.c frame.c free.c math_utils.c mlx.c read_map.c

OBJS	=	$(addprefix $(OBJDIR),$(SRCS:.c=.o))
DEPS	=	$(addprefix $(DEPDIR),$(SRCS:.c=.d))
LIBFT	=   libft/libft.a
LIBMLX	=	mlx_linux/libmlx_Linux.a
FLAGS	=	-Wall -Wextra -Werror
SRCDIR	=	./srcs/
OBJDIR	=	./objs/
DEPDIR	=	./objs/
INCDIR	=	./includes/

$(OBJDIR)%.o:$(SRCDIR)%.c
			gcc $(FLAGS) -MMD -MP -c -I libft -I mlx_linux -I $(INCDIR) $< -o $@

all:		$(LIBFT) $(LIBMLX) $(NAME)

$(LIBFT):		
			make bonus -C libft

$(LIBMLX):		
			make -C mlx_linux

$(OBJDIR):
			mkdir -p $(OBJDIR)

$(NAME):	$(OBJDIR) $(OBJS)
		gcc $(FLAGS) $(OBJS) -o $(NAME) $(LIBFT) $(LIBMLX) -lm -lXext -lX11

clean:
			/bin/rm -rf objs
			make -C ./libft clean

fclean:		clean
			/bin/rm -f $(NAME)
			make -C ./libft/ fclean
			make -C ./mlx_linux/ clean
 

re:			fclean all

.PHONY:		all clean fclean re

-include $(DEPS)
