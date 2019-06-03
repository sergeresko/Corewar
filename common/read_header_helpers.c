/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 17:03:08 by vlvereta          #+#    #+#             */
/*   Updated: 2019/05/28 17:34:57 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

unsigned		parse_int(void const *buf)
{
	int			i;
	int			size;
	unsigned	result;

	i = 0;
	size = 4;
	result = 0;
	while (size)
	{
		result += ((unsigned char *)buf)[--size] << i;
		i += 8;
	}
	return (result);
}

void			is_no_null_error(char *str, int i)
{
	if (str[i])
	{
		ft_printf("No null at %d\n", i);
		exit(-1);
	}
}
