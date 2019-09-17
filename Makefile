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

SOURCES = \
	csp_module.c\
	dnum_utilities.c\
	expand_argument.c\
	float_module.c\
	ft_printf.c\
	num_utilities.c\
	place_num.c\
	process_utilities.c\
	processings.c\
	bonuses_1.c\

CC = gcc
NAME = libftprintf.a
FLAGS = -Wall -Wextra -Werror

LIBFT = libft
LIBFTA = libft.a

SRCS_DIR = srcs
INCS_DIR = incs

OBJS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	make -C libft
	cp libft/libft.a ./$(NAME)
	ar rcs $(NAME) $(OBJS)

%.o: $(SRCS_DIR)/%.c $(INCS_DIR)/ft_printf.h
	$(CC) $(FLAGS) -I $(INCS_DIR) -o $@ -c $<

$(LIB):
	make -C $(LIBFT)

clean:
	rm -f $(OBJS)
	make clean -C $(LIBFT)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT)

re: fclean all

.PHONY: all clean lclean fclean re