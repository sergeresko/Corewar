/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozalisky <ozalisky@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 20:50:03 by vlvereta          #+#    #+#             */
/*   Updated: 2019/02/10 15:48:09 by ozalisky         ###   ########.fr       */
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
	ft_strdel(line);
	return (tline ? tline : NULL);
}

int		get_substr_index(const char *big, const char *little)
{
	int		i;
	int 	j;
	int 	k;

	i = 0;
	if (!(*little))
		return (0);
	while (big[i])
	{
		j = 0;
		k = i;
		while (big[i] && little[j] && big[i] == little[j])
		{
			if (!little[++j])
				return (k);
			i++;
		}
		i = ++k;
	}
	return (-1);
}

char	*convert_int_to_hex(int num)
{
	int		num_len;
	int 	res_len;
	char	*result;
	char	*number;

	result = NULL;
	if ((number = ft_itoa_base(num, 16)))
	{
		num_len = ft_strlen(number);
		if ((result = ft_strnew(9)))
		{
			res_len = 8;
			result = ft_memset((void *)result, '0', res_len);
			while (num_len > 0)
				result[--res_len] = ft_tolower(number[--num_len]);
		}
		ft_strdel(&number);
	}
	return (result);
}

void	read_command(char *tline, size_t start, size_t end, t_asm *asm_struct)
{
	char	*name;
	t_com	*command;

	name = ft_strsub(tline, (unsigned int)start, end - start);
	if (!asm_struct->header.name[0] || !asm_struct->header.description[0] || asm_struct->command)
	{
		ft_printf("Syntax error, command %s\n", name);
		exit(-1);
	}
	if (name)
	{
		if ((command = check_command(name)))
			asm_struct->command = command;
		else
		{
			ft_printf("Lexical error: %s\n", name);
		}
	}
	else
		perror(ALLOCATION_ERROR);

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
	if (!asm_struct->header.name[0] || !asm_struct->header.description[0] || asm_struct->command)
	{
		ft_printf("Syntax error, label %s\n", name);
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
		perror(ALLOCATION_ERROR);
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

int 	is_register(char *tline, size_t i)
{
	if (ft_isdigit(tline[++i]))
	{
		i += !ft_isdigit(tline[i + 1]) ? 1 : 2;
		if (tline[i] == ' ' || tline[i] == '\t' || tline[i] == '\n' || tline[i] == '\0' || tline[i] == SEPARATOR_CHAR)
			return (TRUE);
	}
	return (FALSE);
}

int		includes(const char *str, char c)
{
	if (!c || !str || !(*str))
		return (FALSE);
	while (*str)
	{
		if (*str == c)
			return (TRUE);
		str++;
	}
	return (FALSE);
}

void	check_command_line(t_asm *asm_struct)
{
	if (asm_struct->command->is_codage)
		asm_struct->command->codage = make_codage(asm_struct->command);
	g_index += command_length(asm_struct->command);
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

char	*byte_in_bits(char c)
{
	int 	i;
	char	*result;

	if ((result = ft_strnew(sizeof(char) * 8)))
	{
		i = 8;
		while (i > 0)
		{
			result[--i] = c % 2 + '0';
			c /= 2;
		}
		return (result);
	}
	return (NULL);
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








