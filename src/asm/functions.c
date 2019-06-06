/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 20:50:03 by vlvereta          #+#    #+#             */
/*   Updated: 2019/06/03 19:37:49 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	*get_trimmed_line(char **line, t_asm *asm_struct)
{
	char	*tline;

	++asm_struct->data.line;
	asm_struct->data.row = (asm_struct->data.error_case) ?
			asm_struct->data.row : (int)ft_strlen(*line);
	asm_struct->data.row = (asm_struct->data.skipped_line) ?
			(int)ft_strlen(*line) : asm_struct->data.row;
	tline = ft_strtrim(*line);
	asm_struct->data.skipped_spaces = (int)ft_get_substr_index(*line, ".") + 1;
	ft_strdel(line);
	return (tline ? tline : NULL);
}

void	push_command_front(t_com **commands, t_com *command)
{
	if (!commands)
		ft_printf("Commands list == 'NULL'\n");
	if (commands)
	{
		command->next = *commands;
		*commands = command;
	}
}

int		check_label(char *tline, int end, int check_label_char)
{
	int		start;

	start = end;
	while (includes(LABEL_CHARS, tline[end]))
		end++;
	if (start == end || (check_label_char && tline[end] != LABEL_CHAR))
		return (FALSE);
	return (end);
}

void	read_label(char *tl, size_t st, size_t end, t_asm *asm_str)
{
	char	*name;
	t_label	*label;

	name = ft_strsub(tl, (unsigned int)st, end - st);
	if (!asm_str->data.got_name || !asm_str->data.got_description)
	{
		ft_printf("Syntax error at token [TOKEN][%03d:%03d] LABEL \"%s:\"\n",
			asm_str->data.line, (int)(st + 1), name);
		exit(-1);
	}
	if (!asm_str->header.hex_name[0]
		|| !asm_str->header.hex_description[0] || asm_str->command)
	{
		ft_printf("Syntax error, label \"%s:\"\n", name);
		exit(-1);
	}
	label = ft_memalloc(sizeof(t_label));
	if (name && label)
	{
		label->name = name;
		label->index = g_index;
		push_label_front(&(asm_str->labels), label);
	}
	else
		perror("");
}

void	push_label_front(t_label **labels, t_label *label)
{
	if (!labels)
		ft_printf("Labels list == 'NULL'\n");
	if (labels)
	{
		label->next = *labels;
		*labels = label;
	}
}
