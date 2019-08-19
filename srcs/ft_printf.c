/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 20:33:13 by sxhondo           #+#    #+#             */
/*   Updated: 2019/08/04 20:33:16 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>
#include "ft_printf.h"

int					print_module(t_fmt *fmt, va_list args, int fd, char *buf_ptr)
{
//	print_collected_data(&fmt);

	if (*fmt->iter == 'c')
		return (get_char(&fmt, args, buf_ptr));
	if (*fmt->iter == 's')
		return (get_str(&fmt, args, buf_ptr));
	if (*fmt->iter == 'p')
		return (get_ptr(&fmt, args, fd, buf_ptr));
//	if (*fmt->iter == 'd' || *fmt->iter == 'i')
//		return (get_decimal(&fmt, args, fd, buf_ptr));

}

int 					ft_fprintf(int fd, const char *fmt, va_list args)
{
	char 				*buf_ptr; //points to buf
	t_fmt				*format; // list of data
	int 				done;

	format = ft_memalloc(sizeof(t_fmt));
	format->iter = fmt;
	buf_ptr = format->buf;
	while (*format->iter)
	{
		while (*format->iter != '%' && *format->iter)
			*buf_ptr++ = *format->iter++;
		if (!*format->iter)
			break;
		/*	parsing		*/
		process_flags(format);
		process_width(format, args);
		process_precision(format, args);
		process_length_modifier(format, args);
		buf_ptr += print_module(format, args, fd, buf_ptr);
	}
	ft_putstr(format->buf);
	free (format);
	return (0);
}

int				ft_printf(char *fmt, ...)
{
	va_list 	args;
	int 		done;

	if (fmt == NULL)
		return (-1);
	va_start(args, fmt); /* устанавливает аrgs на 1-й безымянный аргумент после fmt */
	done = ft_fprintf(1, fmt, args);
	va_end(args);
	return (done);
}
