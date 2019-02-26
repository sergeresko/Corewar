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

void	make_hex_name(char *hex_name, char *name)
{
	int 	i;
	int 	j;
	int 	len;
	char	*temp;

	ft_memset((void *)hex_name, '0', HEX_NAME_LENGTH);
	hex_name[HEX_NAME_LENGTH] = '\0';
	i = 0;
	j = 0;
	len = ft_strlen(name);
	while (i < len && j < HEX_NAME_LENGTH - 1)
	{
		temp = ft_itoa_base(name[i++], 16);
		hex_name[j++] = ft_tolower(temp[0]);
		hex_name[j++] = ft_tolower(temp[1]);
		ft_strdel(&temp);
	}
}

void	make_hex_description(char *hex_description, char *description)
{
	int 	i;
	int 	j;
	int 	len;
	char	*temp;

	ft_memset((void *)hex_description, '0', HEX_DESCRIPTION_LENGTH);
	hex_description[HEX_DESCRIPTION_LENGTH] = '\0';
	i = 0;
	j = 0;
	len = ft_strlen(description);
	while (i < len && j < HEX_DESCRIPTION_LENGTH - 1)
	{
		temp = ft_itoa_base(description[i++], 16);
		hex_description[j++] = ft_tolower(temp[0]);
		hex_description[j++] = ft_tolower(temp[1]);
		ft_strdel(&temp);
	}
}

int		new_label(t_label **labels, char *name, int index)
{
	t_label	*new_label;

	if (name && (new_label = ft_memalloc(sizeof(t_label))))
	{
		new_label->name = name;
		new_label->index = index;
		if (*labels)
			new_label->next = *labels;
		*labels = new_label;
		return (1);
	}
	return (0);
}