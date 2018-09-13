/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 04:05:56 by saxiao            #+#    #+#             */
/*   Updated: 2018/09/13 16:20:48 by acauchy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdint.h>
# include <wchar.h>
# define NB_CON	16

typedef enum	e_cast
{
	none = 1,
	hh,
	h,
	l,
	ll,
	j,
	z,
}				t_cast;

typedef	struct	s_data
{
	char		*ori;
	char		flags[10];
	int			width;
	int			precison;
	int			no_pre;
	int			len;
	int			blank;
	t_cast		cast;
}				t_data;

typedef	struct	s_mark
{
	int			i;
	int			j;
	int			nbr;
	int			per;
}				t_mark;

typedef struct	s_fu
{
	char		c;
	void		(*func)(va_list args, t_data * data, char *foamat, int size);
}				t_fu;

void			con_d(va_list args, t_data *data, char *foamat, int size);
void			con_b(va_list args, t_data *data, char *foamat, int size);
void			con_bigd(va_list args, t_data *data, char *foamat, int size);
void			con_i(va_list args, t_data *data, char *foamat, int size);
void			con_c(va_list args, t_data *data, char *foamat, int size);
void			con_bigc(va_list args, t_data *data, char *foamat, int size);
void			con_s(va_list args, t_data *data, char *foamat, int size);
void			con_bigs(va_list args, t_data *data, char *foamat, int size);
void			con_o(va_list args, t_data *data, char *foamat, int size);
void			con_bigo(va_list args, t_data *data, char *foamat, int size);
void			con_u(va_list args, t_data *data, char *foamat, int size);
void			con_bigu(va_list args, t_data *data, char *foamat, int size);
void			con_p(va_list args, t_data *data, char *foamat, int size);
void			con_per(va_list args, t_data *data, char *foamat, int size);
void			con_x(va_list args, t_data *data, char *foamat, int size);
void			con_bigx(va_list args, t_data *data, char *foamat, int size);
void			set_flags(va_list args, t_data *data, char *format, int size);
void			set_print_oxu_hash(t_data *data, char *pre_fix);
void			set_print_d(t_data *data);
void			put_zero_d(t_data *data);
void			go_right_oux(t_data *data, char *pre_fix);
void			put_zero_oux(t_data *data);
void			ini_set(t_fu *set, t_mark *m);
char			*ft_itoa_max(intmax_t n);
char			*ft_itoa_unmax(uintmax_t n);
char			*ft_itoa_short(short n);
char			*ft_itoa_signchar(char n);
char			*ft_convert_base(char *nbr, char *base_from, char *base_to);
char			*itoa_base(uintmax_t nb, int from, int to);
char			*itoa_hex(uintmax_t nb, char x);
int				max_2(int x, int y);
int				max_3(int x, int y, int z);
int				nb_digit(char *str);
int				is_f(char c);
uintmax_t		nb_dg_inbase(uintmax_t n, unsigned int base_to);
void			ft_putnwstr(wchar_t *s, int nbr);
void			ft_putnchar(char c, int nbr);
void			add_hash_p(t_data *data);
char			*ft_strnchr(const char *s, int c, int size);
int				ft_strnchr_double(const char *s, int c, int size);
void			ft_putwchar(wchar_t we);
void			ft_putnwchar(wchar_t *we, int nbr);
size_t			ft_wstrlen(wchar_t *we);
void			set_cast(t_data *data, char *format, int size);
int				ft_printf(const char *restrict format, ...);

#endif
