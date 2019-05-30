/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozalisky <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 02:37:26 by ozalisky          #+#    #+#             */
/*   Updated: 2019/05/31 02:37:26 by ozalisky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	*get_revert_integer(t_com *command, int arg_num, int delta)
{
	unsigned int 	revert_delta;

	revert_delta = ~delta + 1;
	if (command->arg_types[arg_num] == T_IND)
		return short_in_hex(revert_delta);
	return command->label_size == 2
		   ? short_in_hex(revert_delta)
		   : integer_in_hex(revert_delta);
}

int 	get_label_index(t_label *labels, char *label_name)
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
			return temp->name;
		temp = temp->next;
	}
	return (NULL);
}
