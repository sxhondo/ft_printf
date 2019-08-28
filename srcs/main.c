/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sxhondo <w13cho@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 20:32:45 by sxhondo           #+#    #+#             */
/*   Updated: 2019/08/27 00:30:46 by sxhondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ft_printf.h"
//#include "ft_printf.h"

char		 		*fraction(double num, char s[])
{
	int 	exp = 5;
	int 	whole[exp];
	int 	i;

	i = 0;
	while (i < exp)
	{
		num *= 2;
		if ((int)num > 1)
			num -= 2;
		whole[i] = (int)num;
//		printf("%d\n", whole[i]);
		i++;
	}
	i = -1;
	while (++i < exp)
		*s++ = whole[i] + '0';
	return (NULL);
}

int 	main()
{

	printf("%s", "Запишите код действительного числа,\n" \
			  "интерпретируя его как величину типа Double: 446.15625\n\n");

	char 	whole[100];
	char 	fract[100];
	char 	wf[100];
	char 	*p = wf;
	char 	exp[100];

	// 1. Берем целую часть числа 446,15625 (446).
	// Переводим число в двоичное представление. Exp целой части = 3;
	itoa_base(446, whole, 0, 2);
//	printf(". 446 в двоичном представлении: %s\n", whole);

	// 2. Берем дробную часть числа 446,15625 (0.15625).
	// Умножаем его на два 5 раз. Exp дробной части = 5
	fraction(0.15625, fract);


	printf(". 446.15625 в b2: \nsub-normal form: %15s %s\t", whole, fract);
	//14277//
	printf("<- Необходимо представить это число в нормализированной форме(1,1011111000101 * 2^8)\n");
//	printf("normal form: %20s", p);



	//3. Знак S = 0
	// EXP = 3 + 5 + 1023 = 1031(b10)
	// whole_part + fract_part + смещение exp для типа double
//	itoa_base(1031, exp, 0, 2);
//	printf(". EXP = %s", exp);
//	printf(". MANT = %s", )


	return (0);
}
