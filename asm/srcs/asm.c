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

void	file_processing(int fd, const char *name)
{
	int			r;
	char		*line;
	t_label		*labels;
	t_header	*header;

	if (!head_init(&header, &labels))
		return ;
	while ((r = get_next_line(fd, &line))) {
		if (r == -1)
		{
			e__read_file(fd);
			clean_and_exit((void **)&header);
		}
		if (!check_comment(&line))
			continue;
		if (*line)
			ft_printf("%s\n", line);
//			line_processing(line, &header, &labels);
		ft_strdel(&line);
	}

	ft_memdel((void **)&header);
}

int		head_init(t_header **header, t_label **labels)
{
	*header = NULL;
	*labels = NULL;

	*header = ft_memalloc(sizeof(t_header));
	if (*header == NULL)
	{
		perror(ALLOCATION_ERROR);
		return (0);
	}
	return (1);
}