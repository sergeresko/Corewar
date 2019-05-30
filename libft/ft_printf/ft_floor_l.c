/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_floor_l.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syeresko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 18:53:03 by syeresko          #+#    #+#             */
/*   Updated: 2018/12/03 20:54:16 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	returns the integral part of a non-negative argument
*/

long double	ft_floor_l(long double num)
{
	t_long_double	u;
	unsigned		e;

	u.f = num;
	e = u.i.e << 1 >> 1;
	if (e < 0x3fff)
		return (0.);
	e -= 0x3fff;
	if (e < 63)
	{
		u.i.m >>= 63 - e;
		u.i.m <<= 63 - e;
	}
	return (u.f);
}
