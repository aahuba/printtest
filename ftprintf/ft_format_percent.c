#include "ft_printf.h"

void	ft_format_percent(t_printf *all, int *pd)
{
	if (all->precis == 0)
			all->precis = 1;
	ft_pstr(ft_strdup("%"), *all, pd, 's');
}
