/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 20:50:03 by vlvereta          #+#    #+#             */
/*   Updated: 2019/05/26 18:56:53 by vlvereta         ###   ########.fr       */
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
	asm_struct->data.skipped_spaces = (int) ft_get_substr_index(*line, ".") + 1;
	ft_strdel(line);
	return (tline ? tline : NULL);
}

void	push_command_front(t_com **commands, t_com *command)
{
	if (!commands)		// handle error
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
		printf("Syntax error at token [TOKEN][%03d:%03d] LABEL \"%s\"\n",
			   asm_str->data.line, (int)(st + 1), name);
		exit(-1);
	}
	if (!asm_str->header.hex_name[0] || !asm_str->header.hex_description[0] || asm_str->command)
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
	if (!labels)		// handle error
		ft_printf("Labels list == 'NULL'\n");
	if (labels)
	{
		label->next = *labels;
		*labels = label;
	}
}

void	check_command_line(t_asm *asm_struct)
{
	if (asm_struct->command->is_codage)
		asm_struct->command->codage = make_codage(asm_struct->command);
	asm_struct->command->length = command_length(asm_struct->command);
	asm_struct->command->index = g_index;
	g_index += asm_struct->command->length;
	t_com	*new_command = ft_memalloc(sizeof(t_com));
	push_command_front(&(asm_struct->commands), ft_memcpy(new_command, asm_struct->command, sizeof(t_com)));
	ft_memdel((void **)(&(asm_struct->command)));
}

char	make_codage(t_com *command)
{
	int 	count;
	char	result;

	count = 0;
	result = 0;
	while (count < 3)
	{
		if (command->arg_types[count] == T_REG)
			result = result | (char)REG_CODE;
		else if (command->arg_types[count] == T_DIR)
			result = result | (char)DIR_CODE;
		else if (command->arg_types[count] == T_IND)
			result = result | (char)IND_CODE;
		result = result << 2;
		count++;
	}
	return (result);
}

int 	command_length(t_com *command)
{
	int 	count;
	int 	result;

	count = 0;
	result = 1;
	while (count < 3)
	{
		if (command->arg_types[count] == T_REG)
			result += 1;
		else if (command->arg_types[count] == T_DIR)
			result += command->label_size;
		else if (command->arg_types[count] == T_IND)
			result += 2;
		count++;
	}
	if (command->is_codage)
		result += 1;
	return (result);
}

void	write_arg(t_com *com, int a_n, t_arg_type a_t, int arg)
{
	com->arg_types[a_n] = a_t;
	if (a_t == T_REG)
		com->arguments[a_n] = (char)arg;
	else if (a_t == T_DIR)
		com->arguments[a_n] = (short)arg;
	else
		com->arguments[a_n] = arg;
}

void	write_l_a(t_com *com, int a_n, t_arg_type a_t, char **l)
{
	com->arg_types[a_n] = a_t;
	com->arg_labels[a_n] = *l;
}

int 	check_proper_ending(const char *line, int i)
{
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\t')
			++i;
		else if (line[i] == '#')
		{
			while (line[i] != '\0')
				++i;
		}
		else if (line[i] == SEPARATOR_CHAR || line[i] == '\n')
			return (++i);
		else
		{
			g_error_mode = TRUE;
			return (i);
		}
	}
	return (i);
}

void	cook_champion(t_asm *asm_struct)
{
	int 	i;
	int 	length;

	length = g_index * 2;
	asm_struct->header.size = (unsigned int)g_index;
	if ((asm_struct->champion = ft_strnew(sizeof(char) * length)))
	{
		i = 0;
		ft_memset(asm_struct->champion, '0', (size_t)length);
		cook_command(asm_struct->commands, i, asm_struct);
	}
	else
		perror("");
}

void	cook_command(t_com *command, int i, t_asm *asm_struct)
{
	char	*temp;
	int 	current_index;

	if (command->next)
		cook_command(command->next, i + command->length, asm_struct);
	current_index = (g_index - i - command->length) * 2;
	temp = byte_in_hex((unsigned char)command->code);
	ft_strncpy(&(asm_struct->champion[current_index]), temp, 2);
	current_index += 2;
	ft_strdel(&temp);
	if (command->is_codage)
	{
		temp = byte_in_hex((unsigned char)command->codage);
		ft_strncpy(&(asm_struct->champion[current_index]), temp, 2);
		current_index += 2;
		ft_strdel(&temp);
	}
	if (command->arg_types[0])
		current_index = !command->arg_labels[0]
			? cook_arg(command, 0, current_index, asm_struct)
			: cook_l_arg(command, 0, current_index, asm_struct);
	if (command->arg_types[1])
		current_index = !command->arg_labels[1]
			? cook_arg(command, 1, current_index, asm_struct)
			: cook_l_arg(command, 1, current_index, asm_struct);
	if (command->arg_types[2])
		!command->arg_labels[2]
			? cook_arg(command, 2, current_index, asm_struct)
			: cook_l_arg(command, 2, current_index, asm_struct);
}

int		cook_arg(t_com *com, int a_n, int index, t_asm *asm_str)
{
	char	*temp;

	if (com->arg_types[a_n] == T_REG)
	{
		temp = byte_in_hex((unsigned char)com->arguments[a_n]);
		ft_strncpy(&(asm_str->champion[index]), temp, 2);
		index += 2;
	}
	else if (com->arg_types[a_n] == T_DIR)
	{
		if (com->label_size == 2)
			temp = short_in_hex((unsigned short)com->arguments[a_n]);
		else
			temp = integer_in_hex(com->arguments[a_n]);
		ft_strncpy(&(asm_str->champion[index]), temp, com->label_size == 2 ? 4 : 8);
		index += com->label_size == 2 ? 4 : 8;
	}
	else if (com->arg_types[a_n] == T_IND)
	{
		temp = short_in_hex((unsigned short)com->arguments[a_n]);
		ft_strncpy(&(asm_str->champion[index]), temp, 4);
		index += 4;
	}
	ft_strdel(&temp);
	return (index);
}

int 	cook_l_arg(t_com *com, int a_n, int index, t_asm *asm_str)
{
	char	*temp;
	int 	delta;
	int 	label_index;

	if ((label_index = get_label_index(asm_str->labels, com->arg_labels[a_n])) != -1)
	{
		if (com->arg_types[a_n] == T_DIR)
		{
//			ft_printf("Direct %s label index = %d, command index = %d\n", command->arg_labels[arg_num], label_index, command->index);
			if ((delta = label_index - com->index) >= 0)
				temp = com->label_size == 2
					? short_in_hex(delta)
					: integer_in_hex(delta);
			else
				temp = get_revert_integer(com, a_n, -delta);
			ft_strncpy(&(asm_str->champion[index]), temp, com->label_size == 2 ? 4 : 8);
			index += com->label_size == 2 ? 4 : 8;
			ft_strdel(&temp);
			return index;
		}
		else if (com->arg_types[a_n] == T_IND)
		{
//			ft_printf("Indirect %s label index = %d, command index = %d\n", command->arg_labels[arg_num], label_index, command->index);
			if ((delta = label_index - com->index) >= 0)
				temp = short_in_hex(delta);
			else
				temp = get_revert_integer(com, a_n, -delta);
			ft_strncpy(&(asm_str->champion[index]), temp, 4);
			index += 4;
			ft_strdel(&temp);
			return index;
		}
		return (index + 1 + (int)ft_strlen(com->arg_labels[a_n]));
	}
	ft_printf("No such label %s while attempting to dereference token %s \"%c%s\"\n",
			com->arg_labels[a_n],
			com->arg_types[a_n] == T_DIR ? "DIRECT_LABEL" : "INDIRECT_LABEL",
			com->arg_types[a_n] == T_DIR ? '%' : ':', com->arg_labels[a_n]);
	exit(-1);
}

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



