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
//	if (ERROR_MODE || !asm_struct->header.name[0] || !asm_struct->header.description[0] || asm_struct->command)
//	{
//		ft_printf("Syntax error at token: %s\n", name);
//		exit(-1);
//	}
	if (name)
	{
		if ((command = check_command(name)))
			asm_struct->command = command;
		else
		{
			ft_printf("Lexical error: %s\n", name);
		}
		ft_strdel(&name);
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


size_t	check_label(char *tline, size_t end, int check_label_char)
{
	size_t	start;

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
//	if (ERROR_MODE || !asm_struct->header.name[0] || !asm_struct->header.description[0] || asm_struct->command)
//	{
//		ft_printf("Syntax error at token: %s\n", name);
//		exit(-1);
//	}
	label = ft_memalloc(sizeof(t_label));
	if (name && label)
	{
		label->name = name;
//		label->index = index;
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

int		check_register(char *tline, size_t i)
{
	int		two;

	two = 2;
	while (two > 0)
	{
		if (ft_isdigit(tline[++i]))
		{
			if (tline[i + 1] == ' ' || tline[i + 1] == '\t' || tline[i + 1] == '\n' || tline[i + 1] == SEPARATOR_CHAR || tline[i + 1] == '\0')
				return (ft_atoi(&tline[i + (two - 2)]) < REG_NUMBER ? TRUE : FALSE);
			two--;
			continue ;
		}
		break ;
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









