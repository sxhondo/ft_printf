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

#include "../incs/ft_printf.h"

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
	int64_t		num;

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
	get_num(num, fmt, buf, 1);
}

void					positive_nums(t_fmt *fmt, va_list args, t_vec *buf)
{
	uint64_t 		num;

	fmt->flags &= ~PLUS;
	fmt->flags &= ~SPACE;
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
	get_num(num, fmt, buf, 0);
}

void					floats(t_fmt *fmt, va_list args, t_vec *buf)
{
	long double			dnum;

	if (fmt->lmodifier & LLONG)
		dnum = va_arg(args, long double);
	else
		dnum = va_arg(args, double);
	get_dnum(dnum, fmt, buf);

}

int						print_module(t_fmt *fmt, va_list args, t_vec *buf)
{
		/* PERCENT, CHAR, STRING, POINTER */
	if (*fmt->iter == '%' || *fmt->iter == 'c' || *fmt->iter == 's'
		|| *fmt->iter == 'p')
		pcsp(fmt, args, buf);

		/* SIGNED NUMS */
	else if (*fmt->iter == 'd' || *fmt->iter == 'i')
		positive_negative_nums(fmt, args, buf);

		/* UNSIGNED  NUMS */
	else if (*fmt->iter == 'o' || *fmt->iter == 'u' || *fmt->iter == 'x'
			|| *fmt->iter == 'X' || *fmt->iter == 'b')
		positive_nums(fmt, args, buf);

		/* FLOATS */
	else if (*fmt->iter == 'f')
		floats(fmt, args, buf);
	return (0);
}

t_fmt					*parse_format_string(t_fmt *fmt, va_list args)
{
	fmt->flags = process_flags(fmt);
	fmt->width = process_width(fmt, args);
	fmt->precision = process_precision(fmt, args);
	fmt->lmodifier = process_lmodifier(fmt);
	fmt->base = process_base(fmt);
}

char					*process_color(t_fmt *fmt)
{
	unsigned int		bold;

	bold = 0;
	while (*fmt->iter++ && *fmt->iter != '}' && *fmt->iter)
	{
		if (*fmt->iter == 'B')
			bold |= (unsigned)1;
	}
}

void					write_in_buf(t_fmt *fmt, t_vec *buf)
{
	char 				*str;
	int 				i;

	i = 0;
	while (*fmt->iter != '%' && *fmt->iter)
	{
		if (*fmt->iter == '{')
			process_color(fmt);
		ft_vec_add(&buf, (char *)&*fmt->iter++);
	}
}

int 					ft_fprintf(int fd, const char *fmt, va_list args)
{
	t_vec				*buf;
	t_fmt				*format;
	size_t 				save;
	int 				i;

	if (!(buf = ft_vec_init(1, sizeof(char)))
			|| !(format = ft_memalloc(sizeof(t_fmt))))
		return (0);
	format->iter = fmt;
	while (*format->iter)
	{
		write_in_buf(format, buf);
		if (!*format->iter)
			break;
		parse_format_string(format, args);
		print_module(format, args, buf);
	}
	i = -1;
	save = buf->total;
	while (++i < buf->total)
		write(fd, &buf->data[i], 1);
	ft_vec_del(&buf);
	free (format);
	return (save);
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
