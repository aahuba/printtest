/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahuba <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 15:04:40 by ahuba             #+#    #+#             */
/*   Updated: 2018/06/26 15:04:42 by ahuba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			ft_numb(t_printf *all, va_list ap, int *pd)
{
	char	c;

	c = (all->format)[0];
	(c == 'p') ? ft_format_p(ap, all, pd) : 0;
	(all->h == 1) ? all->zero = 0 : 0;
	(c == 'i' || c == 'd') ? ft_format_d(ap, all, pd) : 0;
	(c == 'D') ? ft_format_dd(ap, all, pd) : 0;
	(c == 'x' || c == 'X') ? ft_format_xx(ap, all, pd, c) : 0;
	if (c == 'o' || c == 'O' || c == 'u' || c == 'U')
	{
		if (c == 'U')
			ft_format_uu(ap, all, pd);
		else
			ft_format(ap, all, pd, c);
	}
}

void			ft_chr(t_printf *all, va_list ap, int *pd)
{
	if ((all->format)[0] == 's' && all->l_m != 3)
		ft_pstr(va_arg(ap, char *), *all, pd, 's');
	else if ((all->format)[0] == 'S' ||
	((all->format)[0] == 's' && all->l_m == 3))
		ft_unicode(*all, ap, pd);
	else if ((all->format)[0] == 'c' && all->l_m != 3)
		ft_format_c(all, ap, pd, (all->format)[0]);
	else if ((all->format)[0] == 'C' ||
	((all->format)[0] == 'c' && all->l_m == 3))
		ft_format_c(all, ap, pd, (all->format)[0]);
}

t_printf		*init_printf(t_printf *all)
{
	all = NULL;
	all = (t_printf *)malloc(sizeof(t_printf));
	all->type = 'n';
	all->zero = 0;
	all->w = 0;
	all->precis = -1;
	all->h = 0;
	all->spec = 0;
	all->minus = 0;
	all->hash = 0;
	all->left = 0;
	all->l_m = 0;
	all->min = 0;
	all->znak = 'n';
	all->format = ft_strnew(1);
	all->format_spec = ft_strnew(2);
	return (all);
}

char			*ft_check(t_printf *all, char *format, int *pd, va_list ap)
{
	all = init_printf(all);
	while (*format != '\0')
	{
		if (is_changeable(format) == '0' && som(&format, all, pd))
			return (format);
		else if (is_changeable(format) == 'f')
			ft_flag(all, (*format++));
		else if (is_changeable(format) == 'w')
			ft_width(all, &format);
		else if (is_changeable(format) == 'm')
			ft_modif(all, &format);
		else if (is_changeable(format) == 'p')
			format = ft_precision(all, format);
		else if (is_changeable(format) == 't')
		{
			ft_type(all, ap, *format, pd);
			return (++format);
		}
		else if (format++)
			ft_precision(all, "0");
	}
	return (NULL);
}

int				ft_printf(char *format, ...)
{
	va_list		ap;
	int			pd;
	char		*ptr;
	t_printf	*all;

	if (ft_strcmp(format, "%") == 0)
		return (0);
	all = NULL;
	pd = 0;
	va_start(ap, format);
	while (format && *format)
	{
		while (*format != '\0' && *format != '%' && ++pd)
			ft_putchar(*format++);
		if (*format != '\0' && *format++ == '%')
		{
			ptr = ft_check(all, format, &pd, ap);
			format = ptr;
		}
	}
	va_end(ap);
	return (pd);
}
