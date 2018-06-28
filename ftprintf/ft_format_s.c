/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_s.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahuba <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 15:04:12 by ahuba             #+#    #+#             */
/*   Updated: 2018/06/26 15:04:14 by ahuba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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

char	*ft_format_c(t_printf *all, va_list ap, int *pd, char c)
{
	unsigned int	a;
	char			*ret;
	int				num_bits;

	ret = ft_strnew(2);
	if (!ret)
		return (NULL);
	a = (unsigned int)va_arg(ap, wint_t);
	num_bits = n_bits(a, all);
	if (((c == 'C') || (c == 'c' && all->l_m == 3))
	&& num_bits == 2 && (*pd += 2))
	{
		ft_two_bit(a);
		return (0);
	}
	if (((c == 'C') || (c == 'c' && all->l_m == 3))
	&& num_bits == 3 && (*pd += 3))
	{
		ft_three_bit(a);
		return (0);
	}
	ret[0] = a;
	ret[1] = 0;
	ft_pstr(ret, *all, pd, 'c');
	return (ret);
}
