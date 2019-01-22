/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 20:50:03 by vlvereta          #+#    #+#             */
/*   Updated: 2018/09/30 20:50:32 by vlvereta         ###   ########.fr       */
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
		if (r == -1 || !(tline = get_trimmed_line(&line)))
		{
			perror(READ_FILE_ERROR);
			return (0);
		}
		if (is_skipable(&tline))
			continue ;
		if (!check_line(&tline, asm_struct))
			return (0);
		ft_strdel(&tline);
	}
	return (1);
}

/*
 * Function to get champ's name or description or create new label's node.
 */
int		check_line(char **line, t_asm *asm_struct)
{
	int 	i;
	int		len;

	if (!asm_struct->header.name[0] && !get_substr_index(*line, ".name")) {}
//		return get_champ_name(line, asm_struct);
	else if (!asm_struct->header.description[0] && !get_substr_index(*line, ".comment")) {}
//		return get_champ_comment(line, asm_struct);
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