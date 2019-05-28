/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_print_signed.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syeresko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 16:51:02 by syeresko          #+#    #+#             */
/*   Updated: 2018/12/09 20:08:26 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <inttypes.h>
#include <unistd.h>

static char	get_sign(const t_fmt *f, intmax_t num)
{
	if (num < 0)
		return ('-');
	if (f->plus)
		return ('+');
	if (f->blank)
		return (' ');
	return ('\0');
}

int			pf_print_signed(const t_fmt *f, intmax_t num)
{
	char	*s;
	char	sign;
	int		n_zeroes;
	int		n_digits;
	int		val_len;

	sign = get_sign(f, num);
	s = pf_itoa(f, num < 0 ? -num : num);
	n_digits = ft_strlen(s);
	n_zeroes = pf_count_zeroes(f, (sign != '\0'), n_digits);
	val_len = (sign != '\0') + n_zeroes + n_digits;
	if (!f->left && !(f->zero && f->prec == PF_PREC_NONE))
		ft_putnchar(' ', f->width - val_len);
	if (sign)
		ft_putchar(sign);
	ft_putnchar('0', n_zeroes);
	write(1, s, n_digits);
	if (f->left)
		ft_putnchar(' ', f->width - val_len);
	return (ft_max(f->width, val_len));
}
