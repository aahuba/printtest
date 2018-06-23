/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahuba <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 15:51:11 by ahuba             #+#    #+#             */
/*   Updated: 2018/01/03 23:41:23 by ahuba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>

# define SPACES(x) (x == ' ' || x == '\t' || x == '\n')
# define GNL_BUFF_SIZE 42

typedef	struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
	int				x[4];
	int				y[4];
}					t_list;

void				ft_bzero(void *s, size_t n);
void				ft_memdel(void **ap);
void				ft_free(char ***tab);
void				ft_freen(char ***tab, int n);
void				ft_strdel(char **as);
void				*ft_memalloc(size_t size);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				ft_putstr(char const *s);
void				ft_putchar(char c);
void				ft_putendl(char const *s);
char				**ft_strsplit(char const *s, char c);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strnew(size_t size);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strchr(const char *s, int c);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strdup(const char *s1);
char				*ft_strndup(const char *s1, size_t n);
char				*ft_strstr(const char *hastack, const char *needle);
size_t				ft_strlen(const char *s);
int					ft_get_next_line(const int fd, char **line);
int					ft_atoi(const char *str);
int					ft_countwords(char const *s, char c);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_isdigit(int c);
int					ft_toupper(int c);
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstadd(t_list **alst, t_list *new);
void				*ft_memset(void *dest, int c, size_t n);
void				ft_strupper(char *a);

# ifndef SPACES
#  define SPACES(x) (x == ' ' || x == '\n' || x == '\t')
# endif

#endif
