/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 20:50:03 by vlvereta          #+#    #+#             */
/*   Updated: 2018/11/08 20:50:32 by vlvereta         ###   ########.fr       */
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

char	*byte_in_bits(char c)
{
	int		i;
	char	*result;

	if ((result = ft_strnew(sizeof(char) * 8)))
	{
		i = 8;
		while (i > 0)
		{
			result[--i] = c % 2 + '0';
			c /= 2;
		}
		return (result);
	}
	return (NULL);
}
