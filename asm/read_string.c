/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_string.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozalisky <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 02:27:51 by ozalisky          #+#    #+#             */
/*   Updated: 2019/05/31 02:27:51 by ozalisky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

size_t	read_string(char **tline, size_t i, t_asm *asm_struct)
{
	size_t	j;

	if ((j = check_label(*tline, i, TRUE)))
	{
		read_label(*tline, i, j, asm_struct);
		return (++j);
	}
	j = i;
	while (includes(LABEL_CHARS, (*tline)[j]))
		j++;
	read_com(*tline, i, j, asm_struct);
	return (j);
}
