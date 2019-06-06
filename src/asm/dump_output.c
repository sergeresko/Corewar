/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump_output.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 20:50:03 by vlvereta          #+#    #+#             */
/*   Updated: 2019/05/31 18:38:46 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	dump_output(t_asm *asm_struct)
{
	ft_printf("Dumping annotated program on standard output\n");
	ft_printf("Program size : %d bytes\n", g_index);
	ft_printf("Name : \"%s\"\n", asm_struct->header.name);
	ft_printf("Comment : \"%s\"\n\n", asm_struct->header.description);
	rush_through_com(asm_struct->commands, 0, asm_struct);
}

void	rush_through_com(t_com *com, int index, t_asm *asm_str)
{
	char	*temp;
	char	*label_name;
	int		current_index;

	if (com->next)
		rush_through_com(com->next, index + com->length, asm_str);
	current_index = g_index - index - com->length;
	if ((label_name = get_label_name(asm_str->labels, current_index)))
	{
		temp = ft_itoa(current_index);
		print_in_length(11, &temp);
		ft_printf(":    %s:\n", label_name);
	}
	print_command_line(com, current_index);
	print_add_com_line_1(com, 1, asm_str);
	print_add_com_line_1(com, 2, asm_str);
	ft_putchar('\n');
}
