/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_name_and_description.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozalisky <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 20:50:03 by vlvereta          #+#    #+#             */
/*   Updated: 2019/06/05 00:12:52 by ozalisky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	long_name_error()
{
	ft_printf("Champion name too long (Max length 128)\n");
	exit(-1);
}

int		concatinate_name_strings(char *field, char *line, t_asm *asm_struct)
{
	int field_len;
	int new_len;
	int reverse_counter;

	field_len = ft_strlen(field);
	new_len = ft_strlen(line);
	reverse_counter = new_len;
	while (reverse_counter > 0 && field_len + (new_len - reverse_counter) <= NAME_LENGTH && line[(new_len - reverse_counter)] != '"')
	{
		field[field_len + (new_len - reverse_counter)] = line[(new_len - reverse_counter)];
		--reverse_counter;
	}
	if (field_len + (new_len - reverse_counter) > NAME_LENGTH)
		long_name_error();
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

void	read_multi_line(t_asm *asm_struct, char *field)
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
		if (!concatinate_name_strings(field, tline, asm_struct))
		{
			ft_strdel(&line);
			return ;
		}
		ft_strdel(&line);
		if (tline && !tline[0])
			ft_strdel(&tline);
	}
}

int		get_name(int i, char *line, t_asm *asm_struct, char *field)
{
	size_t	j;

	j = 0;
	while (i < (int)ft_strlen(line) && line[i] != '"')
		field[j++] = line[i++];
	if (line[i] == '\0')
	{
		field[j] = '\n';
		read_multi_line(asm_struct, field);
	}
//		get_error_code(line, asm_struct, i);
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
	if (j > NAME_LENGTH)
		long_name_error();
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
	while (line[i] == ' ' || line[i] == '\t')
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
