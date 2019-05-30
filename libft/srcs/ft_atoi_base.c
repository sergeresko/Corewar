/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaliskyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 16:33:04 by zaliskyi          #+#    #+#             */
/*   Updated: 2019/05/28 20:35:49 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_power(int nb, int power)
{
	if (power == 0)
		return (1);
	else if (power < 0)
		return (0);
	return (nb * ft_power(nb, power - 1));
}

static int	ft_convert_number(char c, int base)
{
	int		result;

	if (c >= '0' && c <= '9')
		result = c - 48;
	else if (c >= 'a' && c <= 'z')
		result = c - 97 + 10;
	else if (c >= 'A' && c <= 'Z')
		result = c - 65 + 10;
	else
		result = -1;
	if (result < base && result != -1)
		return (result);
	else
		return (-1);
}

static int	ft_numlen(char *str, int base)
{
	int		length;

	length = 0;
	while (str[length])
	{
		if (ft_convert_number(str[length], base) == -1)
			break ;
		++length;
	}
	return (length);
}

int			ft_atoi_base(char *num, int base)
{
	int		result;
	int		length;

	if (base == 10)
		return (ft_atoi(num));
	while (*num == ' ' || *num == '\t' || *num == '\n'
			|| *num == '\v' || *num == '\r' || *num == '\f')
		++num;
	result = 0;
	length = ft_numlen(num, base) - 1;
	while (*num && length >= 0 && ft_convert_number(*num, base) != -1)
	{
		result += ft_convert_number(*num, base) * ft_power(base, length);
		++num;
		--length;
	}
	return (result);
}
