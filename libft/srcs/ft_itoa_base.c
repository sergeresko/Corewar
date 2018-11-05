/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 08:32:22 by vlvereta          #+#    #+#             */
/*   Updated: 2018/01/22 08:32:48 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*write_array(unsigned long long number, int base, int size, int sign)
{
	int		temp;
	char	*array;

	if (!(array = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	array[size] = '\0';
	if (sign)
		array[0] = '-';
	if (!number)
		array[--size] = '0';
	while (number)
	{
		temp = number % base;
		array[--size] = (temp > 9) ? temp + 55 : temp + '0';
		number /= base;
	}
	return (array);
}

char	*ft_itoa_base(long long value, int base)
{
	int					sign;
	int					size;
	unsigned long long	number;

	sign = (value < 0 ? 1 : 0);
	size = (value < 0 || !value ? 1 : 0);
	number = (value < 0 && base == 10 ? -value : value);
	while (value)
	{
		value /= base;
		size++;
	}
	return (write_array(number, base, size, sign));
}
