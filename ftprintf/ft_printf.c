#include "ft_printf.h"

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

char		*ft_precision(t_printf *all, char *format)
{
	++format;
	all->precis = ft_atoi(format);
	while (ft_isdigit((int)*format) && *format != '\0')
		format++;
	all->h = 1;
	return (format);
}

void		parse_conv(t_printf *all, char *format)
{
	if (ft_strchr(TYPE, *format))
	{
		if (*format == 'i')
			*format = 'd';
		all->format[0] = *format;
	}
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

int		ft_spaces(t_printf all, char *s, int l, char c)
{
	int spaces;

	spaces = 0;
	spaces = (all.precis > l) ? all.precis : l;
	spaces = (all.znak != 'n') ? spaces + 1 : spaces;
	spaces = (*s == '0' && all.precis == 0) ? 0 : spaces;
	spaces = (all.w > spaces) ? all.w - spaces : 0;
	spaces = (c == 'x' && all.hash == 1 && all.zero == 0 && (*s != '0' \
		|| c == 'p')) ? spaces - 2 : spaces;
	spaces = (c == 'o' && all.hash == 1) ? spaces - 1 : spaces;
	return (spaces);
}

void	ft_prnum(char *s, t_printf all, char c, int *pd)
{
	int		spaces;
	int		l;

	l = (s != NULL) ? ft_strlen(s) : 0;
	spaces = ft_spaces(all, s, l, c);
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

void		ft_numb(t_printf *all, va_list ap, int *pd)
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

void		ft_chr(t_printf *all, va_list ap, int *pd)
{
	if ((all->format)[0] == 's' && all->l_m != 3)
		ft_pstr(va_arg(ap, char *), *all, pd, 's');
	else if ((all->format)[0] == 'S' || ((all->format)[0] == 's' && all->l_m == 3))
		ft_unicode(*all, ap, pd);
	else if ((all->format)[0] == 'c' && all->l_m != 3)
		ft_format_c(all, ap, pd, (all->format)[0]);
	else if ((all->format)[0] == 'C' || ((all->format)[0] == 'c' && all->l_m == 3))
		ft_format_c(all, ap, pd, (all->format)[0]);
}

void		ft_type(t_printf *all, va_list ap, char format, int *pd)
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

t_printf	*init_printf(t_printf *all)
{
	if ((all = (t_printf *)malloc(sizeof(t_printf))) == NULL)
		exit(1);
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

char	*ft_check(t_printf *all, char *format, int *pd, va_list ap)
{
	int		i;

	i = 0;
	all = init_printf(all);
	while (*format != '\0')
	{
		if (is_changeable(format) == '0')
			return (format);
		else if (is_changeable(format) == 'f')
			ft_flag(all, (*format++));
		else if (is_changeable(format) == 'w')
		{
			all->w = ft_atoi(format);
			while (ft_isdigit(*format))
				format++;
			continue;
		}
		else if (is_changeable(format) == 'm')
		{
			while (*format && ft_strchr(SPEC, *format))
			{
				(all->format_spec)[i++] = *format;
				format++;
			}
		}
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

int     ft_printf(char *format, ...)
{
	va_list		ap;
	int			pd;
	char		*ptr;
	t_printf    *all;

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