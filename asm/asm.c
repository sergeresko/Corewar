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
	if (!get_labels(fd, asm_struct))
	{
		clean_asm_struct(&asm_struct);
		return ;
	}

	asm_struct->header.size = 320;
	make_program_name(asm_struct->header.name, "Jumper !");
	make_program_description(asm_struct->header.desctiption, "en fait C forker !");
	output_to_file(asm_struct);
	clean_asm_struct(&asm_struct);
}

/*
 * General function for first file reading and create labels' list as well.
 */
int		get_labels(int fd, t_asm *asm_struct)
{
	int		r;
	char	*line;
	char	*tline;		// trimmed line

	while ((r = get_next_line(fd, &line)))
	{
		if (r == -1)
		{
			perror(READ_FILE_ERROR);
			return (0);
		}
		if (!check_comment(&line))
			continue ;
		if (*line && (tline = ft_strtrim(line)))
		{
			if (!(*tline))
				ft_strdel(&tline);
			else if (!check_line(tline, asm_struct))
			{
				ft_strdel(&line);
				return (0);
			}
		}
		ft_strdel(&line);
	}
	return (1);
}

/*
 * Function to get champ's name or description or create new label's node.
 */
int		check_line(char *tline, t_asm *asm_struct)
{
	ft_printf("%s\n", tline);
	ft_strdel(&tline);
	return (1);
}