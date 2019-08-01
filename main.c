/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 19:51:38 by sxhondo           #+#    #+#             */
/*   Updated: 2019/07/29 14:15:55 by null             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/ft_printf.h"
#include <stdio.h>
#include <libft.h>
#include <stdarg.h>
#include <unistd.h>

#define ZEROPAD	1		/* pad with zero */
#define PLUS	4		/* show plus */
#define SPACE	8		/* space if plus */
#define LEFT	16		/* left justified */
#define SPECIAL	64		/* 0x */

typedef struct		s_fmt
{
	char 			type;
	unsigned int	width;
	unsigned int	precision;
	int 			flags;
	int 			iter;
}					t_fmt;

static int 		skip_atoi(const char *s)
{
	int 	i;

	i = 0;
	while (ft_isdigit(*s))
		i = i * 10 + *s++ - '0';
	return (i);
}

t_fmt 		*process_flags(const char *fmt)
{
	int 	flags;
	t_fmt	*tmp;

	tmp = ft_memalloc(sizeof(t_fmt));
	while (!ft_isdigit(*fmt) || *fmt == '0')
	{
		if (*fmt == '*')
			break;
		++fmt;
		if (*fmt == '-')
		{
			tmp->flags |= LEFT;
			tmp->iter++;
			continue;
		}
		if (*fmt == '+')
		{
			tmp->flags |= PLUS;
			tmp->iter++;
			continue;
		}
		if (*fmt == ' ')
		{
			tmp->flags |= SPACE;
			tmp->iter++;
			continue;
		}
		if (*fmt == '#')
		{
			tmp->flags |= SPECIAL;
			tmp->iter++;
			continue;
		}
		if (*fmt == '0')
		{
			tmp->flags |= ZEROPAD;
			tmp->iter++;
			continue;
		}
	}
	return (tmp);
}

unsigned int		process_width(const char *fmt, va_list args, t_fmt *data)
{
	if (ft_isdigit(*fmt))
		data->width = skip_atoi(fmt);
	else if (*fmt == '*')
	{
		++fmt;
		data->width = va_arg(args, int);
	}
	return (NULL);
}

unsigned int		process_precision(const char *fmt, va_list args)
{
	unsigned int	precision;

	while (*fmt != '.')
		fmt++;
	fmt++;
	if (ft_isdigit(*fmt))
		precision = skip_atoi(fmt);
	else if (*fmt == '*')
	{
		fmt++;
		precision = va_arg(args, int);
	}
	return (precision);
}

char			*process_datatype(const char *fmt, va_list args, t_fmt *data)
{
	printf("FORMAT STRING [%s]\n", fmt);
	int 	i;

	i = 0;
	while (fmt[i])
	{
		if (fmt[i] == 'c' || fmt[i] == 's' || fmt[i] == 'p')
			data->type = fmt[i];
		i++;
	}
	return (NULL);

}

int				ft_fprintf(int fd, const char *fmt, va_list args)
{
	char				buf[1024];
	char				*str;
	t_fmt				*data;

	str = buf;
	while (*fmt != '%')
		*str++ = *fmt++;
	data = process_flags(fmt);
	process_width(fmt + data->iter + 1, args, data);
	data->precision = process_precision(fmt, args);
	process_datatype(fmt, args, data);


	printf("FLAGS [%d]\n", data->flags);
	printf("WIDTH [%d]\n", data->width);
	printf("PRECISION [%d]\n", data->precision);
	printf("DATA_TYPE: [%c]\n", data->type);
	printf("BUF [%s]\n", buf);
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

int 	main()
{
	ft_printf("this is string %*.5p", 'A');
//	printf("%10s", "hello");
}
