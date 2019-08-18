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

void			get_char(t_fmt **fmt, va_list args, int fd, char *buf_ptr)
{
	t_fmt	*f;

	f = *fmt;
	/* Applying width (If there IS width and no LEFT-flag) */
	while (f->width > -1 && --f->width > 0 && !(f->flags & LEFT))
		*buf_ptr++ = ((f->flags & ZERO) && !(f->flags & LEFT)) ? '0' : ' ';
	*buf_ptr++ = (unsigned char)va_arg(args, int);
//	ft_putstr(f->buf);
}

void			get_str(t_fmt **fmt, va_list args, int fd, char *buf_ptr)
{
	t_fmt		*f;
	size_t 		len;
	char 		*str;

	f = *fmt;
	str = va_arg(args, char *);
	len = ft_strnlen(str, f->precision);
	/* Applying width (If there IS width and no LEFT-flag) */
	while (--f->width >= len && f->width > -1 && !(f->flags & LEFT))
		*buf_ptr++ = ((f->flags & ZERO) && !(f->flags & LEFT)) ? '0' : ' ';
	while (len--)
		*buf_ptr++ = *str++;
//	ft_putstr(f->buf);
}

void			get_ptr(t_fmt **fmt, va_list args, int fd, char *buf_ptr)
{
	t_fmt		*f;
	int 		i;
	char 		*hex;
	uintmax_t 	pointer; //aka 'unsigned long',
	/* Платформа обязана в рамках стандарта С99 поддерживать следующие типы:
	 * intmax_t, uintmax_t, которые могут представлять максимальные
	 * целочисленные значения. */
//	uint64_t 	pointer; //aka 'unsigned long long'
	/* Тип с точной шириной. Не все системы могут поддерживать все эти типы. */

	i = 0;
	f = *fmt;
	pointer = (uintmax_t)va_arg(args, void *);
	hex = base_any((void *)pointer, 16);
	*buf_ptr++ = '0';
	*buf_ptr++ = 'x';
	while (hex[i])
		*buf_ptr++ = hex[i++];
	ft_strdel(&hex);
	ft_putstr(f->buf);
}