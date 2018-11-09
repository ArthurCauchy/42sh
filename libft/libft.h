/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acauchy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 10:12:28 by acauchy           #+#    #+#             */
/*   Updated: 2018/11/09 17:03:55 by ccharrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <stdarg.h>

# define GNL_BUFF_SIZE 15

typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

typedef struct	s_arg
{
	int		alignleft;
	int		width;
	void	(*print_fct)(int, struct s_arg*, void*);
}				t_arg;

typedef struct	s_stock_list
{
	int					fd;
	char				*stock;
	struct s_stock_list	*next;
}				t_stocklist;

void			*ft_memset(void *b, int c, size_t len);
void			ft_bzero(void	*s, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
size_t			ft_strlen(const char *s);
char			*ft_strdup(const char *s1);
char			*ft_strndup(const char *s1, size_t n);
char			*ft_strdup_free(char *s1);
char			*ft_strcpy(char *dst, const char *src);
char			*ft_strncpy(char *dst, const char *src, size_t len);
char			*ft_strcat(char *s1, const char *s2);
char			*ft_strncat(char *s1, const char *s2, size_t n);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
char			*ft_strchr(const char *s, int c);
int				ft_strchr_index(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
char			*ft_strstr(const char *haystack, const char *needle);
char			*ft_strnstr(const char *haystack,
							const char *needle, size_t len);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_atoi(const char *str);
int				ft_islower(int c);
int				ft_isupper(int c);
int				ft_isalpha(int c);
int				ft_isspace(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);

void			*ft_memalloc(size_t size);
void			ft_memdel(void **ap);
char			*ft_strnew(size_t size);
void			ft_strdel(char **as);
void			ft_strclr(char *s);
void			ft_striter(char *s, void (*f)(char *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strmap(char const *s, char (*f)(char));
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int				ft_strequ(char const *s1, char const *s2);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
char			*ft_charjoin(char *s1, char s2);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strjoinl(char *s1, char *s2);
char			*ft_strjoin_free(char *s1, char *s2);
char			*ft_strtrim(char const *s);
char			**ft_strsplit(char const *s, char c);
char			**ft_split(char *str, char *charset);
char			*ft_strfill_right(char const *s, size_t size, char fill_char);
char			*ft_itoa(int n);
char			*ft_lltoa(long long n);
void			ft_putchar(char c);
void			ft_putstr(char const *str);
void			ft_putnstr(char const *str, size_t n);
void			ft_putendl(char const *str);
void			ft_putnbr(int n);
void			ft_puthex(unsigned char c);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char const *str, int fd);
void			ft_putendl_fd(char const *str, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_puthex_fd(unsigned char c, int fd);

t_list			*ft_lstnew(void const *content, size_t content_size);
void			ft_lstdelone(t_list **alst, void (*del)(void*, size_t));
void			ft_lstdel(t_list **alst, void (*del)(void*, size_t));
void			ft_lstadd(t_list **alst, t_list *new);
t_list			*ft_lstpushback(t_list **alst, t_list *new);
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));

int				ft_swap(void **ptr1, void **ptr2, size_t size1, size_t size2);
int				ft_sqrt(int nb);
int				ft_nbrlen(long long nb);
void			ft_fminiprint(int fd, char *str, ...);
void			ft_multifree(int nbargs, ...);
int				ft_count(char *str, char c);
int				ft_str_is_numeric(char *str);
int				get_next_line(const int fd, char **line);
int				ft_isprintable(int c);

/*
** The following functions MUST NOT be used.
*/

void			print_errortype(int fd, t_arg *arg, void *realarg);
void			print_integer(int fd, t_arg *arg, void *realarg);
void			print_string(int fd, t_arg *arg, void *realarg);

#endif
