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

typedef struct 		s_fmt
{
	struct s_fmt 	*next;
	void 			*flags;
	int 			width;
	int 			precision;
	char 			type;
}					t_fmt;

#endif //FT_PRINTF_FT_PRINTF_H
