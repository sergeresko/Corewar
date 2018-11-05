/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 16:32:58 by vlvereta          #+#    #+#             */
/*   Updated: 2017/10/26 16:35:52 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	unsigned int res;

	if (n < 0)
	{
		ft_putchar('-');
		res = n * -1;
	}
	else
		res = n;
	if (res <= 9)
		ft_putchar(res + '0');
	else
	{
		ft_putnbr(res / 10);
		ft_putnbr(res % 10);
	}
}
