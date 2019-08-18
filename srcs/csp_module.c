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

int			get_char(t_fmt **fmt, va_list args, int fd, char *buf_ptr)
{
	t_fmt	*f;

	f = *fmt;
	/* Applying width (If there IS width and no LEFT-flag) */
	while (f->width > -1 && --f->width > 0 && !(f->flags & LEFT))
		*buf_ptr++ = ((f->flags & ZERO) && !(f->flags & LEFT)) ? '0' : ' ';
	*buf_ptr++ = (unsigned char)va_arg(args, int);

	// RETURN VALUES
}

int				get_str(t_fmt **fmt, va_list args, int fd, char *buf_ptr)
{
	t_fmt		*f;
	size_t 		len;
	size_t 		done;
	char 		*str;

	f = *fmt;
	str = va_arg(args, char *);
	len = ft_strnlen(str, f->precision);
	/* to return jump on the iter */
//	done = f->width > -1 ? len + f->width : len;
	/* Applying width (If there IS width and no LEFT-flag) */
	while (--f->width >= len && f->width > -1 && !(f->flags & LEFT))
		*buf_ptr++ = ((f->flags & ZERO) && !(f->flags & LEFT)) ? '0' : ' ';
	while (len--)
		*buf_ptr++ = *str++;
	// RETURN VALUES
	// return (done);
}

int				get_ptr(t_fmt **fmt, va_list args, int fd, char *buf_ptr)
{
	t_fmt		*f;
	int 		i;
	int 		len;
	char 		*hex;
	uintmax_t 	pointer; //aka 'unsigned long',
	/* Платформа обязана в рамках стандарта С99 поддерживать следующие типы:
	 * intmax_t, uintmax_t, которые могут представлять максимальные
	 * целочисленные значения. */
//	uint64_t 	pointer; //aka 'unsigned long long'
	/* Тип с точной шириной. Не все системы могут поддерживать все эти типы. */

	i = 0;
	f = *fmt;
	if (f->precision != -1)
	{
		ft_putstr("'precision' - results in undefined behaviour with 'p' conversion qualifier.");
		return (0);
	}
	pointer = (uintmax_t)va_arg(args, void *);
	hex = base_any(pointer, 16);
	while (--f->width > ft_strlen(hex) + 1 && f->width > -1 && !(f->flags & LEFT))
	{
		/* Original printf filling 'width' with 'zero's even if CLion says its result
		 * undefinied behaviour. Not sure should I handle this. Just leave both. */
		if (f->flags & ZERO || f->flags & SPECIAL || f->flags & PLUS
		|| f->flags & SPACE)
		{
			ft_putstr("Flag '0', '+', ' ', '#' - results in undefined behaviour with 'p' conversion qualifier.");
			ft_strdel(&hex);
			return (0);
		}
//		*buf_ptr++ = ((f->flags & ZERO) && !(f->flags & LEFT)) ? '0' : ' ';
		*buf_ptr++ = ' ';
	}
	ft_strcat(buf_ptr, "0x");
	buf_ptr += 2;
	/* Iterator here to safely delete 'hex'-string after writing */
	while (hex[i])
		*buf_ptr++ = hex[i++];
	ft_strdel(&hex);
	ft_putstr(f->buf);
}