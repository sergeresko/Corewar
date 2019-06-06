/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 20:50:03 by vlvereta          #+#    #+#             */
/*   Updated: 2019/06/03 19:31:28 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		main(int argc, char *argv[])
{
	int		fd;

	if (argc == 2 || argc == 3)
	{
		if ((fd = open(argv[argc - 1], O_RDONLY)) < 0)
			e__open_file(argv[argc - 1]);
		if (argc == 3 && ft_strequ(argv[1], "-a"))
			g_dump_mode = TRUE;
		if (argc == 3 && ft_strequ(argv[1], "-d"))
			disassemble_processing(fd, argv[argc - 1]);
		else
			file_processing(fd, argv[argc - 1]);
		close(fd);
	}
	else
		e__args_amount();
	return (0);
}

void	file_processing(int fd, const char *argv)
{
	t_asm *asm_struct;

	if (!asm_init(&asm_struct, argv))
		e__asm_initialization();
	read_file(fd, asm_struct);
	if (!g_dump_mode)
	{
		cook_champion(asm_struct);
		output_to_file(asm_struct);
	}
	else
		dump_output(asm_struct);
	clean_asm_struct(&asm_struct);
}

void	read_file(int fd, t_asm *asm_struct)
{
	int		r;
	char	*line;
	char	*tline;

	asm_struct->data.fd = fd;
	while ((r = get_next_line(fd, &line)))
	{
		if (r == -1)
			e__read_file(asm_struct, 6);
		if (r == 5)
			return (e__read_file(asm_struct, 5));
		if (!(tline = get_trimmed_line(&line, asm_struct)))
			e__trim_line(line);
		ft_strdel(&line);
		if (tline && !tline[0])
			ft_strdel(&tline);
		else
			read_line_1(&tline, asm_struct);
	}
}

void	read_line_1(char **tline, t_asm *asm_struct)
{
	size_t	i;

	i = 0;
	while ((*tline)[i])
	{
		if ((*tline)[i] == COMMENT_CHAR || (*tline)[i] == ALT_COMMENT_CHAR)
			break ;
		else if ((*tline)[i] == '.')
			i = read_dot_instr(tline, i, asm_struct);
		else if ((*tline)[i] == DIRECT_CHAR)
			i = read_dir(tline, i, asm_struct->command);
		else if ((*tline)[i] == LABEL_CHAR || ft_isdigit((*tline)[i])
			|| (*tline)[i] == '-')
			i = read_indir(tline, i, asm_struct->command, asm_struct);
		else if ((*tline)[i] == 'r' && is_register(*tline, i))
			i = read_register(tline, i, asm_struct->command);
		else if (ft_strchr(LABEL_CHARS, (*tline)[i]))
			i = read_string(tline, i, asm_struct);
		else
			i = read_line_2(tline, i);
	}
	if (asm_struct->command)
		check_command_line(asm_struct);
	ft_strdel(tline);
}

size_t	read_line_2(char **tline, size_t i)
{
	if ((*tline)[i] == ' ' || (*tline)[i] == '\t')
		return (++i);
	else
	{
		ft_printf("Lexical error\n");
		exit(-1);
	}
}
