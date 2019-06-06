/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_hex_name_and_desc.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozalisky <ozalisky@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 12:48:06 by syeresko          #+#    #+#             */
/*   Updated: 2019/06/06 17:05:55 by ozalisky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	hex_digit(unsigned char n)
{
	return (n + (n < 10 ? '0' : 'a' - 10));
}

void	make_hex_name(char *hex_name, char *name)
{
	int				i;
	int				j;
	int				len;
	unsigned char	c;

	ft_memset((void *)hex_name, '0', HEX_NAME_LENGTH);
	hex_name[HEX_NAME_LENGTH] = '\0';
	i = 0;
	j = 0;
	len = ft_strlen(name);
	while (i < len && j < HEX_NAME_LENGTH - 1)
	{
		c = name[i++];
		hex_name[j++] = hex_digit(c / 16);
		hex_name[j++] = hex_digit(c % 16);
	}
}

void	make_hex_desc(char *hex_description, char *description)
{
	int				i;
	int				j;
	int				len;
	unsigned char	c;

	ft_memset((void *)hex_description, '0', HEX_DESC_LENGTH);
	hex_description[HEX_DESC_LENGTH] = '\0';
	i = 0;
	j = 0;
	len = ft_strlen(description);
	while (i < len && j < HEX_DESC_LENGTH - 1)
	{
		c = description[i++];
		hex_description[j++] = hex_digit(c / 16);
		hex_description[j++] = hex_digit(c % 16);
	}
}
