/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_out.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahuba <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 15:04:32 by ahuba             #+#    #+#             */
/*   Updated: 2018/06/26 15:04:34 by ahuba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_spaces(t_printf all, char *s, int l, char c)
{
	int spaces;

	spaces = (all.precis > l) ? all.precis : l;
	spaces = (all.znak != 'n') ? spaces + 1 : spaces;
	spaces = (*s == '0' && all.precis == 0) ? 0 : spaces;
	spaces = (all.w > spaces) ? all.w - spaces : 0;
	spaces = (c == 'x' && all.hash == 1 && all.zero == 0 && (*s != '0' \
		|| all.type == 'p')) ? spaces - 2 : spaces;
	spaces = (c == 'o' && all.hash == 1) ? spaces - 1 : spaces;
	return (spaces);
}

void	ft_prnum(char *s, t_printf all, char c, int *pd)
{
	int		spaces;
	int		l;

	l = (s != NULL) ? ft_strlen(s) : 0;
	spaces = ft_spaces(all, s, l, c) > 0 ? ft_spaces(all, s, l, c) : 0;
	l = (all.precis > l) ? all.precis - l : 0;
	if (all.hash == 1 && (c == 'x' || c == 'X') && all.zero != 0)
	{
		(c == 'X') ? write(1, "0X", 2) : write(1, "0x", 2);
		spaces -= 2;
		(*pd) += 2;
	}
	if (all.znak != 'n' && all.zero != 0 && ++(*pd))
		write(1, &all.znak, 1);
	while (spaces > 0 && all.left == 0 && ++(*pd) && spaces--)
		(all.zero == 0) ? write(1, " ", 1) : write(1, "0", 1);
	(all.type == 'p' && all.zero == 0 && (*pd += 2)) ? write(1, "0x", 2) : 0;
	(c == 'o' && all.hash == 1 && all.zero == 0 && ++(*pd) && --l) ? write(1, "0", 1) : 0;
	if (all.znak != 'n' && all.zero == 0 && ++(*pd))
		write(1, &all.znak, 1);
	while (l-- > 0 && ++(*pd))
		write(1, "0", 1);
	*pd < 0 ? *pd += 2 : 0;
	if (s != NULL && !(*s == '0' && all.precis == 0) && !(*s == '0'
		&& c == 'o' && all.hash == 1) && ((*pd) += ft_strlen(s)))
		ft_putstr(s);
	while (spaces-- && all.left == 1 && ++(*pd))
		(all.zero == 0) ? write(1, " ", 1) : write(1, "0", 1);
}

void		ft_pstr(char *str, t_printf all, int *pd, char c)
{
	int		l;
	int		i;

	if (!str)
		str = ft_strjoin(str, "(null)");
	l = (*str == '\0' && c == 'c') ? 1 : ft_strlen(str);
	if (l > all.precis && (all.precis != -1 && !(*str == '\0' && c == 'c')))
		l = all.precis;
	i = (all.w > l && all.left != 1) ? (all.w - l) : 0;
	while (i > 0 && i-- && ++(*pd))
		(all.zero == 0) ? write(1, " ", 1) : write(1, "0", 1);
	(*str == '\0' && c == 'c' && ++(*pd)) ? write(1, "\0", 1) : 0;
	if (*str)
		while (i < l && ++(*pd))
			ft_putchar(str[i++]);
	i = (all.w > l && all.left == 1) ? (all.w - l) : 0;
	while (i--)
		(all.zero == 0 && ++(*pd)) ? write(1, " ", 1) : 0;
}
