/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 16:34:24 by sxhondo           #+#    #+#             */
/*   Updated: 2019/07/26 16:34:26 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_FT_PRINTF_H
#define FT_PRINTF_FT_PRINTF_H

#include "../libft/incs/libft.h"
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <limits.h>

#define ZERO	(unsigned)1			/* filling with zeroes */
#define PLUS	(unsigned)4			/* show plus */
#define SPACE	(unsigned)8			/* space if plus */
#define LEFT	(unsigned)16		/* left justified */
#define SPECIAL	(unsigned)64		/* 0x */


typedef struct		s_fmt
{
	struct s_fmt 	*next;
	char 			*type;
	int				width;
	unsigned int	flags;
	int 			qualifier;
	int				precision;
	const char		*iter;
	char 			buf[1024];
}					t_fmt;

	/* processings */
int					process_precision(t_fmt *node, va_list args);
int					process_width(t_fmt *node, va_list args);
int 				process_flags(t_fmt *node);
void				process_conversion_qualifier(t_fmt	*node, va_list args);


	/* utilities */
int 				skip_atoi(const char *s);
int					ft_isspecial(char ch);
char 				small_itoa(int nb);
void				refresh_node(t_fmt *node);
int					search_spec(char *str, char ch);
void				print_collected_data(t_fmt **fmt);
void				put_uns_number(unsigned int nb, int fd);

	/* handlers */
void 				handle_wrong_flags(t_fmt *fmt);


	/* tables */
char 				*base_any(void *p, int base);
char 				*parse_oct_table(t_list **row);
char 				*parse_hex_table(t_list **row);
char 				*parse_bin_table(t_list **row);


	/* prints */
/* char, string, pointer*/
void				get_char(t_fmt **fmt, va_list args, int fd, char *str);
void				get_str(t_fmt **fmt, va_list args, int fd, char *buf_ptr);
void				get_ptr(t_fmt **fmt, va_list args, int fd, char *buf_ptr);

/* decimal */
void				print_diu(t_fmt **fmt, va_list args, int fd);
char 				*print_oxX(t_fmt **fmt, va_list args, int fd);


int					ft_printf(char *fmt, ...);


#endif //FT_PRINTF_FT_PRINTF_H
