/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_champs_description.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozalisky <ozalisky@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 16:40:40 by ozalisky          #+#    #+#             */
/*   Updated: 2019/06/06 20:43:13 by ozalisky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		concatinate_desc_strings(char *field, char *line, t_asm *asm_struct)
{
	int const	field_len = ft_strlen(field);
	int const	new_len = ft_strlen(line);
	int			i;

	i = 0;
	while (i < new_len && field_len + i <= DESC_LENGTH && line[i] != '"')
	{
		field[field_len + i] = line[i];
		++i;
	}
	if (field_len + i > DESC_LENGTH)
		long_desc_error();
	if (line[i] == '"')
	{
		++i;
		while (line[i] == ' ' || line[i] == '\t')
			++i;
		if (line[i] != '\0' && line[i] != '#')
			get_error_code(line, asm_struct, i);
		return (0);
	}
	field[field_len + new_len] = '\n';
	if (line && !line[0])
		ft_strdel(&line);
	return (1);
}

void	read_multi_line_desc(t_asm *asm_struct, char *field)
{
	int		r;
	char	*line;
	char	*tline;

	while ((r = get_next_line(asm_struct->data.fd, &line)))
	{
		if (r == -1)
			e__read_file(asm_struct, 6);
		if (r == 5)
			return (e__read_file(asm_struct, 5));
		if (!(tline = get_trimmed_line_multi(&line, asm_struct)))
			e__trim_line(line);
		if (!concatinate_desc_strings(field, tline, asm_struct))
		{
			ft_strdel(&line);
			ft_strdel(&tline);
			return ;
		}
		ft_strdel(&line);
		if (ft_strcmp("", tline))
			ft_strdel(&tline);
	}
}

int		get_description(int i, char *line, t_asm *asm_struct, char *field)
{
	int const	line_len = ft_strlen(line);
	int			j;

	j = 0;
	while (i < line_len && line[i] != '"')
		field[j++] = line[i++];
	if (line[i] == '\0')
	{
		field[j] = '\n';
		read_multi_line_desc(asm_struct, field);
	}
	ft_strncpy(asm_struct->header.description, field, ft_strlen(field));
	make_hex_desc(asm_struct->header.hex_description, field);
	ft_strdel(&field);
	asm_struct->data.got_description = 1;
	return (i);
}

int		get_i(int i, char *line, t_asm *asm_struct, char *field)
{
	int const	line_len = ft_strlen(line);
	int			j;

	j = 0;
	i++;
	while (i < line_len && line[i] != '"')
		i++ && j++;
	if (j > DESC_LENGTH)
		long_desc_error();
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
	i += 7;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == '"')
		i = get_i(i, line, asm_struct, field);
	else
		get_error_code(line, asm_struct, i);
	if (line[i] == '"')
		++i;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] != '\0' && line[i] != '#')
		get_error_code(line, asm_struct, i);
}
