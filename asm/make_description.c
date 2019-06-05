/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_description.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 16:40:40 by ozalisky          #+#    #+#             */
/*   Updated: 2019/06/03 14:01:26 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		get_description(int i, char *line, t_asm *asm_struct, char *field)
{
	size_t	j;

	j = 0;
	while (i < (int)ft_strlen(line) && line[i] != '"')
		field[j++] = line[i++];
	if (line[i] == '\0')
		get_error_code(line, asm_struct, i);
	ft_strncpy(asm_struct->header.description, field, ft_strlen(field));
	make_hex_desc(asm_struct->header.hex_description, field);
	ft_strdel(&field);
	asm_struct->data.got_description = 1;
	return (i);
}

int		get_i(int i, char *line, t_asm *asm_struct, char *field)
{
	size_t	j;

	j = 0;
	i++;
	while (i < (int)ft_strlen(line) && line[i] != '"')
		i++ && j++;
	return (get_description(i - j, line, asm_struct, field));
}

void	get_champs_description(char *line, t_asm *asm_struct)
{
	size_t	i;
	char	*field;

	i = 0;
	if (!(field = ft_strnew(DESC_LENGTH)))
		return ;
	if (line[i] == '.')
		i++;
	i = i + 7;
	while (line[i] == ' ' || (line[i] == '\t'))
		i++;
	if (line[i] == '"')
		i = get_i(i, line, asm_struct, field);
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
