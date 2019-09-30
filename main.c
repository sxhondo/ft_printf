
#include "incs/ft_printf.h"

int 	main()
{
	ft_printf("this is {yellow} YELLOW{eoc} color\n");
	ft_printf("{Bmagenta}BOLD_MAGENTA {eoc}color\n");
	ft_printf("{Bred}VERY SPECIAL RED{eoc}color\n");
	ft_printf("{cyan}cyan..oh cyan! {eoc}{Bcyan} FAT CYAN...OH FAT CYAN!{eoc}\n");
	ft_printf("{cyan}%%{eoc}");
}
