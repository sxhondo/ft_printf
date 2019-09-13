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

#define ZERO		(unsigned)1			/* filling with zeroes */
#define PLUS		(unsigned)4			/* show sign of number */
#define SPACE		(unsigned)8			/* space if plus */
#define LEFT		(unsigned)16		/* left alignment */
#define CASE		(unsigned)32		/* is it 'x' or 'X' (0 if lowcase, 1 if uppercase OR 'L'*/
#define SHARP		(unsigned)64		/* alternative form (0 for %o, 0x for %x) */

#define CHAR		(unsigned)1			/* 'hh' */
#define SHORT		(unsigned)2			/* 'h'	*/
#define LONG		(unsigned)8			/* 'l'	*/
#define LONG_LONG	(unsigned)16		/* 'll'	*/
#define LLONG		(unsigned)32		/*	'L'	*/

typedef struct		s_fmt
{
	unsigned int	flags;
	int				width;
	unsigned int	lmodifier;
	int				precision;
	unsigned int	base;
	const char		*iter;
}					t_fmt;

//[0;31m	Red
//[1;31m	Bold Red
//[0;32m	Green
//[1;32m	Bold Green
//[0;33m	Yellow
//[01;33m	Bold Yellow
//[0;34m	Blue
//[1;34m	Bold Blue
//[0;35m	Magenta
//[1;35m	Bold Magenta
//[0;36m	Cyan
//[1;36m	Bold Cyan
//[0m	Reset


	/* processings */
int					process_precision(t_fmt *fmt, va_list args);
int					process_width(t_fmt *fmt, va_list args);
unsigned int		process_flags(t_fmt *fmt);
unsigned int		process_lmodifier(t_fmt *fmt);
unsigned int		process_base(t_fmt	*fmt);

	/* conversions */
int					get_percent(t_fmt *fmt, t_vec *buf);
int					get_str(t_fmt *fmt, va_list args, t_vec *buf);
int					get_ptr(t_fmt *fmt, va_list args, t_vec *buf);
int					get_char(t_fmt *fmt, va_list args, t_vec *buf);
int 				get_num(int64_t num, t_fmt *fmt, t_vec *buf, int sig);
long				get_dnum(long double dnum, t_fmt *fmt, t_vec *buf);
unsigned int 		itoa_base(uint64_t num, char s[], unsigned base, int sig);

int					ft_printf(const char *restrict format, ...);



#endif //FT_PRINTF_FT_PRINTF_H
