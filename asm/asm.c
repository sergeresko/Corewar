/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozalisky <ozalisky@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 20:50:03 by vlvereta          #+#    #+#             */
/*   Updated: 2018/11/11 19:46:59 by ozalisky         ###   ########.fr       */
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

int		isSpaceTab(char c)
{
	if (c == 32 || c == 9)
		return (1);
	return (0);
}

int		get_name(char *tline, t_asm *asm_struct)
{
	size_t i;
	size_t line_len;

	i = 5;
	line_len = ft_strlen(tline);
	while (isSpaceTab(tline[i]) && i < line_len)
		++i;
	while (i < line_len)
	{
		if (tline[i] == '"')
		{
//			copy_name_struct
		}
	}
}

/*
 * Function to get champ's name or description or create new label's node.
 */
int		check_line(char *tline, t_asm *asm_struct)
{
//	if (!ft_strncmp(tline, ".name", 5)) //find if  line contains '.name'
	if (ft_strstr(tline, ".name"))
	{

		get_name(tline, asm_struct);
	}
	else if (!ft_strncmp(tline, ".comment", 5))
	{

	}
	else
	ft_printf("%s\n", tline);
	ft_strdel(&tline);
}