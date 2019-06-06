/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_converters.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 20:50:03 by vlvereta          #+#    #+#             */
/*   Updated: 2019/05/26 18:11:37 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	*byte_in_hex(unsigned char c)
{
	int		i;
	int		j;
	char	*hex;
	char	*result;

	if ((result = ft_strnew(sizeof(char) * 2)))
	{
		if ((hex = ft_itoa_base(c, 16)))
		{
			ft_memset(result, '0', 2);
			i = (int)ft_strlen(result);
			j = (int)ft_strlen(hex);
			while (j > 0)
				result[--i] = (char)ft_tolower(hex[--j]);
			ft_strdel(&hex);
			return (result);
		}
	}
	perror("Byte to hexadecimal converting.");
	exit(-1);
}

char	*short_in_hex(unsigned short s)
{
	int		i;
	int		j;
	char	*hex;
	char	*result;

	if ((result = ft_strnew(sizeof(char) * 4)))
	{
		if ((hex = ft_itoa_base(s, 16)))
		{
			ft_memset(result, '0', 4);
			i = (int)ft_strlen(result);
			j = (int)ft_strlen(hex);
			while (j > 0)
				result[--i] = (char)ft_tolower(hex[--j]);
			ft_strdel(&hex);
			return (result);
		}
	}
	perror("Short to hexadecimal converting.");
	exit(-1);
}

char	*integer_in_hex(unsigned int num)
{
	int		i;
	int		j;
	char	*hex;
	char	*result;

	if ((result = ft_strnew(sizeof(char) * 8)))
	{
		if ((hex = ft_itoa_base(num, 16)))
		{
			ft_memset(result, '0', 8);
			i = (int)ft_strlen(result);
			j = (int)ft_strlen(hex);
			while (j > 0)
				result[--i] = (char)ft_tolower(hex[--j]);
			ft_strdel(&hex);
			return (result);
		}
	}
	perror("Integer to hexadecimal converting.");
	exit(-1);
}
