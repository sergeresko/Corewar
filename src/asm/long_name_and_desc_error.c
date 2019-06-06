/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_name_and_desc_error.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozalisky <ozalisky@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 12:51:25 by syeresko          #+#    #+#             */
/*   Updated: 2019/06/06 19:31:19 by ozalisky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	*get_trimmed_line_multi(char **line, t_asm *asm_struct)
{
	char	*tline;

	++asm_struct->data.line;
	asm_struct->data.row = (asm_struct->data.error_case) ?
						asm_struct->data.row : (int)ft_strlen(*line);
	asm_struct->data.row = (asm_struct->data.skipped_line) ?
						(int)ft_strlen(*line) : asm_struct->data.row;
	tline = ft_strtrim_multi(*line);
	asm_struct->data.skipped_spaces = (int)ft_get_substr_index(*line, ".") + 1;
	ft_strdel(line);
	return (tline ? tline : NULL);
}

void	long_name_error(void)
{
	ft_printf("Champion name too long (Max length 128)\n");
	exit(-1);
}

void	long_desc_error(void)
{
	ft_printf("Champion comment too long (Max length 2048)");
	exit(-1);
}
