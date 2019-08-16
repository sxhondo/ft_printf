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

#include "ft_printf.h"

void					print_module(t_fmt *fmt, va_list args, int fd)
{
	if (ft_strlen(fmt->type) > 3) //TODO: some handler
		printf("WRONG AMOUNT\n");
	while (fmt->type)
	{
		if (search_spec(fmt->type, 'c'))
		{
			print_char(&fmt, args, fd);
			break;
		}
		if (search_spec(fmt->type, 's'))
		{
			print_str(&fmt, args, fd);
			break;
		}
		if (search_spec(fmt->type, 'p'))
		{
			print_ptr(&fmt, args, fd);
			break;
		}
		if (search_spec(fmt->type, 'd') || search_spec(fmt->type, 'i')
			|| search_spec(fmt->type, 'u'))
		{
			print_diu(&fmt, args, fd);
			break;
		}
		if (search_spec(fmt->type, 'o') || search_spec(fmt->type, 'x')
		|| search_spec(fmt->type, 'X'))
		{
			print_oxX(&fmt, args, fd);
			break;
		}
	}
}

int 					ft_fprintf(int fd, const char *fmt, va_list args)
{
	char 				*fmcp;
	t_fmt				*node;

	fmcp = ft_strdup(fmt);
	node = ft_memalloc(sizeof(t_fmt));
	node->precision = -1;
	node->iter = fmcp;
	while (*node->iter)
	{
		while (*node->iter != '%' && *node->iter)
			write(fd, &*node->iter++, 1);
		if (!*node->iter)
			break;
		/* parsing */
		process_flags(node);
		process_width(node, args);
		process_precision(node, args);
		process_datatype(node, args);

		/* debugging */
		print_collected_data(&node);

		/* printing */
		print_module(node, args, fd);

		refresh_node(node);

	}
	ft_strdel(&fmcp);
	free (node);
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
