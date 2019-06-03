/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_champ_header.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syeresko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 18:41:10 by syeresko          #+#    #+#             */
/*   Updated: 2019/05/28 18:09:02 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

#define HEADER_SIZE			2192

#define POSITION_NAME		4
#define POSITION_NULL_1		132
#define POSITION_SIZE		136
#define POSITION_COMMENT	140
#define POSITION_NULL_2		2188

static void		check_null(char const *header, int place, t_champ const *champ)
{
	if (parse_int(header + place) != 0)
	{
		ft_printf("ERROR: No null at position %d in \"%s\".\n",
				place, champ->filename);
		exit(-1);
	}
}

static void		save_champ_name(char const *header, t_champ *champ)
{
	if (header[4] == '\0')
	{
		ft_printf("ERROR: No champion name in \"%s\".\n", champ->filename);
		exit(-1);
	}
	if ((champ->name = ft_strdup(header + POSITION_NAME)) == NULL)
	{
		perror_exit("save_champ_name");
	}
}

static void		save_champ_size(char const *header, t_champ *champ)
{
	if ((champ->size = parse_int(header + POSITION_SIZE)) > CHAMP_MAX_SIZE)
	{
		ft_printf("ERROR: Size field in \"%s\" too large.\n", champ->filename);
		exit(-1);
	}
}

static void		save_champ_comment(char const *header, t_champ *champ)
{
	if ((champ->comment = ft_strdup(header + POSITION_COMMENT)) == NULL)
	{
		perror_exit("save_champ_comment");
	}
}

/*
**	read and validate the header;
**	parse it into `name`, `size` and `comment` fields of `champ`
*/

void			read_champ_header(int fd, t_champ *champ)
{
	char		header[HEADER_SIZE];
	int			header_size;

	if ((header_size = read(fd, header, HEADER_SIZE)) == -1)
	{
		perror_exit("read_champ_header");
	}
	if (header_size != HEADER_SIZE)
	{
		ft_printf("ERROR: Incomplete header in \"%s\".\n", champ->filename);
		exit(-1);
	}
	if (parse_int(header) != COREWAR_EXEC_MAGIC)
	{
		ft_printf("ERROR: No magic in \"%s\".\n", champ->filename);
		exit(-1);
	}
	check_null(header, POSITION_NULL_1, champ);
	check_null(header, POSITION_NULL_2, champ);
	save_champ_name(header, champ);
	save_champ_size(header, champ);
	save_champ_comment(header, champ);
}
