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

int					print_module(t_fmt *fmt, va_list args)
{
	uint64_t 	num;

	if (*fmt->iter == 'c')
		return (get_char(&fmt, args));
	if (*fmt->iter == 's')
		return (get_str(&fmt, args));
	if (*fmt->iter == 'p')
		return (get_ptr(&fmt, args));

//	print_collected_data(&fmt);

	/* SIGNED GUYS */
	if (*fmt->iter == 'd' || *fmt->iter == 'i')
	{
		if (fmt->lmodifier == 208) // signed char ('hh')
			;
		else if (fmt->lmodifier == 104) // signed short int ('h')
			num = (short)va_arg(args, int);
		else if (fmt->lmodifier == 108) // signed long int ('l')
			num = va_arg(args, long int);
		else if (fmt->lmodifier == 216) // signed long long int ('ll')
			num = va_arg(args, long long int);
		else
			num = va_arg(args, int);
		//print my number
	}
	/* UNSIGNED GUYS */

	if (*fmt->iter == 'o' || *fmt->iter == 'u' || *fmt->iter == 'x'
			|| *fmt->iter == 'X')
	{
		if (fmt->lmodifier == 208) // unsigned char ('hh')
		{
			num = (unsigned char)va_arg(args, unsigned int);
			printf("%hhu\n", num);
		}
		else if (fmt->lmodifier == 104) // unsigned short int ('h')
		{
			num = (unsigned short)va_arg(args, unsigned int);
			printf("%hu\n", num);
		}
		else if (fmt->lmodifier == 108) // unsigned long int ('l')
		{
			num = va_arg(args, unsigned long);
			printf("%lu\n", num);
		}
		else if (fmt->lmodifier == 216) // unsigned long long int ('ll')
		{
			num = va_arg(args, unsigned long long);
			printf("%llu\n", num);
		}
		else
		{
			num = va_arg(args, unsigned int);
			printf("%u\n", num);
		}
	}

}

int 					ft_fprintf(int fd, const char *fmt, va_list args)
{
	char 				buf[1024];
	t_fmt				*format; // list of data

	format = ft_memalloc(sizeof(t_fmt));
	format->iter = fmt;
	format->buf_ptr = buf;
	while (*format->iter)
	{
		while (*format->iter != '%' && *format->iter)
			*format->buf_ptr++ = *format->iter++;
		if (!*format->iter)
			break;
		/*	parsing		*/
		process_flags(format);
		process_width(format, args);
		process_precision(format, args);
		process_length_modifier(format, args);
		process_base(format, args);

		print_module(format, args);
	}
//	ft_putstr(buf);
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
