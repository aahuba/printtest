#include "ft_printf.h"

char	*ft_format(va_list ap, t_printf *all, int *pd, char c)
{
	unsigned long long int a;

	c == 'O' ? ft_modific(all, "l") : 0;
	a = va_arg(ap, unsigned long long int);
	if (all->l_m == 0)
		a = (unsigned int)(a);
	else if (all->l_m == 1)
		a = (unsigned char)(a);
	else if (all->l_m == 2)
		a = (unsigned short)(a);
	else if (all->l_m == 3)
		a = (unsigned long)(a);
	else if (all->l_m == 4)
		a = (unsigned long long)(a);
	else if (all->l_m == 5)
		a = (uintmax_t)(a);
	else if (all->l_m == 6)
		a = (size_t)(a);
	(c == 'O' || c == 'o') ? ft_prnum(ft_itoa_base(a, 8, all), *all, c, pd) : 0;
	(c == 'u') ? ft_prnum(ft_itoa_base(a, 10, all), *all, 'u', pd) : 0;
	if (c == 'x' || c == 'X')
		return (ft_itoa_base(a, 16, all));
	return (0);
}

void	ft_format_uu(va_list ap, t_printf *all, int *pd)
{
	unsigned long int a;

	ft_modific(all, "l");
	a = (unsigned long)va_arg(ap, long int);
	ft_prnum(ft_itoa_base(a, 10, all), *all, 'U', pd);
}

void	ft_format_xx(va_list ap, t_printf *all, int *pd, char c)
{
	char *a;

	a = ft_format(ap, all, pd, c);
	if (c == 'x' && all->hash == 1 && all->zero == 0 && *a != '0' && (*pd -= 2))
		a = ft_strjoin("0x", a);
	if (c == 'X' && all->hash == 1 && all->zero == 0 && *a != '0' && (*pd -= 2))
		a = ft_strjoin("0X", a);
	if (c == 'X')
		ft_strupper(a);
	ft_prnum(a, *all, c, pd);
}

void	ft_format_d(va_list ap, t_printf *all, int *pd)
{
	long long int	a;

	a = va_arg(ap, long long int);
	if (all->l_m == 0)
		a = (int)a;
	else if (all->l_m == 1)
		a = (signed char)a;
	else if (all->l_m == 2)
		a = (short)a;
	else if (all->l_m == 3)
		a = (long)a;
	else if (all->l_m == 4)
		a = (long long)a;
	else if (all->l_m == 5)
		a = (intmax_t)a;
	else if (all->l_m == 6)
		a = (size_t)a ;
	ft_prnum(ft_itoa(a, all), *all, 'd', pd);
}

void	ft_format_dd(va_list ap, t_printf *all, int *pd)
{
	long a;

	ft_modific(all, "l");
	a = va_arg(ap, long);
	ft_prnum(ft_itoa(a, all), *all, 'D', pd);
}
