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
#define CASE	(unsigned)32		/* is it 'x' or 'X' (0 if lowcase, 1 if uppercase */
#define SHARP	(unsigned)64		/* alternative form (0 for %o, 0x for %x) */


typedef struct		s_fmt
{
	unsigned int	flags;
	int				width;
	int 			lmodifier;
	int				precision;
	unsigned int	base;
	const char		*iter;
	unsigned char	*buf_ptr;
}					t_fmt;

	/* processings */
int					process_precision(t_fmt *node, va_list args);
int					process_width(t_fmt *node, va_list args);
int 				process_flags(t_fmt *node);
void				process_length_modifier(t_fmt	*node, va_list args);
void				process_base(t_fmt	*node, va_list args);

	/* conversions */
int					get_percent(t_fmt *fmt);
int 				get_num(int64_t num, t_fmt *fmt, int sig);
int					get_str(t_fmt *fmt, va_list args);
int					get_ptr(t_fmt *fmt, va_list args);
int					get_char(t_fmt *fmt, va_list args);

char		 		*itoa_base(uint64_t num, char s[], int sig, unsigned base);

int					ft_printf(char *fmt, ...);
void				print_collected_data(t_fmt **fmt);

#endif //FT_PRINTF_FT_PRINTF_H
