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


t_fmt			*parse_format_string(const char *fmt)
{
	int 	i;
	char 	*new;

	//		%42d%21c
	while (fmt[i])
	{
		while (!ft_isalpha(fmt[i]))
		{

			i++;
		}
		ft_putchar(fmt[i]);
		i++;
	}



}

int				ft_fprintf(int fd, const char *fmt, va_list args)
{
	/* Later I should create some kind of table to compare given values with existing values */
	int 	i;
	t_fmt	*format;

	format = parse_format_string(fmt);


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
	ft_printf("%42d%21c", "value trash");
//	printf("%char", 'e');
}
