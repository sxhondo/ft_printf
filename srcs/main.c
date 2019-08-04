/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 20:32:45 by sxhondo           #+#    #+#             */
/*   Updated: 2019/08/04 20:32:46 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int 	main()
{
	char 	buf[] = "hello";
	char 	*p;
	t_list	*tmp;

	p = buf;
	ft_printf("%p", p);
//	printf("\n\n----ORIGINAL PRINTF------\n");
//	printf("%10.3s %s = %p", "string", "streng", p);
//	printf("%*.5c = %10.*s", 10, 'b', 1, "str");

}
