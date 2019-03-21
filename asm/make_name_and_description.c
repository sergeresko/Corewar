/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_name_and_description.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 20:50:03 by vlvereta          #+#    #+#             */
/*   Updated: 2019/03/19 20:51:18 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	get_champs_name(char *line, t_asm *asm_struct)
{
	size_t	i;
	size_t	j;
	char 	*field;

	i = 0;
	j = 0;
	if (!(field = ft_strnew(NAME_LENGTH)))
		return ;
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
		make_hex_name(asm_struct->header.name, field);
		ft_strdel(&field);
	}
	else if (line[i] == '\0')
		asm_struct->data.errorCase = 1;
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

void	get_champs_description(char *line, t_asm *asm_struct)
{
	size_t	i;
	size_t	j;
	char 	*field;

	i = 0;
	j = 0;
	if (!(field = ft_strnew(DESCRIPTION_LENGTH)))
		return ;
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
		make_hex_description(asm_struct->header.description, field);
		ft_strdel(&field);
	}
	else if (line[i] == '\0')
		asm_struct->data.errorCase = 1;
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
