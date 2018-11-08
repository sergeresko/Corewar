/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 20:50:03 by vlvereta          #+#    #+#             */
/*   Updated: 2018/11/05 20:50:32 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	*check_comment(char **line)
{
	if (**line == '#')
	{
		ft_strdel(line);
		return (NULL);
	}
	return (*line);
}

void	clean_asm_struct(t_asm **asm_struct)
{
	if ((*asm_struct)->header)
		ft_memdel((void **)&(*asm_struct)->header);
	if ((*asm_struct)->filename)
		ft_memdel((void **)&(*asm_struct)->filename);
//	if ((*asm_struct)->labels)
//		clean_labels_list(&(*asm_struct)->labels);
	ft_memdel((void **)asm_struct);
}
