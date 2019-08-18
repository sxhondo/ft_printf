/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   di.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 18:34:01 by sxhondo           #+#    #+#             */
/*   Updated: 2019/08/14 18:34:02 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char 		skip_itoa(int nb)
{
	return (nb % 10 + '0');
}

int				get_decimal(t_fmt **fmt, va_list args, int fd, char *buf_ptr)
{
	//TODO: get the decimal according flags, width, qualifier...
	print_collected_data(fmt);
	exit (0);


//	char 			*type;
//	intmax_t 		n;
//	uintmax_t		un;
//
//	if (search_spec((*fmt)->type, 'd') || search_spec((*fmt)->type, 'i'))
//	{
//		n = va_arg(args, int);
//		type = get_type((*fmt)->type);
//		if (ft_strequ(type, "char"))
//			ft_putnbr_fd((char)n, fd);
//		else if (ft_strequ(type, "int"))
//			ft_putnbr_fd((int)n, fd);
//		else if (ft_strequ(type, "short"))
//			ft_putnbr_fd((short)n, fd);
//		else if (ft_strequ(type, "long"))
//			ft_putnbr_fd((long)n, fd);
//		else if (ft_strequ(type, "long long"))
//			ft_putnbr_fd((long long)n, fd);
//	}
//	if (search_spec((*fmt)->type, 'u'))
//	{
//		un = va_arg(args, unsigned int);
//		type = get_type((*fmt)->type);
//		if (ft_strequ(type, "char"))
//			put_uns_number((unsigned char)un, fd);
//		else if (ft_strequ(type, "int"))
//			put_uns_number((unsigned int)un, fd);
//		else if (ft_strequ(type, "short"))
//			put_uns_number((unsigned short)un, fd);
//		else if (ft_strequ(type, "long")) //DONT UNDERSTAND
//			put_uns_number((unsigned long)un, fd);
//		else if (ft_strequ(type, "long long"))
//			put_uns_number((unsigned long long)un, fd);
//	}
}

//char 				*print_oxX(t_fmt **fmt, va_list args, int fd)
//{
//	int 		i;
//	t_fmt		*tmp;
//	int		  	*nb;
//	char 		*number;
//
//	i = 0;
//	tmp = *fmt;
//	nb = va_arg(args, void *);
//	if (search_spec(tmp->type, 'o'))
//	{
//		number = base_any(nb, 8);
//		ft_putstr(number);
//		ft_strdel(&number);
//	}
//	else if (search_spec(tmp->type, 'x') || search_spec(tmp->type, 'X'))
//	{
//		number = base_any(nb, 16);
//		if (search_spec(tmp->type, 'X'))
//			while (number[i++])
//				number[i] = ft_toupper(number[i]);
//		ft_putstr(number);
//		ft_strdel(&number);
//	}
//	return (NULL);
//
//}
