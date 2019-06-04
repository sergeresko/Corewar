/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_description.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozalisky <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 16:40:40 by ozalisky          #+#    #+#             */
/*   Updated: 2019/06/05 00:04:36 by ozalisky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	long_desc_error()
{
	ft_printf("Champion comment too long (Max length 2048)");
	exit(-1);
}

int		concatinate_desc_strings(char *field, char *line, t_asm *asm_struct)
{
	int field_len;
	int new_len;
	int reverse_counter;

	field_len = ft_strlen(field);
	new_len = ft_strlen(line);
	reverse_counter = new_len;
	while (reverse_counter > 0 && field_len + (new_len - reverse_counter) <= DESC_LENGTH && line[(new_len - reverse_counter)] != '"')
	{
		field[field_len + (new_len - reverse_counter)] = line[(new_len - reverse_counter)];
		--reverse_counter;
	}
	if (field_len + (new_len - reverse_counter) > DESC_LENGTH)
		long_desc_error();
	if (line[(new_len - reverse_counter)] == '"')
	{
		--reverse_counter;
		while (line[(new_len - reverse_counter)] == ' ' || line[(new_len - reverse_counter)] == '\t')
			--reverse_counter;
		if (line[(new_len - reverse_counter)] != '\0' && line[(new_len - reverse_counter)] != '#')
			get_error_code(line, asm_struct, (new_len - reverse_counter));
		return (0);
	}
	field[field_len + new_len] = '\n';
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
		if (!(tline = get_trimmed_line(&line, asm_struct)))
			e__trim_line(line);
		if (!concatinate_desc_strings(field, tline, asm_struct))
		{
			ft_strdel(&line);
			return ;
		}
		ft_strdel(&line);
		if (tline && !tline[0])
			ft_strdel(&tline);
	}
}

int		get_description(int i, char *line, t_asm *asm_struct, char *field)
{
	size_t	j;

	j = 0;
	while (i < (int)ft_strlen(line) && line[i] != '"')
		field[j++] = line[i++];
	if (line[i] == '\0')
	{
		field[j] = '\n';
		read_multi_line_desc(asm_struct, field);
	}
//		get_error_code(line, asm_struct, i);
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
	i = i + 7;
	while (line[i] == ' ' || (line[i] == '\t'))
		i++;
	if (line[i] == '"')
		i = get_i(i, line, asm_struct, field);
	else
		get_error_code(line, asm_struct, i);
	++i;
	while (line[i] == ' ' || line[i] == '\t')
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
