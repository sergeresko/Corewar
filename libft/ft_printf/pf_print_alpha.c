/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_print_alpha.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syeresko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 12:41:52 by syeresko          #+#    #+#             */
/*   Updated: 2018/12/09 19:48:22 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>
#include <unistd.h>
#include <wchar.h>

static int	pf_print_character(const t_fmt *f, char c)
{
	if (!f->left)
		ft_putnchar((f->zero ? '0' : ' '), f->width - 1);
	ft_putchar(c);
	if (f->left)
		ft_putnchar(' ', f->width - 1);
	return (ft_max(1, f->width));
}

static int	pf_print_string(const t_fmt *f, const char *str)
{
	const char	null_msg[] = "(null)";
	int			n_characters;

	if (!str)
		str = null_msg;
	n_characters = ft_strlen(str);
	if (f->prec != PF_PREC_NONE && f->prec < n_characters)
		n_characters = f->prec;
	if (!f->left)
		ft_putnchar((f->zero) ? '0' : ' ', f->width - n_characters);
	write(1, str, n_characters);
	if (f->left)
		ft_putnchar(' ', f->width - n_characters);
	return (ft_max(f->width, n_characters));
}

static int	pf_print_wide_character(const t_fmt *f, wchar_t wc)
{
	char	*s;
	int		n_bytes;

	s = pf_wctomb(wc);
	n_bytes = ft_strlen(s);
	if (!f->left)
		ft_putnchar((f->zero) ? '0' : ' ', f->width - n_bytes);
	write(1, s, n_bytes);
	if (f->left)
		ft_putnchar(' ', f->width - n_bytes);
	return (ft_max(f->width, n_bytes));
}

static int	pf_print_wide_string(const t_fmt *f, const wchar_t *wstr)
{
	const wchar_t	null_msg[] = L"(null)";
	int				n_wchars;
	int				n_bytes;
	int				wlen;

	if (!wstr)
		wstr = null_msg;
	n_wchars = 0;
	n_bytes = 0;
	while (wstr[n_wchars])
	{
		wlen = ft_utf8_len(wstr[n_wchars]);
		if (f->prec != PF_PREC_NONE && n_bytes + wlen > f->prec)
			break ;
		n_bytes += wlen;
		++n_wchars;
	}
	if (!f->left)
		ft_putnchar((f->zero) ? '0' : ' ', f->width - n_bytes);
	while (n_wchars--)
		ft_putstr(pf_wctomb(*(wstr++)));
	if (f->left)
		ft_putnchar(' ', f->width - n_bytes);
	return (ft_max(f->width, n_bytes));
}

int			pf_print_alpha(const t_fmt *f, va_list ap)
{
	if (f->conv == 'c')
	{
		if (f->mod == MOD_L)
			return (pf_print_wide_character(f, (wchar_t)va_arg(ap, wint_t)));
		return (pf_print_character(f, (char)va_arg(ap, int)));
	}
	if (f->conv == 's')
	{
		if (f->mod == MOD_L)
			return (pf_print_wide_string(f, (wchar_t *)va_arg(ap, wint_t *)));
		return (pf_print_string(f, va_arg(ap, char *)));
	}
	return (pf_print_character(f, '%'));
}
