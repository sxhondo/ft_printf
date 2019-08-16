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

char			*apply_width(void *p, int width, char type)
{
	char 		*container;
	char 		*str;

	if (type == 's')
	{
		str = *(char **)p;
		container = ft_strnew(width + 1);
		if (width > ft_strlen(str))
			ft_memset(container, ' ', width - ft_strlen(str));
		ft_strcat(container, str);
		return (container);
	}
	if (type == 'c')
	{
		container = ft_strnew(width + 1);
		ft_memset(container, ' ', width);
		container[width - 1] = *(char *)p;
		return (container);
	}
}

void			print_char(t_fmt **fmt, va_list args, int fd)
{
	char 		*buf;
	t_fmt		*tmp;
	char 		ch;

	tmp = *fmt;
	ch = va_arg(args, int);

	if (tmp->width > 1)
	{
		buf = apply_width(&ch, tmp->width, 'c'); //todo: choose symbol to set (from flags)
		ft_putstr(buf);
		ft_strdel(&buf);
	}
	else
		write(fd, &ch, 1);
}

void			print_str(t_fmt **fmt, va_list args, int fd)
{
	char 		*buf;
	char 		*str;
	t_fmt		*tmp;

	tmp = *fmt;
	/* processing precision for a string*/
	if (tmp->precision != -1)
		str = ft_strndup(va_arg(args, char *), tmp->precision);
	else
		str = va_arg(args, char*);
	/* processing width */
	if (tmp->width > 1)
	{
		buf = apply_width(&str, tmp->width, 's');
		ft_putstr(buf);
		ft_strdel(&buf);
		if (tmp->precision != -1)
			ft_strdel(&str);
		return;
	}
	ft_putstr(str);
	if (tmp->precision != -1)
		ft_strdel(&str);
}

char 			*add_0x(char *str)
{
	char 	*newstr;

	newstr = ft_strnew(ft_strlen(str) + 2);
	ft_strcat(newstr, "0x");
	ft_strcat(newstr, str);
	return (newstr);
}

void			print_ptr(t_fmt **fmt, va_list args, int fd)
{
//	uint64_t 	*point; ???
	int		 	*point;
	char 		*pnt;
	char 		*zero_x;
	t_fmt		*tmp;

	tmp = *fmt;
	point = va_arg(args, void *);
	pnt = base_any(point, 16);
	zero_x = ft_strnew(ft_strlen(pnt) + 2);
	ft_strcat(zero_x, "0x");
	ft_strcat(zero_x, pnt);
	ft_strdel(&pnt);
	write(fd, zero_x, ft_strlen(zero_x));
	ft_strdel(&zero_x);
}