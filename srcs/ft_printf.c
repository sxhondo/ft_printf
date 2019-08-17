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

void					print_module(t_fmt *fmt, va_list args, int fd, char *buf_ptr)
{
//	print_collected_data(&fmt);

	if (*fmt->iter == 'c')
		get_char(&fmt, args, fd, buf_ptr);
	if (*fmt->iter == 's')
		get_str(&fmt, args, fd, buf_ptr);
}

int 					ft_fprintf(int fd, const char *fmt, va_list args)
{
	char 				*buf_ptr; //points to buf
	char 				*fmcp; //copy of a original format string
	t_fmt				*format; // list of data

	fmcp = ft_strdup(fmt);
	format = ft_memalloc(sizeof(t_fmt));
	buf_ptr = format->buf;
	format->iter = fmcp;

	while (*format->iter)
	{
		while (*format->iter != '%' && *format->iter)
			*buf_ptr++ = *format->iter++;
		/*	parsing		*/
		process_flags(format);
		process_width(format, args);
		process_precision(format, args);
		process_conversion_qualifier(format, args);

//		print_collected_data(&format);

		print_module(format, args, fd, buf_ptr);

		format->iter++;
	}
	ft_strdel(&fmcp);
	free (format);
	return (0);
}

int				ft_printf(char *fmt, ...)
{
	va_list 	args;
	int 		done;

	/*
 	* va_arg( ) function will never receive arguments of type char, short int, or float.
	* function only accept arguments of type char *, unsigned int, int or double.
 	*/

	if (fmt == NULL)
		return (-1);
	va_start(args, fmt); /* устанавливает аrgs на 1-й безымянный аргумент после fmt */
	done = ft_fprintf(1, fmt, args);
	va_end(args);
	return (done);
}
