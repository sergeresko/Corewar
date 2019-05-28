/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_count_zeroes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syeresko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:56:30 by syeresko          #+#    #+#             */
/*   Updated: 2018/12/09 19:42:22 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		pf_count_zeroes(const t_fmt *f, int n_prefix, int n_digits)
{
	if (f->prec >= 0)
		return (ft_max(0, f->prec - n_digits));
	if (f->zero && !f->left)
		return (ft_max((n_digits == 0), f->width - n_prefix - n_digits));
	return (n_digits == 0);
}
