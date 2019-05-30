/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syeresko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 18:59:57 by syeresko          #+#    #+#             */
/*   Updated: 2018/11/22 20:43:01 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void	ft_putnchar(char c, int times)
{
	char	buf[16];

	ft_memset(buf, c, 16);
	while (times > 16)
	{
		write(STDOUT_FILENO, buf, 16);
		times -= 16;
	}
	if (times > 0)
		write(STDOUT_FILENO, buf, times);
}
