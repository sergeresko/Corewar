/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 20:50:03 by vlvereta          #+#    #+#             */
/*   Updated: 2018/11/05 20:50:32 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	*check_comment(char **line)
{
	if (**line == '#')
	{
		ft_strdel(line);
		return (NULL);
	}
	return (*line);
}

void	clean_asm_struct(t_asm **asm_struct)
{
	if ((*asm_struct)->filename)
		ft_memdel((void **)&(*asm_struct)->filename);
//	if ((*asm_struct)->labels)
//		clean_labels_list(&(*asm_struct)->labels);
	ft_memdel((void **)asm_struct);
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

void	make_program_name(char *hex_name, char *name)
{
	int 	i;
	int 	j;
	int 	len;
	char	*temp;

	ft_memset((void *)hex_name, '0', NAME_LENGTH);
	hex_name[NAME_LENGTH] = '\0';
	i = 0;
	j = 0;
	len = ft_strlen(name);
	while (i < len && j < NAME_LENGTH - 1)
	{
		temp = ft_itoa_base(name[i++], 16);
		hex_name[j++] = ft_tolower(temp[0]);
		hex_name[j++] = ft_tolower(temp[1]);
		ft_strdel(&temp);
	}
}

void	make_program_description(char *hex_description, char *description)
{
	int 	i;
	int 	j;
	int 	len;
	char	*temp;

	ft_memset((void *)hex_description, '0', DESCRIPTION_LENGTH);
	hex_description[DESCRIPTION_LENGTH] = '\0';
	i = 0;
	j = 0;
	len = ft_strlen(description);
	while (i < len && j < DESCRIPTION_LENGTH - 1)
	{
		temp = ft_itoa_base(description[i++], 16);
		hex_description[j++] = ft_tolower(temp[0]);
		hex_description[j++] = ft_tolower(temp[1]);
		ft_strdel(&temp);
	}
}