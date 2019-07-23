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

#include <stdio.h>
#include <libft.h>
#include <stdarg.h>

char 	get_slash(char spec)
{
	printf("%d", spec);
}

void	ft_printf(char *fmt, ...)
{
	va_list		args;
	int 		ival;
	int 		i;

	i = 0;
	va_start(args, fmt); /* устанавливает аrgs на 1-й безымянный аргумент после fmt */
	while (*fmt)
	{
		while(*fmt != '%')
			ft_putchar(*fmt++);
		fmt++;
		if (*fmt == '\\')
		{
			*fmt++;
			ft_putchar(*fmt);
		}
		if (*fmt == 'd')
		{
			ival = va_arg(args, int); /* va_arg раскрывается в выражение типа [int], которое представляет собой следующий аргумент из args */
			ft_putnbr(ival);
		}
		fmt++;
	}
	va_end(args);

}

int 	main()
{
	int j = 21;

	ft_printf("random string: %d", 42);
}
