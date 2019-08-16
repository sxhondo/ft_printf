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

#include "libft.h"
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <limits.h>


typedef struct		s_fmt
{
	struct s_fmt 	*next;
	char 			*type;
	int				width;
	int				precision;
	int 			flags;
	char 			*iter;
}					t_fmt;

	/* processings */
int					process_precision(t_fmt *node, va_list args);
int					process_width(t_fmt *node, va_list args);
int 				process_flags(t_fmt *node);
void				process_datatype(t_fmt *fmt, va_list args);


	/* utilities */
int 				skip_atoi(const char *s);
int					ft_isspecial(char ch);
char 				small_itoa(int nb);
void				refresh_node(t_fmt *node);
int					search_spec(char *str, char ch);
void				print_collected_data(t_fmt **fmt);
void				put_uns_number(unsigned int nb, int fd);



	/* tables */
char 				*base_any(void *p, int base);
char 				*parse_oct_table(t_list **row);
char 				*parse_hex_table(t_list **row);
char 				*parse_bin_table(t_list **row);


	/* prints */
/* char, string, pointer*/
void				print_char(t_fmt **fmt, va_list args, int fd);
void				print_str(t_fmt **fmt, va_list args, int fd);
void				print_ptr(t_fmt **fmt, va_list args, int fd);

/* decimal */
void				print_diu(t_fmt **fmt, va_list args, int fd);
char 				*print_oxX(t_fmt **fmt, va_list args, int fd);


int					ft_printf(char *fmt, ...);


#endif //FT_PRINTF_FT_PRINTF_H
