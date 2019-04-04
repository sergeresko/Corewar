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
 * Test output function. Delete on production!
 */
void	test_output(t_asm *asm_struct)
{
	if (!asm_struct) return;
	ft_printf("----> TEST OUTPUT!\n");

	if (asm_struct->header.name[0])
		ft_printf("Name: %s\n", asm_struct->header.name);
	if (asm_struct->header.description[0])
		ft_printf("Description: %s\n", asm_struct->header.description);

	t_label *l_temp = asm_struct->labels;
	while (l_temp)
	{
		ft_printf("%s ", l_temp->name);
		l_temp = l_temp->next;
	}
	ft_printf("\n");
//	t_com *c_temp = asm_struct->commands;
//	while (c_temp)
//	{
//		ft_printf("%#x ", c_temp->code);
//		c_temp = c_temp->next;
//	}
//	ft_printf("\n");
//	ft_printf("<-----------------\n");
}

/*
 * General function for all file reading/creating actions.
 */
void	 file_processing(int fd, const char *argv)
{
	t_asm *asm_struct;

	if (!asm_init(&asm_struct, argv))
		return ;
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
			read_line(&tline, asm_struct);
	}
}

void	read_line(char **tline, t_asm *asm_struct)
{
	size_t			i;

	i = 0;
	while ((*tline)[i])
	{
		if ((*tline)[i] == COMMENT_CHAR || (*tline)[i] == ALT_COMMENT_CHAR)
			break ;
		else if ((*tline)[i] == '.')
			i = read_dot_instruction(tline, i, asm_struct);
		else if ((*tline)[i] == '%')
			i = read_direct(tline, i, asm_struct);
		else if ((*tline)[i] == ':')
			i = read_indirect(tline, i, asm_struct);
		else if (ft_strchr(LABEL_CHARS, (*tline)[i]))
			i = read_string(tline, i, asm_struct);
		else if ((*tline)[i] == ' ' || (*tline)[i] == '\t')
			i++;
		else
		{
			ft_printf("Lexical error -> exit(-1)\n");
			break ;
		}
	}
	ft_strdel(tline);
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

size_t read_direct(char **tline, size_t i, t_asm *asm_struct)
{
	ft_printf("%s\n", *tline);
	return ft_strlen(*tline);
}

size_t read_indirect(char **tline, size_t i, t_asm *asm_struct)
{
	ft_printf("%s\n", *tline);
	return ft_strlen(*tline);
}

size_t read_string(char **tline, size_t i, t_asm *asm_struct)
{
	ft_printf("%s\n", *tline);
	return ft_strlen(*tline);
}


/*
 * General function for first file reading and create labels' list as well.
 */
//int 	read_file(int fd, t_asm *asm_struct)
//{
//	int		r;
//	char	*line;
//	char	*tline;
//
//	while ((r = get_next_line(fd, &line)))
//	{
//		if (r == -1 || !(tline = get_trimmed_line(&line, asm_struct)))
//		{
//			perror(READ_FILE_ERROR);
//			return (0);
//		}
//		if (is_skipable(&tline, asm_struct))
//			continue ;
//		else if (asm_struct->data.errorCase == 1)
//		{
//			--asm_struct->data.line;
//			asm_struct->data.skippedLine ? asm_struct->data.row = 0 : 1;
////			TODO when multiple lines & last empty line got spaces
//			e__read_file(asm_struct, 1);
//		}
//		if (!check_line(&tline, asm_struct))
//			return (0);
//		ft_strdel(&tline);
//	}
//	return (1);
//}

/*
 * Function to get champ's name or description or create new label's node.
 * Read flow must be like in printf project with recursion!!!!!!!!!!!!11111
 */
//int		check_line(char **line, t_asm *asm_struct)
//{
//	char	*label_name;
//	t_label	*new_label;
//
//	if (!asm_struct->header.name[0] && !get_substr_index(*line, NAME_CMD_STRING))
//	{
//		get_champs_name(*line + 5, asm_struct);
//		return (1);
//	}
//	else if (!asm_struct->header.description[0] && !get_substr_index(*line, COMMENT_CMD_STRING))
//	{
//		get_champs_description(*line + 8, asm_struct);
//		return (1);
//	}
//	if ((label_name = get_label_name(line)))
//		if ((new_label = new_label_node(label_name)))
//			push_label_front(&(asm_struct->labels), new_label);
//	return check_for_command(line, asm_struct, 0);
//}

//int 	check_for_command(char **line, t_asm *asm_struct, int start)
//{
//	char	*tline;
//	t_com	*new_command;
//	char	*command_name;
//
//	tline = get_trimmed_line(line, asm_struct);
//	if ((command_name = get_command_name(&tline)))
//	{
//		if ((new_command = check_command(command_name)))
//			push_command_front(&(asm_struct->commands), new_command);
//		ft_strdel(&command_name);
//		ft_strdel(line);
//		ft_strdel(&tline);
//	}
//	return (1);
//}

