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

int		is_skipable(char **line, t_asm *asm_struct)
{
	if (**line == 0 || **line == '#')
	{
		asm_struct->data.skippedLine = 1;
		ft_strdel(line);
		return (1);
	}
	return (0);
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

// modify to work with line labels as well as with arg labels
char	*get_label_name(char **tline)
{
	int 	i;
	char	*label_name;

	i = 0;
	label_name = NULL;
	while(ft_strchr(LABEL_CHARS, (*tline)[i++]))
	{
		if ((*tline)[i] == LABEL_CHAR)
		{
			label_name = ft_strsub(*tline, 0, i);
			if (!label_name)
				perror(ALLOCATION_ERROR);
			*tline = cut_some_piece(*tline, ++i);
		}
	}
	return (label_name);
}

char	*cut_some_piece(char *line, unsigned int start)
{
	char	*temp;

	temp = ft_strsub(line, start, ft_strlen(line) - start);
	if (!temp)
		perror(ALLOCATION_ERROR);
	ft_strdel(&line);
	return (temp);
}

// add check for created label name
t_label	*new_label_node(char *label_name)
{
	t_label	*new_label;

	if ((new_label = ft_memalloc(sizeof(t_label))))
	{
		new_label->name = label_name;
//		new_label->index = index;
	}
	else
		perror(ALLOCATION_ERROR);
	return (new_label);
}

void	push_label_front(t_label **labels, t_label *label)
{
	if (!labels)		// handle error
		ft_printf("Label's list == 'NULL'\n");
	if (labels)
	{
		label->next = *labels;
		*labels = label;
	}
}












