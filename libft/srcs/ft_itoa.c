/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 10:06:58 by vlvereta          #+#    #+#             */
/*   Updated: 2017/10/30 10:25:30 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*write_array(unsigned int number, int size, int sign)
{
	char	*result;

	result = (char *)malloc(sizeof(char) * (size + 1));
	if (result)
	{
		result[size] = 0;
		if (!number)
			result[0] = '0';
		else
		{
			if (sign)
				result[0] = '-';
			while (number)
			{
				result[--size] = '0' + (number % 10);
				number /= 10;
			}
		}
	}
	return (result);
}

char		*ft_itoa(int n)
{
	int				size;
	int				sign;
	unsigned int	number;

	size = 0;
	sign = 0;
	if (!n)
		size++;
	if (n < 0)
	{
		size++;
		sign = 1;
		number = n * -1;
	}
	else
		number = n;
	while (n)
	{
		size++;
		n /= 10;
	}
	return (write_array(number, size, sign));
}
