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

	// delete
	asm_struct->header.size = 320;
	make_hex_name(asm_struct->header.name, "Jumper !");
	make_hex_description(asm_struct->header.description, "en fait C forker !");


	output_to_file(asm_struct);
	clean_asm_struct(&asm_struct);
}

/*
 * General function for first file reading and create labels' list as well.
 */
int 	read_file(int fd, t_asm *asm_struct)
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
		if (is_skipable(&tline, asm_struct))
			continue ;
		else if (asm_struct->data.errorCase == 1)
		{
			--asm_struct->data.line;
			asm_struct->data.skippedLine ? asm_struct->data.row = 0 : 1;
//			TODO when multiple lines & last empty line got spaces
			e__read_file(asm_struct, 1);
		}
		if (!check_line(&tline, asm_struct))
			return (0);
		ft_strdel(&tline);
	}
	return (1);
}

void	get_champ_headers(char *tline, char *field, t_asm *asm_struct)
{
	size_t	i;
	size_t	newStrLngth; //length of malloced str

	i = 0;
	newStrLngth = 0;
	while (tline[i] == ' ')
		++i;
	if (tline[i] == '"')
	{
		++i;
		while (i < ft_strlen(tline) && tline[i] != '"')
			++i && ++newStrLngth;
		i = i - newStrLngth;
		newStrLngth = 0;
		while (i < ft_strlen(tline) && tline[i] != '"')
			field[newStrLngth++] = tline[i++];
	}
	else if (tline[i] == '\0'){
		asm_struct->data.errorCase = 1;
//		e__read_file(asm_struct, "ENDLINE");
	}
}

/*
 * Function to get champ's name or description or create new label's node.
 */
int		check_line(char **line, t_asm *asm_struct)
{
	int 	i;
	int		len;

	if (!asm_struct->header.name[0] && !get_substr_index(*line, ".name"))
		get_champ_headers(*line + 5, asm_struct->header.name, asm_struct);
	else if (!asm_struct->header.description[0] && !get_substr_index(*line, ".comment"))
		get_champ_headers(*line + 8, asm_struct->header.description, asm_struct);
	i = 0;
	len = ft_strlen(*line);
	while (ft_strchr(LABEL_CHARS, (*line)[i++]))
	{
		if ((*line)[i] == LABEL_CHAR)
		{
			if (new_label(&(asm_struct->labels), ft_strsub(*line, 0, i), i))
				return check_for_command(line, asm_struct, ++i);
			else
				perror(ALLOCATION_ERROR);
			ft_strdel(line);
			return (0);
		}
	}
	return check_for_command(line, asm_struct, 0);
}

int 	check_for_command(char **line, t_asm *asm_struct, int start)
{
	ft_strdel(line);
	return (1);
}