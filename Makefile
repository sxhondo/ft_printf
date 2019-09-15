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

	#Operations
NAME = libftprintf.a
LIB	= libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror

	#Directories
INC_DIR = incs/
LIB_INC_DIR = libft/incs
SRCS_DIR = srcs/
OBJ_DIR = obj/

	#Files
SRCS_LIST =\
	csp_module.c\
	dnum_utilities.c\
	expand_argument.c\
	float_module.c\
	ft_printf.c\
	num_utilities.c\
	place_num.c\
	process_utilities.c\
	processings.c\

SOURCES = $(addprefix $(SRCS_DIR), $(SRCS_LIST))
OBJ_LIST = $(SRCS_LIST:%.c=%.o)
OBJECTS = $(addprefix $(OBJ_DIR), $(OBJ_LIST))

all: $(NAME)

$(NAME): $(LIB) $(OBJ_DIR) $(SRCS_DIR)
	@$(CC) $(CFLAGS) -c $(SOURCES) -I $(INC_DIR) -I $(LIB_INC_DIR)
	@ar rc $(NAME) $(OBJECTS)
#	@gcc  -c srcs/*.c -I libft/incs/ -I incs/

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

.PHONY: all clean fclean re