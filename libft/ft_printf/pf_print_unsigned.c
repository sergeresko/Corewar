/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_print_unsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syeresko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 17:05:38 by syeresko          #+#    #+#             */
/*   Updated: 2018/12/09 20:08:51 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <inttypes.h>
#include <unistd.h>

static int	pf_print_decimal(const t_fmt *f, uintmax_t num)
{
	char	*s;
	int		n_prefix;
	int		n_zeroes;
	int		n_digits;
	int		val_len;

	s = pf_itoa(f, num);
	n_prefix = 0;
	n_digits = ft_strlen(s);
	n_zeroes = pf_count_zeroes(f, n_prefix, n_digits);
	val_len = n_prefix + n_zeroes + n_digits;
	if (!f->left && !(f->zero && f->prec == PF_PREC_NONE))
		ft_putnchar(' ', f->width - val_len);
	ft_putnchar('0', n_zeroes);
	write(1, s, n_digits);
	if (f->left)
		ft_putnchar(' ', f->width - val_len);
	return (ft_max(f->width, val_len));
}

static int	pf_print_hexadecimal(const t_fmt *f, uintmax_t num)
{
	char	*s;
	int		n_prefix;
	int		n_zeroes;
	int		n_digits;
	int		val_len;

	s = pf_itoa(f, num);
	n_prefix = (f->alt && num) ? 2 : 0;
	n_digits = ft_strlen(s);
	n_zeroes = pf_count_zeroes(f, n_prefix, n_digits);
	val_len = n_prefix + n_zeroes + n_digits;
	if (!f->left && !(f->zero && f->prec == PF_PREC_NONE))
		ft_putnchar(' ', f->width - val_len);
	if (n_prefix)
		ft_putstr(f->conv == 'X' ? "0X" : "0x");
	ft_putnchar('0', n_zeroes);
	write(1, s, n_digits);
	if (f->left)
		ft_putnchar(' ', f->width - val_len);
	return (ft_max(f->width, val_len));
}

static int	pf_print_octal(const t_fmt *f, uintmax_t num)
{
	char	*s;
	int		n_prefix;
	int		n_zeroes;
	int		n_digits;
	int		val_len;

	s = pf_itoa(f, num);
	n_digits = ft_strlen(s);
	n_prefix = (f->alt && n_digits >= f->prec) ? 1 : 0;
	n_zeroes = pf_count_zeroes(f, n_prefix, n_digits);
	if (n_zeroes == 1 && n_prefix && n_digits == 0)
		n_zeroes = 0;
	val_len = n_prefix + n_zeroes + n_digits;
	if (!f->left && !(f->zero && f->prec == PF_PREC_NONE))
		ft_putnchar(' ', f->width - val_len);
	if (n_prefix)
		ft_putchar('0');
	ft_putnchar('0', n_zeroes);
	write(1, s, n_digits);
	if (f->left)
		ft_putnchar(' ', f->width - val_len);
	return (ft_max(f->width, val_len));
}

static int	pf_print_binary(const t_fmt *f, uintmax_t num)
{
	char	*s;
	int		n_prefix;
	int		n_zeroes;
	int		n_digits;
	int		val_len;

	s = pf_itoa(f, num);
	n_prefix = (f->alt && num) ? 2 : 0;
	n_digits = ft_strlen(s);
	n_zeroes = pf_count_zeroes(f, n_prefix, n_digits);
	val_len = n_prefix + n_zeroes + n_digits;
	if (!f->left && !(f->zero && f->prec == PF_PREC_NONE))
		ft_putnchar(' ', f->width - val_len);
	if (n_prefix)
		ft_putstr(f->conv == 'B' ? "0B" : "0b");
	ft_putnchar('0', n_zeroes);
	write(1, s, n_digits);
	if (f->left)
		ft_putnchar(' ', f->width - val_len);
	return (ft_max(f->width, val_len));
}

int			pf_print_unsigned(const t_fmt *f, uintmax_t num)
{
	if (f->conv == 'u')
		return (pf_print_decimal(f, num));
	if (f->conv == 'o')
		return (pf_print_octal(f, num));
	if (ft_strchr("bB", f->conv))
		return (pf_print_binary(f, num));
	return (pf_print_hexadecimal(f, num));
}
