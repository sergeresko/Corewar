/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 17:03:08 by vlvereta          #+#    #+#             */
/*   Updated: 2019/05/18 17:07:54 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

unsigned int	parse_int(void *buf)
{
	int				i;
	int				size;
	unsigned int	result;

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
