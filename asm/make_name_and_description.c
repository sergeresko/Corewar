/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_name_and_description.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 20:50:03 by vlvereta          #+#    #+#             */
/*   Updated: 2019/06/05 21:13:12 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		get_name(int i, char *line, t_asm *asm_struct, char *field)
{
	size_t	j;

	j = 0;
	while (i < (int)ft_strlen(line) && line[i] != '"')
		field[j++] = line[i++];
	if (line[i] == '\0')
		get_error_code(line, asm_struct, i);
	ft_strncpy(asm_struct->header.name, field, ft_strlen(field));
	make_hex_name(asm_struct->header.hex_name, field);
	ft_strdel(&field);
	asm_struct->data.got_name = 1;
	return (i);
}

int		get_name_i(int i, char *line, t_asm *asm_struct, char *field)
{
	size_t	j;

	j = 0;
	i++;
	while (i < (int)ft_strlen(line) && line[i] != '"')
		i++ && j++;
	return (get_name(i - j, line, asm_struct, field));
}

void	get_champs_name(char *line, t_asm *asm_struct)
{
	size_t	i;
	char	*field;

	i = 0;
	if (!(field = ft_strnew(NAME_LENGTH)))
		return ;
	if (line[i] == '.')
		i++;
	i += 4;
	while (line[i] == ' ' || (line[i] == '\t'))
		i++;
	if (line[i] == '"')
		i = get_name_i(i, line, asm_struct, field);
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
