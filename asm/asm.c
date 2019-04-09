/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozalisky <ozalisky@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 20:50:03 by vlvereta          #+#    #+#             */
/*   Updated: 2019/02/10 15:41:18 by ozalisky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
 * Test output function. Delete on production!
 */
void	test_output(t_asm *asm_struct)
{
	if (!asm_struct) return;
	ft_printf("----> TEST OUTPUT!\n");

//	if (asm_struct->header.name[0])
//		ft_printf("Name: %s\n", asm_struct->header.name);
//	if (asm_struct->header.description[0])
//		ft_printf("Description: %s\n", asm_struct->header.description);

	t_label *l_temp = asm_struct->labels;
	while (l_temp)
	{
		ft_printf("%s ", l_temp->name);
		l_temp = l_temp->next;
	}
	ft_printf("\n");
	t_com *c_temp = asm_struct->commands;
	while (c_temp)
	{
		ft_printf("%#x ", c_temp->code);
		c_temp = c_temp->next;
	}
	ft_printf("\n");
	ft_printf("<-----------------\n");
}

int 	main(int argc, char *argv[])
{
	int		fd;

	if (argc == 2 || argc == 3)
	{
		if ((fd = open(argv[argc - 1], O_RDONLY)) < 0)
			e__open_file(argv[argc - 1]);
		if (argc == 3 && ft_strequ(argv[1], "-a"))
			ft_putendl(STDOUT);
		else
			file_processing(fd, argv[argc - 1]);
		close(fd);
	}
	else
		e__no_args();

	system("leaks asm");
	return (0);
}

/*
 * General function for all file reading/creating actions.
 */
void	 file_processing(int fd, const char *argv)
{
	t_asm *asm_struct;
	if (!asm_init(&asm_struct, argv))
		return ;
	/*
	 * Test data!
	 */
	make_hex_name(asm_struct->header.name, "Test");
	make_hex_description(asm_struct->header.description, "Test");
	/*                           */


	read_file(fd, asm_struct);

	test_output(asm_struct);
	output_to_file(asm_struct);
	clean_asm_struct(&asm_struct);
}

void	read_file(int fd, t_asm *asm_struct)
{
	int 	r;
	char	*line;
	char	*tline;

	while ((r = get_next_line(fd, &line)))
	{
		if (r == -1)
		{
			perror(READ_FILE_ERROR);
			exit(-1);
		}
		if (!(tline = get_trimmed_line(&line, asm_struct)))
		{
			perror(TRIM_LINE_ERROR);
			exit(-1);
		}
		ft_strdel(&line);
		if (!tline[0])
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
			i = read_dot_instruction(tline, i, asm_struct);
		else if ((*tline)[i] == DIRECT_CHAR)
			i = read_direct(tline, i, asm_struct);
		else if ((*tline)[i] == LABEL_CHAR)
			i = read_indirect(tline, i, asm_struct);
		else if ((*tline)[i] == 'r' && check_register(*tline, i))
			i = read_register(tline, i, asm_struct);
		else if (ft_strchr(LABEL_CHARS, (*tline)[i]))
			i = read_string(tline, i, asm_struct);
		else
			i = read_line_2(tline, i, asm_struct);
	}
	if (asm_struct->command)
		check_command_line(asm_struct);
	ft_strdel(tline);
}

size_t	read_line_2(char **tline, size_t i, t_asm *asm_struct)
{
	if ((*tline)[i] == ' ' || (*tline)[i] == '\t')
		return ++i;
	else
	{
		ft_printf("Lexical error -> exit(-1)\n");
		return (ft_strlen(*tline));
	}
}

size_t	read_dot_instruction(char **tline, size_t i, t_asm *asm_struct)
{
	if (get_substr_index(*tline, NAME_CMD_STRING) == i)
	{
		ft_printf("%s\n", &((*tline)[i]));
	}
	else if (get_substr_index(*tline, COMMENT_CMD_STRING) == i)
	{
		ft_printf("%s\n", &((*tline)[i]));
	}
	else
		ft_printf("Lexical error -> exit(-1)\n");
	return ft_strlen(*tline);
}

size_t	read_register(char **tline, size_t i, t_asm *asm_struct)
{
	ft_printf("%s\n", &((*tline)[i]));
	return ft_strlen(*tline);
}

size_t	read_direct(char **tline, size_t i, t_asm *asm_struct)
{
	ft_printf("%s\n", &((*tline)[i]));
	return ft_strlen(*tline);
}

size_t	read_indirect(char **tline, size_t i, t_asm *asm_struct)
{
	ft_printf("%s\n", &((*tline)[i]));
	return ft_strlen(*tline);
}

size_t	read_string(char **tline, size_t i, t_asm *asm_struct)
{
	size_t	j;

	if ((j = check_label(*tline, i, TRUE)))
	{
		read_label(*tline, i, j, asm_struct);
		return (++j);
	}
	j = i;
	while (includes(LABEL_CHARS, (*tline)[j]))
		j++;
	read_command(*tline, i, j, asm_struct);
	return (j);
}
