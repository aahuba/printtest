/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahuba <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 15:04:23 by ahuba             #+#    #+#             */
/*   Updated: 2018/06/26 15:04:25 by ahuba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	str_len_i(long long int n)
{
	int i;

	i = 0;
	if (n < 0)
	{
		i++;
		n = -n;
	}
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char		*ft_itoa(long long int n, t_printf *all)
{
	char	*ret;
	int		i;

	if ((unsigned long long)n == 9223372036854775808U)
		return (ft_strdup("-9223372036854775808"));
	if (n == -0)
		return (ft_strdup("0"));
	if (!(ret = ft_strnew(str_len_i(n))))
		return (NULL);
	if (n < 0)
	{
		n *= -1;
		all->znak = '-';
	}
	i = str_len_i(n);
	ret[i--] = 0;
	while (n > 0)
	{
		ret[i] = (n % 10) + '0';
		n = n / 10;
		i--;
	}
	return (ret);
}

static int	str_len(unsigned long long int n, int base)
{
	int i;

	i = 0;
	while (n > 0)
	{
		n = n / base;
		i++;
	}
	return (i);
}

char		convert_letter(int a)
{
	if (a == 10)
		return ('a');
	if (a == 11)
		return ('b');
	if (a == 12)
		return ('c');
	if (a == 13)
		return ('d');
	if (a == 14)
		return ('e');
	if (a == 15)
		return ('f');
	return (a + '0');
}

char		*ft_itoa_base(unsigned long long int n, int base, t_printf *all)
{
	char				*ret;
	int					i;

	all->znak = 'n';
	if (n == -0)
		return (ft_strdup("0"));
	if (!(ret = ft_strnew(str_len(n, base))))
		return (NULL);
	i = str_len(n, base);
	ret[i--] = 0;
	while (n > 0)
	{
		ret[i] = convert_letter(n % base);
		n = n / base;
		i--;
	}
	return (ret);
}
