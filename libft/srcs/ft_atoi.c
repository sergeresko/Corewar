/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 12:41:31 by vlvereta          #+#    #+#             */
/*   Updated: 2017/10/26 12:49:05 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_whitespace(int c)
{
	if (c == ' ' || c == '\n' || c == '\t' ||
			c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

int			ft_atoi(const char *str)
{
	int						sign;
	unsigned long int		result;

	sign = 1;
	result = 0;
	while (ft_is_whitespace((unsigned char)*str))
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str && ft_isdigit(*str))
	{
		if ((result > 922337203685477580 || (result == 922337203685477580 &&
			(*str - '0') > 7)) && sign == 1)
			return (-1);
		else if ((result > 922337203685477580 || (result == 922337203685477580
			&& (*str - '0') > 8)) && sign == -1)
			return (0);
		result = (result * 10) + (*str - '0');
		str++;
	}
	return ((int)(result * sign));
}
