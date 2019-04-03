/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_file_output.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 22:50:03 by vlvereta          #+#    #+#             */
/*   Updated: 2019/01/04 22:50:32 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	output_to_file(t_asm *champ)
{
	int 	file_fd;
	char	*champion;
	char 	*head_str;
	char	*body_str;
	char	*filename;

	filename = ft_strjoin(champ->filename, ".cor");
	file_fd = open(filename, O_TRUNC | O_CREAT | O_WRONLY | O_APPEND, 0744);
	head_str = make_header_string(&(champ->header));
	body_str = "";
	champion = ft_strjoin(head_str, body_str);
	format_file_output(file_fd, champion);
	ft_printf("Writing output program to %s\n", filename);
	ft_strdel(&head_str);
//	ft_strdel(&body_str);
	ft_strdel(&champion);
	ft_strdel(&filename);
	close(file_fd);
}

void	format_file_output(int fd, char *champ) // pass how much length to output??
{
	int 	i;
	size_t 	len;

	i = 0;
	len = ft_strlen(champ);
	while (i < len)
	{
		ft_putchar_fd(champ[i++], fd);
		if (!(i % 32))
			ft_putchar_fd('\n', fd);
		else if (!(i % 4))
			ft_putchar_fd(' ', fd);
		if (i == len)
			break ;
	}
}

char	*make_header_string(t_header *header)
{
	int 	i;
	char	*size;
	char	*magic;
	char	*result;
	size_t 	len;

	i = 0;
	if ((result = ft_strnew(HEX_HEADER)))
	{
		ft_memset((void *)result, '0', HEX_HEADER);
		magic = convert_int_to_hex(COREWAR_EXEC_MAGIC);
		ft_strncpy(&(result[i]), magic, BYTE);
		ft_strdel(&magic);
		i += BYTE;
		len = ft_strlen(header->name);
		ft_strncpy(&(result[i]), header->name, len);
		i += len + BYTE;
		size = convert_int_to_hex(header->size);
		ft_strncpy(&(result[i]), size, BYTE);
		ft_strdel(&size);
		i += BYTE;
		ft_strncpy(&(result[i]), header->description, ft_strlen(header->description));
	}
	return (result);
}

//char	*make_body_string();
