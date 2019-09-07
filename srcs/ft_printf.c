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

void					pcsp(t_fmt	*fmt, va_list args, t_vec *buf)
{
	if (*fmt->iter == '%')
		get_percent(fmt, buf);
	else if (*fmt->iter == 'c')
		get_char(fmt, args, buf);
	else if (*fmt->iter == 's')
		get_str(fmt, args, buf);
	else if (*fmt->iter == 'p')
		get_ptr(fmt, args, buf);
}

void					positive_negative_nums(t_fmt *fmt, va_list args, t_vec *buf)
{
	int64_t 			num;

	num = 0;
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
	get_num(num, fmt, buf);
}

void					positive_nums(t_fmt *fmt, va_list args, t_vec *buf)
{
	int64_t 			num;

	num = 0;
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
	get_num(num, fmt, buf);

}

void					floating_point(t_fmt *fmt, va_list args, t_vec *buf)
{
	long double			dnum;

	dnum = 0;
	if (fmt->lmodifier & LLONG)
		dnum = va_arg(args, long double);
	else
		dnum = va_arg(args, double);
//	get_dnum(dnum, fmt);

}

int						print_module(t_fmt *fmt, va_list args, t_vec *buf)
{
	int64_t 			num;

	num = 0;
		/* PERCENT, CHAR, STRING, POINTER */
	if (*fmt->iter == '%' || *fmt->iter == 'c' || *fmt->iter == 's'
		|| *fmt->iter == 'p')
		pcsp(fmt, args, buf);

		/* SIGNED NUMS */
	if (*fmt->iter == 'd' || *fmt->iter == 'i')
		positive_negative_nums(fmt, args, buf);

		/* UNSIGNED  NUMS */
	if (*fmt->iter == 'o' || *fmt->iter == 'u' || *fmt->iter == 'x'
			|| *fmt->iter == 'X' || *fmt->iter == 'b')
		positive_nums(fmt, args, buf);

		/* FLOATS */
	if (*fmt->iter == 'f')
		floating_point(fmt, args, buf);
	return (0);
}

long 					ft_fprintf(int fd, const char *fmt, va_list args)
{
	t_vec				*buf;
	t_fmt				*format;

	format = ft_memalloc(sizeof(t_fmt));
	format->iter = fmt;
	buf = ft_vec_init(1, sizeof(char));
	while (*format->iter)
	{
		while (*format->iter != '%' && *format->iter)
			ft_vec_add(&buf, (char *)format->iter++);
		if (!*format->iter)
			break;
		/* processings */
		format->flags = process_flags(format);
		format->width = process_width(format, args);
		format->precision = process_precision(format, args);
		format->lmodifier = process_lmodifier(format);
		format->base = process_base(format);
		print_module(format, args, buf);
	}
	int i = 0;
	while (++i <= buf->total)
		write(fd, &*buf->data++, 1);
	free (format);
	return (buf->total);
}

int				ft_printf(const char *restrict format, ...)
{
	va_list 	args;
	int 		done;

	if (!format)
		return (-1);
	va_start(args, format);
	done = (int)ft_fprintf(1, format, args);
	va_end(args);
	return (done);
}
