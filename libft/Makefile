# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/23 14:11:08 by sxhondo           #+#    #+#              #
#    Updated: 2019/07/23 14:11:13 by sxhondo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_LIST = \
	ft_atoi.c\
	ft_bzero.c\
	ft_isalnum.c\
	ft_isalpha.c\
	ft_isascii.c\
	ft_isdigit.c\
	ft_isprint.c\
	ft_memccpy.c\
	ft_memchr.c\
	ft_memcmp.c\
	ft_memcpy.c\
	ft_memmove.c\
	ft_memset.c\
	ft_putchar.c\
	ft_putnbr.c\
	ft_strcat.c\
	ft_strlcat.c\
	ft_strchr.c\
	ft_strcmp.c\
	ft_strcpy.c\
	ft_strdup.c\
	ft_strlen.c\
	ft_strncat.c\
	ft_strncmp.c\
	ft_strncpy.c\
	ft_strnstr.c\
	ft_strrchr.c\
	ft_strstr.c\
	ft_tolower.c\
	ft_toupper.c\
	ft_memalloc.c\
	ft_strnew.c\
	ft_memdel.c\
	ft_strdel.c\
	ft_strclr.c\
	ft_striter.c\
	ft_striteri.c\
	ft_strmap.c\
	ft_strmapi.c\
	ft_strequ.c\
	ft_strnequ.c\
	ft_strsub.c\
	ft_strjoin.c\
	ft_putstr.c\
	ft_strtrim.c\
	ft_putchar_fd.c\
	ft_putstr_fd.c\
	ft_strsplit.c\
	ft_putendl.c\
	ft_putendl_fd.c\
	ft_itoa.c\
	ft_putnbr_fd.c\
	ft_strrev.c\
	ft_strndup.c\
	ft_lstnew.c\
	ft_lstdelone.c\
	ft_lstdel.c\
	ft_lstiter.c\
	ft_lstadd.c\
	ft_lstmap.c\
	ft_cntwrds.c\
	ft_nblen.c\
	ft_strjoin_free.c\
	ft_lstfree.c\
	ft_lstpushback.c\
	ft_realloc.c \
	ft_vec_init.c \
	ft_vec_resize.c \
	ft_vec_add.c \
	ft_vec_del.c
	
NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror

	#Directories
INC_DIR= incs/
SRCS_DIR = srcs/
OBJ_DIR= obj/

	#Files
SOURCES = $(addprefix $(SRCS_DIR), $(SRCS_LIST))
OBJ_LIST = $(SRCS_LIST:%.c=%.o) 
OBJECTS = $(addprefix $(OBJ_DIR), $(OBJ_LIST))	

all: $(NAME) 

$(NAME): $(OBJ_DIR)
	@echo "\033[32m\033[1m$(NAME) - compiling\033[0m"	
	@$(CC) $(CFLAGS) -I $(INC_DIR) -c $(SOURCES)
	@mv $(OBJ_LIST) $(OBJ_DIR)
	@ar rc $(NAME) $(OBJECTS)
	@ranlib $(NAME)	

$(OBJ_DIR):
	@echo "\033[33m\033[1m$(NAME) - creating obj directory:\033[0m"
	@mkdir -p $(OBJ_DIR)

clean:
	@echo "\033[36m\033[1m$(NAME) - clean:\033[0m"
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "\033[36m\033[1m$(NAME) - fclean:\033[0m"
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
