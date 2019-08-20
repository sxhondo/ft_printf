/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/16 15:08:28 by sxhondo           #+#    #+#             */
/*   Updated: 2019/08/16 15:08:29 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

void	put_uns_number(unsigned int nb, int fd)
{
	if (nb >= 10)
	{
		put_uns_number(nb / 10, fd);
		ft_putchar_fd(nb % 10 + '0', fd);
	}
	else
		ft_putchar_fd(nb + '0', fd);
}


int			search_spec(char *str, char ch)
{
	int 	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ch)
			return (1);
		i++;
	}
	return (0);
}

int 		skip_atoi(const char *s)
{
	int 		i;

	i = 0;
	while (ft_isdigit(*s))
		i = i * 10 + *s++ - '0';
	return (i);
}

int			ft_isspecial(char ch)
{
	if (ch == '*' || ch == '.')
		return (0);
	if (ch >= ' ' && ch <= '0')
		return (1);
	return (0);
}

void			print_collected_data(t_fmt **fmt)
{
	t_fmt		*f;

	f = *fmt;
	printf("\n--------FORMAT----------\n");
	printf("FLAGS: \t\t\t\t[%d]\n", f->flags);
	printf("WIDTH: \t\t\t\t[%d]\n", f->width);
	printf("PRECISION: \t\t\t[%d]\n", f->precision);
	printf("L_MODIFIER: \t\t[%d] or [%c]\n", f->lmodifier, f->lmodifier);
	printf("BASE: \t\t\t\t[%u]\n", f->base);
	printf("ITERATOR: \t\t\t[%s]\n", f->iter);
	printf("------------------------\n");
}
