/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   csp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 16:14:51 by sxhondo           #+#    #+#             */
/*   Updated: 2019/08/14 16:14:53 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char 			*parse_16table(t_list **row)
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

void			print_char(t_fmt **fmt, va_list args, int fd)
{
	t_vec		*container;
	t_fmt		*tmp;
	char 		ch;

	tmp = *fmt;
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

void			print_str(t_fmt **fmt, va_list args, int fd)
{
	char 		*str;
	t_vec		*container;
	t_fmt		*tmp;

	tmp = *fmt;
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

void			print_ptr(t_fmt **fmt, va_list args, int fd)
{
	uint64_t 	*point;
	char 		*pnt;
	t_fmt		*tmp;

	tmp = *fmt;
	point = va_arg(args, void *);
	pnt = base_16(point);
	write(fd, pnt, ft_strlen(pnt));
	ft_strdel(&pnt);
}