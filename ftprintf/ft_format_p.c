#include "ft_printf.h"

void	ft_format_p(va_list ap, t_printf *all, int *pd)
{
	char *a;
	char *ret;

	a = va_arg(ap, char*);
	all->l_m = 4;
	all->hash = 1;
	ret = ft_strdup("0x");
	ft_strcat(ret, ft_itoa_base((unsigned long int)a, 16, all));
	ft_prnum(ret, *all, 'p', pd);
}
