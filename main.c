/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 19:51:38 by sxhondo           #+#    #+#             */
/*   Updated: 2019/07/23 19:51:39 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/ft_printf.h"
#include <stdio.h>
#include <libft.h>
#include <stdarg.h>
#include <unistd.h>

int				ft_fprintf(int fd, const char *fmt, va_list args)
{
	char	buf[1024];
	char	*str;

	str = buf;
	while (*fmt)
	{
		if (*fmt != '%')
		{
			*str++ = *fmt++;
			continue;
		}
		fmt++;
	}
	//printf("%-1000s\n", buf);
	printf("hello%10d\n", 10);
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
	ft_printf("some string %d", 42);
//	printf("%char", 'e');
}
