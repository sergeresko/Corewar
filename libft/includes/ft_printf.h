/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 14:36:59 by vlvereta          #+#    #+#             */
/*   Updated: 2018/02/05 16:09:15 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

# define AMOUNT 16

typedef struct		s_flags
{
	int				width;
	int				prec;
	int				left;
	int				sign;
	int				space;
	int				hash;
	int				zero;
	int				l;
	int				ll;
	int				h;
	int				hh;
	int				j;
	int				z;
	int				high_l;
}					t_flags;

typedef int			(*t_handler)(void *);

typedef struct		s_info
{
	va_list			ap;
	char			*types;
	t_handler		type_handlers[AMOUNT];
	t_flags			*cur_flags;
	char			*output;
	int				outlen;
	int				error;
}					t_info;

int					ft_printf(const char *format, ...);
int					start_initialization(t_info *p);
void				type_handlers_init(t_handler type_handlers[]);
void				flags_to_null(t_flags *flags);
int					read_flags(char **format, t_info *p);
int					read_width(char **format, t_info *p);
void				read_precision(char **format, t_info *p);
int					read_size(char **format, t_info *p);
int					clean_return(void *ptr1, void *ptr2, void *ptr3, int ret);
int					check_flags_for_di(t_info *p, char *s);
char				*precision_for_di(t_flags *flags, char *s, char sing);
char				*width_for_di(t_flags *flags, char *s, char sign);
void				check_flags_for_oux(t_flags *flags, char **str, char type);
char				*precision_for_oux(t_flags *flags, char *str);
char				*width_for_oux(t_flags *flags, char *str, int extra_len);
char				*llu_base(unsigned long long value, int base);
unsigned long long	to_unsigned(t_info *p);
void				width_for_char(t_info *p, char c);
void				char_to_output(t_info *p, char c);
int					wchar_encoder(unsigned int c, char **unichar);
int					add_unichar(char **res, int len, char *unichar, int ulen);
void				width_for_unichar(t_info *p, char *unichar, int len);
int					read_unistring(int precision, wchar_t *s, char **result);
int					width_for_unistring(t_flags *flags, char **result, int len);
int					string_processing(t_info *p, char *s, int len);
int					width_for_string(t_flags *flags, char **result, int len);
void				string_to_output(t_info *p, char *s, int len);

int					type_low_c(void *info);
int					type_high_c(void *info);
int					type_low_di(void *info);
int					type_high_d(void *info);
int					type_n(void *info);
int					type_low_o(void *info);
int					type_high_o(void *info);
int					type_p(void *info);
int					type_low_s(void *info);
int					type_high_s(void *info);
int					type_low_u(void *info);
int					type_high_u(void *info);
int					type_low_x(void *info);
int					type_high_x(void *info);
int					percent_handling(void *info);

#endif
