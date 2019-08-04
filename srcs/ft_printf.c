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

char 			*parse_16table(t_list **row)
{
	char 		table[] = "0123456789abcdef";
	char 		*str;
	int 		i;
	t_list		*next;
	t_list		*curr;

	i = 2;
	curr = *row;
	str = ft_strnew(ft_lstlen(&curr) + 2);
	ft_strcat(str, "0x");
	while (curr)
	{
		next = curr->next;
		str[i] = table[*(int *)curr->content];
		ft_memdel(&curr->content);
		free(curr);
		curr = next;
		i++;
	}
	return (str);
}

char					*base_16(void	*p)
{
	unsigned long long 	nb;
	unsigned long long 	minus;
	unsigned long long 	next;
	unsigned long long 	save;
	t_list				*node;
	t_list				*row;

	row = NULL;
	nb = (unsigned long long)p;
	save = 16;
	while (save > 15)
	{
		next = nb / 16;
		save = next * 16;
		minus = nb - save;
		nb = next;
		node = ft_lstnew(&minus, sizeof(unsigned long long));
		ft_lstadd(&row, node);
	}
	return (parse_16table(&row));

}

void			print_csp(t_fmt **fmt, va_list args, int fd)
{
	uint64_t 	*point;
	t_vec		*container;
	t_fmt		*tmp;
	char 		*pnt;
	char 		ch;
	char 		*str;
	int 		i;


	i = 0;
	tmp = *fmt;
	if (tmp->type == 'c')
	{
		ch = va_arg(args, int);
		if (tmp->width > 1)
		{
			container = ft_vec_init(tmp->width + 2, sizeof(char));
			ft_memset(container->data, ' ', tmp->width - 1);
			((char *)container->data)[tmp->width - 1] = ch;
			ft_putstr(container->data);
			ft_vec_del(&container);
		}
		else
			write(fd, &ch, 1);
	}
	if (tmp->type == 's')
	{
		/* processing precision for a string*/
		if (tmp->precision != -1)
			str = ft_strndup(va_arg(args, char *), tmp->precision);
		else
			str = va_arg(args, char*);
		/* processing width */
		container = ft_vec_init(tmp->width + 1, sizeof(char));
		if (tmp->width > ft_strlen(str))
			ft_memset(container->data, ' ', tmp->width - ft_strlen(str));
		ft_strcat(container->data, str);
		ft_putstr(container->data);
		ft_vec_del(&container);
		if (tmp->precision != -1)
			ft_strdel(&str);
	}
	if (tmp->type == 'p')
	{
		point = va_arg(args, void *);
		pnt = base_16(point);
		write(fd, pnt, ft_strlen(pnt));
		ft_strdel(&pnt);
	}
}

t_fmt					*ft_fprintf(int fd, const char *fmt, va_list args)
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
		while (*node->iter != '%')
			write(fd, &*node->iter++, 1);
		/* parsing */
		process_flags(node);
		process_width(node, args);
		process_precision(node, args);
		node->type = *node->iter++;

		/* debugging */
		print_data(&node);
		if (node->type == 'c' || node->type == 's' || node->type == 'p')
			print_csp(&node, args, fd);

		add_data_refresh_node(&data, node);
	}
	ft_strdel(&fmcp);
	free (node);
	return (data);
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
