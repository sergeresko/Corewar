/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 20:50:03 by vlvereta          #+#    #+#             */
/*   Updated: 2019/06/03 12:30:05 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		includes(const char *str, char c)
{
	if (!c || !str || !(*str))
		return (FALSE);
	while (*str)
	{
		if (*str == c)
			return (TRUE);
		str++;
	}
	return (FALSE);
}

char	*convert_int_to_hex(int num)
{
	int		num_len;
	int		res_len;
	char	*result;
	char	*number;

	result = NULL;
	if ((number = ft_itoa_base(num, 16)))
	{
		num_len = ft_strlen(number);
		if ((result = ft_strnew(9)))
		{
			res_len = 8;
			result = ft_memset((void *)result, '0', res_len);
			while (num_len > 0)
				result[--res_len] = ft_tolower(number[--num_len]);
		}
		ft_strdel(&number);
	}
	return (result);
}
