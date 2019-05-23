/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaliskyi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 20:50:03 by vlvereta          #+#    #+#             */
/*   Updated: 2019/04/30 00:20:36 by zaliskyi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	*get_trimmed_line(char **line, t_asm *asm_struct)
{
	char	*tline;

	++asm_struct->data.line;
	asm_struct->data.row = (asm_struct->data.errorCase) ?
			asm_struct->data.row : (int)ft_strlen(*line);
	asm_struct->data.row = (asm_struct->data.skippedLine) ?
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

void	read_label(char *tline, size_t start, size_t end, t_asm *asm_struct)
{
	char	*name;
	t_label	*label;

	name = ft_strsub(tline, (unsigned int)start, end - start);
	if (!asm_struct->data.got_name || !asm_struct->data.got_description)
	{
		printf("Syntax error at token [TOKEN][%03d:%03d] LABEL \"%s\"\n",
			   asm_struct->data.line, (int)(start + 1), name);
		exit(-1);
	}
	if (!asm_struct->header.hex_name[0] || !asm_struct->header.hex_description[0] || asm_struct->command)
	{
		ft_printf("Syntax error, label \"%s:\"\n", name);
		exit(-1);
	}
	label = ft_memalloc(sizeof(t_label));
	if (name && label)
	{
		label->name = name;
		label->index = g_index;
		push_label_front(&(asm_struct->labels), label);
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

void	write_argument(t_com *command, int arg_num, t_arg_type arg_type, int argument)
{
	command->arg_types[arg_num] = arg_type;
	if (arg_type == T_REG)
		command->arguments[arg_num] = (char)argument;
	else if (arg_type == T_DIR)
		command->arguments[arg_num] = (short)argument;
	else
		command->arguments[arg_num] = argument;
}

void	write_label_argument(t_com *command, int arg_num, t_arg_type arg_type, char **label)
{
	command->arg_types[arg_num] = arg_type;
	command->arg_labels[arg_num] = *label;
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
			? cook_argument(command, 0, current_index, asm_struct)
			: cook_label_argument(command, 0, current_index, asm_struct);
	if (command->arg_types[1])
		current_index = !command->arg_labels[1]
			? cook_argument(command, 1, current_index, asm_struct)
			: cook_label_argument(command, 1, current_index, asm_struct);
	if (command->arg_types[2])
		!command->arg_labels[2]
			? cook_argument(command, 2, current_index, asm_struct)
			: cook_label_argument(command, 2, current_index, asm_struct);
}

int		cook_argument(t_com *command, int arg_num, int index, t_asm *asm_struct)
{
	char	*temp;

	if (command->arg_types[arg_num] == T_REG)
	{
		temp = byte_in_hex((unsigned char)command->arguments[arg_num]);
		ft_strncpy(&(asm_struct->champion[index]), temp, 2);
		index += 2;
	}
	else if (command->arg_types[arg_num] == T_DIR)
	{
		if (command->label_size == 2)
			temp = short_in_hex((unsigned short)command->arguments[arg_num]);
		else
			temp = integer_in_hex(command->arguments[arg_num]);
		ft_strncpy(&(asm_struct->champion[index]), temp, command->label_size == 2 ? 4 : 8);
		index += command->label_size == 2 ? 4 : 8;
	}
	else if (command->arg_types[arg_num] == T_IND)
	{
		temp = short_in_hex((unsigned short)command->arguments[arg_num]);
		ft_strncpy(&(asm_struct->champion[index]), temp, 4);
		index += 4;
	}
	ft_strdel(&temp);
	return (index);
}

int 	cook_label_argument(t_com *command, int arg_num, int index, t_asm *asm_struct)
{
	char	*temp;
	int 	delta;
	int 	label_index;

	if ((label_index = get_label_index(asm_struct->labels, command->arg_labels[arg_num])) != -1)
	{
		if (command->arg_types[arg_num] == T_DIR)
		{
//			ft_printf("Direct %s label index = %d, command index = %d\n", command->arg_labels[arg_num], label_index, command->index);
			if ((delta = label_index - command->index) >= 0)
				temp = command->label_size == 2
					? short_in_hex(delta)
					: integer_in_hex(delta);
			else
				temp = get_revert_integer(command, arg_num, -delta);
			ft_strncpy(&(asm_struct->champion[index]), temp, command->label_size == 2 ? 4 : 8);
			index += command->label_size == 2 ? 4 : 8;
			ft_strdel(&temp);
			return index;
		}
		else if (command->arg_types[arg_num] == T_IND)
		{
//			ft_printf("Indirect %s label index = %d, command index = %d\n", command->arg_labels[arg_num], label_index, command->index);
			if ((delta = label_index - command->index) >= 0)
				temp = short_in_hex(delta);
			else
				temp = get_revert_integer(command, arg_num, -delta);
			ft_strncpy(&(asm_struct->champion[index]), temp, 4);
			index += 4;
			ft_strdel(&temp);
			return index;
		}
		return (index + 1 + (int)ft_strlen(command->arg_labels[arg_num]));
	}
	ft_printf("No such label %s while attempting to dereference token %s \"%c%s\"\n",
			command->arg_labels[arg_num],
			command->arg_types[arg_num] == T_DIR ? "DIRECT_LABEL" : "INDIRECT_LABEL",
			command->arg_types[arg_num] == T_DIR ? '%' : ':', command->arg_labels[arg_num]);
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



