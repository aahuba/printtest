/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahuba <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 15:04:52 by ahuba             #+#    #+#             */
/*   Updated: 2018/06/26 15:04:55 by ahuba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_flag(t_printf *all, char c)
{
	if (c == '+')
		all->znak = '+';
	else if (c == ' ' && all->znak != '+')
		all->znak = ' ';
	else if (c == '-')
	{
		all->zero = 0;
		all->left = 1;
	}
	else if (c == '0' && all->left != 1)
		all->zero = 1;
	else if (c == '#')
		all->hash = 1;
}

char	is_changeable(char *c)
{
	if (*c == '.' && *(c + 1) && (*(c + 1) >= '0' && *(c + 1) <= '9'))
		return ('p');
	if (*c == '.' && *(c + 1) && !(*(c + 1) >= '0' && *(c + 1) <= '9'))
		return ('g');
	if (ft_strchr(FLAG, *c))
		return ('f');
	if (*c >= '1' && *c <= '9')
		return ('w');
	if (ft_strchr(SPEC, *c))
		return ('m');
	if (ft_strchr(TYPE, *c))
		return ('t');
	return ('0');
}

void	parse_conv(t_printf *all, char *format)
{
	if (ft_strchr(TYPE, *format))
	{
		if (*format == 'i')
			*format = 'd';
		all->format[0] = *format;
	}
}

char	*ft_precision(t_printf *all, char *format)
{
	++format;
	all->precis = ft_atoi(format);
	while (ft_isdigit((int)*format) && *format != '\0')
		format++;
	all->h = 1;
	return (format);
}

void	ft_type(t_printf *all, va_list ap, char format, int *pd)
{
	parse_conv(all, &format);
	ft_modific(all, all->format_spec);
	if ((all->format)[0] == 's' || (all->format)[0] == 'S' || \
		(all->format)[0] == 'c' || (all->format)[0] == 'C')
		ft_chr(all, ap, pd);
	else if ((all->format)[0] == '%')
		ft_format_percent(all, pd);
	else
		ft_numb(all, ap, pd);
}
