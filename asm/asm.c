/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozalisky <ozalisky@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 20:50:03 by vlvereta          #+#    #+#             */
/*   Updated: 2019/01/27 16:46:52 by ozalisky         ###   ########.fr       */
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

int		get_name(char *tline, t_asm *asm_struct)
{
	size_t	i;
	size_t	newStrLngth; //length of malloced str
	char	*tempVar;

	i = 0;
	newStrLngth = 0;
	tline = ft_strtrim(tline);
	if (tline[i] == '"')
	{
		++i;
		while (i < ft_strlen(tline) && tline[i] != '"')
			++i && ++newStrLngth;
		tempVar = ft_memalloc(sizeof(char) * (newStrLngth + 1));
		i = i - newStrLngth;
		newStrLngth = 0;
		while (i < ft_strlen(tline) && tline[i] != '"')
			tempVar[newStrLngth++] = tline[i++];
		if (i == ft_strlen(tline) - 1)
			return (tempVar);
	}
	return (NULL);
}

/*
 * Function to get champ's name or description or create new label's node.
 */
int		check_line(char **line, t_asm *asm_struct)
{
	if (ft_strnstr(*line, ".name",5))
	{
		asm_struct->header.name[0] = get_name(*line + 5, asm_struct); //add function to save name & description to structure
	}
	else if (!ft_strncmp(*line, ".comment", 8))
	{
		asm_struct->header.description[0] = get_name(*line + 8, asm_struct);
	}
	ft_printf("%s\n", line);
	ft_strdel(line);
}