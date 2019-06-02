/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozalisky <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 02:37:26 by ozalisky          #+#    #+#             */
/*   Updated: 2019/06/02 01:20:02 by ozalisky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	*get_revert_integer(t_com *command, int arg_num, int delta)
{
	unsigned int	revert_delta;

	revert_delta = ~delta + 1;
	if (command->arg_types[arg_num] == T_IND)
		return (short_in_hex(revert_delta));
	return (command->label_size == 2
		? short_in_hex(revert_delta)
		: integer_in_hex(revert_delta));
}

int		get_label_index(t_label *labels, char *label_name)
{
	t_label	*temp;

	temp = labels;
	while (temp)
	{
		if (ft_strequ(temp->name, label_name))
			return (temp->index);
		temp = temp->next;
	}
	return (-1);
}

char	*get_label_name(t_label *labels, int index)
{
	t_label	*temp;

	temp = labels;
	while (temp)
	{
		if (temp->index == index)
			return (temp->name);
		temp = temp->next;
	}
	return (NULL);
}

int		cook_l_arg(t_com *com, int a_n, int index, t_asm *asm_str)
{
	char	*temp;
	int		delta;
	int		l_ind;

	if ((l_ind = get_label_index(asm_str->labels, com->arg_labels[a_n])) != -1)
	{
		if (com->arg_types[a_n] == T_DIR)
		{
			if ((delta = l_ind - com->index) >= 0)
				temp = com->label_size == 2
					? short_in_hex(delta)
					: integer_in_hex(delta);
			else
				temp = get_revert_integer(com, a_n, -delta);
			ft_strncpy(&(asm_str->champion[index]),
					temp, com->label_size == 2 ? 4 : 8);
			index += com->label_size == 2 ? 4 : 8;
			ft_strdel(&temp);
			return (index);
		}
		else if (com->arg_types[a_n] == T_IND)
		{
			temp = (delta = l_ind - com->index) >= 0
				? short_in_hex(delta)
				: get_revert_integer(com, a_n, -delta);
			ft_strncpy(&(asm_str->champion[index]), temp, 4);
			index += 4;
			ft_strdel(&temp);
			return (index);
		}
		return (index + 1 + (int)ft_strlen(com->arg_labels[a_n]));
	}
	ft_printf("No such label %s while attempting to dereference"
			"token %s \"%c%s\"\n", com->arg_labels[a_n],
			com->arg_types[a_n] == T_DIR ? "DIRECT_LABEL" : "INDIRECT_LABEL",
			com->arg_types[a_n] == T_DIR ? '%' : ':', com->arg_labels[a_n]);
	exit(-1);
}
