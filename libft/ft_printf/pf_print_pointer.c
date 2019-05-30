/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_print_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syeresko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 20:18:34 by syeresko          #+#    #+#             */
/*   Updated: 2018/12/09 20:08:13 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <inttypes.h>
#include <unistd.h>

int		pf_print_pointer(const t_fmt *f, void *ptr)
{
	char	*s;
	int		n_prefix;
	int		n_zeroes;
	int		n_digits;
	int		val_len;

	s = pf_itoa(f, (uintmax_t)ptr);
	n_prefix = 2;
	n_digits = ft_strlen(s);
	n_zeroes = pf_count_zeroes(f, n_prefix, n_digits);
	val_len = n_prefix + n_zeroes + n_digits;
	if (!f->left && !(f->zero && f->prec == PF_PREC_NONE))
		ft_putnchar(' ', f->width - val_len);
	write(1, "0x", 2);
	ft_putnchar('0', n_zeroes);
	write(1, s, n_digits);
	if (f->left)
		ft_putnchar(' ', f->width - val_len);
	return (ft_max(f->width, val_len));
}
