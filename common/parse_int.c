/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 17:03:08 by vlvereta          #+#    #+#             */
/*   Updated: 2019/06/03 23:44:35 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

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
