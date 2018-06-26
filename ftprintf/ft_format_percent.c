/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_percent.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahuba <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 15:04:02 by ahuba             #+#    #+#             */
/*   Updated: 2018/06/26 15:04:05 by ahuba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_format_percent(t_printf *all, int *pd)
{
	if (all->precis == 0)
			all->precis = 1;
	ft_pstr(ft_strdup("%"), *all, pd, 's');
}

void	ft_prunic(unsigned int num, int *pd, int size)
{
	if (size == 1 && ((*pd) += 1))
		ft_one_bit(num);
	else if (size == 2 && ((*pd) += 2))
		ft_two_bit(num);
	else if (size == 3 && ((*pd) += 3))
		ft_three_bit(num);
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
