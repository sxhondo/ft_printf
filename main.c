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

#define ZEROPAD	1		/* pad with zero */
#define PLUS	4		/* show plus */
#define SPACE	8		/* space if plus */
#define LEFT	16		/* left justified */
#define SPECIAL	64		/* 0x */

void			print_and_free_data(t_fmt **fmt)
{
	t_fmt		*curr;
	t_fmt		*next;

	curr = *fmt;
	while (curr)
	{
		printf("FLAGS: [%d]\n", curr->flags);
		printf("WIDTH: [%d]\n", curr->width);
		printf("PRECISION: [%d]\n", curr->precision);
		printf("DATA_TYPE: [%c]\n", curr->type);
		printf("STR: [%s]\n", curr->str);
		printf("----------------------\n");
		next = curr->next;
		free (curr);
		curr = next;
	}
}

void			add_data_refresh_node(t_fmt **data, t_fmt *node)
{
	t_fmt		*tmp;
	t_fmt		*new;

	tmp = *data;
	new = ft_memalloc(sizeof(t_fmt));
	new->flags = node->flags;
	new->type = node->type;
	new->precision = node->precision;
	new->width = node->width;
	new->iter = node->iter;
	new->str = node->str;

	node->flags = 0;
	node->width= 0;
	node->precision = 0;

	if (!*data)
		*data = new;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->next = NULL;
	}
}

static int 		skip_atoi(const char *s)
{
	int 	i;

	i = 0;
	while (ft_isdigit(*s))
		i = i * 10 + *s++ - '0';
	return (i);
}

int 			ft_isspecial(char ch)
{
	if (ch == '*')
		return (0);
	if (ch >= ' ' && ch <= '0')
		return (1);
	return (0);
}

int 			process_flags(t_fmt *node)
{
	while (*node->iter++ && ft_isspecial(*node->iter))
	{
		if (*node->iter == '-')
		{
			node->flags |= LEFT;
			continue;
		}
		if (*node->iter == '+')
		{
			node->flags |= PLUS;
			continue;
		}
		if (*node->iter == ' ')
		{
			node->flags |= SPACE;
			continue;
		}
		if (*node->iter == '#')
		{
			node->flags |= SPECIAL;
			continue;
		}
		if (*node->iter == '0')
		{
			node->flags |= ZEROPAD;
			continue;
		}
	}
	return (0);
}

unsigned int		process_width(t_fmt *node, va_list args)
{
	if (ft_isdigit(*node->iter))
	{
		node->width = skip_atoi(node->iter);
		node->iter += ft_nblen(node->width);
	}
	else if (*node->iter == '*')
	{
		++node->iter;
		node->width = va_arg(args, int);
	}
	return (0);
}

unsigned int		process_precision(t_fmt *node, va_list args)
{
	if (*node->iter == '.')
		node->iter++;
	if (ft_isdigit(*node->iter))
	{
		node->precision = skip_atoi(node->iter);
		node->iter += ft_nblen(node->precision);
	}
	else if (*node->iter == '*')
	{
		node->iter++;
		node->precision = va_arg(args, int);
	}
	return (0);
}

int				ft_fprintf(int fd, const char *fmt, va_list args)
{
	char 				buf[1024];
	char 				*str;
	t_fmt				*node;
	t_fmt				*data;
	t_vec				*vec;

	if (!(vec = ft_vec_init(ft_strlen(fmt), sizeof(char))))
		return (0);
	while (*fmt)
		ft_vec_add(&vec, (void *)fmt++);
	ft_vec_add(&vec, "\0");
	if (!(ft_vec_resize(&vec)))
	{
		ft_vec_del(&vec);
		return (0);
	}

	str = buf;
	data = NULL;
	node = ft_memalloc(sizeof(t_fmt));
	node->iter = (char *)vec->data;
	while (*node->iter)
	{
		while (*node->iter != '%')
			*str++ = *node->iter++;
		process_flags(node);
		process_width(node, args);
		process_precision(node, args);
		node->type = *node->iter++;

			/* just for tests */
			va_arg(args, int);
		add_data_refresh_node(&data, node);
	}
	print_and_free_data(&data);
	ft_vec_del(&vec);
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

int 	main()
{

//	ft_printf("str%14.14284c stringi %s", 'c');
	ft_printf("hello%0#10.15s = %013.14c", "str");
//	printf("%*.5c = %10.*s", 10, 'b', 1, "str");
}
