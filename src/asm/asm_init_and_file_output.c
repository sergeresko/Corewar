/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_init_and_file_output.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 20:50:03 by vlvereta          #+#    #+#             */
/*   Updated: 2019/06/05 18:58:56 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		asm_init(t_asm **asm_struct, const char *argv)
{
	if (!(*asm_struct = ft_memalloc(sizeof(t_asm))))
		return (0);
	if (!((*asm_struct)->filename = get_filename(argv)))
	{
		clean_asm_struct(asm_struct);
		return (0);
	}
	return (1);
}

char	*get_filename(const char *argv)
{
	char *const	extension = ft_strrchr(argv, '.');
	char		*filename;

	if (extension == NULL || extension == argv
			|| extension[-1] == '/' || !ft_strequ(extension, ".s"))
	{
		ft_printf("Not a valid .s file '%s'\n", argv);
		exit(-1);
	}
	if (!(filename = ft_strsub(argv, 0, ft_strlen(argv) - 2)))
	{
		perror("get_filename");
		exit(-1);
	}
	return (filename);
}

char	*make_header_string(t_header *header)
{
	int		i;
	char	*size;
	char	*magic;
	char	*result;
	size_t	len;

	i = 0;
	if ((result = ft_strnew(HEX_HEADER)))
	{
		ft_memset((void *)result, '0', HEX_HEADER);
		magic = convert_int_to_hex(COREWAR_EXEC_MAGIC);
		ft_strncpy(&(result[i]), magic, BYTE);
		ft_strdel(&magic);
		i += BYTE;
		len = ft_strlen(header->hex_name);
		ft_strncpy(&(result[i]), header->hex_name, len);
		i += len + BYTE;
		size = convert_int_to_hex(header->size);
		ft_strncpy(&(result[i]), size, BYTE);
		ft_strdel(&size);
		i += BYTE;
		ft_strncpy(&(result[i]), header->hex_description,
				ft_strlen(header->hex_description));
	}
	return (result);
}

void	output_to_file(t_asm *champ)
{
	int		file_fd;
	char	*champion;
	char	*head_str;
	char	*filename;

	filename = ft_strjoin(champ->filename, ".cor");
	file_fd = open(filename, O_TRUNC | O_CREAT | O_WRONLY | O_APPEND, 0744);
	head_str = make_header_string(&(champ->header));
	champion = ft_strjoin(head_str, champ->champion);
	format_file_output(file_fd, champion);
	ft_printf("Writing output program to %s\n", filename);
	ft_strdel(&head_str);
	ft_strdel(&champion);
	ft_strdel(&filename);
	close(file_fd);
}

void	format_file_output(int fd, char *champ)
{
	unsigned int	i;
	size_t			len;
	char			*hex;

	i = 0;
	hex = ft_strnew(2);
	len = ft_strlen(champ);
	while (i < len)
	{
		hex[0] = champ[i++];
		hex[1] = champ[i++];
		ft_putchar_fd_wo_check(ft_atoi_base(hex, 16), fd);
		if (i == len)
			break ;
	}
	free(hex);
}
