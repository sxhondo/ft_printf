# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/16 18:42:04 by sxhondo           #+#    #+#              #
#    Updated: 2019/08/16 18:42:04 by sxhondo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = libftprintf.a
LIB	= libft.a

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(LIB)
	@gcc  -c srcs/*.c -I libft/incs/ -I incs/

	@ar -q $(NAME) *.o

$(LIB):
	@gcc -c libft/srcs/*.c -I libft/incs/ -I incs/
	@ar -q libft/$(LIB) *.o


clean:
	@rm -rf *.o libft/*.o

fclean: clean
	@rm -rf $(NAME)
	@rm -rf libft/$(LIB)

re: fclean $(LIB) all