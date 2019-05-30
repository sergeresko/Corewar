/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utf8_len.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syeresko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 19:38:57 by syeresko          #+#    #+#             */
/*   Updated: 2018/12/03 19:39:46 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <wchar.h>

int		ft_utf8_len(wchar_t wc)
{
	if (wc < 0x80)
		return (1);
	if (wc < 0x800)
		return (2);
	if (wc < 0x10000)
		return (3);
	return (4);
}
