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

#define SIGN	2		/* unsigned/signed long */
#define SMALL	32		/* Must be 32 == 0x20 */
#define ZEROPAD	1		/* pad with zero */
#define PLUS	4		/* show plus */
#define SPACE	8		/* space if plus */
#define LEFT	16		/* left justified */
#define SPECIAL	64		/* 0x */

static int 		skip_atoi(const char **s)
{
	int 	i;

	i = 0;
	while (ft_isdigit(**s))
		i = i * 10 + *((*s)++) - '0';
	return (i);
}

int 			process_flags(const char *fmt)
{
	int 	flags;

	++fmt; /* skip % */
	while (*fmt)
	{
		if (*fmt == '-')
		{
			flags |= LEFT; /* left justified */
			process_flags(++fmt);
		}
		if (*fmt == '+')
		{
			flags |= PLUS; /* show plus */
			process_flags(++fmt);
		}
		if (*fmt == ' ')
		{
			flags |= SPACE;/* space if plus */
			process_flags(++fmt);
		}
		if (*fmt == '#')
		{
			flags |= SPECIAL; /* 0x */
			process_flags(++fmt);
		}
		if (*fmt == '0')
		{
			flags |= ZEROPAD;/* pad with zero */
			process_flags(++fmt);
		}
		fmt++;
	}
	return (flags);
}

int 			get_fwidth(const char *fmt, va_list args, int flags)
{
	int 	width = -1;
	if (ft_isdigit(*fmt))
		width = skip_atoi(&fmt);
	else if (*fmt == '*')
	{
		++fmt;
		width = va_arg(args, int);
		flags |= 16;
	}
	return (width);

}
int				ft_fprintf(int fd, const char *fmt, va_list args)
{
	char		buf[1024];
	char		*str;
	int 		flags;
	int 		fwidth;

	flags = 0;
	fwidth = -1;
	str = buf;
	while (*fmt)
	{
		if (*fmt != '%')
		{
			*str++ = *fmt++;
			continue;
		}
		flags = process_flags(fmt);
//		fwidth = get_fwidth(fmt, args, flags);
		fmt++;
	}
	printf("FLAGS [%d]\n", flags);
//	printf("FIELD WIDTH [%d]\n", fwidth);
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
	ft_printf("%+d", 42);
//	printf("%+10d%+d", -42, 21);
}
