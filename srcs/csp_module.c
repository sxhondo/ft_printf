/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   csp_module.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 20:21:35 by sxhondo           #+#    #+#             */
/*   Updated: 2019/08/27 00:30:19 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <ft_printf.h>
#include "../incs/ft_printf.h"

int 				get_percent(t_fmt *fmt)
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

int				get_char(t_fmt *fmt, va_list args)
{
	fmt->iter += 1;
	/* applying width (If there IS width and no LEFT-flag) */
	if (fmt->flags & LEFT)
		*fmt->buf_ptr++ = (unsigned char)va_arg(args, int);
	if (fmt->width < -1)
	{
		*fmt->buf_ptr++ = (unsigned char)va_arg(args, int);
		while (++fmt->width < -1)
			*fmt->buf_ptr++ = ' ';
	}
	while (--fmt->width > 0)
		*fmt->buf_ptr++ = fmt->flags & ZERO ? '0' : ' ';
	if (fmt->precision > -1)
		*fmt->buf_ptr++ = (unsigned char)va_arg(args, int);
	else if (!(fmt->flags & LEFT))
		*fmt->buf_ptr++ = (unsigned char)va_arg(args, int);
	return (0);
}

int				get_str(t_fmt *fmt, va_list args)
{
	int 			len;
	int 			lcpy;
	const char 		*str;
	char 			zero[] = "(null)";
	char 			*z = zero;

	fmt->iter += 1;
	if (!(str = va_arg(args, const char *)))
	{
		while (*z)
			*fmt->buf_ptr++ = *z++;
		return (0);
	}
	if (*str == '\0')
		len -= 1;
	len = ft_strnlen(str, fmt->precision);
	lcpy = len;
	while (fmt->flags & LEFT && lcpy--)
		*fmt->buf_ptr++ = *str++;
	while (fmt->width > -1 && --fmt->width >= len)
		*fmt->buf_ptr++ = fmt->flags & ZERO ? '0' : ' ';
	while (len-- && lcpy > 0)
		*fmt->buf_ptr++ = *str++;
	return (0);
}

int				get_ptr(t_fmt *fmt, va_list args)
{
	int 			hxlen;
	char 			hex[15];
	char 			*hex_ptr = hex;
	uint64_t 		pointer; //aka 'unsigned long long'
	int 			prec;


	fmt->iter += 1;
	pointer = (uint64_t)va_arg(args, void *);
		/* seems like valgrind things that return of va_arg (called with void *)
		 * can't be initialized. */
	itoa_base(pointer, hex_ptr, 0, 16);
	hxlen = ft_strlen(hex);
		/* this is for . and .0 and pointer is 0 cases */
	prec = 0;
	if (fmt->precision == 0 && !(ft_strcmp(hex, "0")) && ++prec)
		*hex_ptr++ = '\0';
	//	-	-	-	-	-	-	-	-	-	//
	if (fmt->flags & LEFT)
	{
		*fmt->buf_ptr++ = '0';
		*fmt->buf_ptr++ = 'x';
		if (fmt->precision > -1)
			while (fmt->precision-- > hxlen)
				*fmt->buf_ptr++ = '0';
		while (*hex_ptr)
			*fmt->buf_ptr++ = *hex_ptr++;
	}
	while (--fmt->width > hxlen + 1 && fmt->width > -1)
		*fmt->buf_ptr++ = ' ';
	//	-	-	-	-	-	-	-	-	-	//
	if (!(fmt->flags & LEFT))
	{
		*fmt->buf_ptr++ = '0';
		*fmt->buf_ptr++ = 'x';
		if (fmt->precision > -1)
		{
			while (fmt->precision-- > hxlen && ++prec)
				*fmt->buf_ptr++ = '0';
		}
		while (*hex_ptr && !(fmt->flags & LEFT))
		{
			*fmt->buf_ptr++ = *hex_ptr++;
			prec--;
		}
	}
	//	-	-	-	-	-	-	-	-	-	//
	return (0);
}
