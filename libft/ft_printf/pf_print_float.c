/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_print_float.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syeresko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 13:06:36 by syeresko          #+#    #+#             */
/*   Updated: 2018/12/09 20:10:47 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long double	round_add(long double num, int prec)
{
	long double		frac;
	long double		unit;

	frac = num - ft_floor_l(num);
	unit = 1.;
	while (prec--)
	{
		unit *= 0.1;
		frac *= 10.;
		frac -= ft_floor_l(frac);
	}
	if (frac >= 0.5)
		num += unit * 0.5;
	return (num);
}

static char			get_sign(const t_fmt *f, long double num)
{
	if (num < 0.)
		return ('-');
	if (f->plus)
		return ('+');
	if (f->blank)
		return (' ');
	return ('\0');
}

static int			print_inf_or_nan(const t_fmt *f, long double num)
{
	t_long_double	u;
	char			sign;
	int				val_len;

	u.f = num;
	if (~u.i.e & 0x7fff)
		return (0);
	sign = (u.i.m << 1 >> 1) ? '\0' : get_sign(f, num);
	val_len = (sign != '\0') + 3;
	if (!f->left)
		ft_putnchar(' ', f->width - val_len);
	if (sign)
		ft_putchar(sign);
	ft_putstr((u.i.m << 1 >> 1) ? "nan" : "inf");
	if (f->left)
		ft_putnchar(' ', f->width - val_len);
	return (ft_max(f->width, val_len));
}

int					pf_print_float(const t_fmt *f, long double num)
{
	char	*s;
	char	sign;
	int		prec;
	int		val_len;

	if ((val_len = print_inf_or_nan(f, num)))
		return (val_len);
	sign = get_sign(f, num);
	prec = (f->prec == PF_PREC_NONE) ? 6 : f->prec;
	num = round_add((num < 0.) ? -num : num, prec);
	s = pf_entier_to_string(num);
	val_len = (sign != '\0') + ft_strlen(s) + (prec > 0 || f->alt) + prec;
	if (!f->left && !f->zero)
		ft_putnchar(' ', f->width - val_len);
	if (sign)
		ft_putchar(sign);
	if (!f->left && f->zero)
		ft_putnchar('0', f->width - val_len);
	ft_putstr(s);
	if (prec > 0 || f->alt)
		ft_putchar('.');
	ft_putstr(pf_frac_to_string(num - ft_floor_l(num), prec));
	if (f->left)
		ft_putnchar(' ', f->width - val_len);
	return (ft_max(f->width, val_len));
}
