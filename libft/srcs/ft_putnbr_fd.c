/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 16:36:09 by vlvereta          #+#    #+#             */
/*   Updated: 2017/10/26 16:38:36 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int res;

	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		res = n * -1;
	}
	else
		res = n;
	if (res <= 9)
		ft_putchar_fd(res + '0', fd);
	else
	{
		ft_putnbr_fd(res / 10, fd);
		ft_putnbr_fd(res % 10, fd);
	}
}
