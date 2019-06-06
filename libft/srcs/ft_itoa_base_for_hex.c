/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_for_hex.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozalisky <ozalisky@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 12:28:38 by ozalisky          #+#    #+#             */
/*   Updated: 2019/06/06 12:34:17 by ozalisky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*write_array_hex(unsigned long long number, int base, int size,
		int sign)
{
	int		temp;
	char	*array;

	if (!(array = (char *)malloc(sizeof(char) * (3))))
		return (NULL);
	array[2] = '\0';
	if (sign)
		array[0] = '-';
	if (!number)
		array[--size] = '0';
	if (size < 2)
	{
		array[0] = '0';
		temp = number % base;
		array[1] = (temp > 9) ? temp + 55 : temp + '0';
	}
	else
		while (number)
		{
			temp = number % base;
			array[--size] = (temp > 9) ? temp + 55 : temp + '0';
			number /= base;
		}
	return (array);
}

char	*ft_itoa_base_hex_convertions(long long value, int base)
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
	return (write_array_hex(number, base, size, sign));
}
