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
	int 	i;

	i = 0;
	if (ft_strlen(fmt->type) > 3) //TODO: some handler
		printf("WRONG AMOUNT\n");
	while (fmt->type)
	{
		if (fmt->type[i] == 'c')
		{
			print_char(&fmt, args, fd);
			break;
		}
		if (fmt->type[i] == 's')
		{
			print_str(&fmt, args, fd);
			break;
		}
		if (fmt->type[i] == 'p')
		{
			print_ptr(&fmt, args, fd);
			break;
		}
		if (*fmt->type == 'c' || *fmt->type == 's' || *fmt->type == 'p'
			|| *fmt->type == 'd' || *fmt->type == 'i' || *fmt->type == 'o'
			|| *fmt->type == 'u' || *fmt->type == 'x' || *fmt->type == 'X')
		{
			print_diouxX(&fmt, args, fd);
			break;
		}
		i++;
	}
}

int 					ft_fprintf(int fd, const char *fmt, va_list args)
{
	int 				i;
	char 				*fmcp;
	t_fmt				*node;
	t_fmt				*data;

	i = 0;
	data = NULL;
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
		add_data_refresh_node(&data, node);
	}
	free_data(&data);
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
