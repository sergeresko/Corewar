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
	ft_printf("TEST OUTPUT!\n");
	ft_printf("- - - - - - - - - - - - -\n");

//	if (asm_struct->header.name[0])
//		ft_printf("Name: %s\n", asm_struct->header.name);
//	if (asm_struct->header.description[0])
//		ft_printf("Description: %s\n", asm_struct->header.description);

	// Labels output
	t_label *l_temp = asm_struct->labels;
	ft_printf("Labels list: ");
	while (l_temp)
	{
		ft_printf("%s - %d", l_temp->name, l_temp->index);

		l_temp = l_temp->next;
		if (l_temp)
			ft_printf(", ");
		else
			ft_printf("\n");
	}
	ft_printf("- - - - - - - - - - - - -\n");

	// Commands output
	t_com *c_temp = asm_struct->commands;
	while (c_temp)
	{
		ft_printf("Command: %s -> ", c_temp->name);
		ft_printf("[\n");
		for (int i = 0; i < 3; i++)
		{
			ft_printf("  Arg_%d: \n", i);
			ft_printf("    type: %d, label: %s, itself: %d;\n", c_temp->arg_types[i], c_temp->arg_labels[i], c_temp->arguments[i]);
		}
		if (c_temp->is_codage)
		{
			char *temp = byte_in_bits(c_temp->codage);
			ft_printf("  Codage: %s\n", temp);
			ft_strdel(&temp);
		}
		ft_printf("]\n");
		c_temp = c_temp->next;
	}
	ft_printf("- - - - - - - - - - - - -\n");
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
			i = read_direct(tline, i, asm_struct->command);
		else if ((*tline)[i] == LABEL_CHAR || ft_isdigit((*tline)[i]) || (*tline)[i] == '-')
			i = read_indirect(tline, i, asm_struct->command);
		else if ((*tline)[i] == 'r' && is_register(*tline, i))
			i = read_register(tline, i, asm_struct->command);
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

size_t	read_register(char **tline, size_t i, t_com *command)
{
	int 	arg;
	int 	checked;
	int		arg_num;

	arg = ft_atoi(&((*tline)[++i]));
	if (g_error_mode || !command)
	{
		ft_printf("Syntax error, register \"r%d\"\n", arg);
		exit(-1);
	}
	if ((arg_num = get_argument_number(command)) == -1)
	{
		ft_printf("Argument number - %d\n", arg_num);
		exit(-1);
	}
	if ((checked = check_argument_1(command->name, arg_num, T_REG)) == -1)
	{
		ft_printf("Syntax error, register \"r%d\"\n", arg);
		exit(-1);
	}
	if (!checked)
	{
		ft_printf("Invalid parameter %d type register for instruction %s\n", arg_num, command->name);
		exit(-1);
	}
	write_argument(command, arg_num, T_REG, arg);
	while (ft_isdigit((*tline)[i]))
		i++;
	return (check_proper_ending(*tline, i));
}

int	read_direct(char **tline, int i, t_com *command)
{
	int 	arg;
	int 	arg_num;
	int 	checked;

	if ((*tline)[++i] == LABEL_CHAR)
		return read_direct_label(tline, i, command);
	arg = ft_atoi(&((*tline)[i]));
	if (g_error_mode || !command)
	{
		ft_printf("Syntax error, direct \"%%%d\"\n", arg);
		exit(-1);
	}
	if ((arg_num = get_argument_number(command)) == -1)
	{
		ft_printf("Argument number - %d\n", arg_num);
		exit(-1);
	}
	if ((checked = check_argument_1(command->name, arg_num, T_DIR)) == -1)
	{
		ft_printf("Syntax error, direct \"%%%d\"\n", arg);
		exit(-1);
	}
	if (!checked)
	{
		ft_printf("Invalid parameter %d type direct for instruction %s\n", arg_num, command->name);
		exit(-1);
	}
	write_argument(command, arg_num, T_DIR, arg);
	i += (*tline)[i] != '-' ? 0 : 1;
	while (ft_isdigit((*tline)[i]))
		i++;
	return (check_proper_ending(*tline, i));
}

int		read_direct_label(char **tline, int i, t_com *command)
{
	int 	j;
	int 	arg_num;
	int 	checked;
	char	*label;

	if ((j = check_label(*tline, ++i, FALSE)))
	{
		label = ft_strsub(*tline, i, j - i);
		if (g_error_mode || !command)
		{
			ft_printf("Syntax error, direct_label \"%%:%s\"\n", label);
			exit(-1);
		}
		if ((arg_num = get_argument_number(command)) == -1)
		{
			ft_printf("Argument number - %d\n", arg_num);
			exit(-1);
		}
		if ((checked = check_argument_1(command->name, arg_num, T_DIR)) == -1)
		{
			ft_printf("Syntax error, direct \"%%:%s\"\n", label);
			exit(-1);
		}
		if (!checked)
		{
			ft_printf("Invalid parameter %d type direct for instruction %s\n", arg_num, command->name);
			exit(-1);
		}
		write_label_argument(command, arg_num, T_DIR, &label);
		return (check_proper_ending(*tline, j));
	}
	return (i);
}

int		read_indirect(char **tline, int i, t_com *command)
{
	int 	arg;
	int 	arg_num;
	int 	checked;

	if ((*tline)[i] == LABEL_CHAR)
		return read_indirect_label(tline, i, command);
	arg = ft_atoi(&((*tline)[i]));
	if (g_error_mode || !command)
	{
		ft_printf("Syntax error, indirect \"%d\"\n", arg);
		exit(-1);
	}
	if ((arg_num = get_argument_number(command)) == -1)
	{
		ft_printf("Argument number - %d\n", arg_num);
		exit(-1);
	}
	if ((checked = check_argument_1(command->name, arg_num, T_IND)) == -1)
	{
		ft_printf("Syntax error, indirect \"%d\"\n", arg);
		exit(-1);
	}
	if (!checked)
	{
		ft_printf("Invalid parameter %d type indirect for instruction %s\n", arg_num, command->name);
		exit(-1);
	}
	write_argument(command, arg_num, T_IND, arg);
	i += (*tline)[i] != '-' ? 0 : 1;
	while (ft_isdigit((*tline)[i]))
		i++;
	return (check_proper_ending(*tline, i));
}

int		read_indirect_label(char **tline, int i, t_com *command)
{
	int 	j;
	int 	arg_num;
	int 	checked;
	char	*label;

	if ((j = check_label(*tline, ++i, FALSE)))
	{
		label = ft_strsub(*tline, i, j - i);
		if (g_error_mode || !command)
		{
			ft_printf("Syntax error, indirect_label \"%%:%s\"\n", label);
			exit(-1);
		}
		if ((arg_num = get_argument_number(command)) == -1)
		{
			ft_printf("Argument number - %d\n", arg_num);
			exit(-1);
		}
		if ((checked = check_argument_1(command->name, arg_num, T_IND)) == -1)
		{
			ft_printf("Syntax error, indirect \"%%:%s\"\n", label);
			exit(-1);
		}
		if (!checked)
		{
			ft_printf("Invalid parameter %d type indirect for instruction %s\n", arg_num, command->name);
			exit(-1);
		}
		write_label_argument(command, arg_num, T_IND, &label);
		return (check_proper_ending(*tline, j));
	}
	return (i);
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
