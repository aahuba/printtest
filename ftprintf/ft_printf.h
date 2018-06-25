/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahuba <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 15:38:09 by ahuba             #+#    #+#             */
/*   Updated: 2018/02/05 15:38:12 by ahuba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

#include <stdarg.h>
#include "../libft/libft.h"
#include <stdio.h> /* delete printf */
#include <wchar.h>
#include <limits.h>

# define TYPE "sSpd%DioOuUxXcC"
# define SPEC "lhjz"
# define FLAG "#0 -+"

typedef struct	s_printf
{
	int			w;
	int			precis;
	int			h;
	int			l_m;
	char		*res; // result
	int			hash;
	int			zero;
	int			min;
	int			minus;
	int			space;
	int			left;
	int			spec;
	int			plus;
	char		znak;
	char		*format;
	char		*format_spec;
}				t_printf;

int		ft_printf(char *format, ...);
void	ft_pstr(char *str, t_printf all, int *pd, char c);
void	ft_modific(t_printf *all, char *str);
void	ft_prnum(char *s, t_printf all, char c, int *pd);
void	ft_putwchar(wchar_t chr, int *pd);
void	ft_format_ss(va_list ap, t_printf *all, int *pd);
void	ft_format_percent(t_printf *all, int *pd);
void	ft_format_xx(va_list ap, t_printf *all, int *pd, char c);
char	*ft_format(va_list ap, t_printf *all, int *pd, char c);
char	*ft_format_c(t_printf *all, va_list ap, int *pd, char c);
char	*ft_itoa_base(unsigned long long int n, int base, t_printf *all);
char	convert_letter(int a);
char	*ft_itoa(long long int n, t_printf *all);
void	ft_format_uu(va_list ap, t_printf *all, int *pd);
void	ft_format_p(va_list ap, t_printf *all, int *pd);
void	ft_format_dd(va_list ap, t_printf *all, int *pd);
void	ft_format_d(va_list ap, t_printf *all, int *pd);
void	ft_unicode(t_printf all, va_list ap, int *pd);

#endif
