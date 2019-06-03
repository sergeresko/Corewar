/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_dot_instr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozalisky <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 02:19:41 by ozalisky          #+#    #+#             */
/*   Updated: 2019/06/02 02:23:39 by ozalisky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

size_t	read_dot_instr(char **tline, size_t i, t_asm *asm_struct)
{
	if (ft_get_substr_index(*tline, NAME_CMD_STRING) == (int)i)
	{
		get_champs_name(*tline, asm_struct);
	}
	else if (ft_get_substr_index(*tline, COMMENT_CMD_STRING) == (int)i)
	{
		get_champs_description(*tline, asm_struct);
	}
	else
	{
		ft_printf("Lexical error at [%d:%d]\n", asm_struct->data.line,
				(int)ft_get_substr_index(*tline, ".") +
				asm_struct->data.skipped_spaces);
		exit(-1);
	}
	return (ft_strlen(*tline));
}
