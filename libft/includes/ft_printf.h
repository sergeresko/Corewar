/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syeresko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 13:37:22 by syeresko          #+#    #+#             */
/*   Updated: 2019/06/01 15:12:49 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <unistd.h>
# include <inttypes.h>
# include <wchar.h>
# include <stdarg.h>

void			ft_putnchar(char c, int times);

int				ft_min(int a, int b);
int				ft_max(int a, int b);
int				ft_abs(int a);

/*
**	floating point functions
*/

typedef union	u_long_double
{
	long double	f;
	struct		s_i
	{
		uintmax_t		m;
		unsigned short	e;
	}			i;
}				t_long_double;

long double		ft_floor_l(long double num);

/*
**	unicode functions
*/

int				ft_utf8_len(wchar_t wc);

/*
**	parsing functions
*/

int				ft_parse_number(const char **a_str);

/*
**	ft_printf
*/

# define PF_FLAGS		"#0- +\'"
# define PF_MODIFIERS	"hljzL"
# define PF_CONVERSIONS	"cspdibBouxXf%"

typedef enum	e_modifier
{
	MOD_NONE = 0,
	MOD_HH,
	MOD_H,
	MOD_L,
	MOD_LL,
	MOD_J,
	MOD_Z,
	MOD_L_CAPITAL
}				t_modifier;

typedef struct	s_fmt
{
	int			width;
	int			prec;
	unsigned	alt: 1;
	unsigned	zero: 1;
	unsigned	left: 1;
	unsigned	blank: 1;
	unsigned	plus: 1;
	unsigned	group: 1;
	t_modifier	mod;
	char		conv;
}				t_fmt;

# define PF_PREC_NONE 	(-1)

# define PF_RESET		"\033[0m"
# define PF_BOLD		"\033[1m"
# define PF_RED			"\033[31m"
# define PF_GREEN		"\033[32m"
# define PF_YELLOW		"\033[33m"
# define PF_BLUE		"\033[34m"
# define PF_MAGENTA		"\033[35m"
# define PF_CYAN		"\033[36m"
# define PF_GREY		"\033[90m"

# define PF_BUF_SIZE 	1024

char			g_pf_buf[PF_BUF_SIZE + 1];

# define PF_BUF_START	g_pf_buf
# define PF_BUF_END		(g_pf_buf + PF_BUF_SIZE)

char			*pf_itoa(const t_fmt *f, uintmax_t num);
char			*pf_wctomb(wchar_t wc);
char			*pf_entier_to_string(long double ent);
char			*pf_frac_to_string(long double frac, int prec);

int				pf_count_zeroes(const t_fmt *f, int n_prefix, int n_digits);

int				pf_print_alpha(const t_fmt *f, va_list ap);
int				pf_print_signed(const t_fmt *f, intmax_t num);
int				pf_print_unsigned(const t_fmt *f, uintmax_t num);
int				pf_print_pointer(const t_fmt *f, void *ptr);
int				pf_print_float(const t_fmt *f, long double num);

void			pf_parse_format(t_fmt *a_fmt, const char **a_str, va_list ap);
int				ft_printf(const char *format, ...);

#endif
