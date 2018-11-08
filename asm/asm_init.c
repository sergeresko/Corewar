/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 20:50:03 by vlvereta          #+#    #+#             */
/*   Updated: 2018/11/08 20:50:32 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		asm_init(t_asm **asm_struct, const char *argv)
{
	*asm_struct = ft_memalloc(sizeof(t_asm));
	if (!(*asm_struct))
	{
		perror(ALLOCATION_ERROR);
		return (0);
	}
	(*asm_struct)->filename = get_filename(argv);
	if (!((*asm_struct)->filename) ||
			!((*asm_struct)->header = ft_memalloc(sizeof(t_header))))
	{
		clean_asm_struct(asm_struct);
		return (0);
	}
	(*asm_struct)->counter = MAX_COUNTER;
	(*asm_struct)->header->magic = COREWAR_EXEC_MAGIC;
	return (1);
}

char	*get_filename(const char *argv)
{
	unsigned int len;

	len = ft_strlen(argv);
	if (len <= 2 || argv[len - 1] != 's' || argv[len - 2] != '.')
		return (NULL);
	return (ft_strsub(argv, 0, len - 2));
}