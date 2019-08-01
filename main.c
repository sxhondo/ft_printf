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
	struct s_fmt 	*next;
	char 			type;
	unsigned int	width;
	unsigned int	precision;
	int 			flags;
	int 			iter;
}					t_fmt;

void			print_and_free_fmt(t_fmt **fmt, char buf[])
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
		printf("BUF: [%s]\n", buf);
		printf("----------------------\n");
		next = curr->next;
		free (curr);
		curr = next;
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

t_fmt 		*process_flags(const char *fmt)
{
	int 	flags;
	t_fmt	*tmp;

	tmp = ft_memalloc(sizeof(t_fmt));
	while ((!ft_isdigit(*fmt) || *fmt == '0') && *fmt)
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
	return (0);
}

unsigned int		process_precision(const char *fmt, va_list args)
{
	unsigned int	precision;

	precision = 0;
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

int			process_datatype(const char *fmt, va_list args, t_fmt *data)
{
//	printf("FORMAT STRING [%s]\n", fmt);
	int 	i;

	i = 0;
	while (fmt[i])
	{
		if (fmt[i] == 'c' || fmt[i] == 's' || fmt[i] == 'p')
		{
			data->type = fmt[i];
			break;
		}
		i++;
	}
	return (i);
}

void			add_data(t_fmt **data, t_fmt *node)
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

int				ft_fprintf(int fd, const char *fmt, va_list args)
{
	char				buf[1024];
	char				*str;
	int 				jump;
	t_fmt				*node;
	t_fmt				*data;

	str = buf;
	while (*fmt)
	{
		while (*fmt != '%')
			*str++ = *fmt++;
		node = process_flags(fmt);
		process_width(fmt + node->iter + 1, args, node);
		node->precision = process_precision(fmt, args);
		jump = (process_datatype(fmt, args, node) + 1);
		/* just for tests */
			va_arg(args, int);
		add_data(&data, node);
		free (node);
		fmt += jump;
	}
	print_and_free_fmt(&data, buf);
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
	ft_printf("%*.5c = %10.*s and %#20.13p", 2, 'a', 4, "str");
//	printf("%*.5c = %10.*s", 10, 'b', 1, "str");
}
