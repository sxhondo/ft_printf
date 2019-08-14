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
	char 			*type;
	unsigned int	width;
	unsigned int	precision;
	int 			flags;
	char 			*iter;
}					t_fmt;

	/* processings */
unsigned int		process_precision(t_fmt *node, va_list args);
unsigned int		process_width(t_fmt *node, va_list args);
int 				process_flags(t_fmt *node);
void				process_datatype(t_fmt *fmt, va_list args);


	/* utilities */
int 				skip_atoi(const char *s);
int					ft_isspecial(char ch);
void				add_data_refresh_node(t_fmt **data, t_fmt *node);
void				print_collected_data(t_fmt **fmt);
void				free_data(t_fmt **fmt);

	/* prints */
/* char, string, pointer*/
void				print_char(t_fmt **fmt, va_list args, int fd);
void				print_str(t_fmt **fmt, va_list args, int fd);
void				print_ptr(t_fmt **fmt, va_list args, int fd);
//void				print_csp(t_fmt **fmt, va_list args, int fd)

/* decimal */
void				print_diouxX(t_fmt **fmt, va_list args, int fd);


int					ft_printf(char *fmt, ...);


#endif //FT_PRINTF_FT_PRINTF_H
