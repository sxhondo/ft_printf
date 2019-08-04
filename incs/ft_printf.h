/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 16:34:24 by sxhondo           #+#    #+#             */
/*   Updated: 2019/07/26 16:34:26 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_FT_PRINTF_H
#define FT_PRINTF_FT_PRINTF_H

#include "libft.h"
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>

typedef struct		s_fmt
{
	struct s_fmt 	*next;
	char 			type;
	unsigned int	width;
	unsigned int	precision;
	int 			flags;
	char 			*iter;
}					t_fmt;


unsigned int		process_precision(t_fmt *node, va_list args);
unsigned int		process_width(t_fmt *node, va_list args);
int 				process_flags(t_fmt *node);
void				add_data_refresh_node(t_fmt **data, t_fmt *node);
void				free_data(t_fmt **fmt);
void				print_data(t_fmt **fmt);
void				print_csp(t_fmt **fmt, va_list args, int fd);

#endif //FT_PRINTF_FT_PRINTF_H
