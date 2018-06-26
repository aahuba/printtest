/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahuba <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 15:03:51 by ahuba             #+#    #+#             */
/*   Updated: 2018/06/26 15:03:55 by ahuba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_format_p(va_list ap, t_printf *all, int *pd)
{
	char *a;
	char *ret;

	a = va_arg(ap, char*);
	all->l_m = 4;
	all->hash = 1;
	all->type = 'p';
	ret = ft_strdup("");
	ft_strcat(ret, ft_itoa_base((unsigned long int)a, 16, all));
	ft_prnum(ret, *all, 'x', pd);
}

char	*ft_modific_2(t_printf *all, char *str)
{
	if (all->l_m < 3)
		all->l_m = 3;
	if (*(str + 1) != '\0' && *(str + 1) == 'l' && (*str++))
	{
		if (all->l_m < 4)
			all->l_m = 4;
	}
	return (str);
}

char	*ft_modific_1(t_printf *all, char *str)
{
	if (*(str + 1) != '\0' && *(str + 1) == 'h')
	{
		if (all->l_m < 1)
			all->l_m = 1;
		str++;
	}
	else if (all->l_m < 2)
		all->l_m = 2;
	return (str);
}

void	ft_modific(t_printf *all, char *str)
{
	while (*str && (*str == 'h' || *str == 'l' || *str == 'z' || *str == 'j'))
	{
		if (*str == 'h')
			str = ft_modific_1(all, str);
		else if (*str == 'l')
			str = ft_modific_2(all, str);
		else if (*str == 'z')
			all->l_m = 6;
		else if (*str == 'j' && all->l_m != 6)
			all->l_m = 5;
		++str;
	}
}

int		som(char **str, t_printf *all, int *pd)
{
	char	*m;

	if (all->w != 0)
	{
		m = malloc(sizeof(char) * 2);
		m[0] = **str;
		m[1] = '\0';
		if (all->precis == 0)
			all->precis = 1;
		ft_pstr(m, *all, pd, 's');
		(*str)++;
		free(m);
	}
	return (1);
}
