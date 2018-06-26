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
	char		type;
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

/*
**	ft_format_p.c
*/

void		ft_format_p(va_list ap, t_printf *all, int *pd);
char		*ft_modific_2(t_printf *all, char *str);
char		*ft_modific_1(t_printf *all, char *str);
void		ft_modific(t_printf *all, char *str);
int			som(char **str, t_printf *all, int *pd);

/*
**	ft_format_percent.c
*/

int			n_bits(unsigned int num, t_printf *all);
void		ft_prunic(unsigned int num, int *pd, int size);
void		ft_format_percent(t_printf *all, int *pd);
void		ft_unicode(t_printf all, va_list ap, int *pd);

/*
**	ft_format_s.c
*/

void		ft_one_bit(unsigned int num);
void		ft_two_bit(unsigned int num);
void		ft_three_bit(unsigned int num);
char		*ft_format_c(t_printf *all, va_list ap, int *pd, char c);

/*
**	ft_format.c
*/

char		*ft_format(va_list ap, t_printf *all, int *pd, char c);
void		ft_format_uu(va_list ap, t_printf *all, int *pd);
void		ft_format_xx(va_list ap, t_printf *all, int *pd, char c);
void		ft_format_d(va_list ap, t_printf *all, int *pd);
void		ft_format_dd(va_list ap, t_printf *all, int *pd);

/*
**	ft_itoa_base.c
*/

char		*ft_itoa(long long int n, t_printf *all);
char		convert_letter(int a);
char		*ft_itoa_base(unsigned long long int n, int base, t_printf *all);

/*
**	ft_out.c
*/

int			ft_spaces(t_printf all, char *s, int l, char c);
void		ft_prnum(char *s, t_printf all, char c, int *pd);
void		ft_pstr(char *str, t_printf all, int *pd, char c);

/*
**	ft_printf.c
*/

void		ft_numb(t_printf *all, va_list ap, int *pd);
void		ft_chr(t_printf *all, va_list ap, int *pd);
t_printf	*init_printf(t_printf *all);
char		*ft_check(t_printf *all, char *format, int *pd, va_list ap);
int     	ft_printf(char *format, ...);

/*
**	ft_read.c
*/

void		ft_flag(t_printf *all, char c);
char		is_changeable(char *c);
void		parse_conv(t_printf *all, char *format);
char		*ft_precision(t_printf *all, char *format);
void		ft_type(t_printf *all, va_list ap, char format, int *pd);

#endif
