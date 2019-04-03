/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozalisky <ozalisky@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 20:50:03 by vlvereta          #+#    #+#             */
/*   Updated: 2019/03/16 15:35:51 by ozalisky         ###   ########.fr       */
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
 * General function for all file reading/creating actions.
 */
void	 file_processing(int fd, const char *argv)
{
	t_asm *asm_struct;

	if (!asm_init(&asm_struct, argv))
		return ;
	if (!read_file(fd, asm_struct))
	{
		clean_asm_struct(&asm_struct);
		return ;
	}

	ft_printf("---> Here some results!\n");

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
	output_to_file(asm_struct);
	clean_asm_struct(&asm_struct);
}

/*
 * function to process error codes
 */
int		error_handling(t_asm *asm_struct)
{
	--asm_struct->data.line;
	asm_struct->data.skippedLine ? asm_struct->data.row = 0 : 1;
//TODO when multiple lines & last empty line got spaces
//TODO wrong line number when e-code is 2
	return e__read_file(asm_struct, 1);
}


/*
 * General function for first file reading and create labels' list as well.
 */
int		read_file(int fd, t_asm *asm_struct)
{
	int		r;
	char	*line;
	char	*tline;

	while ((r = get_next_line(fd, &line)))
	{
		if (r == -1 || !(tline = get_trimmed_line(&line, asm_struct)))
		{
			perror(READ_FILE_ERROR);
			return (0);
		}
		if (r == -2)
		{
			return e__read_file(asm_struct, 5);
		}
		if (is_skipable(&tline, asm_struct))
			continue ;
		if (asm_struct->data.errorCase > 0)
			return error_handling(asm_struct);
		if (!check_line(&tline, asm_struct))
			return (0);
		ft_strdel(&tline);
	}
	return (1);
}

/*
 * Function to get champ's name or description or create new label's node.
 * Read flow must be like in printf project with recursion!!!!!!!!!!!!11111
 */
int		check_line(char **line, t_asm *asm_struct)
{
	char	*label_name;
	t_label	*new_label;

	if (!asm_struct->header.name[0] && !get_substr_index(*line, NAME_CMD_STRING))
	{
		get_champs_name(*line + 5, asm_struct);
		return (1);
	}
	else if (!asm_struct->header.description[0] && !get_substr_index(*line, COMMENT_CMD_STRING))
	{
		get_champs_description(*line + 8, asm_struct);
		return (1);
	}
	else if (get_substr_index(*line, ".") >= 0)
		return e__read_file(asm_struct, 2);
	if ((label_name = get_label_name(line)))
		if ((new_label = new_label_node(label_name)))
			push_label_front(&(asm_struct->labels), new_label);
	return check_for_command(line, asm_struct, 0);
}

int 	check_for_command(char **line, t_asm *asm_struct, int start)
{
	char	*tline;
	t_com	*new_command;
	char	*command_name;

	tline = get_trimmed_line(line, asm_struct);
	if ((command_name = get_command_name(&tline)))
	{
		if ((new_command = check_command(command_name)))
			push_command_front(&(asm_struct->commands), new_command);
		ft_strdel(&command_name);
		ft_strdel(line);
		ft_strdel(&tline);
	}
	return (1);
}