/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   csp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 16:14:51 by sxhondo           #+#    #+#             */
/*   Updated: 2019/08/14 16:14:53 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			get_char(t_fmt **fmt, va_list args)
{
	t_fmt	*f;
	int 	done;

	f = *fmt;
//	if (f->precision != -1) ?
//		"'precision' - results in undefined behaviour with 'p' conversion qualifier.");
	/* applying width (If there IS width and no LEFT-flag) */
	while (f->width > -1 && --f->width > 0 && !(f->flags & LEFT))
		*f->buf_ptr++ = ((f->flags & ZERO) && !(f->flags & LEFT)) ? '0' : ' ';
	*f->buf_ptr++ = (unsigned char)va_arg(args, int);
	f->iter += 1;
//	return (?);
}

int				get_str(t_fmt **fmt, va_list args)
{
	t_fmt			*f;
	size_t 			len;
	size_t 			done;
	const char 		*str;

	f = *fmt;
	str = va_arg(args, const char *);
	len = ft_strnlen(str, f->precision);
	/* applying width (If there IS width and no LEFT-flag) */
	while (--f->width >= len && f->width > -1 && !(f->flags & LEFT))
		*f->buf_ptr++ = ((f->flags & ZERO) && !(f->flags & LEFT)) ? '0' : ' ';
	while (len--)
		*f->buf_ptr++ = *str++;
	f->iter += 1;
//	return (?);
}

int				get_ptr(t_fmt **fmt, va_list args)
{
	t_fmt			*f;
	int 			i;
	char 			*hex;
//	uintmax_t 	pointer; //aka 'unsigned long',
	/* Платформа обязана в рамках стандарта С99 поддерживать следующие типы:
	 * intmax_t, uintmax_t, которые могут представлять максимальные целочисленные значения. ~wiki
	 * UPDATED: uintmax_t/intmax_t не работает на ubuntu. При компиляции:
	 * "Unknown type uintmax_t, did you mean uint64_t?" */

	uint64_t 		pointer; //aka 'unsigned long long'
	/* Тип с точной шириной. Не все системы могут поддерживать эти типы. ~ wiki */
//	unsigned long 	pointer;
	i = 0;
	f = *fmt;
	pointer = (uint64_t)va_arg(args, void *);

//	if (f->precision != -1)
//		"'precision' - results in undefined behaviour with 'p' conversion qualifier.";

	/* seems like valgrind things that return of va_arg (called with void *)
	 * can't be initialized. */
	hex = base_any(pointer, 16);
	while (--f->width > ft_strlen(hex) + 1 && f->width > -1 && !(f->flags & LEFT))
	{
		/* Original printf filling 'width' with 'zero's even if CLion says its result
		 * undefinied behaviour. Not sure should I handle this. Just leave both.

		if (f->flags & ZERO || f->flags & SPECIAL || f->flags & PLUS
		|| f->flags & SPACE){
			ft_putstr("Flag '0', '+', ' ', '#' - results in undefined behaviour with 'p' conversion qualifier.");
			ft_strdel(&hex);} */
//		*buf_ptr++ = ((f->flags & ZERO) && !(f->flags & LEFT)) ? '0' : ' ';
		*f->buf_ptr++ = ' ';
	}
	/* adding '0x' in buffer, moving pointer */
	*f->buf_ptr++ = '0';
	*f->buf_ptr++ = 'x';

	/* Filling buf. Iterator here to safely delete 'hex'-string after writing */
	while (hex[i])
		*f->buf_ptr++ = hex[i++];
	ft_strdel(&hex);
	f->iter += 1;
//	return (?);

}