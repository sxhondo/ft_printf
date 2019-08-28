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

//#include <ft_printf.h>
#include "../incs/ft_printf.h"

void			print_collected_data(t_fmt *fmt)
{
	printf("\n--------FORMAT----------\n");
	printf("FLAGS: \t\t\t\t[%d]\n", fmt->flags);
	printf("WIDTH: \t\t\t\t[%d]\n", fmt->width);
	printf("PRECISION: \t\t\t[%d]\n", fmt->precision);
	printf("L_MODIFIER: \t\t[%d] or [%c]\n", fmt->lmodifier, fmt->lmodifier);
	printf("BASE: \t\t\t\t[%u]\n", fmt->base);
	printf("ITERATOR: \t\t\t[%s]\n", fmt->iter);
	printf("------------------------\n");
}

int					print_module(t_fmt *fmt, va_list args)
{
	int64_t 		num = 0;

	if (*fmt->iter == '%')
		return (get_percent(fmt));
	if (*fmt->iter == 'c')
		return (get_char(fmt, args));
	else if (*fmt->iter == 's')
		return (get_str(fmt, args));
	else if (*fmt->iter == 'p')
		return (get_ptr(fmt, args));

		/* SIGNED */
	if (*fmt->iter == 'd' || *fmt->iter == 'i')
	{
		if (fmt->lmodifier & CHAR) // char ('hh')
			num = (char)va_arg(args, int);
		else if (fmt->lmodifier & SHORT) // short int ('h')
			num = (short)va_arg(args, int);
		else if (fmt->lmodifier & LONG) // long int ('l')
			num = va_arg(args, long int);
		else if (fmt->lmodifier & LONG_LONG) // long long int ('ll')
			num = va_arg(args, long long int);
		else
			num = va_arg(args, int);
		get_num(num, fmt, 1);
	}

		/* UNSIGNED */
	if (*fmt->iter == 'o' || *fmt->iter == 'u' || *fmt->iter == 'x'
			|| *fmt->iter == 'X' || *fmt->iter == 'b')
	{
		if (fmt->lmodifier & CHAR) // unsigned char ('hh')
			num = (unsigned char)va_arg(args, unsigned int);
		else if (fmt->lmodifier & SHORT) // unsigned short int ('h')
			num = (unsigned short)va_arg(args, unsigned int);
		else if (fmt->lmodifier & LONG) // unsigned long int ('l')
			num = va_arg(args, unsigned long);
		else if (fmt->lmodifier & LONG_LONG) // unsigned long long int ('ll')
			num = va_arg(args, unsigned long long);
		else
			num = va_arg(args, unsigned int);
		get_num(num, fmt, 0);
	}
	return (0);
}

long 					ft_fprintf(int fd, const char *fmt, va_list args)
{
	unsigned char		buf[1024];
	unsigned char		*ptr = buf;
	long int 			i;
	t_fmt				*format;

	format = ft_memalloc(sizeof(t_fmt));
	format->iter = fmt;
	format->buf_ptr = buf;
	while (*format->iter)
	{
		while (*format->iter != '%' && *format->iter)
			*format->buf_ptr++ = *format->iter++;
		if (!*format->iter)
			break;
		/* processings */
		process_flags(format);
		process_width(format, args);
		process_precision(format, args);
		process_lmodifier(format);
		process_base(format);
		print_module(format, args);
	}
	/* print buf */
	*format->buf_ptr = '\0';
	i = 0;
	while (++i <= format->buf_ptr - buf)
		write(fd, &*ptr++, 1);
	free (format);
	return (format->buf_ptr - buf);
}

int				ft_printf(const char *restrict format, ...)
{
	va_list 	args;
	int 		done;

	if (!format)
		return (-1);
	va_start(args, format); /* устанавливает аrgs на 1-й безымянный аргумент после fmt */
	done = (int)ft_fprintf(1, format, args);
	va_end(args);
	return (done);
}
