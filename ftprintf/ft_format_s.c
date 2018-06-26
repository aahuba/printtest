#include "ft_printf.h"

void	ft_putwchar(wchar_t chr, int *pd)
{
	if (chr <= 0x7F && (*pd)++)
		ft_putchar(chr);
	else if (chr <= 0x7FF && (*pd += 2))
	{
		ft_putchar((chr >> 6) + 0xC0);
		ft_putchar((chr & 0x3F) + 0x80);
	}
	else if (chr <= 0xFFFF && (*pd += 3))
	{
		ft_putchar((chr >> 12) + 0xE0);
		ft_putchar(((chr >> 6) & 0x3F) + 0x80);
		ft_putchar((chr & 0x3F) + 0x80);
	}
	else if (chr <= 0x10FFFF && (*pd += 4))
	{
		ft_putchar((chr >> 18) + 0xF0);
		ft_putchar(((chr >> 12) & 0x3F) + 0x80);
		ft_putchar(((chr >> 6) & 0x3F) + 0x80);
		ft_putchar((chr & 0x3F) + 0x80);
	}
}

void	ft_format_ss(va_list ap, t_printf *all, int *pd)
{
	wchar_t		*a;
	size_t		i;

	i = 0;
	a = va_arg(ap, wchar_t *);
	if (!a)
		ft_pstr(NULL, *all, pd, 's');
	else
	{
		while (*a)
			ft_putwchar(*a++, pd);
	}
}

void	ft_one_bit(unsigned int num)
{
	unsigned char	octet;

	octet = (unsigned char)num;
	write(1, &octet, 1);
}

void	ft_two_bit(unsigned int num)
{
	unsigned int	mask1;
	unsigned char	o2;
	unsigned char	o1;
	unsigned char	octet;

	mask1 = 49280;
	o2 = (num << 26) >> 26;
	o1 = ((num >> 6) << 27) >> 27;
	octet = (mask1 >> 8) | o1;
	write(1, &octet, 1);
	octet = ((mask1 << 24) >> 24) | o2;
	write(1, &octet, 1);
}

void	ft_three_bit(unsigned int num)
{
	unsigned int	mask2;
	unsigned char	o3;
	unsigned char	o2;
	unsigned char	o1;
	unsigned char	octet;

	mask2 = 14712960;
	o3 = (num << 26) >> 26;
	o2 = ((num >> 6) << 26) >> 26;
	o1 = ((num >> 12) << 28) >> 28;
	octet = (mask2 >> 16) | o1;
	write(1, &octet, 1);
	octet = ((mask2 << 16) >> 24) | o2;
	write(1, &octet, 1);
	octet = ((mask2 << 24) >> 24) | o3;
	write(1, &octet, 1);
}

void	ft_four_bit(int *n, unsigned int num)
{
	unsigned char	o4;
	unsigned char	o3;
	unsigned char	o2;
	unsigned char	o1;
	unsigned char	octet;

	(*n) += 4;
	o4 = (num << 26) >> 26;
	o3 = ((num >> 6) << 26) >> 26;
	o2 = ((num >> 12) << 26) >> 26;
	o1 = ((num >> 18) << 29) >> 29;
	octet = (4034953344 >> 24) | o1;
	write(1, &octet, 1);
	octet = ((4034953344 << 8) >> 24) | o2;
	write(1, &octet, 1);
	octet = ((4034953344 << 16) >> 24) | o3;
	write(1, &octet, 1);
	octet = ((4034953344 << 24) >> 24) | o4;
	write(1, &octet, 1);
}

void	ft_prunic(unsigned int num, int *pd, int size)
{
	if (size == 1 && ((*pd) += 1))
		ft_one_bit(num);
	else if (size == 2 && ((*pd) += 2))
		ft_two_bit(num);
	else if (size == 3 && ((*pd) += 3))
		ft_three_bit(num);
	else
		ft_four_bit(pd, num);
	return ;
}

int		n_bits(unsigned int num, t_printf *all)
{
	int		num_bits;
	char	*p;

	p = ft_itoa_base(num, 2, all);
	num_bits = ft_strlen(p);
	free(p);
	num_bits /= 2;
	if (num_bits < 4)
		num_bits = 1;
	else if (num_bits >= 4 && num_bits <= 5)
		num_bits = 2;
	else if (num_bits >= 6 && num_bits <= 8)
		num_bits = 3;
	else
		num_bits = 4;
	return (num_bits);
}

void	ft_unicode(t_printf all, va_list ap, int *pd)
{
	wchar_t			*str;
	unsigned int	c;
	int				i;
	int				num_bits;

	i = 0;
	num_bits = 0;
	str = va_arg(ap, wchar_t*);
	if (!str)
		ft_pstr(NULL, all, pd, 's');
	while (str && str[i])
		num_bits += n_bits(str[i++], &all);
	num_bits == 13 ? num_bits = 0 : 0;
	while (all.left != 1 && all.w-- > num_bits && ++(*pd))
		(all.zero == 0) ? write(1, " ", 1) : write(1, "0", 1);
	i = 0;
	while (num_bits > 0)
	{
		c = (unsigned int)n_bits(str[i], &all);
		ft_prunic(str[i++], pd, c);
		num_bits -= c;
	}
}

char	*ft_format_c(t_printf *all, va_list ap, int *pd, char c)
{
	unsigned int	a;
	char	*ret;
	int			num_bits;

	ret = ft_strnew(2);
	if (!ret)
		return (NULL);
	a = (unsigned int)va_arg(ap, wint_t);
	num_bits = n_bits(a, all);
	if (((c == 'C') || (c == 'c' && all->l_m == 3)) && num_bits == 2 && (*pd += 2))
	{
		ft_two_bit(a);
		return (0);
	}
	if (((c == 'C') || (c == 'c' && all->l_m == 3)) && num_bits == 3 && (*pd += 3))
	{
		ft_three_bit(a);
		return (0);
	}
	ret[0] = a;
	ret[1] = 0;
	ft_pstr(ret, *all, pd, 'c');
	return (ret);
}
