
#include "incs/ft_printf.h"

int 	main()
{
	void	*p;

	ft_printf("{red}char: %c\n", 'c');
	ft_printf("{blue}string: %s\n", "presentation!");
	ft_printf("{cyan}pointer: %p\n", p);
	ft_printf("{yellow}%%\n");

	ft_printf("{green}decimal and width: %5d\n", 42);
	ft_printf("{Bred}decimal and precision: %.4i\n", 42);
	ft_printf("{Bblue}unsigned decimal and flags '-': %-10u\n", 42);
	ft_printf("{Bcyan}octal notation and flag '#': %#o\n", 42);
	ft_printf("{Byellow}hex notation; %x\n", 42);
	ft_printf("{magenta}HEX NOTATION: %X\n", 42);
	ft_printf("{Bmagenta}binary notation: %b\n", 42);
	ft_printf("{Bgreen}%f\n", 3.14);
	ft_printf("{green}%e\n", 0.014);
}
