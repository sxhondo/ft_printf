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
	uint64_t 	*point;
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