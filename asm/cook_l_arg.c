/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cook_l_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozalisky <ozalisky@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 16:15:33 by ozalisky          #+#    #+#             */
/*   Updated: 2019/06/02 16:16:05 by ozalisky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	*get_temp(t_com *com, int delta)
{
	return (com->label_size == 2
			? short_in_hex(delta) : integer_in_hex(delta));
}

int		get_index(t_asm *asm_str, char *temp, t_com *com, int index)
{
	ft_strncpy(&(asm_str->champion[index]),
			temp, com->label_size == 2 ? 4 : 8);
	ft_strdel(&temp);
	index += com->label_size == 2 ? 4 : 8;
	return (index);
}

char	*get_temp2(int delta, int l_ind, t_com *com, int a_n)
{
	return ((delta = l_ind - com->index) >= 0
			? short_in_hex(delta)
			: get_revert_integer(com, a_n, -delta));
}

int		get_index_2(t_asm *asm_str, char *temp, int index)
{
	ft_strncpy(&(asm_str->champion[index]), temp, 4);
	index += 4;
	ft_strdel(&temp);
	return (index);
}

int		cook_l_arg(t_com *com, int a_n, int index, t_asm *asm_str)
{
	char	*temp;
	int		delta;
	int		l_ind;

	delta = 0;
	if ((l_ind = get_label_index(asm_str->labels, com->arg_labels[a_n])) != -1)
	{
		if (com->arg_types[a_n] == T_DIR)
		{
			if ((delta = l_ind - com->index) >= 0)
				temp = get_temp(com, delta);
			else
				temp = get_revert_integer(com, a_n, -delta);
			return (get_index(asm_str, temp, com, index));
		}
		else if (com->arg_types[a_n] == T_IND)
		{
			temp = get_temp2(delta, l_ind, com, a_n);
			return (get_index_2(asm_str, temp, index));
		}
		return (index + 1 + (int)ft_strlen(com->arg_labels[a_n]));
	}
	print_label_error(com, a_n);
	exit(-1);
}
