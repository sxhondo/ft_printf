/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   csp_module.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 20:21:35 by sxhondo           #+#    #+#             */
/*   Updated: 2019/08/21 20:21:36 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int 		get_percent(t_fmt *fmt)
{
	if (fmt->flags & LEFT)
		*fmt->buf_ptr++ = '%';
	while (--fmt->width > 0)
		*fmt->buf_ptr++ = fmt->flags & ZERO ? '0' : ' ';
	if (!(fmt->flags & LEFT))
		*fmt->buf_ptr++ = '%';
	*fmt->buf_ptr = '\0';
	fmt->iter += 1;
	return (0);
}

int			get_char(t_fmt *fmt, va_list args)
{
//	if (f->precision != -1) ?
//		"'precision' - results in undefined behaviour with 'p' conversion qualifier.");
	/* applying width (If there IS width and no LEFT-flag) */
	while (--fmt->width > 0 && !(fmt->flags & LEFT))
		*fmt->buf_ptr++ = fmt->flags & ZERO ? '0' : ' ';
	*fmt->buf_ptr++ = (unsigned char)va_arg(args, int);
	fmt->iter += 1;
	return (0); // ?
}

int				get_str(t_fmt *fmt, va_list args)
{
	size_t 			len;
	const char 		*str;

	str = va_arg(args, const char *);
	len = ft_strnlen(str, fmt->precision);
	/* applying width (If there IS width and no LEFT-flag) */
	while (fmt->width > -1 && --fmt->width >= len && !(fmt->flags & LEFT))
		*fmt->buf_ptr++ = fmt->flags & ZERO ? '0' : ' ';
	while (len--)
		*fmt->buf_ptr++ = *str++;
	fmt->iter += 1;
	return (0); // ?
}

int				get_ptr(t_fmt *fmt, va_list args)
{
	char 			hex[15];
	char 			*hex_ptr = hex;
//	uintmax_t 	pointer; //aka 'unsigned long',
	/* Платформа обязана в рамках стандарта С99 поддерживать следующие типы:
	 * intmax_t, uintmax_t, которые могут представлять максимальные целочисленные значения. ~wiki
	 * UPDATED: uintmax_t/intmax_t не работает на ubuntu. При компиляции:
	 * "Unknown type uintmax_t, did you mean uint64_t?" */

	uint64_t 		pointer; //aka 'unsigned long long'
	/* Тип с точной шириной. Не все системы могут поддерживать эти типы. ~ wiki */
//	unsigned long 	pointer;

	pointer = (uint64_t)va_arg(args, void *);

//	if (f->precision != -1)
//		"'precision' - results in undefined behaviour with 'p' conversion qualifier.";

	/* seems like valgrind things that return of va_arg (called with void *)
	 * can't be initialized. */
	itoa_base(pointer, hex_ptr, 0, 16);
	while (--fmt->width > ft_strlen(hex) + 1 && fmt->width > -1 && !(fmt->flags & LEFT))
	{
		/* Original printf filling 'width' with 'zero's even if CLion says its result
		 * undefinied behaviour. Not sure should I handle this. Just leave both.

		if (f->flags & ZERO || f->flags & SPECIAL || f->flags & PLUS
		|| f->flags & SPACE){
			ft_putstr("Flag '0', '+', ' ', '#' - results in undefined behaviour with 'p' conversion qualifier.");
			ft_strdel(&hex);} */
//		*buf_ptr++ = fmt->flags & ZERO ? '0' : ' ';
		*fmt->buf_ptr++ = ' ';
	}
	/* adding '0x' in buffer, moving pointer */
	*fmt->buf_ptr++ = '0';
	*fmt->buf_ptr++ = 'x';

	/* Filling buf. Iterator here to safely delete 'hex'-string after writing */
	while (*hex_ptr)
		*fmt->buf_ptr++ = *hex_ptr++;
	fmt->iter += 1;
	return (0); // ?

}
