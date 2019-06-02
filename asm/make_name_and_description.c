/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_name_and_description.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozalisky <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 20:50:03 by vlvereta          #+#    #+#             */
/*   Updated: 2019/06/02 03:59:08 by ozalisky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "asm.h"

void	get_champs_name(char *line, t_asm *asm_struct)
{
	size_t	i;
	size_t	j;
	char	*field;

	i = 0;
	j = 0;
	if (!(field = ft_strnew(NAME_LENGTH)))
		return ;
	if (line[i] == '.')
		i++;
	if (strncmp(".name", line, 5) != 0)
		printf("qweq"); //TODO go to error management
	else
		i = i + 4;
	while (line[i] == ' ')
		i++;
	if (line[i] == '"')
	{
		i++;
		while (i < ft_strlen(line) && line[i] != '"')
			i++ && j++;
		i = i - j;
		j = 0;
		while (i < ft_strlen(line) && line[i] != '"')
			field[j++] = line[i++];
		if (line[i] == '\0')
			get_error_code(line, asm_struct, i);
		make_hex_name(asm_struct->header.hex_name, field);
		ft_strdel(&field);
		asm_struct->data.got_name = 1;
	}
	else
		get_error_code(line, asm_struct, i);
	++i;
	while (line[i] == ' ')
		i++;
	if (line[i] != '\0' && line[i] != '#')
		get_error_code(line, asm_struct, i);
}

void	make_hex_name(char *hex_name, char *name)
{
	int		i;
	int		j;
	int		len;
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

void	get_champs_description(char *line, t_asm *asm_struct)
{
	size_t	i;
	size_t	j;
	char	*field;

	i = 0;
	j = 0;
	if (!(field = ft_strnew(DESC_LENGTH)))
		return ;
	if (line[i] == '.')
		i++;
	if (strncmp(".comment", line, 8) != 0)
		printf("qweq");
	else
		i = i + 7;
	while (line[i] == ' ')
		i++;
	if (line[i] == '"')
	{
		i++;
		while (i < ft_strlen(line) && line[i] != '"')
			i++ && j++;
		i = i - j;
		j = 0;
		while (i < ft_strlen(line) && line[i] != '"')
			field[j++] = line[i++];
		if (line[i] == '\0')
			get_error_code(line, asm_struct, i);
		make_hex_desc(asm_struct->header.hex_description, field);
		ft_strdel(&field);
		asm_struct->data.got_description = 1;
	}
	else
		get_error_code(line, asm_struct, i);
	++i;
	while (line[i] == ' ')
		i++;
	if (line[i] != '\0' && line[i] != '#')
		get_error_code(line, asm_struct, i);
}

void	make_hex_desc(char *hex_description, char *description)
{
	int		i;
	int		j;
	int		len;
	char	*temp;

	ft_memset((void *)hex_description, '0', HEX_DESC_LENGTH);
	hex_description[HEX_DESC_LENGTH] = '\0';
	i = 0;
	j = 0;
	len = ft_strlen(description);
	while (i < len && j < HEX_DESC_LENGTH - 1)
	{
		temp = ft_itoa_base(description[i++], 16);
		hex_description[j++] = ft_tolower(temp[0]);
		hex_description[j++] = ft_tolower(temp[1]);
		ft_strdel(&temp);
	}
}
