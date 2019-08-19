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

#include <stdio.h>
#include "../libft/incs/libft.h"
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
	int				width;
	unsigned int	flags;
	int 			qualifier;
	int				precision;
	const char		*iter;
	char 			*buf_ptr;
}					t_fmt;

	/* processings */
int					process_precision(t_fmt *node, va_list args);
int					process_width(t_fmt *node, va_list args);
int 				process_flags(t_fmt *node);
void				process_length_modifier(t_fmt	*node, va_list args);


	/* utilities */
int 				skip_atoi(const char *s);
int					ft_isspecial(char ch);
void				print_collected_data(t_fmt **fmt);


void				put_uns_number(unsigned int nb, int fd);
//char 				*base_any(uintmax_t num, int base);
char 				*base_any(uint64_t num, int base);



	/* conversions */
/* char, string, pointer*/
int					get_char(t_fmt **fmt, va_list args);
int					get_str(t_fmt **fmt, va_list args);
int					get_ptr(t_fmt **fmt, va_list args);

//int					get_decimal(t_fmt **fmt, va_list args, int fd, char *buf_ptr);


int					ft_printf(char *fmt, ...);


#endif //FT_PRINTF_FT_PRINTF_H
