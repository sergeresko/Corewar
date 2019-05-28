/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_converters.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syeresko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 21:13:49 by syeresko          #+#    #+#             */
/*   Updated: 2018/12/09 19:43:11 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <inttypes.h>
#include <wchar.h>

char	*pf_itoa(const t_fmt *f, uintmax_t num)
{
	unsigned	base;
	char		letter_a;
	char		*s;
	char		digit;

	base = 10;
	if (ft_strchr("xXp", f->conv))
		base = 16;
	else if (f->conv == 'o')
		base = 8;
	else if (ft_strchr("bB", f->conv))
		base = 2;
	letter_a = (f->conv == 'X') ? 'A' : 'a';
	s = PF_BUF_END;
	*s = '\0';
	while (num)
	{
		digit = num % base;
		*(--s) = digit + ((digit < 10) ? '0' : (letter_a - 10));
		num /= base;
	}
	return (s);
}

char	*pf_wctomb(wchar_t wc)
{
	char	*s;
	char	mask;

	s = PF_BUF_END;
	*s = '\0';
	if (wc < 0200)
		*(--s) = wc;
	else
	{
		mask = 0200;
		while (wc > 0077)
		{
			*(--s) = 0200 | (wc & 0077);
			wc >>= 6;
			mask = 0200 | (mask >> 1);
		}
		*(--s) = mask | wc;
	}
	return (s);
}

/*
**	the argument need not be a whole number
**	Puts a '0' if the whole part is equal to zero.
*/

char	*pf_entier_to_string(long double ent)
{
	char			*s;
	long double		unit;
	long double		div;

	s = PF_BUF_START;
	unit = 1.;
	while (ent / unit >= 10.)
		unit *= 10.;
	while (unit >= 1.)
	{
		div = ft_floor_l(ent / unit);
		*(s++) = '0' + (char)div;
		ent -= div * unit;
		unit /= 10.;
	}
	if (s == PF_BUF_START)
		*(s++) = '0';
	*s = '\0';
	return (PF_BUF_START);
}

/*
**	the argument must be less than 1.
*/

char	*pf_frac_to_string(long double frac, int prec)
{
	char	*s;

	s = PF_BUF_START;
	while (prec--)
	{
		frac *= 10.;
		*(s++) = '0' + (char)frac;
		frac -= ft_floor_l(frac);
	}
	*s = '\0';
	return (PF_BUF_START);
}
